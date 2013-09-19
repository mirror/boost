// event.hpp, condition variable emulation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/locks.hpp>

#include <boost/sync/detail/config.hpp>
//#include <boost/sync/locks/lock_guard.hpp>
//#include <boost/sync/locks/unique_lock.hpp>
#include <boost/sync/detail/header.hpp>

#define BOOST_SYNC_EVENT_EMULATED

namespace boost {
namespace sync {
BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class event
{
    BOOST_DELETED_FUNCTION(event(event const&));
    BOOST_DELETED_FUNCTION(event& operator=(event const&));

public:
    explicit event(bool auto_reset = false) :
        m_auto_reset(auto_reset), m_is_set(false)
    {}

    void post()
    {
        unique_lock<upgrade_mutex> lock(m_mutex);
        bool already_signaled = m_is_set;
        m_is_set = true;
        if (m_auto_reset) {
            if (!already_signaled)
                m_cond.notify_one();
        } else
            m_cond.notify_all();
    }

    void wait()
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set)
            m_cond.wait(lock);

        if (m_auto_reset) {
            upgrade_to_unique_lock<upgrade_mutex> unique_lock(lock);
            m_is_set = false;
        }
    }

    void reset()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        m_is_set = false;
    }

    bool try_wait()
    {
        lock_guard<upgrade_mutex> lock(m_mutex);
        const bool res = m_is_set;
        if (res && m_auto_reset)
            m_is_set = false;
        return res;
    }

    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & duration)
    {
        return try_wait_until( chrono::system_clock::now() + duration );
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout)
    {
        upgrade_lock<upgrade_mutex> lock(m_mutex);

        while (!m_is_set) {
            if (m_cond.wait_until(lock, timeout) == cv_status::timeout) {
                if (!m_is_set)
                    return false;
                break;
            }
        }

        if (m_auto_reset) {
            upgrade_to_unique_lock<upgrade_mutex> unique_lock(lock);
            m_is_set = false;
        }
        return true;
    }

private:
    upgrade_mutex m_mutex;
    condition_variable_any m_cond;
    const bool m_auto_reset;
    bool m_is_set;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_EVENT_EVENT_EMULATION_HPP_INCLUDED_
