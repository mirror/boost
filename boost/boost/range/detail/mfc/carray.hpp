// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#if !defined( BOOST_RANGE_DETAIL_MFC_CARRAY_HPP ) && defined( BOOST_RANGE_ENABLE_MCF_CARRAY ) 
#define BOOST_RANGE_DETAIL_MFC_CARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <afxtempl.h> // for CArray
#include <boost/range/config.hpp>
#include <boost/range/metafunctions.hpp>

namespace boost
{
    template< class T, class U >
    struct range_iterator< CArray<T,U> >
    {
        typedef T* type;
    };

    //
    // Why is this needed?!?
    //
    template< class T, class U >
    struct range_iterator< const CArray<T,U> >
    {
        typedef T* type;
    };

    template< class T, class U >
    struct range_const_iterator< CArray<T,U> >
    {
        typedef const T* type;
    };
    
    template< class T, class U >
    struct range_difference< CArray<T,U> >
    {
        typedef std::ptrdiff_t type;
    };
    
    template< class T, class U >
    struct range_size< CArray<T,U> >
    {
        typedef int type;
    };

    template< class T, class U >
    struct range_value< CArray<T,U> >
    {
        typedef T type;
    };

    template< class T, class U >
    T* begin( CArray<T,U>& r )
    {
        return r.GetData();
    }
        
    template< class T, class U >
    const T* begin( const CArray<T,U>& r )
    {
        return r.GetData();
    }

    template< class T, class U >
    int size( const CArray<T,U>& r )
    {
        return r.GetSize();
    }
    
    template< class T, class U >
    T* end( CArray<T,U>& r )
    {
        return begin( r ) + size( r );
    }
        
    template< class T, class U >
    const T* end( const CArray<T,U>& r )
    {
        return begin( r ) + size( r );
    }

    // default 'empty()' ok

} // namespace 'boost'

#endif
