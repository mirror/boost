#ifndef BOOST_DETAIL_SP_COUNTED_BASE_HPP_INCLUDED
#define BOOST_DETAIL_SP_COUNTED_BASE_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>
#include <boost/detail/lightweight_mutex.hpp>

#include <typeinfo>

namespace boost
{

namespace detail
{

class sp_counted_base
{
private:

    typedef detail::lightweight_mutex mutex_type;

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

#if defined(BOOST_HAS_THREADS) || defined(BOOST_LWM_WIN32)
    mutable mutex_type mtx_;
#endif

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( std::type_info const & ti ) = 0;

    void add_ref_copy()
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++use_count_;
    }

    bool add_ref_lock() // true on success
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        if( use_count_ == 0 ) return false;
        ++use_count_;
        return true;
    }

    void release() // nothrow
    {
        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            long new_use_count = --use_count_;

            if( new_use_count != 0 ) return;
        }

        dispose();
        weak_release();
    }

    void weak_add_ref() // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        ++weak_count_;
    }

    void weak_release() // nothrow
    {
        long new_weak_count;

        {
#if defined(BOOST_HAS_THREADS)
            mutex_type::scoped_lock lock(mtx_);
#endif
            new_weak_count = --weak_count_;
        }

        if( new_weak_count == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
#if defined(BOOST_HAS_THREADS)
        mutex_type::scoped_lock lock(mtx_);
#endif
        return use_count_;
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_SP_COUNTED_BASE_HPP_INCLUDED
