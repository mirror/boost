// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_EMPTY_HPP
#define BOOST_RANGE_EMPTY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>
#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#include <boost/range/detail/empty.hpp>
#else

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost 
{ 
namespace range 
{

        //////////////////////////////////////////////////////////////////////
        // primary template
        //////////////////////////////////////////////////////////////////////

        template< typename C >
        inline bool empty( const C& c )
        {
            return begin( c ) == end( c );
        }

        //////////////////////////////////////////////////////////////////////
        // string
        //////////////////////////////////////////////////////////////////////

        inline bool empty( const char* s )
        {
            return s == 0 || s[0] == 0;
        }

        inline bool empty( const wchar_t* s )
        {
            return s == 0 || s[0] == 0;
        }
        
} // namespace 'range'

template< class T >
inline bool empty( const T& r )
{
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))        
    using range::empty;
    return empty( r );
#else
    return range::empty( r );
#endif
}

} // namepace 'boost'

#endif //  BOOST_NO_FUNCTION_TEMPLATE_ORDERING

#endif
