// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_BEGIN_HPP
#define BOOST_RANGE_BEGIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>

#ifdef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
#include <boost/range/detail/begin.hpp>
#else

#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

namespace boost 
{
namespace range 
{
    
    //////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////
    
    template< typename C >
    inline BOOST_DEDUCED_TYPENAME const_iterator_of<C>::type
    begin( const C& c )
    {
        return c.begin(); 
    }
    
    template< typename C >
    inline BOOST_DEDUCED_TYPENAME iterator_of<C>::type
    begin( C& c )
    {
        return c.begin(); 
    }
    
    //////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////
    
    template< typename Iterator >
    inline Iterator begin( const std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }
    
    template< typename Iterator >
    inline Iterator begin( std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }
    
    //////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////
    
    template< typename T, std::size_t sz >
    inline const T* begin( const T (&array)[sz] )
    {
        return array;
    }
    
    template< typename T, std::size_t sz >
    inline T* begin( T (&array)[sz] )
    {
        return array;
    }
    
    
    //////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////
    
    inline const char* begin( const char* s )
    {
        return s;
    }
    
    inline char* begin( char* s )
    {
        return s;
    }
    
    inline const wchar_t* begin( const wchar_t* s )
    {
        return s;
    }
    
    inline wchar_t* begin( wchar_t* s )
    {
        return s;
    }

} // namespace 'range'

using range::begin;

} // namespace boost

#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING    

#endif
