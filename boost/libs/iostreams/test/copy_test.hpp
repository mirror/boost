// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_COPY_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_COPY_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void copy_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    test_file test;          

    {
        temp_file  dest;
        ifstream   first(test.name().c_str());
        ofstream   second(dest.name().c_str());
        boost::iostreams::copy(first, second);
        first.close();
        second.close();
        BOOST_CHECK_MESSAGE(
            compare_files(test.name(), dest.name()),
            "failed copying from stream to stream"
        );
    }

    {
        temp_file  dest;
        ifstream   first(test.name().c_str());
        boost::iostreams::copy(first, file_sink(dest.name()));
        first.close();
        BOOST_CHECK_MESSAGE(
            compare_files(test.name(), dest.name()),
            "failed copying from stream to file_sink"
        );
    }

    {
        temp_file  dest;
        ofstream   second(dest.name().c_str());
        boost::iostreams::copy(file_source(test.name()), second);
        second.close();
        BOOST_CHECK_MESSAGE(
            compare_files(test.name(), dest.name()),
            "failed copying from file_source to stream"
        );
    }

    {
        temp_file dest;
        boost::iostreams::copy( file_source(test.name()),
                         file_sink(dest.name()) );
        BOOST_CHECK_MESSAGE(
            compare_files(test.name(), dest.name()),
            "failed copying from file_source to file_sink"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_COPY_HPP_INCLUDED
