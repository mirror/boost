// semaphore.hpp, osx/ios dispatch semaphores
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_DISPATCH_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_DISPATCH_HPP_INCLUDED_

#include <cstddef>
#include <dispatch/dispatch.h>

#include <boost/throw_exception.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/system_error.hpp>
#include <boost/sync/exceptions/resource_error.hpp>

#ifdef BOOST_SYNC_USES_CHRONO
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/ceil.hpp>
#endif

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
        m_sem = dispatch_semaphore_create(i);
        if (m_sem == NULL)
            BOOST_THROW_EXCEPTION(resource_error(sync::detail::system_ns::errc::not_enough_memory, "boost::sync::semaphore constructor failed in dispatch_semaphore_create"));
    }

    ~semaphore() BOOST_NOEXCEPT
    {
        dispatch_release(m_sem);
    }

    void post() BOOST_NOEXCEPT
    {
        dispatch_semaphore_signal(m_sem);
    }

    void wait() BOOST_NOEXCEPT
    {
        dispatch_semaphore_wait(m_sem, DISPATCH_TIME_FOREVER);
    }

    bool try_wait(void) BOOST_NOEXCEPT
    {
        const long status = dispatch_semaphore_wait(m_sem, DISPATCH_TIME_NOW);
        return status == 0;
    }

#ifdef BOOST_SYNC_USES_CHRONO
    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & rel_time) BOOST_NOEXCEPT
    {
        return try_wait_until(chrono::steady_clock::now() + rel_time);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout ) BOOST_NOEXCEPT
    {
        using namespace chrono;
        system_clock::time_point    s_now = system_clock::now();
        typename Clock::time_point  c_now = Clock::now();
        return try_wait_until(s_now + ceil<nanoseconds>(timeout - c_now));
    }

    template <class Duration>
    bool try_wait_until(const chrono::time_point<chrono::system_clock, Duration>& t) BOOST_NOEXCEPT
    {
        using namespace chrono;
        typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
        return try_wait_until(nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
    }

    bool try_wait_until(const chrono::time_point<chrono::system_clock, chrono::nanoseconds>& tp) BOOST_NOEXCEPT
    {
        chrono::nanoseconds d = tp.time_since_epoch();
        timespec ts = boost::detail::to_timespec(d);
        return do_wait_lock_until(dispatch_walltime(&ts, 0));
    }

private:
    bool do_wait_lock_until(const dispatch_time_t timeout) BOOST_NOEXCEPT
    {
        const long status = dispatch_semaphore_wait(m_sem, timeout);
        return status == 0;
    }

#endif // BOOST_SYNC_USES_CHRONO

private:
    dispatch_semaphore_t m_sem;
};

} // namespace posix

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_DISPATCH_HPP_INCLUDED_
