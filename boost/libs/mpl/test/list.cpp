//-----------------------------------------------------------------------------
// boost mpl/test/list.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/list.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list0<> list0;
    typedef mpl::list1<char> list1;
    typedef mpl::list2<char,long> list2;
    typedef mpl::list9<char,char,char,char,char,char,char,char,char> list9;

    return 0;
}
