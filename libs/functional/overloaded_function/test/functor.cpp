
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/functional/overloaded_function

#include "identity.hpp"
#include <boost/functional/overloaded_function.hpp>
#define BOOST_TEST_MODULE TestFunctor
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_functor) {
    //[identity_calls
    BOOST_CHECK(identity_s("abc") == "abc");
    BOOST_CHECK(identity_i(123) == 123);
    BOOST_CHECK(identity_d(1.23) == 1.23);
    //]

    //[identity_functor
    boost::overloaded_function<
          const std::string& (const std::string&)
        , int (int)
        , double (double)
    > identity(identity_s, identity_i, identity_d);

    // All calls via single `identity` function.
    BOOST_CHECK(identity("abc") == "abc");
    BOOST_CHECK(identity(123) == 123);
    BOOST_CHECK(identity(1.23) == 1.23);
    //]
}

