//-----------------------------------------------------------------------------
// boost mpl/test/copy_backward.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/copy_backward.hpp"
#include "boost/mpl/list/list10_c.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;

    typedef mpl::list10_c<int,10,11,12,13,14,15,16,17,18,19>::type numbers;
    typedef mpl::copy_backward<
          mpl::range_c<int,0,10>
        , numbers
        , mpl::push_front<_,_>
        >::type result;

    BOOST_STATIC_ASSERT(mpl::size<result>::value == 20);
    BOOST_STATIC_ASSERT((mpl::equal< result,mpl::range_c<int,0,20> >::type::value));

    return 0;
}
