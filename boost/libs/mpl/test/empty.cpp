//-----------------------------------------------------------------------------
// boost mpl/test/empty.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/empty.hpp"
#include "boost/mpl/list/list10.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list0<> list0;
    typedef mpl::list1<char> list1;
    
    BOOST_STATIC_ASSERT((mpl::empty<list0>::type::value == true));
    BOOST_STATIC_ASSERT((mpl::empty<list1>::type::value == false));

    return 0;
}
