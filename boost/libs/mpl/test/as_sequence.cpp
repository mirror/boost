//-----------------------------------------------------------------------------
// boost mpl/test/as_sequence.cpp source file
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
#include "boost/mpl/as_sequence.hpp"
#include "boost/static_assert.hpp"

using namespace boost::mpl;

struct UDT {};

int main()
{
    BOOST_STATIC_ASSERT(is_sequence< as_sequence<int>::type >::value);
    BOOST_STATIC_ASSERT(is_sequence< as_sequence<UDT>::type >::value);
    BOOST_STATIC_ASSERT(is_sequence< as_sequence< vector<> >::type >::value);

    return 0;
}
