//-----------------------------------------------------------------------------
// boost mpl/test/is_sequence.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/list.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/is_sequence.hpp"
#include "boost/static_assert.hpp"
#include <vector>

using namespace boost::mpl;

struct UDT {};

int main()
{
    BOOST_STATIC_ASSERT(!is_sequence< std::vector<int> >::value);
    BOOST_STATIC_ASSERT(!is_sequence< int >::value);
    BOOST_STATIC_ASSERT(!is_sequence< int& >::value);
    BOOST_STATIC_ASSERT(!is_sequence< UDT >::value);
    BOOST_STATIC_ASSERT(!is_sequence< UDT* >::value);
    BOOST_STATIC_ASSERT((is_sequence< range_c<int,0,0> >::value));
    BOOST_STATIC_ASSERT(is_sequence< list<> >::value);
    BOOST_STATIC_ASSERT(is_sequence< list<int> >::value);
    BOOST_STATIC_ASSERT(is_sequence< vector<> >::value);
    BOOST_STATIC_ASSERT(is_sequence< vector<int> >::value);

    return 0;
}
