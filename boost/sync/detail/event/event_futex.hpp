// event.hpp, futex-based event
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED_

#include <errno.h>
#include <sys/time.h>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/detail/atomic.hpp>
#include <boost/sync/detail/pause.hpp>
#include <boost/sync/detail/futex.hpp>

#include <boost/sync/detail/header.hpp>

namespace boost {
namespace sync {
BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class auto_reset_event
{
    BOOST_DELETED_FUNCTION(auto_reset_event(auto_reset_event const&));
    BOOST_DELETED_FUNCTION(auto_reset_event& operator=(auto_reset_event const&));

public:
    auto_reset_event() BOOST_NOEXCEPT :
        m_state(0)
    {}

    void post() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int old_state = m_state.load();
        if (old_state >= 0)
        {
            for(;;)
            {
                if (m_state.compare_exchange_weak(old_state, old_state - 1))
                    break;
                detail::pause();
            }
            sync::detail::linux_::futex_broadcast(reinterpret_cast< int* >(&m_state)); // wake all threads
        }
    }

    void wait() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int old_state = m_state.fetch_add(1) + 1;

        for (;;)
        {
            const int status = sync::detail::linux_::futex_wait(reinterpret_cast< int* >(&m_state), old_state);
            if (status == 0)
                return;

            switch (errno)
            {
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
        int old_state = m_state.load();

        if (old_state < 0)
        {
            for(;;)
            {
                const bool cas_successful = m_state.compare_exchange_weak(old_state, old_state + 1);
                if (cas_successful) // we succeeded and reset the wait count
                    return true;
                if (old_state >= 0) // another thread succeeded
                    return false;
                detail::pause();
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
        int old_state = m_state.fetch_add(1) + 1;

        for (;;)
        {
            const int status = sync::detail::linux_::futex_timedwait(reinterpret_cast< int* >(&m_state), old_state, &timeout);
            if (status == 0)
                return true;

            switch (errno)
            {
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

private:
    BOOST_STATIC_ASSERT_MSG(sizeof(detail::atomic_ns::atomic<int>) == sizeof(int), "Boost.Sync: unexpected size of atomic<int>");
    detail::atomic_ns::atomic<int> m_state;
};

class manual_reset_event
{
    BOOST_DELETED_FUNCTION(manual_reset_event(manual_reset_event const&));
    BOOST_DELETED_FUNCTION(manual_reset_event& operator=(manual_reset_event const&));

public:
    manual_reset_event() BOOST_NOEXCEPT :
        m_state(0)
    {}

    void post() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
        int old_state = m_state.exchange(1); // set state
        if (old_state == 0)
            sync::detail::linux_::futex_broadcast(reinterpret_cast< int* >(&m_state)); // wake all threads
    }

    void wait() BOOST_NOEXCEPT
    {
        using namespace boost::sync::detail::atomic_ns; // for memory_order
    try_again:

        if ( m_state.load(memory_order_acquire) == 1 )
            return; // fast-path

        const int status = sync::detail::linux_::futex_wait(reinterpret_cast< int* >(&m_state), 0);
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

        const int status = sync::detail::linux_::futex_timedwait(reinterpret_cast< int* >(&m_state), 0, &timeout);
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

private:
    BOOST_STATIC_ASSERT_MSG(sizeof(detail::atomic_ns::atomic<int>) == sizeof(int), "Boost.Sync: unexpected size of atomic<int>");
    detail::atomic_ns::atomic<int> m_state;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED_
