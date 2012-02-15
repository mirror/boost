
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#define BOOST_TEST_MODULE TestAddLocalFunctor
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_add_local_functor ) 
//[add_local_functor
{
    int sum = 0, factor = 10;

    struct local_add { // Unfortunately, boilerplate code to program the class.
        local_add(int& _sum, int _factor): sum(_sum), factor(_factor) {}

        inline void operator()(int num) { // Body uses C++ statement syntax.
            sum += factor * num;
        }
    private: // Unfortunately, cannot bind so repeat variable types.
        int& sum; // Access `sum` by reference.
        const int factor; // Make `factor` constant.
    } add(sum, factor);
    
    add(1);
    int nums[] = {2, 3};
    // Unfortunately, cannot pass as template parameter to `std::for_each`.
    for(size_t i = 0; i < 2; ++i) add(nums[i]);

    BOOST_CHECK( sum == 60 );
}
//]

