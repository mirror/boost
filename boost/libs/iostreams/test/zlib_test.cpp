// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <memory>
#include <vector>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/sequence.hpp"
#include "detail/verification.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;     

struct zlib_alloc : std::allocator<char> { };

void zlib_test()
{
    {
        // Compress and decompress data, using small buffer.
        text_sequence      src;
        vector<char>       compressed;

        zlib_compressor    zc( zlib::default_compression, 
                               default_filter_buffer_size );
        filtering_ostream  out(zc);
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.pop();

        zlib_decompressor  zd( zlib::default_window_bits, 
                               default_filter_buffer_size );
        filtering_istream  in(zd);
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed zlib test with small buffer"
        );
    }

    {
        // Compress and decompress data, using default buffer size.
        text_sequence          src;
        vector<char>           compressed;

        filtering_ostream out;
        out.push(zlib_compressor());
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.reset();

        filtering_istream in;
        in.push(zlib_decompressor());
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed zlib test with default buffer size"
        );
    }

    {
        // Compress and decompress data, using custom allocation.
        text_sequence      src;
        vector<char>       compressed;

        filtering_ostream  out;
        out.push(basic_zlib_compressor<zlib_alloc>());
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.reset();

        filtering_istream  in;
        in.push(basic_zlib_decompressor<zlib_alloc>());
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed zlib test with custom allocation"
        );
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("zlib test");
    test->add(BOOST_TEST_CASE(&zlib_test));
    return test;
}
