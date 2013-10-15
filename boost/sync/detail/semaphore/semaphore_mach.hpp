// semaphore.hpp, mach semaphores
//
// Copyright (C) 2013 Tim Blechmann
// Copyright (C) 2013 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_MACH_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_MACH_HPP_INCLUDED_

#include <mach/task.h>
#include <mach/semaphore.h>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/time_traits.hpp>
#include <boost/sync/detail/time_units.hpp>
#include <boost/sync/detail/throw_exception.hpp>
#include <boost/sync/detail/system_error.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/exceptions/wait_error.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync  {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class semaphore
{
    BOOST_DELETED_FUNCTION(semaphore(semaphore const&))
    BOOST_DELETED_FUNCTION(semaphore& operator=(semaphore const&))

public:
    explicit semaphore(unsigned int i = 0)
    {
        kern_return_t result = semaphore_create(mach_task_self(), &m_sem, SYNC_POLICY_FIFO, i);
        if (result != KERN_SUCCESS)
            BOOST_SYNC_DETAIL_THROW(resource_error, (sync::detail::system_ns::errc::not_enough_memory)("semaphore constructor failed in semaphore_create"));
    }

    ~semaphore()
    {
        kern_return_t result = semaphore_destroy(mach_task_self(), m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    void post()
    {
        kern_return_t result = semaphore_signal(m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    void wait()
    {
        kern_return_t result = semaphore_wait(m_sem);
        if (BOOST_UNLIKELY(result != KERN_SUCCESS))
        {
            switch (result)
            {
            case KERN_INVALID_ARGUMENT:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::invalid_argument)("semaphore::wait failed: the specified semaphore is invalid."));

            case KERN_TERMINATED:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::invalid_argument)("semaphore::wait failed: the specified semaphore has been destroyed"));

            case KERN_ABORTED:
            default:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::operation_canceled)("semaphore::wait failed: the wait operation has been aborted"));
            }
        }
    }

    bool try_wait()
    {
        const mach_timespec_t wait_time = { 0, 0 };
        return priv_timed_wait(wait_time);
    }

    template< typename Time >
    typename enable_if_c< sync::detail::time_traits< Time >::is_specialized, bool >::type timed_wait(Time const& t)
    {
        return priv_timed_wait(sync::detail::time_traits< Time >::to_sync_unit(t));
    }

    template< typename Duration >
    typename enable_if< detail::is_time_tag_of< Duration, detail::time_duration_tag >, bool >::type wait_for(Duration const& duration)
    {
        return priv_timed_wait(sync::detail::time_traits< Duration >::to_sync_unit(duration));
    }

    template< typename TimePoint >
    typename enable_if< detail::is_time_tag_of< TimePoint, detail::time_point_tag >, bool >::type wait_until(TimePoint const& abs_time)
    {
        return priv_timed_wait(sync::detail::time_traits< TimePoint >::to_sync_unit(abs_time));
    }

private:
    bool priv_timed_wait(sync::detail::system_duration dur)
    {
        sync::detail::system_duration::native_type time_left = dur.get();
        if (time_left < 0)
            time_left = 0;
        sync::detail::system_duration::native_type time_left_sec = time_left / system_duration::subsecond_fraction;
        sync::detail::system_duration::native_type time_left_subsec = time_left % system_duration::subsecond_fraction;

        enum
        {
            nanoseconds_fraction = 1000000000u,
            conversion_ratio = static_cast< uint64_t >(nanoseconds_fraction) >= system_duration::subsecond_fraction ?
                nanoseconds_fraction / system_duration::subsecond_fraction :
                system_duration::subsecond_fraction / nanoseconds_fraction
        };

        const mach_timespec_t wait_time =
        {
            time_left_sec,
            static_cast< uint64_t >(nanoseconds_fraction) >= system_duration::subsecond_fraction ?
                time_left_subsec / conversion_ratio : time_left_subsec * conversion_ratio
        };

        return priv_timed_wait(wait_time);
    }

    bool priv_timed_wait(sync::detail::system_time_point const& t)
    {
        return priv_timed_wait(t - sync::detail::system_time_point::now());
    }

    template< typename TimePoint >
    bool priv_timed_wait(sync::detail::chrono_time_point< TimePoint > const& t)
    {
        typedef TimePoint time_point;
        typedef typename time_point::clock clock;
        typedef typename time_point::duration duration;
        time_point now = clock::now();
        while (now < t.get())
        {
            if (priv_timed_wait(sync::detail::time_traits< duration >::to_sync_unit(t.get() - now)))
                return true;
            now = clock::now();
        }
        return false;
    }

    bool priv_timed_wait(const mach_timespec_t& wait_time)
    {
        kern_return_t result = semaphore_timedwait(m_sem, wait_time);

        if (result == KERN_SUCCESS)
            return true;

        if (BOOST_UNLIKELY(result != KERN_OPERATION_TIMED_OUT))
        {
            switch (result)
            {
            case KERN_INVALID_ARGUMENT:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::invalid_argument)("semaphore::try_wait failed: the specified semaphore is invalid."));

            case KERN_TERMINATED:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::invalid_argument)("semaphore::try_wait failed: the specified semaphore has been destroyed"));

            case KERN_ABORTED:
            default:
                BOOST_SYNC_DETAIL_THROW(wait_error, (sync::detail::system_ns::errc::operation_canceled)("semaphore::try_wait failed: the wait operation has been aborted"));
            }
        }

        return false;
    }

private:
    semaphore_t m_sem;
};

} // namespace posix

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_MACH_HPP_INCLUDED_
