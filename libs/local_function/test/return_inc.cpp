
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestReturnInc
#include <boost/test/unit_test.hpp>

boost::function<int (void)> inc(int& value) {
    int BOOST_LOCAL_FUNCTION(bind& value) {
        return ++value;
    } BOOST_LOCAL_FUNCTION_NAME(i)
    return i;
}

BOOST_AUTO_TEST_CASE( test_return_inc ) {
    int value1 = 0; // Reference valid in scope where closure is used.
    boost::function<int (void)> inc1 = inc(value1);
    int value2 = 0;
    boost::function<int (void)> inc2 = inc(value2);

    BOOST_CHECK( inc1() == 1 );
    BOOST_CHECK( inc1() == 2 );
    BOOST_CHECK( inc2() == 1 );
    BOOST_CHECK( inc1() == 3 );
}

