//-----------------------------------------------------------------------------
// boost mpl/test/copy_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/copy_if.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/size.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;
using mpl::_;

int main()
{
    typedef mpl::list_c<int,0,1,2,3,4,5,6,7,8,9>::type numbers;
    typedef mpl::list_c<int,4,3,2,1,0>::type answer;
    typedef mpl::copy_if<
          numbers
        , mpl::list0_c<int>
        , mpl::push_front<_,_>
        , mpl::less<_,mpl::int_<5> >
        >::type result;

    BOOST_STATIC_ASSERT(mpl::size<result>::value == 5);
    BOOST_STATIC_ASSERT((mpl::equal<result,answer>::type::value));

    return 0;
}
