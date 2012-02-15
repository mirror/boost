
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#ifndef BOOST_NO_LAMBDAS

#define BOOST_TEST_MODULE TestGccLambdaCpp11
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_gcc_lambda_cpp11 ) {
    //[gcc_lambda_cpp11
    int val = 2;
    int nums[] = {1, 2, 3};
    int* end = nums + 3;

    int* iter = std::find_if(nums, end, 
        [val](int num) -> bool {
            return num == val;
        }
    );
    //]

    BOOST_CHECK( iter != end );
    BOOST_CHECK( *iter == val );
}

#else // NO_LAMBDAS

int main(void) { return 0; } // Trivial test.

#endif // NO_LAMBDAS

