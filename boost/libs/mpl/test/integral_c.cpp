//-----------------------------------------------------------------------------
// boost mpl/test/integral_c.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"
#include "boost/preprocessor/repeat.hpp"

#include <cassert>

namespace mpl = boost::mpl;

#define INTEGRAL_C_TEST(z, i, T)                                \
    {                                                           \
        typedef mpl::integral_c<T,i> c##i;                      \
        typedef mpl::integral_c<T,i+1> next_c##i;               \
        typedef mpl::integral_c<T,i-1> prior_c##i;              \
        { BOOST_MPL_ASSERT_IS_SAME(c##i::value_type, T); }      \
        { BOOST_MPL_ASSERT_IS_SAME(c##i::type, c##i); }         \
        { BOOST_MPL_ASSERT_IS_SAME(c##i::next, next_c##i); }    \
        { BOOST_MPL_ASSERT_IS_SAME(c##i::prior, prior_c##i); }  \
        { BOOST_STATIC_ASSERT(c##i::value == i); }              \
        assert(c##i() == i);                                    \
    }
/**/

int main()
{
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, char)
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, short)
    BOOST_PP_REPEAT(10, INTEGRAL_C_TEST, int)
    return 0;
}
