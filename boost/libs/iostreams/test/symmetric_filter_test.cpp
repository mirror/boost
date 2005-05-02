// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/symmetric_filter_adapter.hpp>
#include <boost/iostreams/filter/test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "./detail/constants.hpp"
#include "./detail/temp_file.hpp"
#include "./detail/verification.hpp"

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> 

using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;   

// Note: The filter is given an internal buffer, unnecessary in this simple
// case, to test symmetric_filter_adapter.
struct toupper_symmetric_filter_impl {
    typedef char char_type;
    explicit toupper_symmetric_filter_impl( 
                std::streamsize buffer_size = 
                    default_filter_buffer_size 
             ) 
        : buf_(default_filter_buffer_size) 
    {
        buf_.set(0, 0);
    }
    bool filter( const char*& src_begin, const char* src_end,
                 char*& dest_begin, char* dest_end, bool /* flush */ )
    {
        while ( can_read(src_begin, src_end) || 
                can_write(dest_begin, dest_end) ) 
        {
            if (can_read(src_begin, src_end)) 
                read(src_begin, src_end);
            if (can_write(dest_begin, dest_end)) 
                write(dest_begin, dest_end);
        }
        return buf_.ptr() != buf_.eptr();
    }
    void close() { buf_.set(0, 0); }
    void read(const char*& src_begin, const char* src_end)
    {
        std::ptrdiff_t count =
            (std::min) ( src_end - src_begin,
                         static_cast<std::ptrdiff_t>(buf_.size()) - 
                             (buf_.eptr() - buf_.data()) );
        while (count-- > 0)
            *buf_.eptr()++ = std::toupper(*src_begin++);
    }
    void write(char*& dest_begin, char* dest_end)
    {
        std::ptrdiff_t count =
            (std::min) ( dest_end - dest_begin,
                         buf_.eptr() - buf_.ptr() );
        while (count-- > 0)
            *dest_begin++ = *buf_.ptr()++;
        if (buf_.ptr() == buf_.eptr())
            buf_.set(0, 0);
    }
    bool can_read(const char*& src_begin, const char* src_end)
    { return src_begin != src_end && buf_.eptr() != buf_.end(); }
    bool can_write(char*& dest_begin, char* dest_end)
    { return dest_begin != dest_end && buf_.ptr() != buf_.eptr(); }
    boost::iostreams::detail::buffer<char> buf_;
};

typedef symmetric_filter_adapter<toupper_symmetric_filter_impl>
        toupper_symmetric_filter;

void symmetric_filter_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    uppercase_file upper;

    {
        // Note: the ifstream second is placed in a nested scope because 
        // closing and reopening a single ifstream failed for CW 9.4 on Windows.

        test_file          src;
        filtering_istream  first;
        first.push(toupper_symmetric_filter(default_filter_buffer_size));

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
        filtering_ostream  out;
        out.push(toupper_symmetric_filter(default_filter_buffer_size));

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

void read_symmetric_filter_test()
{
    test_file       test;
    uppercase_file  upper;
    BOOST_CHECK(
        test_input_filter( toupper_symmetric_filter(default_filter_buffer_size),
                           file_source(test.name(), in_mode),
                           file_source(upper.name(), in_mode) )
    );
} 

void write_symmetric_filter_test()
{
    const char* input = "abcdefghijklmnopqrstuvwxyz";
    const char* output = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    test_file       test;
    uppercase_file  upper;
    //BOOST_CHECK(
    //    test_output_filter( toupper_symmetric_filter(default_filter_buffer_size),
    //                        input, output )
    //);
    BOOST_CHECK(
        test_output_filter( toupper_symmetric_filter(default_filter_buffer_size),
                            file_source(test.name(), in_mode),
                            file_source(upper.name(), in_mode) )
    );
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("symmetric_filter test");
    test->add(BOOST_TEST_CASE(&symmetric_filter_test));
    //test->add(BOOST_TEST_CASE(&read_symmetric_filter_test));
    //test->add(BOOST_TEST_CASE(&write_symmetric_filter_test));
    return test;
}

#include <boost/iostreams/detail/config/enable_warnings.hpp>
