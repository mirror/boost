//-----------------------------------------------------------------------------
// boost mpl/test/size.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/size.hpp"
#include "boost/mpl/list.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list<> empty_list;
    typedef mpl::list<char,short,int,long> list;
    
    BOOST_STATIC_ASSERT((mpl::size<empty_list>::type::value == 0));
    BOOST_STATIC_ASSERT((mpl::size<list>::type::value == 4));

    return 0;
}
