//-----------------------------------------------------------------------------
// libs mpl/test/max_element.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/max_element.hpp"

#include "boost/static_assert.hpp"
#include "boost/mpl/list_c.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list_c<int, 3, 4, 2, 0, -5, 8, -1, 7>::type numbers;

    typedef mpl::max_element< numbers >::type max_it;
    typedef max_it::type max_value;
    BOOST_STATIC_ASSERT((max_value::value == 8));

    return 0;
}
