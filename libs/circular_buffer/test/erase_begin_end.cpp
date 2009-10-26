// Tests for erase_begin and erase_end methods.

// Copyright (c) 2009 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_CB_DISABLE_DEBUG

#include "test.hpp"

int MyInteger::ms_exception_trigger = 0;
int InstanceCounter::ms_count = 0;

void erase_begin_test() {

    circular_buffer<int> cb1(5);
    cb1.push_back(1);
    cb1.push_back(2);
    cb1.push_back(3);
    cb1.push_back(4);
    cb1.push_back(5);
    cb1.push_back(6);
    cb1.erase_begin(2);

    BOOST_CHECK(cb1.size() == 3);
    BOOST_CHECK(cb1[0] == 4);
    BOOST_CHECK(cb1[1] == 5);
    BOOST_CHECK(cb1[2] == 6);

    cb1.erase_begin(3);
    BOOST_CHECK(cb1.empty());

    cb1.push_back(10);
    cb1.push_back(11);
    cb1.push_back(12);

    BOOST_CHECK(cb1.size() == 3);
    BOOST_CHECK(cb1[0] == 10);
    BOOST_CHECK(cb1[1] == 11);
    BOOST_CHECK(cb1[2] == 12);

    circular_buffer<InstanceCounter> cb2(5, InstanceCounter());

    BOOST_CHECK(cb2.size() == 5);
    BOOST_CHECK(InstanceCounter::count() == 5);

    cb2.erase_begin(2);

    BOOST_CHECK(cb2.size() == 3);
    BOOST_CHECK(InstanceCounter::count() == 3);

    circular_buffer<MyInteger> cb3(5);
    cb3.push_back(1);
    cb3.push_back(2);
    cb3.push_back(3);
    cb3.push_back(4);
    cb3.push_back(5);
    cb3.push_back(6);
    cb3.erase_begin(2);

    BOOST_CHECK(cb3.size() == 3);
    BOOST_CHECK(cb3[0] == 4);
    BOOST_CHECK(cb3[1] == 5);
    BOOST_CHECK(cb3[2] == 6);
}

void erase_end_test() {

    circular_buffer<int> cb1(5);
    cb1.push_back(1);
    cb1.push_back(2);
    cb1.push_back(3);
    cb1.push_back(4);
    cb1.push_back(5);
    cb1.push_back(6);
    cb1.erase_end(2);

    BOOST_CHECK(cb1.size() == 3);
    BOOST_CHECK(cb1[0] == 2);
    BOOST_CHECK(cb1[1] == 3);
    BOOST_CHECK(cb1[2] ==4);

    cb1.erase_end(3);
    BOOST_CHECK(cb1.empty());

    cb1.push_back(10);
    cb1.push_back(11);
    cb1.push_back(12);

    BOOST_CHECK(cb1.size() == 3);
    BOOST_CHECK(cb1[0] == 10);
    BOOST_CHECK(cb1[1] == 11);
    BOOST_CHECK(cb1[2] == 12);

    circular_buffer<InstanceCounter> cb2(5, InstanceCounter());

    BOOST_CHECK(cb2.size() == 5);
    BOOST_CHECK(InstanceCounter::count() == 5);

    cb2.erase_end(2);

    BOOST_CHECK(cb2.size() == 3);
    BOOST_CHECK(InstanceCounter::count() == 3);

    circular_buffer<MyInteger> cb3(5);
    cb3.push_back(1);
    cb3.push_back(2);
    cb3.push_back(3);
    cb3.push_back(4);
    cb3.push_back(5);
    cb3.push_back(6);
    cb3.erase_end(2);

    BOOST_CHECK(cb3.size() == 3);
    BOOST_CHECK(cb3[0] == 2);
    BOOST_CHECK(cb3[1] == 3);
    BOOST_CHECK(cb3[2] == 4);
}

// test main
test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[]) {

    test_suite* tests = BOOST_TEST_SUITE("Unit tests for erase_begin/erase_end methods of the circular_buffer.");

    tests->add(BOOST_TEST_CASE(&erase_begin_test));
    tests->add(BOOST_TEST_CASE(&erase_end_test));

    return tests;
}
