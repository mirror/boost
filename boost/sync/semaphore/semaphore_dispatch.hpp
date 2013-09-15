// semaphore.hpp, osx/ios dispatch semaphores
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_SEMAPHORE_SEMAPHORE_DISPATCH_HPP
#define BOOST_SYNC_SEMAPHORE_SEMAPHORE_DISPATCH_HPP

#include <dispatch/dispatch.h>

#include <boost/thread/exceptions.hpp>

#ifdef BOOST_SYNC_USES_CHRONO
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/ceil.hpp>
#endif

namespace boost {
namespace sync  {

class semaphore
{
    BOOST_DELETED_FUNCTION(semaphore(semaphore const&))
    BOOST_DELETED_FUNCTION(semaphore& operator=(semaphore const&))

public:
    semaphore(int i=0)
    {
        BOOST_ASSERT_MSG(i >= 0, "boost::sync::semaphore constructor called with negative count");
        sem = dispatch_semaphore_create(i);
        if (sem == NULL)
            boost::throw_exception(thread_resource_error(system::errc::not_enough_memory, "boost::sync::semaphore constructor failed in dispatch_semaphore_create"));
    }

    ~semaphore()
    {
        dispatch_release(sem);
    }

    void post()
    {
        dispatch_semaphore_signal(sem);
    }

    void wait()
    {
        dispatch_semaphore_wait(sem, DISPATCH_TIME_FOREVER);
    }

    bool try_wait(void)
    {
        const long status = dispatch_semaphore_wait(sem, DISPATCH_TIME_NOW);
        return status == 0;
    }

#ifdef BOOST_SYNC_USES_CHRONO
    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & rel_time)
    {
        return try_wait_until(chrono::steady_clock::now() + rel_time);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout )
    {
        using namespace chrono;
        system_clock::time_point    s_now = system_clock::now();
        typename Clock::time_point  c_now = Clock::now();
        return try_wait_until(s_now + ceil<nanoseconds>(timeout - c_now));
    }

    template <class Duration>
    bool try_wait_until(const chrono::time_point<chrono::system_clock, Duration>& t)
    {
        using namespace chrono;
        typedef time_point<system_clock, nanoseconds> nano_sys_tmpt;
        return try_wait_until(nano_sys_tmpt(ceil<nanoseconds>(t.time_since_epoch())));
    }

    bool try_wait_until(const chrono::time_point<chrono::system_clock, chrono::nanoseconds>& tp)
    {
        chrono::nanoseconds d = tp.time_since_epoch();
        timespec ts = boost::detail::to_timespec(d);
        return do_wait_lock_until(dispatch_walltime(&ts, 0));
    }

private:
    bool do_wait_lock_until(const dispatch_time_t timeout)
    {
        const long status = dispatch_semaphore_wait(sem, timeout);
        return status == 0;
    }

#endif // BOOST_SYNC_USES_CHRONO

private:
    dispatch_semaphore_t sem;
};

}
}

#endif // BOOST_SYNC_SEMAPHORE_SEMAPHORE_DISPATCH_HPP
