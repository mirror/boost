
#ifndef BOOST_MPL_AUX_TEST_DATA_HPP_INCLUDED
#define BOOST_MPL_AUX_TEST_DATA_HPP_INCLUDED

// + file: boost/mpl/aux_/test/data.hpp
// + last modified: 04/may/03

// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/noncopyable.hpp"

struct UDT {};
struct incomplete;
class abstract { virtual ~abstract() = 0; };
using boost::noncopyable;

// to do: add function types for compilers that are able to handle them
// (T ())(T (int))(void (T))(T (T)) 
//    (T[10])(T const[10])(T volatile[10])(T const volatile[10])
//    (T (*)())(T (* const)())(T (* volatile)())(T (* const volatile)())
//    (T (*)(int))(void (*)(T))(T (*)(T))

#define CTT_basic_modifiers( T ) \
    (T const)(T volatile)(T const volatile) \
    (T&)(T const&)(T volatile&)(T const volatile&) \
    (T*)(T const*)(T volatile*)(T const volatile*) \
/**/

#define CTT_basic_types() \
    (bool)(char)(int)(UDT)(incomplete)(noncopyable)(abstract) \
/**/

#endif // BOOST_MPL_AUX_TEST_DATA_HPP_INCLUDED
