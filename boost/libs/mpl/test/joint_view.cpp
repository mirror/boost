
// + file: libs/mpl/test/joint_view.cpp
// + last modified: 25/may/03

// Copyright (c) 2001-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/joint_view.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/size.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::joint_view<
          mpl::range_c<int,0,10>
        , mpl::range_c<int,10,15>
        > numbers;

    typedef mpl::range_c<int,0,15> answer;

    BOOST_STATIC_ASSERT((mpl::equal<numbers,answer>::type::value));
    BOOST_STATIC_ASSERT((mpl::size<numbers>::value == 15));

    return 0;
}
