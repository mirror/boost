//-----------------------------------------------------------------------------
// boost mpl/test/same_as.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/same_as.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

int main()
{
    BOOST_STATIC_ASSERT((mpl::apply1< mpl::same_as<int>,int >::type::value));
    BOOST_STATIC_ASSERT((!mpl::apply1< mpl::same_as<int>,long >::type::value));
    return 0;
}
