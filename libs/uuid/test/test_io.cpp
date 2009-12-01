//  (C) Copyright Andy Tompkins 2009. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  libs/uuid/test/test_io.cpp  -------------------------------//

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/output_test_stream.hpp>

#include <boost/lexical_cast.hpp>
#include <string>

int test_main(int, char*[])
{
    using namespace boost::uuids;
    using boost::test_tools::output_test_stream;

    const uuid u1 = {{0}};
    const uuid u2 = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
    const uuid u3 = {{0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef}};

    { // test insert/extract operators
        output_test_stream output;
        output << u1;
        BOOST_CHECK(!output.is_empty(false));
        BOOST_CHECK(output.check_length(36, false));
        BOOST_CHECK(output.is_equal("00000000-0000-0000-0000-000000000000"));

        output << u2;
        BOOST_CHECK(!output.is_empty(false));
        BOOST_CHECK(output.check_length(36, false));
        BOOST_CHECK(output.is_equal("00010203-0405-0607-0809-0a0b0c0d0e0f"));

        output << u3;
        BOOST_CHECK(!output.is_empty(false));
        BOOST_CHECK(output.check_length(36, false));
        BOOST_CHECK(output.is_equal("12345678-90ab-cdef-1234-567890abcdef"));
    }

    {
        uuid u;

        std::stringstream ss;
        ss << "00000000-0000-0000-0000-000000000000";
        ss >> u;
        BOOST_CHECK_EQUAL(u, u1);

        ss << "12345678-90ab-cdef-1234-567890abcdef";
        ss >> u;
        BOOST_CHECK_EQUAL(u, u3);
    }

    { // test with lexical_cast
        BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(u1), std::string("00000000-0000-0000-0000-000000000000"));
        BOOST_CHECK_EQUAL(boost::lexical_cast<uuid>("00000000-0000-0000-0000-000000000000"), u1);

        BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(u3), std::string("12345678-90ab-cdef-1234-567890abcdef"));
        BOOST_CHECK_EQUAL(boost::lexical_cast<uuid>("12345678-90ab-cdef-1234-567890abcdef"), u3);
    }

   return 0;
}
