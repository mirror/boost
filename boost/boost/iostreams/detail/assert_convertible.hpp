// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ASSERT_CONVERTIBLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ASSERT_CONVERTIBLE_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              
       
#include <boost/static_assert.hpp>        
#include <boost/type_traits/is_convertible.hpp> 

#define BOOST_IOSTREAMS_ASSERT_CONVERTIBLE(src, tgt) \
    BOOST_STATIC_ASSERT((boost::is_convertible<src, tgt>::value)) \
    /**/

#define BOOST_IOSTREAMS_ASSERT_NOT_CONVERTIBLE(src, tgt) \
    BOOST_STATIC_ASSERT((!boost::is_convertible<src, tgt>::value)) \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ASSERT_CONVERTIBLE_HPP_INCLUDED
