// semaphore.hpp, mutex/condition_varibale emulation
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_EMULATION_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_EMULATION_HPP_INCLUDED_

#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <boost/sync/detail/config.hpp>
//#include <boost/sync/locks/lock_guard.hpp>
//#include <boost/sync/locks/unique_lock.hpp>

#ifdef BOOST_SYNC_USES_CHRONO
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/ceil.hpp>
#endif

#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_SYNC_SEMAPHORE_EMULATED

namespace boost {

namespace sync  {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class semaphore
{
    BOOST_DELETED_FUNCTION(semaphore(semaphore const&))
    BOOST_DELETED_FUNCTION(semaphore& operator=(semaphore const&))

public:
    explicit semaphore(unsigned int i = 0) :
        m_count(i)
    {
    }

    void post(void)
    {
        lock_guard< mutex > lock(m_mutex);
        ++m_count;
        m_cond.notify_one();
    }

    void wait(void)
    {
        unique_lock< mutex > lock(m_mutex);
        while (m_count == 0)
            m_cond.wait(lock);

        --m_count;
    }

    bool try_wait(void)
    {
        lock_guard< mutex > lock(m_mutex);
        if (m_count == 0)
            return false;

        --m_count;
        return true;
    }

#ifdef BOOST_SYNC_USES_CHRONO
    template <class Rep, class Period>
    bool try_wait_for(const chrono::duration<Rep, Period> & rel_time)
    {
        return try_wait_until(chrono::steady_clock::now() + rel_time);
    }

    template <class Clock, class Duration>
    bool try_wait_until(const chrono::time_point<Clock, Duration> & timeout)
    {
        unique_lock< mutex > lock(m_mutex);
        while (m_count == 0)
        {
            if (m_cond.wait_until(lock, timeout) == cv_status::timeout)
            {
                if (m_count == 0)
                    return false;
                break;
            }
        }
        --m_count;
        return true;
    }
#endif // BOOST_SYNC_USES_CHRONO

private:
    mutex m_mutex;
    condition_variable m_cond;
    unsigned int m_count;
};

} // namespace

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_SEMAPHORE_SEMAPHORE_EMULATION_HPP_INCLUDED_
