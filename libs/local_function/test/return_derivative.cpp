
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestReturnDerivative
#include <boost/test/unit_test.hpp>

boost::function<int (int)> derivative(boost::function<int (int)>& f, int dx) {
    int BOOST_LOCAL_FUNCTION(bind& f, const bind dx, int x) {
        return (f(x + dx) - f(x)) / dx;
    } BOOST_LOCAL_FUNCTION_NAME(deriv)
    return deriv;
}

BOOST_AUTO_TEST_CASE( test_return_derivative ) {
    int BOOST_LOCAL_FUNCTION(int x) {
        return x + 4;
    } BOOST_LOCAL_FUNCTION_NAME(add2)
    boost::function<int (int)> a2 = add2; // Reference valid where closure used.

    boost::function<int (int)> d2 = derivative(a2, 2);
    BOOST_CHECK( d2(6) == 1 );
}

