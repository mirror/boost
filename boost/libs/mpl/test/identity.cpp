//-----------------------------------------------------------------------------
// boost mpl/test/identity.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/apply.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/assert_is_same.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::apply1< mpl::identity<>, char >::type t1;
    BOOST_MPL_ASSERT_IS_SAME(t1, char);

    return 0;
}
