//-----------------------------------------------------------------------------
// boost mpl/test/int_c.cpp source file
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

#include "boost/mpl/int_c.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"
#include "boost/preprocessor/repeat.hpp"

#include <cassert>

namespace mpl = boost::mpl;

#define INT_C_TEST(z, i, unused)                                                \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_c<i>::value_type, int); }               \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_c<i>::type, mpl::int_c<i>); }           \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_c<i>::next, mpl::int_c<i+1>); }         \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_c<i>::prior, mpl::int_c<i-1>); }        \
    { BOOST_STATIC_ASSERT(mpl::int_c<i>::value == i); }                         \
    assert(mpl::int_c<i>() == i);
/**/

int main()
{
    BOOST_PP_REPEAT(10, INT_C_TEST, unused)
    return 0;
}
