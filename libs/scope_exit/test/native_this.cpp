
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/scope_exit.hpp>
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

struct this_tester;
BOOST_TYPEOF_REGISTER_TYPE(this_tester) // Register before capture of `this_`.

struct this_tester {
    void check(void) {
        int target;
        BOOST_SCOPE_EXIT( (&target) (this_) ) {
            BOOST_CHECK( this_->value_ == target );
        } BOOST_SCOPE_EXIT_END
#if !defined(BOOST_NO_LAMBDAS) && !defined(BOOST_SCOPE_EXIT_CONFIG_NO_CPP11)
        BOOST_SCOPE_EXIT_ALL(&, this) {
            BOOST_CHECK( this->value_ == target );
        };
#endif
        value_ = target = 3;
    }
private:
    int value_;
};

void test_this(void) { this_tester().check(); }

test_suite* init_unit_test_suite(int, char* []) {
    framework::master_test_suite().p_name.value = "Unit test for ScopeExit";
    framework::master_test_suite().add(BOOST_TEST_CASE(&test_this));
    return 0;
}

