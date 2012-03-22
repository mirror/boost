
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#include "identity.hpp"
#include <boost/functional/overloaded_function.hpp>
#define BOOST_TEST_MODULE TestMakeCall
#include <boost/test/unit_test.hpp>

//[identity_make_checks
template<typename F>
void check(F identity) {
    BOOST_CHECK(identity("abc") == "abc");
    BOOST_CHECK(identity(123) == 123);
    BOOST_CHECK(identity(1.23) == 1.23);
}
//]

BOOST_AUTO_TEST_CASE(test_identity) {
    //[identity_make_call
    check(boost::make_overloaded_function(identity_s, identity_i, identity_d));
    //]
}

