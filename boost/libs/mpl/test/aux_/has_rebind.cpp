//-----------------------------------------------------------------------------
// boost mpl/test/aux_/has_rebind.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/aux_/has_rebind.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct f1 {};
struct f2 { struct rebind; };

int main()
{
    BOOST_STATIC_ASSERT(!mpl::aux::has_rebind<f1>::value);    
    BOOST_STATIC_ASSERT(mpl::aux::has_rebind<f2>::value);    
    return 0;
}
