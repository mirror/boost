// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_TEST_BZIP2_HPP_INCLUDED
#define BOOST_IOSTREAMS_TEST_BZIP2_HPP_INCLUDED

#include <memory>
#include <vector>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/test/test_tools.hpp>
#include "detail/sequence.hpp"
#include "detail/verification.hpp"

struct bzip2_alloc : std::allocator<char> { };

void bzip2_test()
{
    using namespace std;
    using namespace boost;
    using namespace boost::iostreams;
    using namespace boost::iostreams::test;

    {
        // Compress and decompress data, using small buffer.
        text_sequence         src;
        vector<char>          dest;

        bzip2_compressor      zc( bzip2::default_block_size,
                                  default_filter_buffer_size );
        filtering_ostream     out(zc);
        out.push(iostreams::back_inserter(dest));
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.reset();

        bzip2_decompressor    zd( bzip2::default_small,
                                  default_filter_buffer_size );
        filtering_istream     in(zd);
        in.push(dest.begin(), dest.end());

        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed bzip2 test with small buffer"
        );
    }

    {
        // Compress and decompress data, using default buffer size.
        text_sequence         src;
        vector<char>          dest;

        filtering_ostream     out;
        out.push(bzip2_compressor());
        out.push(iostreams::back_inserter(dest));
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.reset();

        filtering_istream     in;
        in.push(bzip2_decompressor());
        in.push(dest.begin(), dest.end());
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed bzip2 test with default buffer size"
        );
    }

    {
        // Compress and decompress data, using custom allocation.
        text_sequence          src;
        vector<char>           dest;

        filtering_ostream      out;
        out.push(basic_bzip2_compressor<bzip2_alloc>());
        out.push(iostreams::back_inserter(dest));
        iostreams::copy(adapt(src.begin(), src.end()), out);
        out.reset();

        filtering_istream      in;
        in.push(basic_bzip2_decompressor<bzip2_alloc>());
        in.push(dest.begin(), dest.end());
        BOOST_CHECK_MESSAGE(
            compare_container_and_stream(src, in),
            "failed bzip2 test with custom allocation"
        );
    }
}

#endif // #ifndef BOOST_IOSTREAMS_TEST_BZIP2_HPP_INCLUDED
