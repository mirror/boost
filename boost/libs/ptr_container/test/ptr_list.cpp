 
#include "sequence_test_data.hpp"
#include <boost/ptr_container/ptr_list.hpp>

void test_list()
{
    reversible_container_test< ptr_list<Base>, Base, Derived >();
    reversible_container_test< ptr_list<Value>, Value, Value >();
    reversible_container_test< ptr_list< nullable<Base> >, Base, Derived >();
    reversible_container_test< ptr_list< nullable<Value> >, Value, Value >();
}

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_list ) );

    return test;
}




