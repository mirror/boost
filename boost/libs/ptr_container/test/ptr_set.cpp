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
 
#include "associative_test_data.hpp"
#include <boost/ptr_container/ptr_set.hpp>

void test_set()
{    

    ptr_set_test< ptr_set<Base>, Base, Derived_class >();
    ptr_set_test< ptr_set<Value>, Value, Value >();

    ptr_set_test< ptr_multiset<Base>, Base, Derived_class >();
    ptr_set_test< ptr_multiset<Value>, Value, Value >();

    ptr_set<int> set;

    BOOST_CHECK_THROW( set.insert( 0 ), bad_ptr_container_operation );
    set.insert( new int(0) );
    BOOST_CHECK_THROW( (set.replace(set.begin(), 0 )), bad_ptr_container_operation );
}

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_set ) );

    return test;
}






