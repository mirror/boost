// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_WRITE_INOUT_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_WRITE_INOUT_FILTER_HPP_INCLUDED

#include <fstream>
#include <boost/iostreams/combine.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/filters.hpp"
#include "detail/sequence.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void write_bidirectional_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    lowercase_file lower;

    {
        temp_file                        lower2;
        filtering_stream<bidirectional>  out;
        out.push(combine(toupper_filter(), tolower_filter()));
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chars(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chars with an "
            "output filter"
        );
    }


    {
        // OutputFilter.
        temp_file                        lower2;
        filtering_stream<bidirectional>  out;
        out.push(combine(toupper_filter(), tolower_filter()));
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chunks(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chunks with an "
            "output filter"
        );
    }

    {
        temp_file                        lower2;
        filtering_stream<bidirectional>  out(
            combine(toupper_filter(), tolower_multichar_filter()), 0
        );
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chars(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chars "
            "with a multichar output filter with no buffer"
        );
    }

    {
        temp_file                        lower2;
        filtering_stream<bidirectional>  out(
            combine(toupper_filter(), tolower_multichar_filter()), 0
        );
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chunks(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chunks "
            "with a multichar output filter with no buffer"
        );
    }

    {
        temp_file                        lower2;
        filtering_stream<bidirectional>  out(
            combine(toupper_filter(), tolower_multichar_filter())
        );
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chars(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chars "
            "with a multichar output filter"
        );
    }

    {
        temp_file                        lower2;
        filtering_stream<bidirectional>  out(
            combine(toupper_filter(), tolower_multichar_filter())
        );
        filebuf dest;
        dest.open(lower2.name().c_str(), BOOST_IOS::out | BOOST_IOS::trunc);
        out.push(dest);
        write_data_in_chunks(out);
        dest.close();
        BOOST_CHECK_MESSAGE(
            compare_files(lower2.name(), lower.name()),
            "failed writing to a filtering_stream<bidirectional> in chunks "
            "with a buffered output filter"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_WRITE_BIDIRECTIONAL_FILTER_HPP_INCLUDED
