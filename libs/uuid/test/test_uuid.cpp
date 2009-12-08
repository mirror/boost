//  (C) Copyright Andy Tompkins 2007. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  libs/uuid/test/test_uuid.cpp  -------------------------------//

#include <boost/uuid/uuid.hpp>

#include <boost/test/included/test_exec_monitor.hpp>
#include <boost/test/test_tools.hpp>

#include <boost/functional/hash.hpp>

#include <boost/uuid/uuid_io.hpp>

int test_main(int, char*[])
{
    using namespace boost::uuids;
    using boost::test_tools::output_test_stream;

    // uuid::static_size
    BOOST_CHECK_EQUAL(uuid::static_size(), 16U);

    { // uuid::operator=()
        uuid u1 = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
        uuid u2 = u1;
        BOOST_CHECK_EQUAL(u2, u1);
    }

    { // uuid::begin(), end()
        uuid u = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
        unsigned char values[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        BOOST_CHECK_EQUAL_COLLECTIONS(u.begin(), u.end(), values, values+16);
    }

    { // uuid::begin() const, end() const
        const uuid u = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
        unsigned char values[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        BOOST_CHECK_EQUAL_COLLECTIONS(u.begin(), u.end(), values, values+16);
    }
    
     { // uuid::size()
        uuid u; // uninitialized
        BOOST_CHECK_EQUAL(u.size(), 16U);
    }

    { // uuid::is_nil()
        uuid u1 = {{0}};
        BOOST_CHECK_EQUAL(u1.is_nil(), true);

        uuid u2 = {{1,0}};
        BOOST_CHECK_EQUAL(u2.is_nil(), false);
    }
    
    { // uuid::variant()
        struct Test {
            unsigned char octet7;
            boost::uuids::uuid::variant_type variant;
        };
        const Test tests[] =
            { { 0x00, boost::uuids::uuid::variant_ncs }
            , { 0x10, boost::uuids::uuid::variant_ncs }
            , { 0x20, boost::uuids::uuid::variant_ncs }
            , { 0x30, boost::uuids::uuid::variant_ncs }
            , { 0x40, boost::uuids::uuid::variant_ncs }
            , { 0x50, boost::uuids::uuid::variant_ncs }
            , { 0x60, boost::uuids::uuid::variant_ncs }
            , { 0x70, boost::uuids::uuid::variant_ncs }
            , { 0x80, boost::uuids::uuid::variant_rfc_4122 }
            , { 0x90, boost::uuids::uuid::variant_rfc_4122 }
            , { 0xa0, boost::uuids::uuid::variant_rfc_4122 }
            , { 0xb0, boost::uuids::uuid::variant_rfc_4122 }
            , { 0xc0, boost::uuids::uuid::variant_microsoft }
            , { 0xd0, boost::uuids::uuid::variant_microsoft }
            , { 0xe0, boost::uuids::uuid::variant_future }
            , { 0xf0, boost::uuids::uuid::variant_future }
            };
        for (size_t i=0; i<sizeof(tests)/sizeof(Test); i++) {
            uuid u = {};
            u.data[8] = tests[i].octet7; // note that octet7 is array index 8
            
            BOOST_CHECK_EQUAL(u.variant(), tests[i].variant);
        }
    }
    
     { // uuid::version()
        struct Test {
            unsigned char octet9;
            boost::uuids::uuid::version_type version;
        };
        const Test tests[] =
            { { 0x00, boost::uuids::uuid::version_unknown }
            , { 0x10, boost::uuids::uuid::version_time_based }
            , { 0x20, boost::uuids::uuid::version_dce_security }
            , { 0x30, boost::uuids::uuid::version_name_based_md5 }
            , { 0x40, boost::uuids::uuid::version_random_number_based }
            , { 0x50, boost::uuids::uuid::version_name_based_sha1 }
            , { 0x60, boost::uuids::uuid::version_unknown }
            , { 0x70, boost::uuids::uuid::version_unknown }
            , { 0x80, boost::uuids::uuid::version_unknown }
            , { 0x90, boost::uuids::uuid::version_unknown }
            , { 0xa0, boost::uuids::uuid::version_unknown }
            , { 0xb0, boost::uuids::uuid::version_unknown }
            , { 0xc0, boost::uuids::uuid::version_unknown }
            , { 0xd0, boost::uuids::uuid::version_unknown }
            , { 0xe0, boost::uuids::uuid::version_unknown }
            , { 0xf0, boost::uuids::uuid::version_unknown }
            };
        for (size_t i=0; i<sizeof(tests)/sizeof(Test); i++) {
            uuid u = {{0}};
            u.data[6] = tests[i].octet9; // note that octet9 is array index 8
            
            BOOST_CHECK_EQUAL(u.version(), tests[i].version);
        }
    }

    { // uuid::swap(), swap()
        uuid u1 = {{0}};
        uuid u2 = {{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}};
        u1.swap(u2);
        
        unsigned char values1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        unsigned char values2[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
        BOOST_CHECK_EQUAL_COLLECTIONS(u1.begin(), u1.end(), values2, values2+16);
        BOOST_CHECK_EQUAL_COLLECTIONS(u2.begin(), u2.end(), values1, values1+16);

        swap(u1, u2);
        BOOST_CHECK_EQUAL_COLLECTIONS(u1.begin(), u1.end(), values1, values1+16);
        BOOST_CHECK_EQUAL_COLLECTIONS(u2.begin(), u2.end(), values2, values2+16);
    }

    { // test comparsion
        uuid u1 = {{0}};
        uuid u2 = {{1,0}};
        uuid u3 = {{255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}};

        BOOST_CHECK_EQUAL(u1, u1);

        BOOST_CHECK_NE(u1, u2);
   
        BOOST_CHECK_LT(u1, u2);
        BOOST_CHECK_LT(u2, u3);

        BOOST_CHECK_LE(u1, u1);
        BOOST_CHECK_LE(u1, u2);
        BOOST_CHECK_LE(u2, u3);

        BOOST_CHECK_GT(u2, u1);
        BOOST_CHECK_GT(u3, u1);

        BOOST_CHECK_GE(u3, u3);
        BOOST_CHECK_GE(u2, u1);
        BOOST_CHECK_GE(u3, u1);
    }
    
    { // test hash
        uuid u1 = {{0}};
        uuid u2 = {{1,0}};
        uuid u3 = {{255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}};

        boost::hash<uuid> uuid_hasher;
        
        BOOST_CHECK_EQUAL(uuid_hasher(u1), boost::hash_range(u1.begin(), u1.end()));
        BOOST_CHECK_EQUAL(uuid_hasher(u2), boost::hash_range(u2.begin(), u2.end()));
        BOOST_CHECK_EQUAL(uuid_hasher(u3), boost::hash_range(u3.begin(), u3.end()));
    }
    
    { // test is_pod
        BOOST_CHECK_EQUAL(boost::is_pod<uuid>::value, true);
    }

    return 0;
}
