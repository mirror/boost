// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>
#include <libs/multi_index/test/employee.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

using namespace boost;
using namespace boost::multi_index;
namespace ba =  boost::assign;

void test_multi_index_container()
{
    employee_set eset;
    
    eset = ba::list_of< employee >(1,"Franz",30)(2,"Hanz",40)(3,"Ilse",50);
    BOOST_CHECK( eset.size() == 3 );
    
    ba::insert( eset )(4,"Kurt",55)(5,"Bjarne",77)(7,"Thorsten",24);
    BOOST_CHECK( eset.size() == 6 );
    
    employee_set_by_name& name_index = eset.get<name>();
    employee_set_by_name::iterator i = name_index.find("Ilse");
    BOOST_CHECK( eset.project<1>(i)->id == 3 );
    BOOST_CHECK( eset.project<1>(i)->age == 50 );
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "List Test Suite" );

    test->add( BOOST_TEST_CASE( &test_multi_index_container ) );

    return test;
}


