//-----------------------------------------------------------------------------
// boost mpl/test/replace_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy and John R. Bandela
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/replace_if.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/greater.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;
    typedef mpl::list_c<int,1,4,5,2,7,5,3,5>::type numbers;
    typedef mpl::replace_if< numbers, mpl::gt<4>, mpl::int_<0> >::type result;

    typedef mpl::list_c<int,1,4,0,2,0,0,3,0>::type answer;
    BOOST_STATIC_ASSERT((mpl::equal< answer,result,mpl::equal_to<_,_> >::type::value));

    return 0;
}
