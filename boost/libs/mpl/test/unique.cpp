//-----------------------------------------------------------------------------
// boost mpl/test/unique.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/unique.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    using namespace mpl::placeholders;
    typedef mpl::list<int,float,float,char,int,int,int,double>::type types;
    typedef mpl::unique<types>::type result;

    typedef mpl::list<int,float,char,int,double>::type answer;
    BOOST_STATIC_ASSERT((mpl::equal< result,answer >::type::value));

    return 0;
}
