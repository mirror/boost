/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007-2008 Anthony Williams
 * (C) Copyright 2012-2013 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   detail/mutexes/mutex_windows.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html.
 */

#ifndef BOOST_SYNC_DETAIL_MUTEXES_MUTEX_WINDOWS_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_MUTEXES_MUTEX_WINDOWS_HPP_INCLUDED_

#include <cstddef>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/detail/win/handles.hpp>
#include <boost/detail/win/synchronization.hpp>
#include <boost/sync/exceptions/lock_error.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/interlocked.hpp>

#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class mutex
{
private:
    enum
    {
        lock_flag_bit = 31u,
        event_set_flag_bit = 30u,
        lock_flag_value = 1u << lock_flag_bit,
        event_set_flag_value = 1u << event_set_flag_bit
    };

private:
    long m_active_count;
    boost::detail::win32::HANDLE_ m_event;

public:
    BOOST_CONSTEXPR mutex() BOOST_NOEXCEPT : m_event(NULL), m_active_count(0)
    {
    }

    ~mutex()
    {
        if (m_event)
            BOOST_VERIFY(boost::detail::win32::CloseHandle(m_event) != 0);
    }

    void lock()
    {
        if (try_lock())
            return;

        long old_count = m_active_count;
        mark_waiting_and_try_lock(old_count);

        if (old_count & lock_flag_value)
        {
            bool lock_acquired = false;
            boost::detail::win32::HANDLE_ const sem = get_event();

            do
            {
                const boost::detail::win32::DWORD_ retval = boost::detail::win32::WaitForSingleObject(sem, boost::detail::win32::infinite);
                BOOST_ASSERT(0 == retval || boost::detail::win32::wait_abandoned == retval);
                clear_waiting_and_try_lock(old_count);
                lock_acquired = (old_count & lock_flag_value) == 0;
            }
            while (!lock_acquired);
        }
    }

    void unlock() BOOST_NOEXCEPT
    {
        long const offset = lock_flag_value;
        long const old_count = BOOST_ATOMIC_INTERLOCKED_EXCHANGE_ADD(&m_active_count, lock_flag_value);
        if ((old_count & event_set_flag_value) == 0 && (old_count > offset))
        {
            if (!sync::detail::windows::interlocked_bit_test_and_set(&m_active_count, event_set_flag_bit))
            {
                boost::detail::win32::SetEvent(get_event());
            }
        }
    }

    bool try_lock() BOOST_NOEXCEPT
    {
        return !sync::detail::windows::interlocked_bit_test_and_set(&m_active_count, lock_flag_bit);
    }

    BOOST_DELETED_FUNCTION(mutex(mutex const&))
    BOOST_DELETED_FUNCTION(mutex& operator= (mutex const&))

private:
    boost::detail::win32::HANDLE_ get_event()
    {
        boost::detail::win32::HANDLE_ event = sync::detail::windows::interlocked_read_acquire(&m_event);

        if (!event)
        {
            event = boost::detail::win32::CreateEventA(NULL, false, false, NULL);
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4311)
#pragma warning(disable:4312)
#endif
            boost::detail::win32::HANDLE_ const old_event = BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE_POINTER(&m_event, event, NULL);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
            if (old_event != NULL)
            {
                boost::detail::win32::CloseHandle(event);
                return old_event;
            }
        }

        return event;
    }

    void mark_waiting_and_try_lock(long& old_count)
    {
        while (true)
        {
            bool const was_locked = (old_count & lock_flag_value) ? true : false;
            long const new_count = was_locked ? (old_count + 1) : (old_count | lock_flag_value);
            long const current = BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&m_active_count, new_count, old_count);
            if (current == old_count)
            {
                if (was_locked)
                    old_count = new_count;
                break;
            }
            old_count = current;
        }
    }

    void clear_waiting_and_try_lock(long& old_count)
    {
        old_count &= ~lock_flag_value;
        old_count |= event_set_flag_value;
        while (true)
        {
            long const new_count = ((old_count & lock_flag_value) ? old_count : ((old_count - 1) | lock_flag_value)) & ~static_cast< long >(event_set_flag_value);
            long const current = BOOST_ATOMIC_INTERLOCKED_COMPARE_EXCHANGE(&m_active_count, new_count, old_count);
            if (current == old_count)
                break;

            old_count = current;
        }
    }
};

} // namespace posix

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_MUTEXES_MUTEX_POSIX_HPP_INCLUDED_
