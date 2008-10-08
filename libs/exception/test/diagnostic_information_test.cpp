//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/info.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
struct test_tag {};
#endif

typedef boost::error_info<struct test_tag,int> tag_int;

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
        error1 x; x << tag_int(42);
        BOOST_TEST(x.what()==std::string("error1"));
        throw x;
        }
    catch(
    boost::exception & x )
        {
        std::string di=boost::diagnostic_information(x);
#ifndef BOOST_NO_RTTI
        BOOST_TEST(di.find("type:")!=std::string::npos);
        BOOST_TEST(di.find("error1")!=std::string::npos);
#endif
        BOOST_TEST(di.find("test_tag")!=std::string::npos);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    try
        {
        error2 x;
        x << tag_int(1);
        throw x;
        }
    catch(
    boost::exception & x )
        {
        std::string w1 = diagnostic_information(x);
        x << tag_int(2);
        std::string w2 = diagnostic_information(x);
        BOOST_TEST( w1!=w2 );
        BOOST_TEST(w1.find("test_tag")!=std::string::npos);
        BOOST_TEST(w2.find("test_tag")!=std::string::npos);
        }
    catch(
    ... )
        {
        BOOST_TEST(false);
        }
    return boost::report_errors();
    }
