
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#ifdef BOOST_NO_VARIADIC_MACROS
#   error "variadic macros required"
#else

#include <boost/local_function.hpp>
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#include <boost/detail/lightweight_test.hpp>
#include <vector>
#include <algorithm>

//[add_typed
struct adder;
BOOST_TYPEOF_REGISTER_TYPE(adder) // Unfortunately needed for `..._NAME` below.

struct adder {
    adder() : sum_(0) {}

    int sum(const std::vector<int>& nums, const int& factor = 10) {
        // Explicitly specify bound variable and result types...
        BOOST_LOCAL_FUNCTION(const bind(const int&) factor,
                bind(adder*) this_, int num, return int) {
            return this_->sum_ += factor * num;
        } BOOST_LOCAL_FUNCTION_NAME(add) // ... but this still uses type-of.
        
        std::for_each(nums.begin(), nums.end(), add);
        return sum_;
    }

private:
    int sum_;
};
//]

int main(void) {
    std::vector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    BOOST_TEST(adder().sum(v) == 60);
    return boost::report_errors();
}

#endif // VARIADIC_MACROS

