//-----------------------------------------------------------------------------
// boost mpl/test/upper_bound.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/upper_bound.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/int.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list_c<int,1,2,3,3,3,5,8> numbers;
    typedef mpl::upper_bound< numbers, mpl::int_<3> >::type iter;
    BOOST_STATIC_ASSERT((mpl::distance< mpl::begin<numbers>::type,iter >::type::value == 5));
    BOOST_STATIC_ASSERT(iter::type::value == 5);
    return 0;
}
