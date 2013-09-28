// event.hpp, condition variable emulation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_

#include <boost/sync/semaphore.hpp>

// we use the semaphore implementation if we have native semaphores
#ifndef BOOST_SYNC_SEMAPHORE_EMULATED
#include <boost/sync/detail/event/event_autoreset_semaphore.hpp>
#endif


#include <boost/thread/condition_variable.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

#include <boost/sync/detail/config.hpp>
//#include <boost/sync/locks/lock_guard.hpp>
//#include <boost/sync/locks/unique_lock.hpp>
#include <boost/sync/detail/header.hpp>

#define BOOST_SYNC_EVENT_EMULATED

namespace boost {
namespace sync {
BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {


#ifdef BOOST_SYNC_SEMAPHORE_EMULATED

class auto_reset_event
{
    BOOST_DELETED_FUNCTION(auto_reset_event(auto_reset_event const&));
    BOOST_DELETED_FUNCTION(auto_reset_event& operator=(auto_reset_event const&));

public:
    auto_reset_event() BOOST_NOEXCEPT :
        m_is_set(false)
    {}

    void post()
    {
        unique_lock<upgrade_mutex> lock(m_mutex);
        bool already_signaled = m_is_set;
        m_is_set = true;
        if (!already_signaled)
            m_cond.notify_one();
    }

    void wait()
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set)
            m_cond.wait(lock);

        upgrade_to_unique_lock<upgrade_mutex> unique_lock(lock);
        m_is_set = false;
    }

    void reset()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        m_is_set = false;
    }

    bool try_wait()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        const bool res = m_is_set;
        if (res)
            m_is_set = false;
        return res;
    }

    template <class Duration>
    bool try_wait_for(const Duration & duration)
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set) {
            if (m_cond.wait_for(lock, duration) == cv_status::timeout) {
                if (!m_is_set)
                    return false;
                break;
            }
        }

        upgrade_to_unique_lock<upgrade_mutex> unique_lock(lock);
        m_is_set = false;
        return true;
    }

    template <typename TimePoint>
    bool try_wait_until(const TimePoint & timeout)
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set) {
            if (m_cond.wait_until(lock, timeout) == cv_status::timeout) {
                if (!m_is_set)
                    return false;
                break;
            }
        }

        upgrade_to_unique_lock<upgrade_mutex> unique_lock(lock);
        m_is_set = false;
        return true;
    }

private:
    bool m_is_set;
    upgrade_mutex m_mutex;
    condition_variable_any m_cond;
};

#endif

class manual_reset_event
{
    BOOST_DELETED_FUNCTION(manual_reset_event(manual_reset_event const&));
    BOOST_DELETED_FUNCTION(manual_reset_event& operator=(manual_reset_event const&));

public:
    manual_reset_event() BOOST_NOEXCEPT :
        m_is_set(false)
    {}

    void post()
    {
        unique_lock<upgrade_mutex> lock(m_mutex);
        bool already_signaled = m_is_set;
        m_is_set = true;
        m_cond.notify_all();
    }

    void wait()
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set)
            m_cond.wait(lock);
    }

    void reset()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        m_is_set = false;
    }

    bool try_wait()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        return m_is_set;
    }

    template <typename Duration>
    bool try_wait_for(const Duration & duration)
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set) {
            if (m_cond.wait_for(lock, duration) == cv_status::timeout) {
                if (!m_is_set)
                    return false;
                break;
            }
        }

        return true;
    }

    template <typename TimePoint>
    bool try_wait_until(const TimePoint & timeout)
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set) {
            if (m_cond.wait_until(lock, timeout) == cv_status::timeout) {
                if (!m_is_set)
                    return false;
                break;
            }
        }

        return true;
    }

private:
    bool m_is_set;
    upgrade_mutex m_mutex;
    condition_variable_any m_cond;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_
