//-----------------------------------------------------------------------------
// boost mpl/test/bool_c.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"

#include <cassert>

namespace mpl = boost::mpl;

#define BOOL_C_TEST(c) \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::bool_c<c>::value_type, bool); } \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::bool_c<c>, mpl::c##_c); } \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::bool_c<c>::type, mpl::bool_c<c>); } \
    { BOOST_STATIC_ASSERT(mpl::bool_c<c>::value == c); } \
    assert(mpl::bool_c<c>() == c); \
/**/

int main()
{
    BOOL_C_TEST(true)
    BOOL_C_TEST(false)
    return 0;
}
