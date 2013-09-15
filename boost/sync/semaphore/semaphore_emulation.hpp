// semaphore.hpp, mutex/condition_varibale emulation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_SEMAPHORE_SEMAPHORE_EMULATION_HPP
#define BOOST_SYNC_SEMAPHORE_SEMAPHORE_EMULATION_HPP

#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

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
    semaphore(int i=0):
      m_count(i)
    {
        BOOST_ASSERT_MSG(i >= 0, "boost::sync::semaphore constructor called with negative count");
    }

    void post(void)
    {
        mutex::scoped_lock lock(m_mutex);
        ++m_count;
        m_cond.notify_one();
    }

    void wait(void)
    {
        mutex::scoped_lock lock(m_mutex);
        m_cond.wait(lock, boost::bind(&semaphore::check_wakeup_condition, this));

        --m_count;
    }

    bool try_wait(void)
    {
        mutex::scoped_lock lock(m_mutex);
        if (!check_wakeup_condition())
            return false;

        --m_count;
        return true;
    }

#ifdef BOOST_SYNC_USES_CHRONO
    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & rel_time)
    {
        mutex::scoped_lock lock(m_mutex);
        return m_cond.wait_for(lock, rel_time, boost::bind(&semaphore::check_wakeup_condition, this));
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout )
    {
        mutex::scoped_lock lock(m_mutex);
        return m_cond.wait_until(lock, timeout, boost::bind(&semaphore::check_wakeup_condition, this));
    }
#endif // BOOST_SYNC_USES_CHRONO

private:
    bool check_wakeup_condition()
    {
        return m_count > 0;
    }

    unsigned int m_count;
    boost::mutex m_mutex;
    boost::condition_variable m_cond;
};

}
}

#endif // BOOST_SYNC_SEMAPHORE_SEMAPHORE_EMULATION_HPP
