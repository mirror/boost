//-----------------------------------------------------------------------------
// boost mpl/test/aux_/has_distance.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/aux_/has_distance.hpp"
#include "boost/mpl/aux_/has_distance_spec.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct iter0 {};
template< typename T > struct iter1
{
    template< typename > struct BOOST_MPL_AUX_ITERATOR_DISTANCE;
};

namespace boost { namespace mpl {
BOOST_MPL_AUX_HAS_DISTANCE_SPEC(1,iter1)
}}

int main()
{
    BOOST_STATIC_ASSERT(!mpl::aux::has_distance<iter0>::value);    
    BOOST_STATIC_ASSERT(mpl::aux::has_distance< iter1<int> >::value);    
    return 0;
}
