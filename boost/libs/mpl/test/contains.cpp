//-----------------------------------------------------------------------------
// boost mpl/test/contains.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/contains.hpp"
#include "boost/mpl/list.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{    
    typedef mpl::list<int,char,long,short,char,long,double,long>::type types;

    BOOST_STATIC_ASSERT((mpl::contains< types,short >::type::value));
    BOOST_STATIC_ASSERT((!mpl::contains< types,unsigned >::type::value));

    return 0;
}
