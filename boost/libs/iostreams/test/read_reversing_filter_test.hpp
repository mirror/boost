// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_READ_REVERSING_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_READ_REVERSING_FILTER_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/reverse.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/filters.hpp"
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void read_reversing_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    test_file       test;
    lowercase_file  lower;

    {
        filtering_istream first(reverse(tolower_filter()), 0);
        first.push(file_source(test.name()));
        ifstream second(lower.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chars with a "
            "reversing_input_filter with no buffer"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()), 0);
        first.push(file_source(test.name()));
        ifstream second(lower.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chunks with a "
            "reversing_input_filter with no buffer"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()));
        first.push(file_source(test.name()));
        ifstream second(lower.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chars with a "
            "reversing_input_filter"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()));
        first.push(file_source(test.name()));
        ifstream second(lower.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from filtering_istream in chunks with a "
            "reversing_input_filter"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_READ_REVERSING_FILTER_HPP_INCLUDED
