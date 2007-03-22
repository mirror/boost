///////////////////////////////////////////////////////////////////////////////
// test_actions.cpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <map>
#include <list>
#include <numeric>
#include <boost/xpressive/xpressive_static.hpp>
#include <boost/xpressive/regex_actions.hpp>
#include <boost/test/unit_test.hpp>

///////////////////////////////////////////////////////////////////////////////
// test1
//  simple action which builds a string
void test1()
{
    using namespace boost::xpressive;

    std::string result;
    std::string str("foo bar baz foo bar baz");
    sregex rx = (+_w)[ result += _ ] >> *(' ' >> (+_w)[ result += ',' + _ ]);

    if(!regex_match(str, rx))
    {
        BOOST_ERROR("oops");
    }
    else
    {
        BOOST_CHECK_EQUAL(result, "foo,bar,baz,foo,bar,baz");
    }
}

///////////////////////////////////////////////////////////////////////////////
// test2
//  test backtracking over actions
void test2()
{
    using namespace boost::xpressive;

    std::string result;
    std::string str("foo bar baz foo bar baz");
    sregex rx = (+_w)[ result += _ ] >> *(' ' >> (+_w)[ result += ',' + _ ]) >> repeat<4>(_);

    if(!regex_match(str, rx))
    {
        BOOST_ERROR("oops");
    }
    else
    {
        BOOST_CHECK_EQUAL(result, "foo,bar,baz,foo,bar");
    }
}

///////////////////////////////////////////////////////////////////////////////
// test3
//  cast string to int, push back into list
void test3()
{
    using namespace boost::xpressive;

    std::list<int> result;
    std::string str("1 23 456 7890");
    sregex rx = (+_d)[ push_back( result, as<int>(_) ) ] 
        >> *(' ' >> (+_w)[ push_back( result, as<int>(_) ) ]);

    if(!regex_match(str, rx))
    {
        BOOST_ERROR("oops");
    }
    else
    {
        BOOST_REQUIRE_EQUAL(result.size(), 4);
        BOOST_CHECK_EQUAL(*result.begin(), 1);
        BOOST_CHECK_EQUAL(*++result.begin(), 23);
        BOOST_CHECK_EQUAL(*++++result.begin(), 456);
        BOOST_CHECK_EQUAL(*++++++result.begin(), 7890);
    }
}

///////////////////////////////////////////////////////////////////////////////
// test4
//  build a map of strings to integers
void test4()
{
    using namespace boost::xpressive;

    std::map<std::string, int> result;
    std::string str("aaa=>1 bbb=>23 ccc=>456");
    sregex pair = ( (s1= +_w) >> "=>" >> (s2= +_d) )[ var(result)[s1] = as<int>(s2) ];
    sregex rx = pair >> *(+_s >> pair);

    if(!regex_match(str, rx))
    {
        BOOST_ERROR("oops");
    }
    else
    {
        BOOST_REQUIRE_EQUAL(result.size(), 3);
        BOOST_CHECK_EQUAL(result["aaa"], 1);
        BOOST_CHECK_EQUAL(result["bbb"], 23);
        BOOST_CHECK_EQUAL(result["ccc"], 456);
    }
}

using namespace boost::unit_test;

///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test_actions");
    test->add(BOOST_TEST_CASE(&test1));
    test->add(BOOST_TEST_CASE(&test2));
    test->add(BOOST_TEST_CASE(&test3));
    test->add(BOOST_TEST_CASE(&test4));
    return test;
}

