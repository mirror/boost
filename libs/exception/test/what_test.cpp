//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/exception/exception.hpp>
#include <exception>
#include <string>
#include <boost/detail/lightweight_test.hpp>

struct
test_exception:
    std::exception,
    boost::exception
    {
    char const *
    what() const throw()
        {
        return "test_exception";
        }
    };

int
main()
    {
    test_exception x;
    std::exception & sx(x);
    boost::exception & bx(x);
    BOOST_TEST(std::string(sx.what())=="test_exception");
    BOOST_TEST(std::string(bx.what())=="test_exception");
    return boost::report_errors();
    }
