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
#include <boost/range/difference_type.hpp>

namespace boost
{
    struct iterator_of< CString >
    {
        typedef TCHAR* type;
    };
    
    struct const_iterator_of< CString >
    {
        typedef const TCHAR* type;
    };
    
    struct difference_type_of< CString >
    {
        typedef std::ptrdiff_t type;
    };
    
    struct size_type_of< CString >
    {
        typedef int type;
    };

    struct value_type_of< CString >
    {
        typedef TCHAR type;
    };

    TCHAR* begin( CString& r )
    {
        return &r[0];
    }
        
    const TCHAR* begin( const CString& r )
    {
        return &r[0];
    }

    int size( const CString& r )
    {
        return r.GetLength();
    }
    
    T* end( CString& r )
    {
        return begin( r ) + size( r );
    }
        
    const T* end( const CString& r )
    {
        return begin( r ) + size( r );
    }

    // default 'empty()' ok

} // namespace 'boost'

#endif
