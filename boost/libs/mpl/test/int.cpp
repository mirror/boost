
// + file: libs/mpl/int.cpp
// + last modified: 12/apr/03

// Copyright (c) 2001-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/int.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"
#include "boost/preprocessor/repeat.hpp"

#include <cassert>

namespace mpl = boost::mpl;

#define INT_C_TEST(unused1, i, unused2) \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_<i>::value_type, int); } \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_<i>::type, mpl::int_<i>); } \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_<i>::next, mpl::int_<i+1>); } \
    { BOOST_MPL_ASSERT_IS_SAME(mpl::int_<i>::prior, mpl::int_<i-1>); } \
    { BOOST_STATIC_ASSERT(mpl::int_<i>::value == i); } \
    assert(mpl::int_<i>() == i); \
/**/

int main()
{
    BOOST_PP_REPEAT(10, INT_C_TEST, unused)
    return 0;
}
