// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/iostreams/detail/config/wide_streams.hpp> // BOOST_IOSTREAMS_NO_WIDE_STREAMS
#include <boost/test/unit_test.hpp>

using boost::unit_test_framework::test_suite;     

#ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS //-------------------------------------//
    void read_wide_input_test()
    {
        const bool wide_streams_unsupported_on_this_platform = false;
        BOOST_CHECK(wide_streams_unsupported_on_this_platform);
    }
    void write_wide_output_test()
    {
        const bool wide_streams_unsupported_on_this_platform = false;
        BOOST_CHECK(wide_streams_unsupported_on_this_platform);
    }
#else // #ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS //----------------------------//
# include <sstream>
# include <vector>
# include <boost/iostreams/device/back_inserter.hpp>
# include <boost/iostreams/filtering_stream.hpp>
# include <boost/range/iterator_range.hpp>
# include "detail/filters.hpp"
# include <boost/test/test_tools.hpp>
# include "detail/sequence.hpp"
# include "detail/temp_file.hpp"
# include "detail/verification.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;

void read_wide_input_test()
{
    test_sequence<wchar_t> seq;

    {
        filtering_wistream            first(make_iterator_range(seq), 0);
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from a filter_wistream in chars with no buffer"
        );
    }

    {
        filtering_wistream            first(make_iterator_range(seq), 0);
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from a filter_wistream in chunks with no buffer"
        );
    }

    {
        filtering_wistream            first(make_iterator_range(seq));
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from a filter_wistream in chars with large buffer"
        );
    }

    {
        filtering_wistream            first(make_iterator_range(seq));
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from a filter_wistream in chunks with large buffer"
        );
    }
}

void write_wide_output_test()
{
    {
        vector<wchar_t>         first;
        test_sequence<wchar_t>  second;
        filtering_wostream      out(iostreams::back_inserter(first), 0);
        write_data_in_chars(out);
        BOOST_CHECK_MESSAGE(
            first.size() == second.size() && 
                equal(first.begin(), first.end(), second.begin()),
            "failed writing to filtering_wostream in chars with no buffer"
        );
    }

    {
        vector<wchar_t>         first;
        test_sequence<wchar_t>  second;
        filtering_wostream      out(iostreams::back_inserter(first), 0);
        write_data_in_chunks(out);
        BOOST_CHECK_MESSAGE(
            first.size() == second.size() && 
                equal(first.begin(), first.end(), second.begin()),
            "failed writing to filtering_wostream in chunks with no buffer"
        );
    }

    {
        vector<wchar_t>         first;
        test_sequence<wchar_t>  second;
        filtering_wostream      out(iostreams::back_inserter(first), 0);
        write_data_in_chars(out);
        BOOST_CHECK_MESSAGE(
            first.size() == second.size() && 
                equal(first.begin(), first.end(), second.begin()),
            "failed writing to filtering_wostream in chars with large buffer"
        );
    }

    {
        vector<wchar_t>         first;
        test_sequence<wchar_t>  second;
        filtering_wostream      out(iostreams::back_inserter(first));
        write_data_in_chunks(out);
        BOOST_CHECK_MESSAGE(
            first.size() == second.size() && 
                equal(first.begin(), first.end(), second.begin()),
            "failed writing to filtering_wostream in chunks with large buffer"
        );
    }
}

#endif // #ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS //---------------------------//

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("wide stream test");
    test->add(BOOST_TEST_CASE(&read_wide_input_test));
    test->add(BOOST_TEST_CASE(&write_wide_output_test));
    return test;
}
