
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestGccAccess
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_gcc_access ) {
    int nums[] = {1, 2, 3};
    int offset = -1;
    int BOOST_LOCAL_FUNCTION(const bind offset, int* array, int index) {
        return array[index + offset];
    } BOOST_LOCAL_FUNCTION_NAME(access)

    BOOST_CHECK( access(nums, 1) == 1 );
    BOOST_CHECK( access(nums, 2) == 2 );
    BOOST_CHECK( access(nums, 3) == 3 );
}

