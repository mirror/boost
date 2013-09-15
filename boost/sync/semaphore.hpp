// semaphore.hpp
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_SEMAPHORE_HPP
#define BOOST_SYNC_SEMAPHORE_HPP

#ifdef BOOST_SYNC_DETAIL_DOXYGEN

namespace boost {
namespace sync  {

class semaphore
{
public:
    /**
     * \b Effects: Constructs a semaphore object. The semaphore is initialized to `initial_count`, which is expected to be non-negative.
     *
     * \b Throws: if an error occurs.
     *
     * */
    semaphore(int initial_count = 0);

    /**
     * \b Precondition: No thread is waiting on the semaphore
     *
     * \b Effects: Destroys the object
     *
     * */
    ~semaphore();

    semaphore(semaphore const&) = delete;
    semaphore& operator= (semaphore const&) = delete;

    /**
     * \b Effects: Increments the semaphore count. If a thread is waiting for this semaphore, it will be unblocked.
     *
     * \b Throws: if an error occurs.
     * */
    void post();

    /**
     * \b Effects: If the semaphore count is positive, it atomically decrements it and returns. Otherwise blocks the current thread, until it can successfully decrement a positive semaphore count.
     *
     * \b Throws: if an error occurs.
     * */
    void wait();

    /**
     * \b Effects: If the semaphore count is positive, it atomically decrements it and returns `true`. Otherwise `false`.
     *
     * \b Throws: if an error occurs.
     * */
    bool try_wait();

    /**
     * \b Effects: If the semaphore count is positive, it atomically decrements it and returns `true`. Otherwise it waits for the semaphore for `duration`.
     *
     * \b Throws: if an error occurs.
     * */
    template <class Duration>
    bool try_wait_for(const Duration & duration);

    /**
     * \b Effects: If the semaphore count is positive, it atomically decrements it and returns `true`. Otherwise it waits for the semaphore until `timeout`.
     *
     * \b Throws: if an error occurs.
     * */
    template <class TimePoint>
    bool try_wait_until(const TimePoint & timeout);
};


}}

#else

#include <boost/sync/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/sync/detail/header.hpp>


#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include <boost/sync/semaphore/semaphore_win32.hpp>

#elif defined(BOOST_THREAD_POSIX_SEMAPHORES)
#include <boost/sync/semaphore/semaphore_posix.hpp>

#elif defined(BOOST_THREAD_DISPATCH_SEMAPHORES)
#include <boost/sync/semaphore/semaphore_dispatch.hpp>

#else

#include <boost/sync/semaphore/semaphore_emulation.hpp>

#endif

#include <boost/sync/detail/footer.hpp>

#endif

#endif // BOOST_THREAD_SEMAPHORE_HPP
