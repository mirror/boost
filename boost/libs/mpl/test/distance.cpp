//-----------------------------------------------------------------------------
// boost mpl/test/distance.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/distance.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

void list_distance_test()
{
    typedef mpl::list<char,short,int,long>::type list;
    typedef mpl::begin<list>::type first;
    typedef mpl::end<list>::type last;
    
    BOOST_STATIC_ASSERT((mpl::distance<first,last>::type::value == 4));
}

void range_distance_test()
{
    typedef mpl::range_c<int,0,10>::type range;
    typedef mpl::begin<range>::type first;
    typedef mpl::end<range>::type last;
    
    BOOST_STATIC_ASSERT((mpl::distance<first,last>::type::value == 10));
}

int main()
{
    return 0;
}
