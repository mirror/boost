// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//

#include <boost/assign.hpp>
#include <string>
#include <vector>
#include <map>

using namespace std;
using namespace boost::assign;

void check_basic_usage()
{
    vector<int> v;
    v += 3,4,5,6,7,8,9;
    push_back( v )(10)(11);
    map<string,int> m;
    insert( m )( "foo", 1 )( "bar", 2 );
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Assign Test Suite" );

    test->add( BOOST_TEST_CASE( &check_basic_usage ) );

    return test;
}

