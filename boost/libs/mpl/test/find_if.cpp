//-----------------------------------------------------------------------------
// boost mpl/test/find_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/find_if.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/distance.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;
    typedef mpl::list9<int,char,long,short,char,long,double,float,char>::type types;

    typedef mpl::find_if< types, boost::is_float<_> >::type iter1;
    typedef mpl::find_if< types, boost::is_same<_,long> >::type iter2;
    typedef mpl::find_if< types, boost::is_same<_,void> >::type iter3;

    BOOST_MPL_ASSERT_IS_SAME(iter1::type, double);
    BOOST_MPL_ASSERT_IS_SAME(iter2::type, long);
    BOOST_MPL_ASSERT_IS_SAME(iter3, mpl::end<types>::type);

    typedef mpl::begin<types>::type first;
    BOOST_STATIC_ASSERT((mpl::distance<first,iter1>::type::value == 6));
    BOOST_STATIC_ASSERT((mpl::distance<first,iter2>::type::value == 2));

    return 0;
}
