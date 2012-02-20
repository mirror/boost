
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/functional/overloaded_function.hpp>
#define BOOST_TEST_MODULE TestOverloadSeq
#include <boost/test/unit_test.hpp>
#include <string>
#include <cmath>

int add_i(int x, int y) { return x + y; }

BOOST_AUTO_TEST_CASE(test_overload_seq) {
    std::string s = "abc";
    std::string BOOST_LOCAL_FUNCTION(
            (const bind& s) (const std::string& x) ) {
        return s + x;
    } BOOST_LOCAL_FUNCTION_NAME(add_s)

    double d = 1.23;
    double BOOST_LOCAL_FUNCTION( (const bind d) (double x)
            (double y)(default 0) ) {
        return d + x + y;
    } BOOST_LOCAL_FUNCTION_NAME(add_d)
    
    boost::overloaded_function<
          std::string (const std::string&)
        , double (double)
        , double (double, double)
        , int (int, int)
    > add(add_s, add_d, add_d, add_i);

    BOOST_CHECK(add("xyz") == "abcxyz");
    BOOST_CHECK(fabs(add(3.21) - 4.44) < 0.001);
    BOOST_CHECK(fabs(add(3.21, 40.0) - 44.44) < 0.001);
    BOOST_CHECK(add(1, 2) == 3);
}

