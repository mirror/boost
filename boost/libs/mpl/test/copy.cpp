//-----------------------------------------------------------------------------
// boost mpl/test/copy.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/copy.hpp"
#include "boost/mpl/vector/vector10_c.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;
using mpl::_;

int main()
{
    typedef mpl::vector10_c<int,9,8,7,6,5,4,3,2,1,0> answer;
    typedef mpl::copy<
          mpl::range_c<int,0,10>
        , mpl::vector<>
        , mpl::push_front<_,_>
        >::type result;

    BOOST_STATIC_ASSERT(mpl::size<result>::value == 10);
    BOOST_STATIC_ASSERT((mpl::equal< result,answer >::type::value));

    return 0;
}
