//-----------------------------------------------------------------------------
// boost mpl/test/list_c.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/list_c.hpp"
#include "boost/mpl/front.hpp"
#include "boost/mpl/size.hpp"
#include "boost/static_assert.hpp"
#include "boost/config.hpp"

namespace mpl = boost::mpl;

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)
void test_bool_list()
{
    typedef mpl::list_c<bool,true>::type list1;
    typedef mpl::list_c<bool,false>::type list2;

    BOOST_STATIC_ASSERT(mpl::front<list1>::type::value == true);
    BOOST_STATIC_ASSERT(mpl::front<list2>::type::value == false);
}
#endif

void test_int_list()
{
    typedef mpl::list_c<int,-1>::type list1;
    typedef mpl::list_c<int,0,1>::type list2;
    typedef mpl::list_c<int,1,2,3>::type list3;

    BOOST_STATIC_ASSERT(mpl::size<list1>::type::value == 1);
    BOOST_STATIC_ASSERT(mpl::size<list2>::type::value == 2);
    BOOST_STATIC_ASSERT(mpl::size<list3>::type::value == 3);
    BOOST_STATIC_ASSERT(mpl::front<list1>::type::value == -1);
    BOOST_STATIC_ASSERT(mpl::front<list2>::type::value == 0);
    BOOST_STATIC_ASSERT(mpl::front<list3>::type::value == 1);
}

void test_unsigned_list()
{
    typedef mpl::list_c<unsigned,0>::type list1;
    typedef mpl::list_c<unsigned,1,2>::type list2;

    BOOST_STATIC_ASSERT(mpl::size<list1>::type::value == 1);
    BOOST_STATIC_ASSERT(mpl::size<list2>::type::value == 2);
    BOOST_STATIC_ASSERT(mpl::front<list1>::type::value == 0);
    BOOST_STATIC_ASSERT(mpl::front<list2>::type::value == 1);
}

int main()
{
    return 0;
}
