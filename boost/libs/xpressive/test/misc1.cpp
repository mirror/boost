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

    // test for a simple regex grammar
    std::string buffer =
        "FROGGIE\r\n"
        "Volume = 1\r\n"
        "Other1= 2\r\n"
        "Channel=3\r\n"
        "Other =4\r\n"
        "\r\n"
        "FROGGIE\r\n"
        "Volume = 5\r\n"
        "Other1= 6\r\n"
        "Channel=7\r\n"
        "Other =8\r\n"
        "\r\n"
        "FROGGIE\r\n"
        "Volume = 9\r\n"
        "Other1= 0\r\n"
        "Channel=10\r\n"
        "\r\n";

    mark_tag name(1), value(2);

    sregex name_value_pair_ =
        (name= +alnum) >> *_s >> "=" >> *_s >>
        (value= +_d) >> *_s >> _ln;

    sregex message_ =
        *_s >> "FROGGIE" >> _ln >> +name_value_pair_ >> _ln;

    sregex re_ = +message_;

    typedef smatch::nested_results_type::const_iterator nested_iterator;
    nested_iterator msg, nvp;

    BOOST_REQUIRE(regex_search(buffer, what, re_));
    BOOST_REQUIRE(3 == what.nested_results().size());

    msg = what.nested_results().begin();
    BOOST_REQUIRE(4 == msg->nested_results().size());

    nvp = msg->nested_results().begin();
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Volume" == (*nvp)[name]);
    BOOST_CHECK("1" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Other1" == (*nvp)[name]);
    BOOST_CHECK("2" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Channel" == (*nvp)[name]);
    BOOST_CHECK("3" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Other" == (*nvp)[name]);
    BOOST_CHECK("4" == (*nvp)[value]);

    ++msg;
    BOOST_REQUIRE(4 == msg->nested_results().size());

    nvp = msg->nested_results().begin();
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Volume" == (*nvp)[name]);
    BOOST_CHECK("5" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Other1" == (*nvp)[name]);
    BOOST_CHECK("6" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Channel" == (*nvp)[name]);
    BOOST_CHECK("7" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Other" == (*nvp)[name]);
    BOOST_CHECK("8" == (*nvp)[value]);

    ++msg;
    BOOST_REQUIRE(3 == msg->nested_results().size());

    nvp = msg->nested_results().begin();
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Volume" == (*nvp)[name]);
    BOOST_CHECK("9" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Other1" == (*nvp)[name]);
    BOOST_CHECK("0" == (*nvp)[value]);
    ++nvp;
    BOOST_REQUIRE(3 == nvp->size());
    BOOST_CHECK("Channel" == (*nvp)[name]);
    BOOST_CHECK("10" == (*nvp)[value]);

    return 0;
}
