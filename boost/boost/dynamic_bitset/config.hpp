// --------------------------------------------------
//
// (C) Copyright Chuck Allison and Jeremy Siek 2001 - 2002.
// (C) Copyright Gennaro Prota                 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

//  See http://www.boost.org/libs/dynamic_bitset for documentation.


#ifndef BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424
#define BOOST_DYNAMIC_BITSET_CONFIG_HPP_GP_20040424

#include "boost/config.hpp"
#include "boost/detail/workaround.hpp"

// support for pre 3.0 libstdc++ - thanks Phil Edwards!
#if defined (__STL_CONFIG_H) && !defined (__STL_USE_NEW_IOSTREAMS)
# define BOOST_OLD_IOSTREAMS
#endif

// this should be in the config system some day
// see http://lists.boost.org/MailArchives/boost/msg62291.php
#define BOOST_DYNAMIC_BITSET_GNUC_VERSION  (  __GNUC__       * 100 * 100     \
                                            + __GNUC_MINOR__ * 100)

// workaround for gcc bug c++/8419 - gps
#if defined(__GNUC__) && BOOST_WORKAROUND(BOOST_DYNAMIC_BITSET_GNUC_VERSION, \
                                          BOOST_TESTED_AT(30300))
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) ((void)0, expr)
#else
# define BOOST_DYNAMIC_BITSET_WRAP_CONSTANT(expr) (expr)
#endif

//
#if (defined __BORLANDC__ && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564)))  \
                             || (defined BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS
#endif

// if we can't use friends then private members are exposed
//
#if defined(BOOST_DYNAMIC_BITSET_DONT_USE_FRIENDS)
#define BOOST_DYNAMIC_BITSET_PRIVATE public
#else
#define BOOST_DYNAMIC_BITSET_PRIVATE private
#endif


#endif // include guard
