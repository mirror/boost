/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007-2008 Anthony Williams
 * (C) Copyright 2011-2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   detail/condition_variables/condition_variable_posix.hpp
 *
 * \brief  This header is the Boost.Sync library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/sync/doc/html/index.html.
 */

#ifndef BOOST_SYNC_DETAIL_CONDITION_VARIABLES_CONDITION_VARIABLE_POSIX_HPP_INCLUDED_
#define BOOST_SYNC_DETAIL_CONDITION_VARIABLES_CONDITION_VARIABLE_POSIX_HPP_INCLUDED_

#include <time.h>
#include <cstddef>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/sync/detail/config.hpp>
#include <boost/sync/locks/unique_lock_fwd.hpp>
#include <boost/sync/exceptions/resource_error.hpp>
#include <boost/sync/traits/is_condition_variable_compatible.hpp>
#include <boost/sync/detail/pthread.hpp>
#include <boost/sync/detail/time_traits.hpp>
#include <boost/sync/detail/time_units.hpp>
#include <boost/sync/condition_variables/cv_status.hpp>
#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_SYNC_DEFINES_CONDITION_VARIABLE_NATIVE_HANDLE

namespace boost {

namespace sync {

BOOST_SYNC_DETAIL_OPEN_ABI_NAMESPACE {

class condition_variable
{
public:
    typedef pthread_cond_t* native_handle_type;

private:
    pthread_cond_t m_cond;

public:
#if defined(PTHREAD_COND_INITIALIZER)
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
    BOOST_CONSTEXPR condition_variable() BOOST_NOEXCEPT : m_cond(PTHREAD_COND_INITIALIZER)
    {
    }
#else
    condition_variable() BOOST_NOEXCEPT
    {
        BOOST_CONSTEXPR_OR_CONST pthread_cond_t temp = PTHREAD_COND_INITIALIZER;
        m_cond = temp;
    }
#endif
#else // defined(PTHREAD_COND_INITIALIZER)
    condition_variable()
    {
        int const res = pthread_cond_init(&m_cond, NULL);
        if (res)
            BOOST_THROW_EXCEPTION(resource_error(res, "boost:: timed_mutex constructor failed in pthread_cond_init"));
    }
#endif // defined(PTHREAD_COND_INITIALIZER)

    ~condition_variable()
    {
        BOOST_VERIFY(::pthread_cond_destroy(&m_cond) == 0);
    }

    void notify_one() BOOST_NOEXCEPT
    {
        BOOST_VERIFY(::pthread_cond_signal(&m_cond) == 0);
    }

    void notify_all() BOOST_NOEXCEPT
    {
        BOOST_VERIFY(::pthread_cond_broadcast(&m_cond) == 0);
    }

    template< typename Mutex >
    typename enable_if< is_condition_variable_compatible< Mutex >, void >::type wait(unique_lock< Mutex >& lock)
    {
        BOOST_ASSERT(lock.owns_lock());
        int const res = sync::detail::posix::pthread_cond_wait(&m_cond, lock.mutex()->native_handle());
        if (res != 0)
            BOOST_THROW_EXCEPTION(runtime_exception(res, "boost::sync::condition_variable::wait failed in pthread_cond_wait"));
    }

    template< typename Mutex, typename Predicate >
    typename enable_if< is_condition_variable_compatible< Mutex >, void >::type wait(unique_lock< Mutex >& lock, Predicate pred)
    {
        while (!pred())
            this->wait(lock);
    }

    template< typename Mutex, typename Time >
    typename enable_if_c< sync::detail::time_traits< Time >::is_specialized, bool >::type timed_wait(unique_lock< Mutex >& lock, Time const& t)
    {
        return priv_timed_wait(lock, sync::detail::time_traits< Time >::to_sync_unit(t));
    }

    template< typename Mutex, typename TimePoint, typename Predicate >
    typename detail::enable_if_tag< TimePoint, detail::time_point_tag, bool >::type timed_wait(unique_lock< Mutex >& lock, TimePoint const& t, Predicate pred)
    {
        typedef typename sync::detail::time_traits< TimePoint >::unit_type unit_type;
        unit_type abs_timeout = sync::detail::time_traits< TimePoint >::to_sync_unit(t);
        while (!pred())
        {
            if (!this->priv_timed_wait(lock, abs_timeout))
                return pred();
        }
        return true;
    }

    template< typename Mutex, typename Duration, typename Predicate >
    typename detail::enable_if_tag< Duration, detail::time_duration_tag, bool >::type timed_wait(unique_lock< Mutex >& lock, Duration const& t, Predicate pred)
    {
        sync::detail::system_time_point abs_timeout = sync::detail::system_time_point::now() + sync::detail::time_traits< Duration >::to_sync_unit(t);
        while (!pred())
        {
            if (!this->priv_timed_wait(lock, abs_timeout))
                return pred();
        }
        return true;
    }

    template< typename Duration >
    typename detail::enable_if_tag< Duration, detail::time_duration_tag, bool >::type try_lock_for(Duration const& rel_time)
    {
        return priv_timed_lock(sync::detail::time_traits< Duration >::to_sync_unit(rel_time));
    }

    template< typename TimePoint >
    typename detail::enable_if_tag< TimePoint, detail::time_point_tag, bool >::type try_lock_until(TimePoint const& abs_time)
    {
        return priv_timed_lock(sync::detail::time_traits< TimePoint >::to_sync_unit(abs_time));
    }

    native_handle_type native_handle() BOOST_NOEXCEPT
    {
        return &m_cond;
    }

    BOOST_DELETED_FUNCTION(condition_variable(condition_variable const&))
    BOOST_DELETED_FUNCTION(condition_variable& operator= (condition_variable const&))

private:
    bool priv_timed_lock(sync::detail::system_duration dur)
    {
        return priv_timed_lock(sync::detail::system_time_point::now() + dur);
    }

    bool priv_timed_lock(sync::detail::system_time_point const& t)
    {
#if defined(BOOST_SYNC_DETAIL_PTHREAD_HAS_TIMEDLOCK)

        int const res = sync::detail::posix::pthread_mutex_timedlock(&m_mutex, &t.get());

        if (res == 0)
            return true;
        else if (res != ETIMEDOUT)
            BOOST_THROW_EXCEPTION(lock_error(res, "boost: timed_mutex timedlock failed in pthread_mutex_timedlock"));
        return false;

#else // defined(BOOST_SYNC_DETAIL_PTHREAD_HAS_TIMEDLOCK)

        sync::detail::posix::pthread_mutex_lock_guard const local_lock(m_mutex);
        while (m_is_locked)
        {
            int const cond_res = pthread_cond_timedwait(&m_cond, &m_mutex, &t.get());
            if (cond_res == ETIMEDOUT)
                return false;
            else if (cond_res != 0)
                BOOST_THROW_EXCEPTION(lock_error(cond_res, "boost: timed_mutex timedlock failed in pthread_cond_timedwait"));
        }
        m_is_locked = true;
        return true;

#endif // defined(BOOST_SYNC_DETAIL_PTHREAD_HAS_TIMEDLOCK)
    }

    template< typename TimePoint >
    bool priv_timed_lock(sync::detail::chrono_time_point< TimePoint > const& t)
    {
        if (try_lock())
            return true;

        typedef TimePoint time_point;
        typedef typename time_point::clock clock;
        typedef typename time_point::duration duration;
        time_point now = clock::now();
        while (now < t.get())
        {
            if (priv_timed_lock(sync::detail::time_traits< duration >::to_sync_unit(t.get() - now)))
                return true;
            now = clock::now();
        }
        return false;
    }
};

} // namespace posix

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_DETAIL_CONDITION_VARIABLES_CONDITION_VARIABLE_POSIX_HPP_INCLUDED_
