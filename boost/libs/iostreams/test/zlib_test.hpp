// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_ZLIB_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_ZLIB_HPP_INCLUDED

#include <memory>
#include <vector>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/sequence.hpp"
#include "detail/verification.hpp"

struct zlib_alloc : std::allocator<char> { };

void zlib_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    {
        // Compress and decompress data, using small buffer.
        text_sequence      src;
        vector<char>       compressed;

        zlib_compressor    zc( zlib::default_compression, 
                               default_filter_buffer_size );
        filtering_ostream  out(zc);
        out.push(iostreams::back_inserter(compressed));
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.pop();

        zlib_decompressor  zd( zlib::default_window_bits, 
                               default_filter_buffer_size );
        filtering_istream  in(zd);
        in.push(compressed.begin(), compressed.end());
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
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.reset();

        filtering_istream in;
        in.push(zlib_decompressor());
        in.push(compressed.begin(), compressed.end());
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
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.reset();

        filtering_istream  in;
        in.push(basic_zlib_decompressor<zlib_alloc>());
        in.push(compressed.begin(), compressed.end());
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed zlib test with custom allocation"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_ZLIB_HPP_INCLUDED
