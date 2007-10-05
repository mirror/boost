///////////////////////////////////////////////////////////////////////////////
// misc2.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/xpressive/xpressive.hpp>
#include <boost/xpressive/traits/cpp_regex_traits.hpp>
#include "./test_minimal.hpp"

using namespace boost::xpressive;

///////////////////////////////////////////////////////////////////////////////
// test for a sub-match scoping
//
void test5()
{
    sregex inner = sregex::compile( "(.)\\1" );
    sregex outer = (s1= _) >> inner >> s1;
    std::string abba("ABBA");

    BOOST_CHECK(regex_match(abba, outer));
}

///////////////////////////////////////////////////////////////////////////////
// Ye olde calculator. Test recursive grammar.
//
void test6()
{
    sregex group, factor, term, expression;

    group       = '(' >> by_ref(expression) >> ')';
    factor      = +_d | group;
    term        = factor >> *(('*' >> factor) | ('/' >> factor));
    expression  = term >> *(('+' >> term) | ('-' >> term));

    smatch what;
    std::string str("foo 9*(10+3) bar");

    BOOST_REQUIRE(regex_search(str, what, expression));
    BOOST_CHECK("9*(10+3)" == what[0]);
}

///////////////////////////////////////////////////////////////////////////////
// test_main
//
int test_main( int, char*[] )
{
    test5();
    test6();

    return 0;
}
