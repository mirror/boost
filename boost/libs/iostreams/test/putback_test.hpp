// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_PUTBACK_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_PUTBACK_HPP_INCLUDED

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void putback_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    test_file test;

    {
        filtering_istream is;
        is.set_device_buffer_size(0);
        is.push(file_source(test.name()));
        BOOST_CHECK_MESSAGE(
            unbuffered_putback_test(is),
            "failed putting back to unbuffered filtering_istream"
        );
    }

    {
        filtering_istream is;
        is.set_pback_size(4);
        is.push(file_source(test.name()));
        BOOST_CHECK_MESSAGE(
            buffered_putback_test(is),
            "failed putting back to buffered filtering_istream"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_PUTBACK_HPP_INCLUDED
