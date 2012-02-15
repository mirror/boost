
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddParams
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_add_params ) {
    //[add_params
    int BOOST_LOCAL_FUNCTION(int x, int y) { // Local function.
        return x + y;
    } BOOST_LOCAL_FUNCTION_NAME(add)
    
    BOOST_CHECK( add(1, 2) == 3 ); // Local function call.
    //]
}
//]

