//-----------------------------------------------------------------------------
// boost mpl/test/next.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/next.hpp"
#include "boost/mpl/prior.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/assert_is_same.hpp"

namespace mpl = boost::mpl;
    
int main()
{
    typedef mpl::int_<0> _0;
    typedef mpl::int_<1> _1;
    typedef mpl::int_<2> _2;

    BOOST_MPL_ASSERT_IS_SAME(mpl::next<_0>::type, _1);
    BOOST_MPL_ASSERT_IS_SAME(mpl::next<_1>::type, _2);
    BOOST_MPL_ASSERT_IS_SAME(mpl::prior<_1>::type, _0);
    BOOST_MPL_ASSERT_IS_SAME(mpl::prior<_2>::type, _1);

    return 0;
}
