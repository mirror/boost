///////////////////////////////////////////////////////////////////////////////
// test_assert.cpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <map>
#include <list>
#include <stack>
#include <numeric>
#include <boost/version.hpp>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::xpressive;

struct three_or_six
{
    bool operator()(ssub_match const &sub) const
    {
        return sub.length() == 3 || sub.length() == 6;
    }
};

///////////////////////////////////////////////////////////////////////////////
// test1
//  simple custom assert that checks the length of a matched sub-expression
void test1()
{
    std::string str("foo barbaz fink");
    // match words of 3 characters or 6 characters.
    sregex rx = (bow >> +_w >> eow)[ check(three_or_six()) ] ;

    sregex_iterator first(str.begin(), str.end(), rx), last;
    BOOST_CHECK_EQUAL(std::distance(first, last), 2);
}

///////////////////////////////////////////////////////////////////////////////
// test2
//  same as above, but using a lambda
void test2()
{
    std::string str("foo barbaz fink");
    // match words of 3 characters or 6 characters.
    sregex rx = (bow >> +_w >> eow)[ check(length(_)==3 || length(_)==6) ] ;

    sregex_iterator first(str.begin(), str.end(), rx), last;
    BOOST_CHECK_EQUAL(std::distance(first, last), 2);
}

using namespace boost::unit_test;

///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test_assert");
    test->add(BOOST_TEST_CASE(&test1));
    test->add(BOOST_TEST_CASE(&test2));
    return test;
}

