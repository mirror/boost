/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// test_nvp.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// should pass compilation and execution

#include <cstdio> // for tmpnam
#include <boost/config.hpp>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::tmpnam; }
#endif

#include <fstream>

#include "test_tools.hpp"

#include <boost/serialization/nvp.hpp>

#include "B.hpp"

int test_main( int argc, char* argv[] )
{
    const char * testfile = tmpnam(NULL);
    BOOST_REQUIRE(NULL != testfile);

    B b, b1;

    {   
        test_ostream os(testfile, TEST_STREAM_FLAGS);
        test_oarchive oa(os);
        oa << BOOST_SERIALIZATION_NVP(b);
    }
    {
        test_istream is(testfile, TEST_STREAM_FLAGS);
        test_iarchive ia(is);
        ia >> BOOST_SERIALIZATION_NVP(b1);
    }
    BOOST_CHECK(b == b1);

    B *bptr = &b;
    B *bptr1;

    {   
        test_ostream os(testfile, TEST_STREAM_FLAGS);
        test_oarchive oa(os);
        oa << BOOST_SERIALIZATION_NVP(bptr);
    }
    {
        test_istream is(testfile, TEST_STREAM_FLAGS);
        test_iarchive ia(is);
        ia >> BOOST_SERIALIZATION_NVP(bptr1);
    }
    BOOST_CHECK(b == *bptr1);

    return boost::exit_success;
}

// EOF
