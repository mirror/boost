// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_CONFIG_HPP
#define BOOST_RANGE_CONFIG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>

#ifdef BOOST_CT_DEDUCED_TYPENAME
#error "macro already defined!"
#endif

#ifdef __BORLANDC__
#define BOOST_CT_DEDUCED_TYPENAME
#else
#define BOOST_CT_DEDUCED_TYPENAME BOOST_DEDUCED_TYPENAME
#endif

#ifdef BOOST_CT_NO_ARRAY_SUPPORT
#error "macro already defined!"
#endif

#if _MSC_VER <= 1200 && !defined( __COMO__ ) && !defined( _GNUC_ )
#define BOOST_CT_NO_ARRAY_SUPPORT
#endif

#ifdef BOOST_CT_NO_ARRAY_SUPPORT
#define BOOST_ARRAY_REF (array)
#define BOOST_CT_NO_STATIC_ASSERT
#else
#define BOOST_ARRAY_REF (&array)
#endif



#endif

