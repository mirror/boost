 
#include <boost/ptr_container/ptr_vector.hpp>

template< class Cont >
void test_conversion()
{
    Cont c;
    // implicit conversion
    typedef typename Cont::iterator iter;
    iter i = c.ptr_begin();
    c.push_back( new int(4) );
    c.erase( iter( c.ptr_begin() ) );
}

void test_iterator()
{
    using namespace boost;
    ptr_vector<int> vec;
    ptr_vector<int>::iterator           mutable_i   = vec.begin();
    ptr_vector<int>::const_iterator     const_i     = vec.begin();
    ptr_vector<int>::ptr_iterator       mutable_ptr = vec.ptr_begin();
    ptr_vector<int>::ptr_const_iterator const_ptr   = vec.ptr_begin();
    
    const ptr_vector<int>& rvec               = vec;
    const_i                                   = rvec.begin();
    const_ptr                                 = rvec.ptr_begin();

    test_conversion< ptr_vector<int> >();
    
}

#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Pointer Container Test Suite" );

    test->add( BOOST_TEST_CASE( &test_iterator ) );

    return test;
}




