// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void seekable_file_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    {
        temp_file temp;
        file f(temp.name(), ios::in | ios::out | ios::trunc | ios::binary);
        filtering_stream<seekable> io(f);
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chars(io),
            "failed seeking within a file, in chars"
        );
    }

    {
        temp_file temp;
        file f(temp.name(), ios::in | ios::out | ios::trunc | ios::binary);
        filtering_stream<seekable> io(f);
        io.exceptions(ios::failbit | ios::badbit);
        BOOST_CHECK_MESSAGE(
            test_seekable_in_chunks(io),
            "failed seeking within a file, in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_SEEKABLE_FILE_HPP_INCLUDED
