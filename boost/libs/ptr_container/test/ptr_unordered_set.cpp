 
#include "associative_test_data.hpp2
#include "concept_check_data.hpp"
#include <boost/ptr_container/ptr_set.hpp>

void test_unordered_set()
{    
    typedef_test< ptr_set<Base>, Derived >();
    typedef_test< ptr_set<Value>, Value >();

    associative_container_test< ptr_set<Base>, Base, Derived >();
    associative_container_test< ptr_set<Value>, Value, Value >();
    
    typedef_test< ptr_multiset<Base>, Derived >();
    typedef_test< ptr_multiset<Value>, Value >();

    associative_container_test< ptr_multiset<Base>, Base, Derived >();
    associative_container_test< ptr_multiset<Value>, Value, Value >();

/*
    algo_test< ptr_vector<Value>, Value >();
    algo_test_polymorphic< ptr_vector<Base>, Derived >();
*/
    //c.insert( T() );
    //c.insert( t );

}


#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Smart Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_unordered_set ) );

    return test;
}





