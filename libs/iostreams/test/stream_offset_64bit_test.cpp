/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.

 * File:        libs/iostreams/test/stream_offset_64bit_test.cpp
 * Date:        Sun Dec 23 21:11:23 MST 2007
 * Copyright:   2007 CodeRage
 * Author:      Jonathan Turkanis
 *
 * Tests the functions defined in the header "boost/iostreams/positioning.hpp"
 * with large (64-bit) file offsets.
 */

#include <sstream>
#include <boost/config.hpp>  // BOOST_MSVC
#include <boost/iostreams/positioning.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using boost::unit_test::test_suite;

#ifdef BOOST_MSVC
# pragma warning(disable:4127)
#endif

void stream_offset_64bit_test()
{    
    stream_offset  large_file = (stream_offset) 100 *
                                (stream_offset) 1024 *
                                (stream_offset) 1024 *
                                (stream_offset) 1024;
    stream_offset  first = -large_file - (-large_file) % 10000000;
    stream_offset  last = large_file - large_file % 10000000;

    for (stream_offset off = first; off < last; off += 10000000)
    {
        if (off != position_to_offset(offset_to_position(off))) {
            stringstream s;
            s << "off != position_to_offset(offset_to_position(off)) "
                 "failed for (off >> 32) == " 
              << static_cast<unsigned int>(off >> 32) 
              << " and (off & 0xFFFFFFFF) == "
              << static_cast<unsigned int>(off & 0xFFFFFFFF);
            BOOST_REQUIRE_MESSAGE(0, s.str().c_str());
        }
    }
}

test_suite* init_unit_test_suite(int, char* [])
{
    test_suite* test = BOOST_TEST_SUITE("stream_offset 64-bit test");
    test->add(BOOST_TEST_CASE(&stream_offset_64bit_test));
    return test;
}
