///////////////////////////////////////////////////////////////////////////////
// misc2.hpp
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/xpressive/xpressive.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;
using namespace boost::xpressive;

///////////////////////////////////////////////////////////////////////////////
//
void test_complement()
{
    sregex rx1 = ~_n >> ~(set='a') >> ~(set='a','b') >> ~set['a'] >> ~_ln
        >> ~before('a') >> ~after('a') >> ~alpha >> ~range('a','b') >> ~_b >> ~as_xpr('a');

#ifndef BOOST_XPRESSIVE_NO_WREGEX
    wsregex rx2 = ~_n >> ~(set=L'a') >> ~(set=L'a',L'b') >> ~set[L'a'] >> ~_ln
        >> ~before(L'a') >> ~after(L'a') >> ~alpha >> ~range(L'a',L'b') >> ~_b >> ~as_xpr(L'a');
#endif
}

///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("miscelaneous tests");

    test->add(BOOST_TEST_CASE(&test_complement));

    return test;
}
