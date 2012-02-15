
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

//[ add_function_inline_cpp
#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddInline
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_add_inline ) {
    //[add_inline
    int sum = 0, factor = 10;

    void BOOST_LOCAL_FUNCTION(const bind factor, bind& sum, int num) {
        sum += factor * num;
    } BOOST_LOCAL_FUNCTION_NAME(inline add) // Inlined.

    std::vector<int> v(100);
    std::fill(v.begin(), v.end(), 1);

    for(size_t i = 0; i < v.size(); ++i) add(v[i]); // Cannot use for_each.
    //]

    BOOST_CHECK( sum == 1000 );
}

