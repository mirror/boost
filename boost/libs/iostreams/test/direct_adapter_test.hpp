// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_DIRECT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_DIRECT_ADAPTER_HPP_INCLUDED

#include <algorithm> // equal.
#include <fstream>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/detail/adapter/direct_adapter.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

struct mytraits : std::char_traits<char> { };

void direct_adapter_test()
{
    using namespace std;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    typedef boost::iostreams::detail::direct_adapter<array_source> 
            indirect_array_source;
    typedef boost::iostreams::detail::direct_adapter<array_sink> 
            indirect_array_sink;
    typedef boost::iostreams::detail::direct_adapter<array> 
            indirect_array;
    typedef stream_facade<indirect_array_source>
            indirect_array_istream;
    typedef stream_facade<indirect_array_sink> 
            indirect_array_ostream;
    typedef stream_facade<indirect_array> 
            indirect_array_stream;

    test_file        test;
    test_sequence<>  seq;

    //--------------indirect_array_istream------------------------------------//

    {
        indirect_array_istream  first(&seq[0], &seq[0] + seq.size());
        ifstream                second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from indirect_array_istream in chars"
        );
    }

    {
        indirect_array_istream  first(&seq[0], &seq[0] + seq.size());
        ifstream                second(test.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from indirect_array_istream in chunks"
        );
    }

    //--------------indirect_array_ostream------------------------------------//

    {
        vector<char>            dest(data_reps * data_length(), 0);
        indirect_array_ostream  out(&dest[0], &dest[0] + dest.size());
        write_data_in_chars(out);
        BOOST_CHECK_MESSAGE(
            std::equal(seq.begin(), seq.end(), dest.begin()),
            "failed writing to indirect_array_ostream in chunks"
        );
    }

    {
        vector<char>            dest(data_reps * data_length(), 0);
        indirect_array_ostream  out(&dest[0], &dest[0] + dest.size());
        write_data_in_chunks(out);
        BOOST_CHECK_MESSAGE(
            std::equal(seq.begin(), seq.end(), dest.begin()),
            "failed writing to indirect_array_ostream in chunks"
        );
    }

    //--------------indirect_array_stream-------------------------------------//

    {
        vector<char> test(data_reps * data_length(), 0);
        indirect_array_stream io(&test[0], &test[0] + test.size());
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within indirect_array_stream, in chars"
        );
    }

    {
        vector<char> test(data_reps * data_length(), 0);
        indirect_array_stream io(&test[0], &test[0] + test.size());
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within indirect_array_stream, in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_DIRECT_ADAPTER_HPP_INCLUDED
