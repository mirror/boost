//-----------------------------------------------------------------------------
// boost mpl/test/front.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/front.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<long>::type types1;
    typedef mpl::list<int,long>::type types2;
    typedef mpl::list<char,int,long>::type types3;

    BOOST_MPL_ASSERT_IS_SAME(mpl::front<types1>::type, long);
    BOOST_MPL_ASSERT_IS_SAME(mpl::front<types2>::type, int);
    BOOST_MPL_ASSERT_IS_SAME(mpl::front<types3>::type, char);

    typedef mpl::list_c<int,1>::type values1;
    typedef mpl::list_c<int,2,1>::type values2;
    typedef mpl::list_c<int,3,2,1>::type values3;

    BOOST_STATIC_ASSERT(mpl::front<values1>::type::value == 1);
    BOOST_STATIC_ASSERT(mpl::front<values2>::type::value == 2);
    BOOST_STATIC_ASSERT(mpl::front<values3>::type::value == 3);

    return 0;
}
