// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_REGEX_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_REGEX_FILTER_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex_filter.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

struct replace_lower {
    std::string operator() (const boost::match_results<const char*>&)
    { return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
};

void regex_filter_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    // Note: Given the basic stream and filter tests, two regex tests 
    // are probably sufficient: reading with a filter based on a function,
    // and writing with a filter based on a format string.

    test_file       test; 
    uppercase_file  upper; 

    boost::regex match_lower("[a-z]+");
    std::string fmt = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    {
        // Test reading from a regex filter based on a function in chars.
        filtering_istream
            first(boost::iostreams::regex_filter(match_lower, replace_lower()));
        first.push(file_source(test.name()));
        ifstream second((upper.name().c_str()));  // CW8.3 Workaround.
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from function-based regex_filter in chars"
        );

        first.pop();
        second.close();

        // Test reading from a regex filter based on a function in chunks.
        // (Also tests reusing the regex filter.)
        first.push(file_source(test.name()));
        second.open(upper.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from function-based regex_filter in chars"
        );

    }

    {
        // Test reading from a regex filter based on a format string in chars.
        filtering_istream 
            first(boost::iostreams::regex_filter(match_lower, fmt));
        first.push(file_source(test.name()));
        ifstream second((upper.name().c_str()));  // CW8.3 Workaround.
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from format-string-based regex_filter in chars"
        );


        first.pop();
        second.close();

        // Test reading from a regex filter based on a format string in chunks.
        // (Also tests reusing the regex filter.)
        first.push(file_source(test.name()));
        second.open(upper.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from format-string-based regex_filter in chunks"
        );
    }

    {
        test_file dest1;
        test_file dest2;

        // Test writing to a regex filter based on a function in chars.
        filtering_ostream 
            out(boost::iostreams::regex_filter(match_lower, replace_lower()));
        out.push(file_sink(dest1.name()));
        write_data_in_chars(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest1.name(), upper.name()),
            "failed writing to function-based regex_filter in chars"
        );

        // Test writing to a regex filter based on a function in chunks.
        // (Also tests reusing the regex filter.)
        out.push(file_sink(dest2.name()));
        write_data_in_chunks(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest2.name(), upper.name()),
            "failed writing to function-based regex_filter in chunks"
        );
    }

    {
        test_file dest1;
        test_file dest2;

        // Test writing to a regex filter based on a format string in chars.
        filtering_ostream  
            out(boost::iostreams::regex_filter(match_lower, fmt));
        out.push(file_sink(dest1.name()));
        write_data_in_chars(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest1.name(), upper.name()),
            "failed writing to format-string-based regex_filter in chars"
        );

        // Test writing to a regex filter based on a format string in chunks.
        // (Also tests reusing the regex filter.)
        out.push(file_sink(dest2.name()));
        write_data_in_chunks(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest2.name(), upper.name()),
            "failed writing to format-string-based regex_filter in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_REGEX_FILTER_HPP_INCLUDED
