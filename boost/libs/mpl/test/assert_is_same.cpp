//-----------------------------------------------------------------------------
// boost mpl/test/assert_is_same.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/assert_is_same.hpp"

namespace {
struct my;
}

int main()
{
    BOOST_MPL_ASSERT_IS_SAME(long, long);
    BOOST_MPL_ASSERT_IS_SAME(my, my);

    BOOST_MPL_ASSERT_NOT_SAME(my, long);
    BOOST_MPL_ASSERT_NOT_SAME(long, my);

    return 0;
}
