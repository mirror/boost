// semaphore.hpp, mach semaphores
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_MACH_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_MACH_HPP_INCLUDED_

#include <cstddef>

#include <boost/throw_exception.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/system_error.hpp>
#include <boost/sync/exceptions/resource_error.hpp>

#ifdef BOOST_SYNC_USES_CHRONO
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/ceil.hpp>
#endif

#include <mach/task.h>
#include <mach/semaphore.h>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>

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
        kern_return_t result = semaphore_create(mach_task_self(), &m_sem, SYNC_POLICY_FIFO, 0);
        if (result != KERN_SUCCESS)
            BOOST_THROW_EXCEPTION(resource_error(sync::detail::system_ns::errc::not_enough_memory, "boost::sync::semaphore constructor failed in semaphore_create"));
    }

    ~semaphore() BOOST_NOEXCEPT
    {
        kern_return_t result = semaphore_destroy(mach_task_self(), m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    void post() BOOST_NOEXCEPT
    {
        kern_return_t result = semaphore_signal(m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    void wait() BOOST_NOEXCEPT
    {
        kern_return_t result = semaphore_wait(m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    bool try_wait(void) BOOST_NOEXCEPT
    {
        const mach_timespec_t mach_wait_time = { 0, 0 };
        return do_try_wait_for( mach_wait_time );
    }

    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & duration) BOOST_NOEXCEPT
    {
        chrono::seconds seconds = chrono::duration_cast<chrono::seconds>(duration);
        chrono::nanoseconds nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration) - seconds;

        const mach_timespec_t mach_wait_time = { static_cast<unsigned int>(seconds.count()), static_cast<clock_res_t>(nanoseconds.count()) };
        return do_try_wait_for(mach_wait_time);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout ) BOOST_NOEXCEPT
    {
        return try_wait_for( timeout - Clock::now() );
    }

private:
    bool do_try_wait_for(const mach_timespec_t & wait_time) BOOST_NOEXCEPT
    {
        kern_return_t result = semaphore_timedwait(m_sem, wait_time);
        if (result == KERN_SUCCESS)
            return true;
        else
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
