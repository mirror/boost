// semaphore.hpp, posix implementation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_SYNC_SEMAPHORE_SEMAPHORE_POSIX_HPP
#define BOOST_SYNC_SEMAPHORE_SEMAPHORE_POSIX_HPP

#include <semaphore.h>

#include <boost/assert.hpp>
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

        const int status = sem_init(&sem, 0, i);
        if (status)
            boost::throw_exception(thread_resource_error(status, "boost::sync::semaphore constructor failed in sem_init"));
    }

    ~semaphore()
    {
        const int status = sem_destroy(&sem);
        (void)status;
        BOOST_ASSERT(!status);
    }

    void post()
    {
        const int status = sem_post(&sem);

        switch (status)
        {
        case EOVERFLOW:
            boost::throw_exception(thread_resource_error(status, "boost::sync::semaphore post failed: Maximum allowable value would be exceeded"));
            break;

        case EINVAL:
            BOOST_ASSERT(false);

        default:
            break;
        }
    }

    void wait(void)
    {
        for (;;)
        {
            const int status = sem_wait(&sem);
            if (status == 0)
                return;

            switch (errno)
            {
            case EINTR: // interrupted by a signal handler
                continue;

            case EINVAL:
            default:
                // we should not reach here
                BOOST_ASSERT(false);
                return;
            }
        }
    }

    bool try_wait(void)
    {
        const int status = sem_trywait(&sem);
        if (status == 0)
            return true;

        switch (errno)
        {
        case EINVAL:
            BOOST_ASSERT(false);

        case EAGAIN:
            return false;

        default:
            return false;
        }
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
        return do_wait_lock_until(ts);
    }

private:
    bool do_wait_lock_until(struct timespec const & timeout)
    {
        for (;;) {
            const int status = sem_timedwait(&sem, &timeout);
            if (status == 0)
                return true;

            switch (errno)
            {
            case ETIMEDOUT:
                return false;

            case EINTR: // interrupted by a signal handler
                continue;

            case EINVAL:
            case EAGAIN:
            default:
                BOOST_ASSERT(false);
                return false;
            }
        }
    }

#endif // BOOST_SYNC_USES_CHRONO

private:
    sem_t sem;
};

}
}

#endif /* BOOST_SYNC_SEMAPHORE_SEMAPHORE_POSIX_HPP */
