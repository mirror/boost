//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/info.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
struct test_tag1 {};
struct test_tag2 {};
#endif

typedef boost::error_info<struct test_tag1,int> tagged_int1;
typedef boost::error_info<struct test_tag2,int> tagged_int2;

std::string
to_string( tagged_int2 const & x )
    {
    if( x.value()==42 )
        return "fourty-two";
    else
        return "bad value";
    }

struct
error1:
    public std::exception,
    public boost::exception
    {
    char const *
    what() const throw()
        {
        return "error1";
        }
    };

struct
error2:
    public boost::exception
    {
    };

int
main()
    {
    using namespace boost;
    try
        {
        error1 x; x << tagged_int1(42) << tagged_int2(42);
        BOOST_TEST(x.what()==std::string("error1"));
        throw x;
        }
    catch(
    boost::exception & x )
        {
        std::string di1=boost::diagnostic_information(x);
        x << tagged_int1(2) << tagged_int2(2);
        std::string di2 = diagnostic_information(x);
#ifndef BOOST_NO_RTTI
        BOOST_TEST(di1.find("type:")!=std::string::npos);
        BOOST_TEST(di1.find("error1")!=std::string::npos);
#endif
        BOOST_TEST(di1.find("test_tag1")!=std::string::npos);
        BOOST_TEST(di1.find("test_tag2")!=std::string::npos);
        BOOST_TEST(di1.find("fourty-two")!=std::string::npos);
#ifndef BOOST_NO_RTTI
        BOOST_TEST(di2.find("type:")!=std::string::npos);
        BOOST_TEST(di2.find("error1")!=std::string::npos);
#endif
        BOOST_TEST(di2.find("test_tag1")!=std::string::npos);
        BOOST_TEST(di2.find("test_tag2")!=std::string::npos);
        BOOST_TEST(di2.find("bad value")!=std::string::npos);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    try
        {
        error2 x;
        x << tagged_int1(42) << tagged_int2(42);
        throw x;
        }
    catch(
    boost::exception & x )
        {
        std::string di1 = diagnostic_information(x);
        x << tagged_int1(2) << tagged_int2(2);
        std::string di2 = diagnostic_information(x);
        BOOST_TEST( di1!=di2 );
        BOOST_TEST(di1.find("test_tag1")!=std::string::npos);
        BOOST_TEST(di1.find("test_tag2")!=std::string::npos);
        BOOST_TEST(di1.find("fourty-two")!=std::string::npos);
        BOOST_TEST(di2.find("test_tag1")!=std::string::npos);
        BOOST_TEST(di2.find("test_tag2")!=std::string::npos);
        BOOST_TEST(di2.find("bad value")!=std::string::npos);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    return boost::report_errors();
    }
