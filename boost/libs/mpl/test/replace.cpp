//-----------------------------------------------------------------------------
// boost mpl/test/replace.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy and John R. Bandela
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/replace.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<int,float,char,float,float,double>::type types;
    typedef mpl::replace< types,float,double >::type result;

    typedef mpl::list<int,double,char,double,double,double>::type answer;
    BOOST_STATIC_ASSERT((mpl::equal< result,answer >::type::value));

    return 0;
}
