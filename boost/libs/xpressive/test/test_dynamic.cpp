///////////////////////////////////////////////////////////////////////////////
// test_dynamic.cpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/xpressive/xpressive_dynamic.hpp>
#include "./test_minimal.hpp"

///////////////////////////////////////////////////////////////////////////////
// test_main
int test_main( int, char*[] )
{
    using namespace boost::xpressive;

    std::string str("bar");
    sregex rx = sregex::compile("b.*ar");
    smatch what;

    if(!regex_match(str, what, rx))
    {
        BOOST_ERROR("oops");
    }

    return 0;
}
