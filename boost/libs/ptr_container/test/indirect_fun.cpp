 
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/list_inserter.hpp> 
#include <boost/test/test_tools.hpp>
#include <algorithm>
#include <functional>
#include <string>

bool lesser_than( const std::string& l, const std::string& r )
{
    return l < r;
}


void test_fun()
{
    using namespace boost;
    ptr_vector<std::string> vec;

    indirect_fun< std::less<std::string> > fun;

    std::string* ptr1  = new std::string("bar");
    std::string* ptr2  = new std::string("foo");
    BOOST_CHECK( fun( ptr1, ptr2 ) == true );
    
    void*       vptr1  = ptr1;
    void*       vptr2  = ptr2;
    void_ptr_indirect_fun< std::less<std::string>, std::string> cast_fun;
    BOOST_CHECK( cast_fun( vptr1, vptr2 ) == true );
    
    assign::push_back( vec )( new std::string("aa") )
                            ( new std::string("bb") )
                            ( new std::string("dd") )
                            ( new std::string("cc") )
                            ( new std::string("a") );
                              
    std::sort( vec.ptr_begin(), vec.ptr_end(), fun );
    BOOST_CHECK( vec[0] == "a" );
    BOOST_CHECK( vec[4] == "dd" );

    std::sort( vec.ptr_begin(), vec.ptr_end(), 
               make_indirect_fun( &lesser_than ) );
    BOOST_CHECK( vec[1] == "aa" );
    BOOST_CHECK( vec[2] == "bb" );    
    
}

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Smart Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_fun ) );

    return test;
}


