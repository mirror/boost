//  boost lexical_cast_test.cpp program  -------------------------------------//

//  See http://www.boost.org for most recent version including documentation.

// what:  lexical_cast custom keyword cast tests
// who:   contributed by Kevlin Henney
// when:  October 2000
// where: tested with MSVC 6.0 and BCC 5.5

#include <boost/lexical_cast.hpp>
#include "test.hpp"
#include <complex>
#include <iostream>
#include <string>

using namespace boost;
using namespace std;

typedef test::test<const char *, void (*)()> test_case;
typedef const test_case * test_case_iterator;

extern const test_case_iterator begin, end;

int main()
{
    test::tester<test_case_iterator> test_suite(begin, end);
    return test_suite() ? EXIT_SUCCESS : EXIT_FAILURE;
}

void test_to_string()
{
    test::check_equal(
        lexical_cast<string>(2001), "2001",
        "2001 -> \"2001\"");
    test::check_equal(
        lexical_cast<string>(2001.0), "2001",
        "2001.0 ->\"2001\"");
    test::check_equal(
        lexical_cast<string>(complex<double>(2000,1)), "(2000,1)",
        "complex<double>(2000,1) -> \"(2000,1)\"");
}

void test_to_int()
{
    test::check_equal(
        lexical_cast<int>("2001"), 2001,
        "\"2001\" -> 2001");
    test::check_equal(
        lexical_cast<int>("    2001"), 2001,
        "\"    2001\" -> 2001");
    test::check_equal(
        lexical_cast<int>("2001    "), 2001,
        "\"2001    \" -> 2001");
    TEST_CHECK_THROW(
        lexical_cast<int>("Two thousand and one"),
        bad_lexical_cast,
        "\"Two thousand and one\"");
    TEST_CHECK_THROW(
        lexical_cast<int>("2001: A Space Odyssey"),
        bad_lexical_cast,
        "\"2001: A Space Odyssey\"");
    TEST_CHECK_THROW(
        lexical_cast<int>(200.1),
        bad_lexical_cast,
        "200.1");
    TEST_CHECK_THROW(
        lexical_cast<int>("200e1"),
        bad_lexical_cast,
        "\"200e1\"");
}

void test_to_char()
{
    test::check_equal(
        lexical_cast<char>("2"), '2',
        "\"2\" -> '2'");
    test::check_equal(
        lexical_cast<char>("    2"), '2',
        "\"    2\" -> '2'");
    test::check_equal(
        lexical_cast<char>("2    "), '2',
        "\"2    \" -> '2'");
    test::check_equal(
        lexical_cast<char>(2), '2',
        "2 -> '2'");
    TEST_CHECK_THROW(
        lexical_cast<char>("2001"),
        bad_lexical_cast,
        "\"2001\"");
    TEST_CHECK_THROW(
        lexical_cast<char>(2001),
        bad_lexical_cast,
        "2001");
}

void test_to_double()
{
    test::check_equal(
        lexical_cast<double>("1e6"), 1e6,
        "\"1e6\" -> 1e6");
    test::check_equal(
        lexical_cast<double>("1e-2"), 1e-2,
        "\"1e-2\" -> 1e-2");
}

void test_to_bool()
{
    test::check_equal(
        lexical_cast<bool>(1), true,
        "1 -> true");
    test::check_equal(
        lexical_cast<bool>('0'), false,
        "'0' -> false");
    TEST_CHECK_THROW(
        lexical_cast<bool>(2001),
        bad_lexical_cast,
        "2001");
    TEST_CHECK_THROW(
        lexical_cast<bool>(2),
        bad_lexical_cast,
        "2");
    TEST_CHECK_THROW(
        lexical_cast<bool>("true thousand and one"),
        bad_lexical_cast,
        "\"true thousand and one\"");
}

const test_case test_cases[] =
{
    { "lexical_cast<std::string>", test_to_string },
    { "lexical_cast<int>",         test_to_int    },
    { "lexical_cast<char>",        test_to_char   },
    { "lexical_cast<double>",      test_to_double },
    { "lexical_cast<bool>",        test_to_bool   }
};

const test_case_iterator begin = test_cases;
const test_case_iterator end =
    test_cases + (sizeof test_cases / sizeof *test_cases);

// Copyright Kevlin Henney, 2000. All rights reserved.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose is hereby granted without fee, provided that this copyright and
// permissions notice appear in all copies and derivatives, and that no
// charge may be made for the software and its documentation except to cover
// cost of distribution.
//
// This software is provided "as is" without express or implied warranty.
