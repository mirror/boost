// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//


#include <boost/config.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/range/functions.hpp>
#include <boost/range/types.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <vector>

using namespace boost;
using boost::unit_test_framework::test_suite;

void check_std_container()
{
    typedef std::vector<int> vec_t;
    vec_t                    vec;
    vec.push_back( 3 ); vec.push_back( 4 );
    const vec_t              cvec( vec ); 

    BOOST_STATIC_ASSERT(( is_same< value_type_of<vec_t>::type, vec_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< iterator_of<vec_t>::type, vec_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( is_same< const_iterator_of<vec_t>::type, vec_t::const_iterator >::value ));
    BOOST_STATIC_ASSERT(( is_same< difference_type_of<vec_t>::type, vec_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< size_type_of<vec_t>::type, vec_t::size_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<vec_t>::type, vec_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( is_same< result_iterator_of<const vec_t>::type, vec_t::const_iterator >::value ));
    
    BOOST_STATIC_ASSERT(( is_same< value_type_of<const vec_t>::type, vec_t::value_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< iterator_of<const vec_t>::type, vec_t::iterator >::value ));
    BOOST_STATIC_ASSERT(( is_same< const_iterator_of<const vec_t>::type, vec_t::const_iterator >::value ));
    BOOST_STATIC_ASSERT(( is_same< difference_type_of<const vec_t>::type, vec_t::difference_type >::value ));
    BOOST_STATIC_ASSERT(( is_same< size_type_of<const vec_t>::type, vec_t::size_type >::value ));

    BOOST_CHECK( begin( vec ) == vec.begin() );
    BOOST_CHECK( end( vec )   == vec.end() );
    BOOST_CHECK( empty( vec ) == vec.empty() );
    BOOST_CHECK( size( vec ) == vec.size() );
    
    BOOST_CHECK( begin( cvec ) == cvec.begin() );
    BOOST_CHECK( end( cvec )   == cvec.end() );
    BOOST_CHECK( empty( cvec ) == cvec.empty() );
    BOOST_CHECK( size( cvec ) == cvec.size() );

}




#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_std_container ) );

    return test;
}






