//-----------------------------------------------------------------------------
// libs mpl/test/index_of.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/index_of.hpp"

#include "boost/static_assert.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/void.hpp"

namespace mpl = boost::mpl;

int test_main(int , char* [])
{
    typedef mpl::list< int, double, float >::type types;

    typedef mpl::index_of< types, int    >::type index_of_int;
    typedef mpl::index_of< types, double >::type index_of_double;
    typedef mpl::index_of< types, float  >::type index_of_float;
    typedef mpl::index_of< types, char   >::type index_of_char;

    BOOST_STATIC_ASSERT(( index_of_int::value    == 0 ));
    BOOST_STATIC_ASSERT(( index_of_double::value == 1 ));
    BOOST_STATIC_ASSERT(( index_of_float::value  == 2 ));

    BOOST_STATIC_ASSERT(( mpl::is_void_< index_of_char >::value ));

    return 0;
}
