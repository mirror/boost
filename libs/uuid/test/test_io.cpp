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
#include <boost/detail/lightweight_test.hpp>

#include <boost/lexical_cast.hpp>
#include <string>

int main(int, char*[])
{
    using namespace boost::uuids;

    const uuid u1 = {{0}};
    const uuid u2 = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
    const uuid u3 = {{0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef,0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef}};

    { // test insert/extract operators
        std::stringstream ss1;
        ss1 << u1;
        BOOST_TEST_EQ(ss1.str(), "00000000-0000-0000-0000-000000000000");

        std::stringstream ss2;
        ss2 << u2;
        BOOST_TEST_EQ(ss2.str(), "00010203-0405-0607-0809-0a0b0c0d0e0f");

        std::stringstream ss3;
        ss3 << u3;
        BOOST_TEST_EQ(ss3.str(), "12345678-90ab-cdef-1234-567890abcdef");
    }

    {
        uuid u;

        std::stringstream ss;
        ss << "00000000-0000-0000-0000-000000000000";
        ss >> u;
        BOOST_TEST_EQ(u, u1);

        ss << "12345678-90ab-cdef-1234-567890abcdef";
        ss >> u;
        BOOST_TEST_EQ(u, u3);
    }

    { // test with lexical_cast
        BOOST_TEST_EQ(boost::lexical_cast<std::string>(u1), std::string("00000000-0000-0000-0000-000000000000"));
        BOOST_TEST_EQ(boost::lexical_cast<uuid>("00000000-0000-0000-0000-000000000000"), u1);

        BOOST_TEST_EQ(boost::lexical_cast<std::string>(u3), std::string("12345678-90ab-cdef-1234-567890abcdef"));
        BOOST_TEST_EQ(boost::lexical_cast<uuid>("12345678-90ab-cdef-1234-567890abcdef"), u3);
    }

   return boost::report_errors();
}
