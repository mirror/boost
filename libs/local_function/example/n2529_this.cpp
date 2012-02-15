
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestN2529This
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>

struct v {
    std::vector<int> nums;
    
    v(const std::vector<int>& numbers): nums(numbers) {}

    void change_sign_all(const std::vector<int>& indices) {
        void BOOST_LOCAL_FUNCTION(bind this_, int i) { // Bind object `this`.
            this_->nums.at(i) = -this_->nums.at(i);
        } BOOST_LOCAL_FUNCTION_NAME(complement)

        std::for_each(indices.begin(), indices.end(), complement);
    }
};

BOOST_AUTO_TEST_CASE( test_n2529_this ) {
    std::vector<int> n(3);
    n[0] = 1; n[1] = 2; n[2] = 3;

    std::vector<int> i(2);
    i[0] = 0; i[1] = 2; // Will change n[0] and n[2] but not n[1].
    
    v vn(n);
    vn.change_sign_all(i);
    
    BOOST_CHECK( vn.nums.at(0) == -1 );
    BOOST_CHECK( vn.nums.at(1) ==  2 );
    BOOST_CHECK( vn.nums.at(2) == -3 );
}

