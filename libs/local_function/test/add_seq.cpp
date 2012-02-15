
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddSeq
#include <boost/test/unit_test.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE( test_add_seq )
//[add_seq
{                                           // Some local scope.
    int sum = 0, factor = 10;               // Variables in scope to bind.
    
    void BOOST_LOCAL_FUNCTION( (const bind factor) (bind& sum) (int num) ) {
        sum += factor * num;                // Parameters as sequence.
    } BOOST_LOCAL_FUNCTION_NAME(add)
    
    add(1);                                 // Call the local function.
    int nums[] = {2, 3};
    std::for_each(nums, nums + 2, add);     // Pass it to an algorithm.

    BOOST_CHECK( sum == 60 );               // Assert final summation value.
}
//]

