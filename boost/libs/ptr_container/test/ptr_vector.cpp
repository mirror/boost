 
#include "sequence_test_data.hpp"
#include "concept_check_data.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/list_inserter.hpp>

void test_ptr_vector()
{ 
    reversible_container_test< ptr_vector<Base>, Base, Derived >();
    reversible_container_test< ptr_vector<Value>, Value, Value >();
    reversible_container_test< ptr_vector< nullable<Base> >, Base, Derived >();
    reversible_container_test< ptr_vector< nullable<Value> >, Value, Value >();

    ptr_vector<int> vec( 100u );
    BOOST_CHECK( vec.capacity() >= 100u );

    BOOST_CHECK_THROW( vec.push_back(0), bad_ptr_container_operation );
    BOOST_CHECK_THROW( (vec.insert( vec.begin(), 0 )), bad_ptr_container_operation );
    BOOST_CHECK_THROW( vec.at( 42 ), bad_ptr_container_operation );
    vec.push_back( new int(0) );
    BOOST_CHECK_THROW( (vec.replace(10u, new int(0))), bad_ptr_container_operation );
    BOOST_CHECK_THROW( (vec.replace(0u, 0)), bad_ptr_container_operation ); 

    assign::push_back( vec )( new int(2) )
                            ( new int(4) )
                            ( new int(6) )
                            ( new int(8) );
    ptr_vector<int> vec2;
    assign::push_back( vec2 )
                        ( new int(1) )
                        ( new int(3) )
                        ( new int(5) )
                        ( new int(7) );
    BOOST_CHECK( vec < vec2 );
    BOOST_CHECK( vec != vec2 );
    BOOST_CHECK( !(vec == vec2 ) );
    BOOST_CHECK( vec2 > vec );

}

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_ptr_vector ) );

    return test;
}




