// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_WRITE_REVERSING_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_WRITE_REVERSING_FILTER_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/reverse.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/filters.hpp"
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void write_reversing_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    uppercase_file upper;

    {
        temp_file dest;
        filtering_ostream out(reverse(toupper_filter()), 0);
        out.push(file_sink(dest.name()));
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
        out.push(file_sink(dest.name()));
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
        out.push(file_sink(dest.name()));
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
        out.push(file_sink(dest.name()));
        write_data_in_chunks(out);
        out.reset();
        BOOST_CHECK_MESSAGE(
            compare_files(dest.name(), upper.name()),
            "failed writing to a filtering_ostream in chunks with a "
            "reversing_output_filter"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_WRITE_REVERSING_FILTER_HPP_INCLUDED
