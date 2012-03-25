
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include "tu_test.hpp"
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

void test(void) {
    BOOST_CHECK(tu1() == 1);
    BOOST_CHECK(tu2() == 2);
}

test_suite* init_unit_test_suite(int, char* []) {
    framework::master_test_suite().p_name.value = "TU unit test for ScopeExit";
    framework::master_test_suite().add(BOOST_TEST_CASE(&test));
    return 0;
}

