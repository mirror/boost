
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddWithDefault
#include <boost/test/unit_test.hpp>

//[add_with_default_macro
#define WITH_DEFAULT , default
//]

BOOST_AUTO_TEST_CASE( test_add_with_default ) {
    //[add_with_default
    int BOOST_LOCAL_FUNCTION(int x, int y WITH_DEFAULT 2) { // Default.
        return x + y;
    } BOOST_LOCAL_FUNCTION_NAME(add)

    BOOST_CHECK( add(1) == 3 );
    //]
}
//]

