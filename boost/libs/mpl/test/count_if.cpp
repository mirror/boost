//-----------------------------------------------------------------------------
// boost mpl/test/count_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/count_if.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/type_traits/is_float.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;
    typedef mpl::list<int,char&,long,short,char&,long,double,long> types;
    typedef mpl::list_c<int,1,0,5,1,7,5,0,5> values;
    
    BOOST_STATIC_ASSERT((mpl::count_if< types, boost::is_float<_> >::type::value == 1));
    BOOST_STATIC_ASSERT((mpl::count_if< types, boost::is_same<_,char&> >::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::count_if< types, boost::is_same<_,void*> >::type::value == 0));

    BOOST_STATIC_ASSERT((mpl::count_if< values, mpl::lt<5> >::type::value == 4));
    BOOST_STATIC_ASSERT((mpl::count_if< values, mpl::eq<0>  >::type::value == 2));
    BOOST_STATIC_ASSERT((mpl::count_if< values, mpl::eq<-1> >::type::value == 0));
    
    return 0;
}
