// event.hpp, futex-based event
//
// Copyright (C) 2013 Tim Blechmann
// Copyright (C) 2013 Andrey Semashev
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
    BOOST_DELETED_FUNCTION(auto_reset_event& operator= (auto_reset_event const&));

private:
    // State bits are divided into post count and waiter count. Post counter is needed to wake
    // the correct number of threads blocked on the event in case if multiple concurrent posts are made.
    enum
    {
        post_count_lowest_bit = 22u,
        post_count_one = 1u << post_count_lowest_bit,
        post_count_mask = 0u - post_count_one,
        wait_count_mask = (~0u) ^ post_count_mask
    };

public:
    auto_reset_event() BOOST_NOEXCEPT : m_state(0)
    {
    }

    void post() BOOST_NOEXCEPT
    {
        unsigned int old_state = m_state.load(detail::atomic_ns::memory_order_acquire);
        unsigned int waiters, posts;
        while (true)
        {
            waiters = old_state & wait_count_mask;
            posts = old_state >> post_count_lowest_bit;
            if (waiters >= posts)
            {
                if (m_state.compare_exchange_weak(old_state, old_state + post_count_one, detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                    break;

                detail::pause();
            }
            else
                return; // the event is already set (enough times so that all waiters are released and the event is still left signalled)
        }

        if (waiters > 0)
            sync::detail::linux_::futex_signal(reinterpret_cast< int* >(&m_state));
    }

    void wait() BOOST_NOEXCEPT
    {
        // Try the fast path first
        if (this->try_wait())
            return;

        // Add one waiter
        unsigned int old_state = m_state.fetch_add(1, detail::atomic_ns::memory_order_acq_rel);
        while (true)
        {
            unsigned int posts = old_state >> post_count_lowest_bit;
            if (posts == 0)
            {
            again:
                const int status = sync::detail::linux_::futex_wait(reinterpret_cast< int* >(&m_state), old_state);
                if (status != 0)
                {
                    const int err = errno;
                    switch (err)
                    {
                    case EINTR:       // signal received
                        goto again;

                    case EWOULDBLOCK: // another thread changed the state
                        break;

                    default:
                        BOOST_ASSERT(false);
                    }
                }

                old_state = m_state.load(detail::atomic_ns::memory_order_acquire);
                posts = old_state >> post_count_lowest_bit;
                if (posts == 0)
                    goto again;
            }

            // Remove one post and one waiter from the counters
            if (m_state.compare_exchange_strong(old_state, old_state - (post_count_one + 1u), detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                break;
        }
    }

    bool try_wait() BOOST_NOEXCEPT
    {
        unsigned int old_state = m_state.load(detail::atomic_ns::memory_order_acquire);

        for (unsigned int posts = old_state >> post_count_lowest_bit; posts > 0; posts = old_state >> post_count_lowest_bit)
        {
            if (m_state.compare_exchange_weak(old_state, old_state - post_count_one, detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                return true;

            detail::pause();
        }

        return false;
    }

    template <typename Duration>
    bool try_wait_for(const Duration & duration) BOOST_NOEXCEPT
    {
        timespec ts = boost::detail::to_timespec(duration);
        return do_wait_for(ts);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout) BOOST_NOEXCEPT
    {
        return try_wait_for( timeout - Clock::now() );
    }

private:
    bool do_wait_for(const struct timespec & timeout)
    {
        // Try the fast path first
        if (this->try_wait())
            return true;

        // Add one waiter
        unsigned int old_state = m_state.fetch_add(1, detail::atomic_ns::memory_order_acq_rel);
        while (true)
        {
            unsigned int posts = old_state >> post_count_lowest_bit;
            if (posts == 0)
            {
            again:
                const int status = sync::detail::linux_::futex_timedwait(reinterpret_cast< int* >(&m_state), old_state, &timeout);
                if (status != 0)
                {
                    const int err = errno;
                    switch (err)
                    {
                    case ETIMEDOUT:
                        old_state = m_state.load(detail::atomic_ns::memory_order_acquire);
                        while (true)
                        {
                            posts = old_state >> post_count_lowest_bit;
                            if (posts == 0)
                            {
                                // Remove one waiter
                                if (m_state.compare_exchange_weak(old_state, old_state - 1u, detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                                    return false;
                            }
                            else
                            {
                                // Remove one post and one waiter from the counters
                                if (m_state.compare_exchange_weak(old_state, old_state - (post_count_one + 1u), detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                                    return true;
                            }

                            detail::pause();
                        }
                        break;

                    case EINTR:       // signal received
                        goto again;

                    case EWOULDBLOCK: // another thread changed the state
                        break;

                    default:
                        BOOST_ASSERT(false);
                    }
                }

                old_state = m_state.load(detail::atomic_ns::memory_order_acquire);
                posts = old_state >> post_count_lowest_bit;
                if (posts == 0)
                    goto again;
            }

            // Remove one post and one waiter from the counters
            if (m_state.compare_exchange_strong(old_state, old_state - (post_count_one + 1u), detail::atomic_ns::memory_order_acquire, detail::atomic_ns::memory_order_release))
                break;
        }

        return true;
    }

private:
    BOOST_STATIC_ASSERT_MSG(sizeof(detail::atomic_ns::atomic< unsigned int >) == sizeof(int), "Boost.Sync: unexpected size of atomic< unsigned int >");
    detail::atomic_ns::atomic< unsigned int > m_state;
};

class manual_reset_event
{
    BOOST_DELETED_FUNCTION(manual_reset_event(manual_reset_event const&));
    BOOST_DELETED_FUNCTION(manual_reset_event& operator= (manual_reset_event const&));

public:
    manual_reset_event() BOOST_NOEXCEPT :
        m_state(0)
    {
    }

    void post() BOOST_NOEXCEPT
    {
        int old_state = m_state.exchange(1, detail::atomic_ns::memory_order_release); // set state
        if (old_state == 0)
            sync::detail::linux_::futex_broadcast(reinterpret_cast< int* >(&m_state)); // wake all threads
    }

    void wait() BOOST_NOEXCEPT
    {
        while (m_state.load(detail::atomic_ns::memory_order_acquire) == 0)
        {
            const int status = sync::detail::linux_::futex_wait(reinterpret_cast< int* >(&m_state), 0);
            if (status == 0)
                break;

            switch (errno)
            {
            case EINTR:       // signal received
            case EWOULDBLOCK: // another thread has reset the event
                continue;

            default:
                BOOST_ASSERT(false);
            }
        }
    }

    bool try_wait()
    {
        return m_state.load(detail::atomic_ns::memory_order_acquire) == 1;
    }

    void reset() BOOST_NOEXCEPT
    {
        m_state.store(0, detail::atomic_ns::memory_order_release);
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
        while (m_state.load(detail::atomic_ns::memory_order_acquire) == 0)
        {
            const int status = sync::detail::linux_::futex_timedwait(reinterpret_cast< int* >(&m_state), 0, &timeout);
            if (status == 0)
                break;

            switch (errno)
            {
            case ETIMEDOUT:
                return false;

            case EINTR:       // signal received
            case EWOULDBLOCK: // another thread has reset the event
                continue;

            default:
                BOOST_ASSERT(false);
            }
        }

        return true;
    }

private:
    BOOST_STATIC_ASSERT_MSG(sizeof(detail::atomic_ns::atomic< int >) == sizeof(int), "Boost.Sync: unexpected size of atomic< int >");
    detail::atomic_ns::atomic< int > m_state;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_FUTEX_HPP_INCLUDED_
