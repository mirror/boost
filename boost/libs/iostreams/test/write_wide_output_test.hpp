// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_WRITE_WIDE_OUTPUT_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_WRITE_WIDE_OUTPUT_HPP_INCLUDED

#include <boost/iostreams/detail/config/locale.hpp> // BOOST_IOSTREAMS_NO_WIDE_STREAMS
#ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    void write_wide_output_test()
    {
        const bool wide_streams_unsupported_on_this_platform = false;
        BOOST_CHECK(wide_streams_unsupported_on_this_platform);
    }
#else
# include <vector>
# include <boost/iostreams/device/back_inserter.hpp>
# include <boost/iostreams/filtering_stream.hpp>
# include <boost/test/test_tools.hpp>
# include "detail/sequence.hpp"
# include "detail/temp_file.hpp"
# include "detail/verification.hpp"

void write_wide_output_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

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

#endif // #ifdef BOOST_IOSTREAMS_NO_WIDE_STREAMS
#endif // #ifndef BOOST_IOSTREAMS_TEST_WRITE_WIDE_OUTPUT_HPP_INCLUDED
