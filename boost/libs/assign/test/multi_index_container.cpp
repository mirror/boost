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



//
// Define a multi_index_container with a list-like index and an ordered index
//
typedef multi_index_container<
  std::string,
  indexed_by<
    sequenced<>,                               // list-like index
    ordered_non_unique<identity<std::string> > // words by alphabetical order
  >
> text_container;



void test_multi_index_container()
{
    employee_set eset = ba::list_of< employee >(1,"Franz",30)(2,"Hanz",40)(3,"Ilse",50);
    BOOST_CHECK( eset.size() == 3u );
    
    //
    // This container is associative, hence we can use 'insert()' 
    // 
    
    ba::insert( eset )(4,"Kurt",55)(5,"Bjarne",77)(7,"Thorsten",24);
    BOOST_CHECK( eset.size() == 6u );
    
    employee_set_by_name& name_index = eset.get<name>();
    employee_set_by_name::iterator i = name_index.find("Ilse");
    BOOST_CHECK( eset.project<1>(i)->id == 3 );
    BOOST_CHECK( eset.project<1>(i)->age == 50 );
    
    text_container text = ba::list_of< std::string >("Have")("you")("ever")("wondered")("how")("much")("Boost")("rocks?!");
    BOOST_CHECK_EQUAL( text.size(), 8u );
    BOOST_CHECK_EQUAL( *text.begin(), "Have" );
    
    //
    // This container is a sequence, hence we can use 'push_back()' and 'push_font()'
    //
    
    ba::push_back( text )("Well")(",")("A")("LOT")(",")("obviously!");
    BOOST_CHECK_EQUAL( text.size(), 14u );
    BOOST_CHECK_EQUAL( *--text.end(), "obviously!" );
    
    ba::push_front( text ) = "question:", "simple", "A";
    BOOST_CHECK_EQUAL( text.size(), 17u );
    BOOST_CHECK_EQUAL( text.front(), "A" );
}



#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "List Test Suite" );

    test->add( BOOST_TEST_CASE( &test_multi_index_container ) );

    return test;
}


