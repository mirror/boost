//-----------------------------------------------------------------------------
// boost mpl/test/back.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/back.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::range_c<int,0,1> range1;
    typedef mpl::range_c<int,0,10> range2;
    typedef mpl::range_c<int,-10,0> range3;
    
    BOOST_STATIC_ASSERT(mpl::back<range1>::type::value == 0);
    BOOST_STATIC_ASSERT(mpl::back<range2>::type::value == 9);
    BOOST_STATIC_ASSERT(mpl::back<range3>::type::value == -1);

    return 0;
}
