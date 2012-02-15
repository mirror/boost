
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#if defined(__GCC__) || !defined(BOOST_NO_LAMBDAS)

#include "gcc_lambda.hpp"
#define BOOST_TEST_MODULE TestGccLambda
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_gcc_lambda ) {
    //[gcc_lambda
    int val = 2;
    int nums[] = {1, 2, 3};
    int* end = nums + 3;

    int* iter = std::find_if(nums, end,
        GCC_LAMBDA(const bind val, int num, return bool) {
            return num == val;
        } GCC_LAMBDA_END
    );
    //]

    BOOST_CHECK( iter != end );
    BOOST_CHECK( *iter == val );
}

#else // GCC || !NO_LAMBDAS

int main(void) { return 0; }

#endif // GCC || !NO_LAMBDAS

