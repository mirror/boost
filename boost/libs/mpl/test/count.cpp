//-----------------------------------------------------------------------------
// boost mpl/test/count.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/count.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/int.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<int,char,long,short,char,long,double,long> types;
    typedef mpl::list_c<int,1,0,5,1,7,5,0,5> values;

    BOOST_STATIC_ASSERT((mpl::count<types,int>::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::count<types,double>::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::count<types,char>::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::count<types,long>::type::value == 3));
    BOOST_STATIC_ASSERT((mpl::count<types,unsigned>::type::value == 0));
    
    BOOST_STATIC_ASSERT((mpl::count< values, mpl::integral_c<int,1> >::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::count< values, mpl::integral_c<int,0> >::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::count< values, mpl::integral_c<int,5> >::type::value == 3));
    BOOST_STATIC_ASSERT((mpl::count< values, mpl::integral_c<int,7> >::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::count< values, mpl::integral_c<int,8> >::type::value == 0));
    
    return 0;
}
