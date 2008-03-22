//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//
 
#include <boost/ptr_container/ptr_map.hpp>
#include <string>

using namespace std;

int test_main( int, char*[] )
{
    typedef_test< ptr_map<int, Base>, Derived >();
    typedef_test< ptr_map<int, Value>, Value >();

    associative_container_test< ptr_map<int, Base>, Base, Derived >();
    associative_container_test< ptr_map<int, Value>, Value, Value >();
    
    typedef_test< ptr_multimap<int, Base>, Derived >();
    typedef_test< ptr_multimap<int, Value>, Value >();

    associative_container_test< ptr_multimap<int, Base>, Base, Derived >();
    associative_container_test< ptr_multimap<int, Value>, Value, Value >();
    
    string joe   = "joe";
    string brian = "brian";
    
    ptr_map<string,int> m;
    m.insert( joe, new int( 4 ) );
    m.insert( brian, std::auto_ptr<int>( new int( 6 ) ) );
    m[ joe ]   += 56;
    m[ brian ] += 10;

    try
    {
        m[ "hans" ] = 4;
    }
    catch( const bad_ptr_container_operation& )
    { }

    return 0;
}


#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_container_adapter ) );

    return test;
}





