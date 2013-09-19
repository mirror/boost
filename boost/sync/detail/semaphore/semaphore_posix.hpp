// semaphore.hpp, posix implementation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_POSIX_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_POSIX_HPP_INCLUDED_

#include <errno.h>
#include <semaphore.h>

#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/sync/detail/config.hpp>
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
        const int status = sem_init(&m_sem, 0, i);
        if (status)
        {
            const int err = errno;
            BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore constructor failed in sem_init"));
        }
    }

    ~semaphore() BOOST_NOEXCEPT
    {
        BOOST_VERIFY(sem_destroy(&m_sem) == 0);
    }

    void post()
    {
        const int status = sem_post(&m_sem);
        if (status == 0)
            return;

        const int err = errno;
        switch (err)
        {
        case EOVERFLOW:
            BOOST_THROW_EXCEPTION(resource_error(err, "boost::sync::semaphore post failed: maximum allowable value would be exceeded"));
            break;

        case EINVAL:
            BOOST_ASSERT(false);

        default:
            break;
        }
    }

    void wait(void) BOOST_NOEXCEPT
    {
        for (;;)
        {
            const int status = sem_wait(&m_sem);
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

    bool try_wait(void) BOOST_NOEXCEPT
    {
        const int status = sem_trywait(&m_sem);
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
    bool try_wait_for(const chrono::duration<Rep, Period> & duration) BOOST_NOEXCEPT
    {
        return try_wait_until(chrono::steady_clock::now() + duration);
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
        return do_wait_lock_until(ts);
    }

private:
    bool do_wait_lock_until(struct timespec const & timeout) BOOST_NOEXCEPT
    {
        for (;;)
        {
            const int status = sem_timedwait(&m_sem, &timeout);
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
    sem_t m_sem;
};

} // namespace posix

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_POSIX_HPP_INCLUDED_
