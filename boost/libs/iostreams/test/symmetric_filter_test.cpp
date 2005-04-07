// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/symmetric_filter_adapter.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/filters.hpp"
#include "detail/filters.hpp"
#include "detail/temp_file.hpp"
#include "detail/verification.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;   

void symmetric_filter_test()
{
    typedef toupper_symmetric_filter             impl_type;
    typedef symmetric_filter_adapter<impl_type>  filter_type;

    uppercase_file upper;

    {
        // Note: the ifstream second is placed in a nested scope because 
        // closing and reopening a single ifstream failed for CW 9.4 on Windows.

        test_file          src;
        filtering_istream  first(filter_type(new impl_type, 4));

        // Test reading from a symmetric filter in chars.
        first.push(file_source(src.name(), in_mode));
        {
            ifstream second(upper.name().c_str(), in_mode);
            BOOST_CHECK_MESSAGE(
                compare_streams_in_chars(first, second),
                "failed reading from symmetric filter in chars"
            );
        }
        first.pop();

        // Test reading from a symmetric filter in chunks.
        // (Also tests reusing the symmetric filter.)
        first.push(file_source(src.name(), in_mode));
        {
            ifstream second(upper.name().c_str(), in_mode);
            BOOST_CHECK_MESSAGE(
                compare_streams_in_chunks(first, second),
                "failed reading from symmetric filter in chunks"
            );
        }
    }

    {
        test_file          dest1;
        test_file          dest2;
        filtering_ostream  out(filter_type(new impl_type));

        // Test writing to a symmetric filter in chars.
        out.push(file_sink(dest1.name(), out_mode));
        write_data_in_chars(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest1.name(), upper.name()),
            "failed writing to symmetric filter in chars"
        );
        
        // Test writing to a symmetric filter in chunks.
        // (Also tests reusing the symmetric filter.)
        out.push(file_sink(dest2.name(), out_mode));
        write_data_in_chunks(out);
        out.pop();
        BOOST_CHECK_MESSAGE(
            compare_files(dest2.name(), upper.name()),
            "failed writing to symmetric filter in chunks"
        );
    }
}   

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("symmetric_filter test");
    test->add(BOOST_TEST_CASE(&symmetric_filter_test));
    return test;
}
