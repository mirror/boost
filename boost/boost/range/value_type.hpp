// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_VALUE_TYPE_HPP
#define BOOST_RANGE_VALUE_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/detail/value_type.hpp>
#else

#include <boost/iterator/iterator_traits.hpp>
#include <cstddef>
#include <utility>


namespace boost
{
    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    template< typename C >
    struct value_type_of
    {
        typedef BOOST_DEDUCED_TYPENAME C::value_type type;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    struct value_type_of< std::pair<Iterator,Iterator> >
    {
        typedef BOOST_DEDUCED_TYPENAME 
            iterator_value<Iterator>::type type;
    };
    
    
    template< typename Iterator >
    struct value_type_of< const std::pair<Iterator,Iterator> >
    {
        typedef BOOST_DEDUCED_TYPENAME 
            iterator_value<Iterator>::type type;
    };

    //////////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////////

    template< typename T, std::size_t sz >
    struct value_type_of< T[sz] >
    {
        typedef T type;
    };

    template< typename T, std::size_t sz >
    struct value_type_of< const T[sz] >
    {
        typedef const T type;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////////

    template<>
    struct value_type_of< char* >
    {
        typedef char type;
    };

    template<>
    struct value_type_of< wchar_t* >
    {
        typedef wchar_t type;
    };

    template<>
    struct value_type_of< const char* >
    {
        typedef const char type;
    };

    template<>
    struct value_type_of< const wchar_t* >
    {
        typedef const wchar_t type;
    };

} // namespace boost

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif
