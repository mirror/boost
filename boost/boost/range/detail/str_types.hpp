// Boost.Range library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DETAIL_STR_TYPES_HPP
#define BOOST_RANGE_DETAIL_STR_TYPES_HPP

#include <boost/range/size_type.hpp>
#include <boost/range/iterator.hpp>

namespace boost
{
    template<>
    struct range_iterator<char*>
    {
        typedef char* type;
    };

    template<>
    struct range_iterator<char* const>
    {
        typedef char* type;
    };
    
    template<>
    struct range_iterator<const char*>
    {
        typedef const char* type;
    };

    template<>
    struct range_iterator<const char* const>
    {
        typedef const char* type;
    };

    template<>
    struct range_iterator<wchar_t*>
    {
        typedef wchar_t* type;
    };

    template<>
    struct range_iterator<wchar_t* const>
    {
        typedef wchar_t* type;
    };

    template<>
    struct range_iterator<const wchar_t*>
    {
        typedef const wchar_t* type;
    };

    template<>
    struct range_iterator<const wchar_t* const>
    {
        typedef const wchar_t* type;
    };

    template<>
    struct range_size<char*>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<char* const>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<const char*>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<const char* const>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<wchar_t*>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<wchar_t* const>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<const wchar_t*>
    {
        typedef std::size_t type;
    };

    template<>
    struct range_size<const wchar_t* const>
    {
        typedef std::size_t type;
    };


}

#endif
