//-----------------------------------------------------------------------------
// boost mpl/test/pop_front.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/pop_front.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<long>::type types1;
    typedef mpl::list<int,long>::type types2;
    typedef mpl::list<char,int,long>::type types3;

    typedef mpl::pop_front<types1>::type result1;
    typedef mpl::pop_front<types2>::type result2;
    typedef mpl::pop_front<types3>::type result3;
    
    BOOST_STATIC_ASSERT(mpl::size<result1>::type::value == 0);
    BOOST_STATIC_ASSERT(mpl::size<result2>::type::value == 1);
    BOOST_STATIC_ASSERT(mpl::size<result3>::type::value == 2);
    
    BOOST_MPL_ASSERT_IS_SAME(mpl::front<result2>::type, long);
    BOOST_MPL_ASSERT_IS_SAME(mpl::front<result3>::type, int);

    return 0;
}
