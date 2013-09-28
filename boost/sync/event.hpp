// event.hpp
//
// Copyright (C) 2013 Tim Blechmann
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SYNC_EVENT_HPP
#define BOOST_SYNC_EVENT_HPP

#ifdef BOOST_SYNC_DETAIL_DOXYGEN

class auto_reset_event
{
public:
    /**
     * \b Effects: Constructs an auto_reset_event object.
     *
     * \b Throws: if an error occurs.
     */
    auto_reset_event();

    auto_reset_event(auto_reset_event const&) = delete;
    auto_reset_event& operator= (auto_reset_event const&) = delete;

    /**
     * \b Effects: Destroys the auto_reset_event object.
     *
     * \b Precondition: No thread waits on this auto_reset_event.
     *
    * \b Throws: nothing.
     */
    ~auto_reset_event() noexcept;

    /**
     * \b Effects: Signals the auto_reset_event: the object remains signalled until one thread has finished waiting for this object.
     *
     * \b Memory Ordering: release
     *
     * \b Throws: if an error occurs.
     */
    void post();

    /**
     * \b Effects: If the auto_reset_event is set, the call returns immediately, otherwise it will block until the thread will be woken up
	 *             by. When a waiting thread is released, the state of the auto_reset_event is automatically reset to the unsignaled state.
     *
     * \b Memory Ordering: acquire
     *
     * \b Throws: if an error occurs.
     */
    void wait();

    /**
     * \b Effects: Tries to wait for the auto_reset_event. If successful, the state of the auto_reset_event us automatically set to the unsignaled state.
     *
     * \b Memory Ordering: acquire, if successful, relaxed otherwise
     *
     * \b Returns: True if the auto_reset_event had been signaled, False, if the call would be blocking or the auto_reset_event has not been signaled.
     *
     * \b Throws: if an error occurs.
     */
    bool try_wait();

   /**
    * \b Effects: Tries to wait for the auto_reset_event until a timeout occurs. If successful, the state of the auto_reset_event us automatically set to the unsignaled state.
    *
    * \b Memory Ordering: acquire, if successful, relaxed otherwise
    *
    * \b Returns: True if the auto_reset_event had been signaled, False, if the call would be blocking or the auto_reset_event has not been signaled.
    *
    * \b Throws: if an error occurs.
    */
    template <typename Duration>
    bool try_wait_for(const Duration & duration);

   /**
    * \b Effects: Tries to wait for the auto_reset_event for a certain duration. If successful, the state of the auto_reset_event us automatically set to the unsignaled state.
    *
    * \b Memory Ordering: acquire, if successful, relaxed otherwise
    *
    * \b Returns: True if the auto_reset_event had been signaled, False, if the call would be blocking or the auto_reset_event has not been signaled.
    *
    * \b Throws: if an error occurs.
    */
    template <typename TimePoint>
    bool try_wait_until(const TimePoint & timeout);
};

class manual_reset_event
{
public:
    /**
     * \b Effects: Constructs a manual_reset_event object.
     *
     * \b Throws: if an error occurs.
     */
    auto_reset_event();

    auto_reset_event(auto_reset_event const&) = delete;
    auto_reset_event& operator= (auto_reset_event const&) = delete;

   /**
    * \b Effects: Destroys the manual_reset_event object.
    *
    * \b Precondition: No thread waits on this manual_reset_event.
    *
    * \b Throws: nothing.
    */
    ~auto_reset_event() noexcept;

    /**
     * \b Effects: Signals the event object: the event is set and waiting threads will be released.
     *
     * \b Memory Ordering: release
     *
     * \b Throws: if an error occurs.
     */
    void post();

    /**
     * \b Effects: Waits for the event to be signaled.
     *
     * \b Memory Ordering: acquire
     *
     * \b Throws: if an error occurs.
     */
    void wait();

    /**
     * \b Effects: Resets the event to the unsignaled state.
     *
     * \b Throws: if an error occurs.
     */
    void reset();

    /**
     * \b Effects: Tries to waits for the event to be signaled.
     *
     * \b Memory Ordering: acquire, if successful, relaxed otherwise
     *
     * \b Returns: True if the event had been signaled, False, if the call would be blocking or the event has not been signaled.
     *
     * \b Throws: if an error occurs.
     */
    bool try_wait();

    /**
     * \b Effects: Waits for the event to be signaled.
     *
     * \b Memory Ordering: acquire, if successful, relaxed otherwise
     *
     * \b Returns: True if the event had been signaled, False, if the call would be blocking or the event has not been signaled.
     *
     * \b Throws: if an error occurs.
     */
    template <typename Duration>
    bool try_wait_for(const Duration & duration);

    /**
     * \b Effects: Waits for the event to be signaled.
     *
     * \b Memory Ordering: acquire, if successful, relaxed otherwise
     *
     * \b Returns: True if the event had been signaled, False, if the call would be blocking or the event has not been signaled.
     *
     * \b Throws: if an error occurs.
     */
    template <typename TimePoint>
    bool try_wait_until(const TimePoint & timeout);
};


#else // BOOST_SYNC_DETAIL_DOXYGEN

#include <boost/sync/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#include <Availability.h>

// OSX
#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED

// Check: do other mach-based platforms support mach semaphores?

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_7
#define BOOST_SYNC_DETAIL_PLATFORM_MACH
#endif

#endif // __MAC_OS_X_VERSION_MIN_REQUIRED
#endif // apple stuff

#if defined(BOOST_SYNC_DETAIL_PLATFORM_WINAPI)
#include <boost/sync/detail/event/event_windows.hpp>

#elif defined(__linux__)
#include <boost/sync/detail/event/event_futex.hpp>

#elif defined(BOOST_SYNC_DETAIL_PLATFORM_MACH)
#include <boost/sync/detail/event/event_mach.hpp>

#else

#include <boost/sync/detail/event/event_emulation.hpp>

#endif

#endif // BOOST_SYNC_DETAIL_DOXYGEN

#endif // BOOST_SYNC_EVENT_HPP
