// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_SYMMETRIC_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_SYMMETRIC_FILTER_HPP_INCLUDED

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/symmetric_filter_adapter.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/filters.hpp"
#include "detail/filters.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

void symmetric_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;
 
    typedef toupper_symmetric_filter             impl_type;
    typedef symmetric_filter_adapter<impl_type>  filter_type;

    uppercase_file upper; 

    {
        test_file          src;
        filtering_istream  first(filter_type(new impl_type, 4));

        // Test reading from a symmetric filter in chars.
        first.push(file_source(src.name()));
        ifstream second((upper.name().c_str()));  // CW8.3 Workaround.
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chars(first, second),
            "failed reading from symmetric filter in chars"
        );

        first.pop();
        second.close();

        // Test reading from a symmetric filter in chunks.
        // (Also tests reusing the symmetric filter.)
        first.push(file_source(src.name()));
        second.open(upper.name().c_str());
        BOOST_CHECK_MESSAGE(
            compare_streams_in_chunks(first, second),
            "failed reading from symmetric filter in chunks"
        );
    }

    {
        test_file          dest1;
        test_file          dest2;
        filtering_ostream  out(filter_type(new impl_type));

        // Test writing to a symmetric filter in chars.
        out.push(file_sink(dest1.name()));
        write_data_in_chars(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest1.name(), upper.name()),
            "failed writing to symmetric filter in chars"
        );
        
        // Test writing to a symmetric filter in chunks.
        // (Also tests reusing the symmetric filter.)
        out.push(file_sink(dest2.name()));
        write_data_in_chunks(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest2.name(), upper.name()),
            "failed writing to symmetric filter in chunks"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_SYMMETRIC_FILTER_HPP_INCLUDED
