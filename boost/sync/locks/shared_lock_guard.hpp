/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   locks/shared_lock_guard.hpp
 *
 * \brief  This header defines an exclusive lock guard.
 */

#ifndef BOOST_SYNC_LOCKS_SHARED_LOCK_GUARD_HPP_INCLUDED_
#define BOOST_SYNC_LOCKS_SHARED_LOCK_GUARD_HPP_INCLUDED_

#include <boost/sync/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/sync/locks/lock_options.hpp>

#include <boost/sync/detail/header.hpp>

namespace boost {

namespace sync {

/*!
 * \brief A shared lock scope guard
 */
template< typename MutexT >
class shared_lock_guard
{
private:
    MutexT& m_mutex;

public:
    typedef MutexT mutex_type;

public:
    explicit shared_lock_guard(mutex_type& m) : m_mutex(m)
    {
        m.lock_shared();
    }

    shared_lock_guard(mutex_type& m, adopt_lock_t) : m_mutex(m)
    {
    }

    ~shared_lock_guard()
    {
        m_mutex.unlock_shared();
    }

    BOOST_DELETED_FUNCTION(shared_lock_guard(shared_lock_guard const&))
    BOOST_DELETED_FUNCTION(shared_lock_guard& operator= (shared_lock_guard const&))
};

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_LOCKS_SHARED_LOCK_GUARD_HPP_INCLUDED_
