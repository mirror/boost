// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/reverse.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/filters.hpp"
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

using boost::unit_test::test_suite;  

void read_reversing_filter_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    test_file       test;
    lowercase_file  lower;

    {
        filtering_istream first(reverse(tolower_filter()), 0);
        first.push(file_source(test.name(), in_mode));
        ifstream second(lower.name().c_str(), in_mode);
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chars with a "
            "reversing_input_filter with no buffer"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()), 0);
        first.push(file_source(test.name(), in_mode));
        ifstream second(lower.name().c_str(), in_mode);
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chunks with a "
            "reversing_input_filter with no buffer"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()));
        first.push(file_source(test.name(), in_mode));
        ifstream second(lower.name().c_str(), in_mode);
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from filtering_istream in chars with a "
            "reversing_input_filter"
        );
    }

    {
        test_file src;
        filtering_istream first(reverse(tolower_filter()));
        first.push(file_source(test.name(), in_mode));
        ifstream second(lower.name().c_str(), in_mode);
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from filtering_istream in chunks with a "
            "reversing_input_filter"
        );
    }
}

void write_reversing_filter_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    uppercase_file upper;

    {
        temp_file dest;
        filtering_ostream out(reverse(toupper_filter()), 0);
        out.push(file_sink(dest.name(), out_mode));
        write_data_in_chars(out);
        out.reset();
        BOOST_CHECK_MESSAGE(
            compare_files(dest.name(), upper.name()),
            "failed writing to a filtering_ostream in chars with a "
            "reversing_output_filter with no buffer"
        );
    }

    {
        temp_file dest;
        filtering_ostream out(reverse(toupper_filter()), 0);      
        out.push(file_sink(dest.name(), out_mode));
        write_data_in_chunks(out);
        out.reset();
        BOOST_CHECK_MESSAGE(
            compare_files(dest.name(), upper.name()),
            "failed writing to a filtering_ostream in chunks with a "
            "reversing_output_filter with no buffer"
        );
    }

    {
        temp_file dest;
        filtering_ostream out(reverse(toupper_filter()));
        out.push(file_sink(dest.name(), out_mode));
        write_data_in_chars(out);
        out.reset();
        BOOST_CHECK_MESSAGE(
            compare_files(dest.name(), upper.name()),
            "failed writing to a filtering_ostream in chars with a "
            "reversing_output_filter"
        );
    }

    {
        temp_file dest;
        filtering_ostream out(reverse(toupper_filter()));
        out.push(file_sink(dest.name(), out_mode));
        write_data_in_chunks(out);
        out.reset();
        BOOST_CHECK_MESSAGE(
            compare_files(dest.name(), upper.name()),
            "failed writing to a filtering_ostream in chunks with a "
            "reversing_output_filter"
        );
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("reverse test");
    test->add(BOOST_TEST_CASE(&read_reversing_filter_test));
    test->add(BOOST_TEST_CASE(&write_reversing_filter_test));
    return test;
}
