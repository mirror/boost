// event.hpp, condition variable emulation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_GENERIC_EVENT_CV_EMULATION_HPP
#define BOOST_SYNC_DETAIL_GENERIC_EVENT_CV_EMULATION_HPP

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>

#include <boost/sync/detail/config.hpp>
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
    explicit event(bool auto_reset = false):
        auto_reset_(auto_reset), set_(false)
    {}

    ~event()
    {}

    void post()
    {
        unique_lock<timed_mutex> lock(mutex_);
        set_ = true;
        cv_.notify_all();
    }

    void wait()
    {
        unique_lock<timed_mutex> lock(mutex_);
        if (set_) {
            if (auto_reset_)
                set_ = false;
            return;
        }

        cv_.wait( lock, bind(&event::is_set, this) );

        if (auto_reset_)
            set_ = false;
    }

    void reset()
    {
        unique_lock<timed_mutex> lock(mutex_);
        set_ = false;
    }

    bool try_wait()
    {
        unique_lock<timed_mutex> lock(mutex_);
        return test_status();
    }

    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & duration)
    {
        return try_wait_until( chrono::system_clock::now() + duration );
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout)
    {
        unique_lock<timed_mutex> lock(mutex_, timeout);

        if (!lock.owns_lock())
            return false;

        const bool success = cv_.wait_until(lock, timeout, bind(&event::is_set, this));
        if (success)
            return test_status();
        else
            return false;
    }

private:
    inline bool is_set()
    {
        return set_;
    }

    bool test_status()
    {
        if (!set_)
            return false;
        else {
            if (auto_reset_)
                set_ = false;

            return true;
        }
    }

    timed_mutex mutex_;
    condition_variable_any cv_;
    const bool auto_reset_;
    bool set_;
};

}
}
}

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_GENERIC_EVENT_CV_EMULATION_HPP
