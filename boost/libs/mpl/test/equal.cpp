//-----------------------------------------------------------------------------
// boost mpl/test/equal.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/equal.hpp"
#include "boost/mpl/list.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<int,float,long,double,char,long,double,float> list1;
    typedef mpl::list<int,float,long,double,char,long,double,float> list2;
    typedef mpl::list<int,float,long,double,char,long,double,short> list3;
    typedef mpl::list<int,float,long,double,char,long,double> list4;

    BOOST_STATIC_ASSERT((mpl::equal<list1,list2>::type::value == true));
    BOOST_STATIC_ASSERT((mpl::equal<list2,list1>::type::value == true));
    BOOST_STATIC_ASSERT((mpl::equal<list2,list3>::type::value == false));
    BOOST_STATIC_ASSERT((mpl::equal<list3,list4>::type::value == false));
    BOOST_STATIC_ASSERT((mpl::equal<list4,list3>::type::value == false));

    return 0;
}
