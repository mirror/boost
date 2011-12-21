#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED

//
//  detail/sp_counted_base_aix.hpp
//   based on: detail/sp_counted_base_w32.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//  Copyright 2006 Michael van der Westhuizen
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <boost/detail/sp_typeinfo.hpp>
#include <sys/atomic_op.h>

namespace boost
{

namespace detail
{

class sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int32_t use_count_;        // #shared
    int32_t weak_count_;       // #weak + (#shared != 0)

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

    virtual void * get_deleter( sp_typeinfo const & ti ) = 0;

    void add_ref_copy()
    {
        fetch_and_add( &use_count_, 1 );
    }

    bool add_ref_lock() // true on success
    {
        int32_t tmp = fetch_and_add( &use_count_, 0 );
        for( ;; )
        {
            if( tmp == 0 ) return false;
            if( compare_and_swap( &use_count_, &tmp, tmp + 1 ) ) return true;
        }
    }

    void release() // nothrow
    {
        if( fetch_and_add( &use_count_, -1 ) == 1 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        fetch_and_add( &weak_count_, 1 );
    }

    void weak_release() // nothrow
    {
        if( fetch_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return fetch_and_add( const_cast<int32_t*>(&use_count_), 0 );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED
