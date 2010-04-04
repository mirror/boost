// Boost.Range library
//
//  Copyright Thorsten Ottosen 2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/range/combine.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <vector>


struct add
{
    template< class T >
    int operator()( const T& tuple ) const
    {
        return boost::get<0>(tuple) + boost::get<1>(tuple);
    }
};

template< class CombinedRng >
void apply( const CombinedRng& r ) 
{
    std::vector<int> v;
    for( typename boost::range_iterator<const CombinedRng>::type 
            i = boost::begin(r),
            e = boost::end(r);
         i != e; ++i )
    {
        
    }
}

void test_combine()
{
    std::vector<int> v1, v2, v3;
    v1 = boost::assign::list_of(1)(2)(3)(4);
    v2 = boost::assign::list_of(1)(2)(3)(4);

    int i1, i2;
    BOOST_FOREACH( boost::tie( i1, i2 ), boost::combine(v1,v2) )
    {
        v3.push_back( i1 + i2 );
    }

    BOOST_CHECK_EQUAL( v3.size(), v1.size() );
}



using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &test_combine ) );

    return test;
}


