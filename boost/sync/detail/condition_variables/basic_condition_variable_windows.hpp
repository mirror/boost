/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007-2008 Anthony Williams
 * (C) Copyright 2011-2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   detail/condition_variables/basic_condition_variable_windows.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html.
 */

#ifndef BOOST_SYNC_DETAIL_CONDITION_VARIABLES_BASIC_CONDITION_VARIABLE_WINDOWS_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_CONDITION_VARIABLES_BASIC_CONDITION_VARIABLE_WINDOWS_HPP_INCLUDED_

#include <limits.h>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/smart_ptr/intrusive_ref_counter.hpp>
#include <boost/detail/winapi/synchronization.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/locks/unique_lock_fwd.hpp>
#include <boost/sync/exceptions/runtime_exception.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/detail/time_traits.hpp>
#include <boost/sync/detail/time_units.hpp>
#include <boost/sync/detail/interlocked.hpp>
#include <boost/sync/detail/auto_handle.hpp>
#include <boost/sync/detail/waitable_timer.hpp>
#include <boost/sync/locks/lock_guard.hpp>
#include <boost/sync/mutexes/mutex.hpp>
#include <boost/sync/condition_variables/cv_status.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

namespace detail {

namespace windows {

class cv_list_entry :
    public intrusive_ref_counter< cv_list_entry >
{
private:
    auto_handle m_semaphore;
    auto_handle m_wake_sem;
    long m_waiters;
    bool m_notified;

public:
    explicit cv_list_entry(auto_handle const& wake_sem):
        m_semaphore(boost::detail::winapi::create_anonymous_semaphore(0, LONG_MAX)),
        m_wake_sem(wake_sem.duplicate()),
        m_waiters(1),
        m_notified(false)
    {
        if (!m_semaphore)
            BOOST_THROW_EXCEPTION(resource_error("boost::sync::condition_variable: failed to create a semaphore"));
    }

    static bool no_waiters(intrusive_ptr< cv_list_entry > const& entry)
    {
        return interlocked_read_acquire(&entry->m_waiters) == 0;
    }

    void add_waiter()
    {
        BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&m_waiters, 1);
    }

    void remove_waiter()
    {
        BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&m_waiters, -1);
    }

    void release(unsigned count_to_release)
    {
        m_notified = true;
        boost::detail::winapi::ReleaseSemaphore(m_semaphore, count_to_release, 0);
    }

    void release_waiters()
    {
        release(interlocked_read_acquire(&m_waiters));
    }

    bool is_notified() const
    {
        return m_notified;
    }

    void wait()
    {
        const boost::detail::winapi::DWORD_ res = boost::detail::winapi::WaitForSingleObject(m_semaphore, boost::detail::winapi::infinite);
        if (res != boost::detail::winapi::wait_object_0)
            BOOST_THROW_EXCEPTION(runtime_exception(res, "boost::sync::condition_variable wait failed in WaitForSingleObject"));
    }

    bool timed_wait(system_duration t)
    {
        sync::detail::system_duration::native_type time_left = t.get();
        while (time_left > 0)
        {
            const unsigned int dur = time_left > static_cast< unsigned int >(boost::detail::winapi::max_non_infinite_wait) ?
                static_cast< unsigned int >(boost::detail::winapi::max_non_infinite_wait) : static_cast< unsigned int >(time_left);
            const boost::detail::winapi::DWORD_ res = boost::detail::winapi::WaitForSingleObject(m_semaphore, dur);
            switch (res)
            {
            case boost::detail::winapi::wait_object_0:
                return true;

            case boost::detail::winapi::wait_timeout:
                time_left -= dur;
                break;

            default:
                BOOST_THROW_EXCEPTION(runtime_exception(res, "boost::sync::condition_variable timed_wait failed in WaitForSingleObject"));
            }
        }
        return false;
    }

    bool woken()
    {
        unsigned long const woken_result = boost::detail::winapi::WaitForSingleObject(m_wake_sem, 0);
        BOOST_ASSERT((woken_result == boost::detail::winapi::timeout) || (woken_result == 0));
        return woken_result == 0;
    }

    BOOST_DELETED_FUNCTION(cv_list_entry(cv_list_entry const&))
    BOOST_DELETED_FUNCTION(cv_list_entry& operator= (cv_list_entry const&))
};

class basic_condition_variable
{
private:
    typedef boost::sync::mutex mutex_type;

    typedef boost::intrusive_ptr< cv_list_entry > entry_ptr;
    typedef std::vector< entry_ptr > generation_list;

    template< typename Lockable >
    class relocker
    {
        Lockable& m_lock;
        bool m_unlocked;

