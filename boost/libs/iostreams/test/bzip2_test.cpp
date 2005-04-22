// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <memory>
#include <vector>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/test.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "detail/sequence.hpp"
#include "detail/verification.hpp"

#include <boost/iostreams/device/file.hpp>
#include <iostream>

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;  

struct bzip2_alloc : std::allocator<char> { };

void bzip2_test()
{

    //{
    //    // Compress and decompress data, using small buffer.
    //    text_sequence         src;
    //    vector<char>          dest;

    //    bzip2_compressor      zc( bzip2::default_block_size,
    //                              default_filter_buffer_size );
    //    filtering_ostream     out(zc);
    //    out.push(boost::iostreams::back_inserter(dest));
    //    iostreams::copy(make_iterator_range(src), out);
    //    out.reset();

    //    bzip2_decompressor    zd( bzip2::default_small,
    //                              default_filter_buffer_size );
    //    filtering_istream     in(zd);
    //    in.push(make_iterator_range(dest));

    //    BOOST_CHECK_MESSAGE(
    //        compare_container_and_stream(src, in),
    //        "failed bzip2 test with small buffer"
    //    );
    //}

    //{
    //    // Compress and decompress data, using default buffer size.
    //    text_sequence         src;
    //    vector<char>          dest;

    //    filtering_ostream     out;
    //    out.push(bzip2_compressor());
    //    out.push(boost::iostreams::back_inserter(dest));
    //    iostreams::copy(make_iterator_range(src), out);
    //    out.reset();

    //    filtering_istream     in;
    //    in.push(bzip2_decompressor());
    //    in.push(make_iterator_range(dest));
    //    //iostreams::copy(in, std::cout);
    //    BOOST_CHECK_MESSAGE(
    //        compare_container_and_stream(src, in),
    //        "failed bzip2 test with default buffer size"
    //    );
    //}

    //{
    //    // Compress and decompress data, using custom allocation.
    //    text_sequence          src;
    //    vector<char>           dest;

    //    filtering_ostream      out;
    //    out.push(basic_bzip2_compressor<bzip2_alloc>());
    //    out.push(iostreams::back_inserter(dest));
    //    iostreams::copy(make_iterator_range(src), out);
    //    out.reset();

    //    filtering_istream      in;
    //    in.push(basic_bzip2_decompressor<bzip2_alloc>());
    //    in.push(make_iterator_range(dest));
    //    BOOST_CHECK_MESSAGE(
    //        compare_container_and_stream(src, in),
    //        "failed bzip2 test with custom allocation"
    //    );
    //}

    text_sequence data;
    BOOST_CHECK(
        test_filter_pair( bzip2_compressor(), 
                          bzip2_decompressor(), 
                          std::string(data.begin(), data.end()).c_str() )
    );
}    

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("bzip2 test");
    test->add(BOOST_TEST_CASE(&bzip2_test));
    return test;
}
