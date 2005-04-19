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


#include <boost/assign/ptr_list_inserter.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_set.hpp>

struct Foo
{
    int i;
    
    Foo() : i(0)
    { }
    Foo( int i ) : i(i)
    { }
    Foo( int i, int ) : i(i)
    { }
    Foo( const char*, int i, int ) : i(i)
    { }
};

inline bool operator<( Foo l, Foo r )
{
    return l.i < r.i;
}

void check_ptr_list_inserter()
{
    using namespace std;
    using namespace boost;
    using namespace boost::assign;

    ptr_deque<Foo> deq;
    ptr_push_back( deq )()();
    BOOST_CHECK( deq.size() == 2u );
    ptr_push_front( deq )( 3 )( 42, 42 )( "foo", 42, 42 );
    BOOST_CHECK( deq.size() == 5 );

    ptr_set<Foo> a_set;
    ptr_insert( a_set )()( 1 )( 2, 2 )( "foo", 3, 3 );
    BOOST_CHECK( a_set.size() == 4 );
    ptr_insert( a_set )()()()();
    BOOST_CHECK( a_set.size() == 4 ); // duplicates not inserted
                        
}



#include <boost/test/unit_test.hpp>
using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "List Test Suite" );

    test->add( BOOST_TEST_CASE( &check_ptr_list_inserter ) );

    return test;
}

