// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#include <fstream>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream_facade.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>  
#include "detail/filters.hpp"
#include "detail/temp_file.hpp"

using namespace std;
using namespace boost;
using namespace boost::iostreams;
using namespace boost::iostreams::test;
using boost::unit_test::test_suite;

void flush_test()
{
    {
        temp_file tmp;
        stream_facade<file_sink> out(tmp.name());
        BOOST_CHECK(!out.flush());
    }
}

test_suite* init_unit_test_suite(int, char* []) 
{
    test_suite* test = BOOST_TEST_SUITE("flush test");
    test->add(BOOST_TEST_CASE(&flush_test));
    return test;
}
