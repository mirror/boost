
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#define BOOST_TEST_MODULE TestAddThisSeq
#include <boost/test/unit_test.hpp>
#include <vector>
#include <algorithm>

struct adder {
    adder() : sum_(0) {}

    int sum(const std::vector<int>& nums, const int factor = 10) {

        void BOOST_LOCAL_FUNCTION( (const bind factor) (bind this_)
                (int num) ) {
            this_->sum_ += factor * num;
        } BOOST_LOCAL_FUNCTION_NAME(add)
        
        std::for_each(nums.begin(), nums.end(), add);
        return sum_;
    }

private:
    int sum_;
};

BOOST_AUTO_TEST_CASE(test_add_this_seq) {
    std::vector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    BOOST_CHECK(adder().sum(v) == 60);
}

