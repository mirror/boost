//-----------------------------------------------------------------------------
// boost mpl/test/erase_range.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/erase.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/find.hpp"
#include "boost/mpl/size.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/static_assert.hpp"
#include "boost/config.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<int,char,long,short,unsigned,long,double,long> types;

    typedef mpl::find<types,short>::type iter1;
    typedef mpl::find<types,double>::type iter2;

    typedef mpl::erase<types,iter1,iter2>::type result;
    
    BOOST_STATIC_ASSERT(mpl::size<result>::type::value == 5);

    typedef mpl::find<result,unsigned>::type iter;
    BOOST_MPL_ASSERT_IS_SAME(iter, mpl::end<result>::type);

    return 0;
}
