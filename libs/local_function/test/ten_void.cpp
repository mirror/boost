
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestTenVoid
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE( test_ten_void ) {
    //[ten_void
    int BOOST_LOCAL_FUNCTION(void) { // No parameter.
        return 10;
    } BOOST_LOCAL_FUNCTION_NAME(ten)

    BOOST_CHECK( ten() == 10 );
    //]
}

