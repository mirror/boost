///////////////////////////////////////////////////////////////////////////////
// misc1.hpp
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
// test_main
//
int test_main( int, char*[] )
{
    // make sure the following compiles:
    sregex a = _;
    sregex b = _;
    sregex c = a >> b;
    c = a | b;
    c = !a;
    c = *a;
    c = +a;

    // test for basic_regex in a keep
    std::locale loc;
    std::string str("Its a mad Mad mAd maD world");
    sregex word = +_w;
    sregex sentence = imbue(loc)(*(keep(word) >> +_s) >> word);
    smatch what;

    BOOST_CHECK(regex_match(str, what, sentence));
    BOOST_CHECK(what.nested_results().size() == 7);
    BOOST_CHECK(what(word, 0)[0] == "Its");
    BOOST_CHECK(what(word, 1)[0] == "a");
    BOOST_CHECK(what(word, 2)[0] == "mad");
    BOOST_CHECK(what(word, 3)[0] == "Mad");
    BOOST_CHECK(what(word, 4)[0] == "mAd");
    BOOST_CHECK(what(word, 5)[0] == "maD");
    BOOST_CHECK(what(word, 6)[0] == "world");

    return 0;
}
