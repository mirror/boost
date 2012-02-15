
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestFactorial
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <vector>

//[factorial
struct calculator {
    std::vector<int> results;

    void factorials(const std::vector<int>& nums) {
        int BOOST_LOCAL_FUNCTION(bind this_, int num,
                bool recursion, default false) {
            int result = 0;
            
            if(num <= 0) result = 1;
            else result = num * factorial(num - 1, true); // Recursive call.

            if(!recursion) this_->results.push_back(result);
            return result;
        } BOOST_LOCAL_FUNCTION_NAME(recursive factorial) // Recursive.
    
        std::for_each(nums.begin(), nums.end(), factorial);
    }
};
//]

BOOST_AUTO_TEST_CASE( test_factorial ) {
    std::vector<int> v(3);
    v[0] = 1; v[1] = 3; v[2] = 4;

    calculator calc;
    calc.factorials(v);
    BOOST_CHECK( calc.results[0] ==  1 );
    BOOST_CHECK( calc.results[1] ==  6 );
    BOOST_CHECK( calc.results[2] == 24 );
}