    public:
        explicit relocker(Lockable& lock) : m_lock(lock), m_unlocked(false)
        {
        }

        ~relocker() BOOST_NOEXCEPT_IF(false)
        {
            if (m_unlocked)
                m_lock.lock();
        }

        void unlock()
        {
            m_lock.unlock();
            m_unlocked = true;
        }

        BOOST_DELETED_FUNCTION(relocker(relocker const&))
        BOOST_DELETED_FUNCTION(relocker& operator= (relocker const&))
    };

    class entry_manager
    {
        entry_ptr const m_entry;
        mutex_type& m_internal_mutex;

    public:
        entry_manager(entry_ptr const& entry, mutex_type& mutex):
            m_entry(entry), m_internal_mutex(mutex)
        {
        }

        ~entry_manager() BOOST_NOEXCEPT_IF(false)
        {
            boost::sync::lock_guard< mutex_type > internal_lock(m_internal_mutex);
            m_entry->remove_waiter();
        }

        cv_list_entry* operator->() const BOOST_NOEXCEPT
        {
            return m_entry.get();
        }

        BOOST_DELETED_FUNCTION(entry_manager(entry_manager const&))
        BOOST_DELETED_FUNCTION(entry_manager& operator= (entry_manager const&))
    };

private:
    mutex_type m_internal_mutex;
    long m_total_count;

    generation_list m_generations;
    auto_handle m_wake_sem;

public:
    BOOST_CONSTEXPR basic_condition_variable() : m_total_count(0)
    {
    }

    void notify_one() BOOST_NOEXCEPT
    {
        if (interlocked_read_acquire(&m_total_count))
        {
            boost::sync::lock_guard< mutex_type > internal_lock(m_internal_mutex);
            if (m_total_count == 0)
                return;

            wake_waiters(1);

            for(generation_list::iterator it = m_generations.begin(), end = m_generations.end(); it != end; ++it)
            {
                (*it)->release(1);
            }
            m_generations.erase(std::remove_if(m_generations.begin(), m_generations.end(), &cv_list_entry::no_waiters), m_generations.end());
        }
    }

    void notify_all() BOOST_NOEXCEPT
    {
        if (interlocked_read_acquire(&m_total_count))
        {
            boost::sync::lock_guard< mutex_type > internal_lock(m_internal_mutex);
            if (m_total_count == 0)
                return;

            wake_waiters(m_total_count);

            for (generation_list::iterator it = m_generations.begin(), end = m_generations.end(); it != end; ++it)
            {
                (*it)->release_waiters();
            }
            m_generations.clear();
            m_wake_sem.reset();
        }
    }

    BOOST_DELETED_FUNCTION(basic_condition_variable(basic_condition_variable const&))
    BOOST_DELETED_FUNCTION(basic_condition_variable& operator= (basic_condition_variable const&))

protected:
    template< typename Lock >
    bool do_wait(Lock& lock,timeout abs_time)
    {
        relocker< Lock > locker(lock);

        entry_manager entry(get_wait_entry(), m_internal_mutex);

        locker.unlock();

        bool woken = false;
        do
        {
            if (!entry->wait(abs_time))
            {
                return false;
            }

            woken = entry->woken();
        }
        while (!woken);

        return woken;
    }

    template<typename lock_type,typename predicate_type>
    bool do_wait(lock_type& m, timeout const& abs_time, predicate_type pred)
    {
        while (!pred())
        {
            if(!do_wait(m, abs_time))
                return pred();
        }
        return true;
    }

private:
    void wake_waiters(long count_to_wake)
    {
        interlocked_write_release(&m_total_count, m_total_count - count_to_wake);
        boost::detail::winapi::ReleaseSemaphore(m_wake_sem, count_to_wake, 0);
    }

    entry_ptr get_wait_entry()
    {
        boost::sync::lock_guard< mutex_type > internal_lock(m_internal_mutex);

        if(!m_wake_sem)
        {
            m_wake_sem = boost::detail::winapi::create_anonymous_semaphore(0, LONG_MAX);
            BOOST_ASSERT(m_wake_sem);
        }

        interlocked_write_release(&m_total_count, m_total_count + 1);
        if (m_generations.empty() || m_generations.back()->is_notified())
        {
            entry_ptr new_entry(new cv_list_entry(m_wake_sem));
            m_generations.push_back(new_entry);
            return new_entry;
        }
        else
        {
            m_generations.back()->add_waiter();
            return m_generations.back();
        }
    }
};

} // namespace windows

} // namespace detail

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_CONDITION_VARIABLES_BASIC_CONDITION_VARIABLE_WINDOWS_HPP_INCLUDED_
