// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_CONST_ITERATOR_HPP
#define BOOST_RANGE_CONST_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/config.hpp>

#ifdef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/range/detail/const_iterator.hpp>
#else

#include <cstddef>
#include <utility>

namespace boost
{
    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    template< typename C >
    struct const_iterator_of
    {
        typedef BOOST_DEDUCED_TYPENAME C::const_iterator type;
    };
    
    //////////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    struct const_iterator_of< std::pair<Iterator,Iterator> >
    {
        typedef Iterator type;
    };
    
    template< typename Iterator >
    struct const_iterator_of< const std::pair<Iterator,Iterator> >
    {
        typedef Iterator type;
    };

    //////////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////////

    template< typename T, std::size_t sz >
    struct const_iterator_of< T[sz] >
    {
        typedef const T* type;
    };

    template< typename T, std::size_t sz >
    struct const_iterator_of< const T[sz] >
    {
        typedef const T* type;
    };

    //////////////////////////////////////////////////////////////////////////
    // string
    //////////////////////////////////////////////////////////////////////////

    template<>
    struct const_iterator_of< char* >
    {
        typedef const char* type;
    };

    template<>
    struct const_iterator_of< wchar_t* >
    {
        typedef const wchar_t* type;
    };

    template<>
    struct const_iterator_of< const char* >
    {
        typedef const char* type;
    };

    template<>
    struct const_iterator_of< const wchar_t* >
    {
        typedef const wchar_t* type;
    };

} // namespace boost

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif
