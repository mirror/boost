
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddTemplate
#include <boost/test/unit_test.hpp>
#include <algorithm>

//[add_template
template<typename T>
T total(const T& x, const T& y, const T& z) {
    T sum = T(), factor = 10;

    // Using the `..._TPL` macro.
    T BOOST_LOCAL_FUNCTION_TPL(const bind factor, bind& sum, T num) {
        return sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(add)

    add(x);
    T nums[2]; nums[0] = y; nums[1] = z;
    std::for_each(nums, nums + 2, add);

    return sum;
}
//]

BOOST_AUTO_TEST_CASE( test_add_template ) {
    BOOST_CHECK( total(1, 2, 3) == 60 );
}

