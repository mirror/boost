//-----------------------------------------------------------------------------
// boost mpl/test/vector.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/vector.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::vector0<> vector0;
    typedef mpl::vector1<char> vector1;
    typedef mpl::vector2<char,long> vector2;
    typedef mpl::vector9<char,char,char,char,char,char,char,char,char> vector9;

    return 0;
}
