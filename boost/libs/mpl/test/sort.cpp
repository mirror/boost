//-----------------------------------------------------------------------------
// libs mpl/test/sort.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/sort.hpp"

#include "boost/static_assert.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/equal.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list_c<int, 3, 4, 0, -5, 8, -1, 7>::type numbers;
    typedef mpl::list_c<int, -5, -1, 0, 3, 4, 7, 8>::type manual_result;

    typedef mpl::sort< numbers >::type result;

    BOOST_STATIC_ASSERT((mpl::equal< result,manual_result >::type::value));

    return 0;
}
