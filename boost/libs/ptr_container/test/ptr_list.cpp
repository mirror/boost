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

#define PTR_LIST_TEST

#include "sequence_test_data.hpp"
#include <boost/ptr_container/ptr_list.hpp>

void list_algorithms_test();

void test_list()
{
    reversible_container_test< ptr_list<Base>, Base, Derived_class >();
    reversible_container_test< ptr_list<Value>, Value, Value >();
    reversible_container_test< ptr_list< nullable<Base> >, Base, Derived_class >();
    reversible_container_test< ptr_list< nullable<Value> >, Value, Value >();

    random_access_algorithms_test< ptr_list<int> >();
    //list_algorithms_test();
}


/*
void list_algorithms_test()
{
    ptr_set<int> c;
    IntContainer c;
    assign::push_back( c )
                    ( new int(1) )
                    ( new int(3) )
                    ( new int(6) )
                    ( new int(7) )
                    ( new int(2) )
                    ( new int(2) )
                    ( new int(0) )
                    ( new int(6) )
                    ( new int(3) );
    c.sort();
    BOOST_CHECK( is_sorted< std::less_equal<int> >( c ) );
    BOOST_CHECK_EQUAL( c.size(), 9u );

    c.unique();
    BOOST_CHECK_EQUAL( c.size(), 6u );
    BOOST_CHECK( c[0] == 0 );
    BOOST_CHECK( c[1] == 1 );
    BOOST_CHECK( c[2] == 2 );
    BOOST_CHECK( c[3] == 3 );
    BOOST_CHECK( c[4] == 6 );
    BOOST_CHECK( c[5] == 7 );

    c.erase_if( equal_to_int(1) );
    BOOST_CHECK_EQUAL( c.size(), 5u );
    BOOST_CHECK_EQUAL( c[0], 0 );
    BOOST_CHECK_EQUAL( c[1], 2 );

    c.erase_if( equal_to_int(7) );
    BOOST_CHECK_EQUAL( c.size(), 4u );
    BOOST_CHECK_EQUAL( c[3], 6 );

    // C = [0,2,3,6]

    IntContainer c2;
    assign::push_back( c2 )
                   ( new int(-1) )
                   ( new int(1) )
                   ( new int(4) )
                   ( new int(5) )
                   ( new int(7) );
    BOOST_CHECK( c2.size() == 5u );
    c.merge( c2 );
    BOOST_CHECK( c2.empty() );
    BOOST_CHECK( c.size() == 9u );
    BOOST_CHECK( is_sorted< std::less_equal<int> >( c ) );

}
*/

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_list ) );

    return test;
}




