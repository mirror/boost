
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/function.hpp>
#define BOOST_TEST_MODULE TestReturnSetGet
#include <boost/test/unit_test.hpp>
#include <string>

boost::function<void (const std::string&)> set;
boost::function<const std::string& (void)> get;

void action(void) {
    // State `message` hidden behind access functions from here.
    BOOST_CHECK( get() == "abc" );
    set("xyz");
    BOOST_CHECK( get() == "xyz" );
}

BOOST_AUTO_TEST_CASE( test_return_setget ) {
    std::string message = "abc"; // Reference valid where closure used.
    
    void BOOST_LOCAL_FUNCTION(bind& message, const std::string& text) {
        message = text;
    } BOOST_LOCAL_FUNCTION_NAME(s)
    set = s;

    const std::string& BOOST_LOCAL_FUNCTION(const bind& message) {
        return message;
    } BOOST_LOCAL_FUNCTION_NAME(g)
    get = g;
    
    action();
}

