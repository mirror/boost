// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_READ_WIDE_INPUT_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_READ_WIDE_INPUT_HPP_INCLUDED

#include <boost/iostreams/detail/config/locale.hpp> // BOOST_IOSTREAMS_NO_WIDE_STREAMS
#ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    void read_wide_input_test()
    {
        const bool wide_streams_unsupported_on_this_platform = false;
        BOOST_CHECK(wide_streams_unsupported_on_this_platform);
    }
#else
# include <sstream>

# include <boost/iostreams/device/back_inserter.hpp>
# include <boost/iostreams/filtering_stream.hpp>
# include "detail/filters.hpp"
# include "detail/sequence.hpp"
# include "detail/temp_file.hpp"
# include "detail/verification.hpp"
 
using namespace std;
using namespace boost::iostreams;
using namespace boost::iostreams::test;

void read_wide_input_test()
{
    test_sequence<wchar_t> seq;

    {
        filtering_wistream            first(adapt(seq.begin(), seq.end()), 0);
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from a filter_wistream in chars with no buffer"
        );
    }

    {
        filtering_wistream            first(adapt(seq.begin(), seq.end()), 0);
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from a filter_wistream in chunks with no buffer"
        );
    }

    {
        filtering_wistream            first(adapt(seq.begin(), seq.end()));
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from a filter_wistream in chars with large buffer"
        );
    }

    {
        filtering_wistream            first(adapt(seq.begin(), seq.end()));
        basic_istringstream<wchar_t>  second(
            basic_string<wchar_t>(seq.begin(), seq.end())
        );
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from a filter_wistream in chunks with large buffer"
        );
    }
}

#endif // #ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS
#endif // #ifndef BOOST_IOSTREAMS_TEST_READ_WIDE_INPUT_HPP_INCLUDED
