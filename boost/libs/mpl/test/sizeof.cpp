//-----------------------------------------------------------------------------
// boost mpl/test/sizeof.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/sizeof.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct my
{
    char a[100];
};

int main()
{
    BOOST_STATIC_ASSERT(mpl::sizeof_<char>::type::value == sizeof(char));
    BOOST_STATIC_ASSERT(mpl::sizeof_<int>::type::value == sizeof(int));
    BOOST_STATIC_ASSERT(mpl::sizeof_<double>::type::value == sizeof(double));
    BOOST_STATIC_ASSERT(mpl::sizeof_<my>::type::value == sizeof(my));
    return 0;
}
