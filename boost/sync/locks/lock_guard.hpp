/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007 Anthony Williams
 * (C) Copyright 2011-2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   locks/lock_guard.hpp
 *
 * \brief  This header defines an exclusive lock guard.
 */

#ifndef BOOST_SYNC_LOCKS_LOCK_GUARD_HPP_INCLUDED_
#define BOOST_SYNC_LOCKS_LOCK_GUARD_HPP_INCLUDED_

#include <boost/sync/detail/config.hpp>
#if !defined(BOOST_SYNC_AUX_NO_CXX11_INITIALIZER_LISTS)
#include <initializer_list>
#include <boost/sync/detail/lockable_wrapper.hpp>
#endif
#include <boost/sync/locks/lock_options.hpp>

#include <boost/sync/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace sync {

/*!
 * \brief A unique lock scope guard
 */
template< typename MutexT >
class lock_guard
{
private:
    MutexT& m_mutex;

public:
    typedef MutexT mutex_type;

public:
    explicit lock_guard(mutex_type& m) : m_mutex(m)
    {
        m.lock();
    }

    lock_guard(mutex_type& m, adopt_lock_t) : m_mutex(m)
    {
    }

#if !defined(BOOST_SYNC_AUX_NO_CXX11_INITIALIZER_LISTS)

    lock_guard(std::initializer_list< aux::lockable_wrapper< mutex_type > > l) :
        m_mutex(*(l.begin()->m_mutex))
    {
        m_mutex.lock();
    }

    lock_guard(std::initializer_list< aux::lockable_wrapper< mutex_type, adopt_lock_t > > l) :
        m_mutex(*(l.begin()->m_mutex))
    {
    }

#endif // BOOST_SYNC_AUX_NO_CXX11_INITIALIZER_LISTS

    ~lock_guard()
    {
        m_mutex.unlock();
    }

    BOOST_DELETED_FUNCTION(lock_guard(lock_guard const&))
    BOOST_DELETED_FUNCTION(lock_guard& operator= (lock_guard const&))
};

#if !defined(BOOST_SYNC_AUX_NO_CXX11_INITIALIZER_LISTS)

template< typename LockableT >
inline lock_guard< LockableT > make_lock_guard(LockableT& mtx)
{
    return { aux::lockable_wrapper< LockableT >(mtx) };
}
template< typename LockableT >
inline lock_guard< LockableT > make_lock_guard(LockableT& mtx, adopt_lock_t)
{
    return { aux::lockable_wrapper< LockableT, adopt_lock_t >(mtx) };
}

#endif // BOOST_SYNC_AUX_NO_CXX11_INITIALIZER_LISTS

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_LOCKS_LOCK_GUARD_HPP_INCLUDED_
