// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_ARRAY_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_ARRAY_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

struct mytraits : std::char_traits<char> { };

void array_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    test_file test;

    //--------------stream_facade<array_source>-------------------------------//

    {
        test_sequence<> seq;
        stream_facade<array_source> 
            first(/*(array_source(*/&seq[0], &seq[0] + seq.size()/*))*/);
        basic_ifstream<char> second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from stream_facade<array_source> in chars"
        );
    }

    {
        test_sequence<> seq;
        stream_facade<array_source> 
            first((array_source(&seq[0], &seq[0] + seq.size())));
        ifstream second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from stream_facade<array_source> in chunks"
        );
    }

    //--------------stream_facade<array_sink>---------------------------------//

    {
        vector<char> first(data_reps * data_length(), 0);
        stream_facade<array_sink> 
            out((array_sink(&first[0], &first[0] + first.size())));
        write_data_in_chars(out);
        ifstream second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(first, second),
            "failed writing to stream_facade<array_sink> in chars"
        );
    }

    {
        vector<char> first(data_reps * data_length(), 0);
        stream_facade<array_sink> 
            out((array_sink(&first[0], &first[0] + first.size())));
        write_data_in_chunks(out);
        ifstream second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(first, second),
            "failed writing to stream_facade<array_sink> in chunks"
        );
    }

    //--------------random access---------------------------------------------//

    {
        vector<char> first(data_reps * data_length(), 0);
        stream_facade<array> io((array(&first[0], &first[0] + first.size())));
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within stream_facade<array>, in chars"
        );
    }

    {
        vector<char> first(data_reps * data_length(), 0);
        stream_facade<array> io((array(&first[0], &first[0] + first.size())));
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within stream_facade<array>, in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_ARRAY_HPP_INCLUDED
