// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#if !defined(BOOST_RANGE_DETAIL_MFC_CSTRING_HPP) && defined(BOOST_RANGE_ENABLE_MFC)
#define BOOST_RANGE_DETAIL_MFC_CSTRING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <afx.h> // for CString
#include <boost/range/config.hpp>
#include <boost/range/metafunctions.hpp>

namespace boost
{
    template<>
    struct range_iterator< CString >
    {
        typedef TCHAR* type;
    };

    //
    // Why is this needed?!?
    //
    template<>
    struct range_iterator< const CString >
    {
        typedef TCHAR* type;
    };

    template<>
    struct range_const_iterator< CString >
    {
        typedef const TCHAR* type;
    };

    template<>
    struct range_difference< CString >
    {
        typedef std::ptrdiff_t type;
    };

    template<>
    struct range_size< CString >
    {
        typedef int type;
    };

    template<>
    struct range_value< CString >
    {
        typedef TCHAR type;
    };

    TCHAR* begin( CString& r )
    {
        return r.GetBuffer(0);
    }
        
    const TCHAR* begin( const CString& r )
    {
        return (LPCTSTR)r;
    }

    int size( const CString& r )
    {
        return r.GetLength();
    }
    
    TCHAR* end( CString& r )
    {
        return begin( r ) + size( r );
    }
        
    const TCHAR* end( const CString& r )
    {
        return begin( r ) + size( r );
    }

    // default 'empty()' ok

} // namespace 'boost'

#endif
