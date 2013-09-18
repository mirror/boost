// event.hpp, mach events
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_EVENT_DETAIL_DARWIN_EVENT_MACH_HPP
#define BOOST_SYNC_EVENT_DETAIL_DARWIN_EVENT_MACH_HPP

#include <cstddef>
#include <boost/assert.hpp>

#include <boost/sync/detail/config.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/detail/header.hpp>

#include <mach/task.h>
#include <mach/semaphore.h>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>

#include <boost/atomic.hpp>

namespace boost {

namespace sync {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class event
{
    BOOST_DELETED_FUNCTION(event(event const&))
    BOOST_DELETED_FUNCTION(event& operator=(event const&));

public:
    explicit event(bool auto_reset = false):
        m_auto_reset(auto_reset), m_signaled(0)
    {
        kern_return_t result = semaphore_create(mach_task_self(), &m_sem, SYNC_POLICY_FIFO, 0);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    ~event()
    {
        kern_return_t result = semaphore_destroy(mach_task_self(), m_sem);
        BOOST_VERIFY(result == KERN_SUCCESS);
    }

    void post()
    {
        if (m_auto_reset) {
            bool already_signaled = m_signaled.exchange(true);
            if (!already_signaled)
                semaphore_signal( m_sem ); // wake one thread!
        } else {
            m_signaled = true;
            semaphore_signal_all( m_sem ); // wake all threads!& reset semaphore count
        }
    }

    void reset()
    {
        m_signaled = false;
    }

    void wait()
    {
        if (m_auto_reset) {
            // the first waiter succeeds and resets the signalled state

        try_again:
            kern_return_t result = semaphore_wait( m_sem );

            if (result == KERN_SUCCESS) {
                bool isTrue = true;
                bool firstWaiter = m_signaled.compare_exchange_strong(isTrue, false);

                if (firstWaiter) // only the first waiter succeeds
                    return;
            }

            goto try_again;
        } else {
            if (m_signaled.load() == true)
                return;

            kern_return_t result = semaphore_wait( m_sem );
            BOOST_VERIFY (result == KERN_SUCCESS);
        }
    }

    bool try_wait()
    {
        const mach_timespec_t immediate = {0, 0};
        return do_try_wait_until(immediate);
    }

    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & duration)
    {
        BOOST_AUTO ( seconds, chrono::duration_cast<chrono::seconds>(duration) );
        BOOST_AUTO ( nanoseconds, chrono::duration_cast<chrono::nanoseconds>(duration) - seconds );

        const mach_timespec_t mach_duration = { seconds.count(), nanoseconds.count() };
        return do_try_wait_until( mach_duration );
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout )
    {
        return try_wait_for( timeout - Clock::now() );
    }

private:
    bool do_try_wait_until (const mach_timespec_t & timeout)
    {
        if (m_auto_reset) {
            // the first waiter succeeds and resets the signaled state

            kern_return_t result = semaphore_timedwait( m_sem, timeout );

            if (result == KERN_SUCCESS) {
                bool isTrue = true;
                bool firstWaiter = m_signaled.compare_exchange_strong(isTrue, false);

                if (firstWaiter) // only the first waiter succeeds
                    return true;
            }
            return false;

        } else {
            if (m_signaled.load() == true)
                return true;

            kern_return_t result = semaphore_timedwait( m_sem, timeout );
            if (result == KERN_SUCCESS)
                return true;
            else
                return false;
        }
    }

    const bool m_auto_reset;
    semaphore_t m_sem;
    atomic_bool m_signaled;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_EVENT_DETAIL_DARWIN_EVENT_MACH_HPP
