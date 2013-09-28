// event.hpp, futex-based event
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED
#define BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED

#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <linux/futex.h>

#include <limits>
#include <boost/assert.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/atomic.hpp>
#include <boost/sync/detail/pause.hpp>

#include <boost/sync/detail/header.hpp>

namespace boost {
namespace sync {
BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class futex_event_base
{
    BOOST_DELETED_FUNCTION(futex_event_base(futex_event_base const&));
    BOOST_DELETED_FUNCTION(futex_event_base& operator=(futex_event_base const&));

protected:
    static long futex(void *addr1, int op, int val1, const struct timespec *timeout = NULL, void *addr2 = NULL, int val3 = 0)
    {
        return syscall(SYS_futex, addr1, op, val1, timeout, addr2, val3);
    }
};

class auto_reset_event : futex_event_base
{
public:
    auto_reset_event() BOOST_NOEXCEPT :
        m_state(0)
    {}

    void post() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int32_t old_state = m_state.load();
        if (old_state >= 0) {
            for(;;) {
                if (m_state.compare_exchange_weak(old_state, old_state - 1))
                    break;
                detail::pause();
            }
            futex(&m_state, FUTEX_WAKE_PRIVATE, std::numeric_limits<int>::max() ); // wake all threads
        }
    }

    void wait() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int32_t old_state = m_state.fetch_add(1) + 1;

        for (;;) {
            long status = futex(&m_state, FUTEX_WAIT_PRIVATE, old_state);
            if (status == 0)
                return;

            switch (errno) {
            case EINTR: // signal received
                continue;

            case EWOULDBLOCK: // another thread changed the state, reread and retry
                old_state = m_state.load();
                continue;

            default:
                BOOST_ASSERT(false);
            }
        }
    }

    bool try_wait()
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int32_t old_state = m_state.load();

        if (old_state < 0) {
            for(;;) {
                int32_t new_state = old_state + 1;
                bool cas_successful = m_state.compare_exchange_weak(old_state, new_state);
                if (cas_successful) // we succeeded and reset the wait count
                    return true;
                if (old_state >= 0) // another thread a succeeded
                    return false;
            }
        }
        return false;
    }

    template <typename Duration>
    bool try_wait_for(const Duration & duration) BOOST_NOEXCEPT
    {
        timespec ts = boost::detail::to_timespec( duration );
        return do_wait_for(ts);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout ) BOOST_NOEXCEPT
    {
        return try_wait_for( timeout - Clock::now() );
    }

private:
    bool do_wait_for(const struct timespec & timeout)
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int32_t old_state = m_state.fetch_add(1) + 1;

        for (;;) {
            long status = futex(&m_state, FUTEX_WAIT_PRIVATE, old_state, &timeout);
            if (status == 0)
                return true;

            switch (errno) {
            case ETIMEDOUT:
                return false;

            case EINTR: // signal received
                continue;

            case EWOULDBLOCK: // another thread changed the state, reread and retry
                old_state = m_state.load();
                continue;

            default:
                BOOST_ASSERT(false);
            }
        }
        BOOST_ASSERT(false);
        return false;
    }

    detail::atomic_ns::atomic<int32_t> m_state;
};

class manual_reset_event: futex_event_base
{
public:
    manual_reset_event() BOOST_NOEXCEPT :
        m_state(0)
    {}

    void post() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int old_state = m_state.exchange(1); // set state
        if (old_state == 0)
            futex(&m_state, FUTEX_WAKE_PRIVATE, std::numeric_limits<int>::max() ); // wake all threads
    }

    void wait() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
    try_again:

        if ( m_state.load(memory_order_acquire) == 1 )
            return; // fast-path

        const long status = futex(&m_state, FUTEX_WAIT_PRIVATE, 0);
        if (status == 0)
            return;

        switch (errno)
        {
        case EINTR:
            // signal received
            goto try_again;

        case EWOULDBLOCK:
            // another thread has reset the event
            goto try_again;
        }
    }

    bool try_wait()
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        if ( m_state.load(memory_order_acquire) == 1 )
            return true; // fast-path
        else
            return false;
    }

    void reset() BOOST_NOEXCEPT
    {
        m_state.store( 0 );
    }

    template <typename Duration>
    bool try_wait_for(const Duration & duration) BOOST_NOEXCEPT
    {
        timespec ts = boost::detail::to_timespec( duration );
        return do_wait_for(ts);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout ) BOOST_NOEXCEPT
    {
        return try_wait_for( timeout - Clock::now() );
    }

private:
    bool do_wait_for(const struct timespec & timeout)
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order

    try_again:
        if ( m_state.load(memory_order_acquire) == 1 )
            return true; // fast-path

        const long status = futex(&m_state, FUTEX_WAIT_PRIVATE, 0, &timeout);
        if (status == 0)
            return true;

        switch (errno)
        {
        case ETIMEDOUT:
            return false;

        case EINTR:
            // signal received
            goto try_again;

        case EWOULDBLOCK:
            // another thread has reset the event
            goto try_again;
        }
        BOOST_ASSERT(false);
        return false;
    }
    detail::atomic_ns::atomic<int32_t> m_state;
};



}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED
