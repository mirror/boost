//-----------------------------------------------------------------------------
// boost mpl/test/aux_/no_has_xxx.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-03
// Aleksey Gurtovoy, Dave Abrahams
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/aux_/has_xxx.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"
#include "boost/static_assert.hpp"

BOOST_MPL_HAS_XXX_TRAIT_DEF(xxx_type)

struct a1;
struct a2 {};
struct a3 { typedef int xxx_type; };
struct a4 { struct xxx_type; };
struct a5 { typedef int& xxx_type; };
struct a6 { typedef int* xxx_type; };
struct a7 { typedef int xxx_type[10]; };
struct a8 { typedef void (*xxx_type)(); };
struct a9 { typedef void (xxx_type)(); };

//
// This file tests that we have the right value for
// BOOST_MPL_NO_AUX_HAS_XXX, and that has_xxx doesn't just fail to
// compile arbitrarily.  Could be used as part of the config tests.
//

#undef FALSE
#undef TRUE
#define FALSE false

#ifdef BOOST_MPL_NO_AUX_HAS_XXX
# define TRUE FALSE
#else
# define TRUE true
#endif

int main()
{
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    BOOST_STATIC_ASSERT(has_xxx_type<int&>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<int*>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<int[]>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<int (*)()>::value == FALSE);
#endif

    BOOST_STATIC_ASSERT(has_xxx_type<int>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<a1>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<a2>::value == FALSE);
    BOOST_STATIC_ASSERT(has_xxx_type<a3>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a4>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a5>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a6>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a7>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a8>::value == TRUE);
    BOOST_STATIC_ASSERT(has_xxx_type<a9>::value == TRUE);

    return 0;
}
