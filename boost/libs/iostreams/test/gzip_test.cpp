// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <memory>
#include <vector>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
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

struct gzip_alloc : std::allocator<char> { };

void gzip_test()
{
    {
        // Compress and decompress data, using small buffer.
        text_sequence      src;
        vector<char>       compressed;

        gzip_compressor    gc(gzip::default_compression);
        filtering_ostream  out(gc);
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.reset();

        gzip_decompressor  gd(gzip::default_window_bits);
        filtering_istream  in(gd);
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed gzip test with small buffer"
        );
    }

    {
        // Compress and decompress data, using default buffer size.
        text_sequence      src;
        vector<char>       compressed;

        filtering_ostream out;
        out.push(gzip_compressor());
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.reset();

        filtering_istream  in;
        in.push(gzip_decompressor());
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed gzip test with default buffer size"
        );
    }

    {
        // Compress and decompress data, using custom allocation.
        text_sequence      src;
        vector<char>       compressed;

        filtering_ostream  out;
        out.push(basic_gzip_compressor<gzip_alloc>());
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(make_iterator_range(src), out);
        out.reset();

        filtering_istream  in;
        in.push(basic_gzip_decompressor<gzip_alloc>());
        in.push(make_iterator_range(compressed));
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed gzip test with custom allocation"
        );
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    using namespace boost::iostreams;
    test_suite* test = BOOST_TEST_SUITE("gzip test");
    test->add(BOOST_TEST_CASE(&gzip_test));
    return test;
}
