//-----------------------------------------------------------------------------
// boost mpl/test/at.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/at.hpp"
#include "boost/mpl/vector/vector10_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::vector10_c<int,9,8,7,6,5,4,3,2,1,0> numbers;

    BOOST_STATIC_ASSERT((mpl::at_c<0, numbers>::type::value == 9));
    BOOST_STATIC_ASSERT((mpl::at_c<1, numbers>::type::value == 8));
    BOOST_STATIC_ASSERT((mpl::at_c<2, numbers>::type::value == 7));
    BOOST_STATIC_ASSERT((mpl::at_c<3, numbers>::type::value == 6));
    BOOST_STATIC_ASSERT((mpl::at_c<4, numbers>::type::value == 5));
    BOOST_STATIC_ASSERT((mpl::at_c<5, numbers>::type::value == 4));
    BOOST_STATIC_ASSERT((mpl::at_c<6, numbers>::type::value == 3));
    BOOST_STATIC_ASSERT((mpl::at_c<7, numbers>::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::at_c<8, numbers>::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::at_c<9, numbers>::type::value == 0));

    return 0;
}
