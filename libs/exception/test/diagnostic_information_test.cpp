//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception/info.hpp>
#include <boost/detail/lightweight_test.hpp>

typedef boost::error_info<struct tag,int> tag_int;

struct
error1:
    public std::exception
    {
    char const *
    what() const throw()
        {
        return "error1";
        }
    };

struct
error2:
    public std::exception,
    public boost::exception
    {
    char const *
    what() const throw()
        {
        return "error2";
        }
    };

struct
error3:
    public boost::exception
    {
    };

std::string
get_diagnostic_information( std::exception const & x )
    {
    return boost::diagnostic_information(x);
    }

int
main()
    {
    using namespace boost;
        {
        error1 x;
		BOOST_TEST(x.what()==std::string("error1"));
        std::string di=get_diagnostic_information(x);
        BOOST_TEST(di.find("type:")!=std::string::npos);
        BOOST_TEST(di.find("error1")!=std::string::npos);
        }
        {
        error2 x; x << tag_int(42);
		BOOST_TEST(x.what()==std::string("error2"));
        std::string di=get_diagnostic_information(x);
        BOOST_TEST(di.find("type:")!=std::string::npos);
        BOOST_TEST(di.find("error2")!=std::string::npos);
        }
        {
        error3 x;
        x << tag_int(1);
        std::string w1 = x.diagnostic_information();
        x << tag_int(2);
        std::string w2 = x.diagnostic_information();
        BOOST_TEST( w1!=w2 );
        }
    return boost::report_errors();
    }
