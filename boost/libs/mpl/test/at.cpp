//-----------------------------------------------------------------------------
// boost mpl/test/at.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/at.hpp"
#include "boost/mpl/vector/vector10_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::vector10_c<int,9,8,7,6,5,4,3,2,1,0> numbers;

    BOOST_STATIC_ASSERT((mpl::at_c<numbers,0>::type::value == 9));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,1>::type::value == 8));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,2>::type::value == 7));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,3>::type::value == 6));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,4>::type::value == 5));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,5>::type::value == 4));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,6>::type::value == 3));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,7>::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,8>::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::at_c<numbers,9>::type::value == 0));

    return 0;
}
