// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED

#include <vector>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/filters.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void seekable_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    {
        vector<char> test(data_reps * data_length(), '0');
        filtering_stream<seekable> io;
        io.push(identity_seekable_filter());
        io.push(make_iterator_range(test));
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within a file, in chars"
        );
    }

    {
        vector<char> test(data_reps * data_length(), '0');
        filtering_stream<seekable> io;
        io.push(identity_seekable_filter());
        io.push(make_iterator_range(test));
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within a file, in chunks"
        );
    }

    {
        vector<char> test(data_reps * data_length(), '0');
        filtering_stream<seekable> io;
        io.push(identity_seekable_multichar_filter());
        io.push(make_iterator_range(test));
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within a file, in chars"
        );
    }

    {
        vector<char> test(data_reps * data_length(), '0');
        filtering_stream<seekable> io;
        io.push(identity_seekable_multichar_filter());
        io.push(make_iterator_range(test));
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within a file, in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED
