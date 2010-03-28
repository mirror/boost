// Boost.Range library
//
//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/adaptor/strided.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <boost/range/algorithm_ext.hpp>

#include <algorithm>
#include <deque>
#include <vector>

namespace boost
{
    namespace
    {
        const int STRIDE_SIZE = 2;

        template< class Container >
        void strided_test_impl( Container& c )
        {
            using namespace boost::adaptors;

            BOOST_ASSERT( c.size() % STRIDE_SIZE == 0 );

            Container reference;

            {
                typedef BOOST_DEDUCED_TYPENAME Container::const_iterator iterator_t;
                iterator_t it = c.begin();
                for (iterator_t last = c.end();
                        it != last; it += STRIDE_SIZE)
                {
                    reference.push_back(*it);
                }
            }

            Container test;
            boost::push_back( test, c | strided(2) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test.begin(), test.end(),
                reference.begin(), reference.end() );

            Container test2;
            boost::push_back( test2, adaptors::stride(c, 2) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test2.begin(), test2.end(),
                reference.begin(), reference.end() );

            // Test the const versions:
            const Container& cc = c;
            Container test3;
            boost::push_back( test3, cc | strided(2) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test3.begin(), test3.end(),
                reference.begin(), reference.end() );

            Container test4;
            boost::push_back( test4, adaptors::stride(cc, 2) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test4.begin(), test4.end(),
                reference.begin(), reference.end() );
        }

        template< class Container >
        void strided_test_impl()
        {
            using namespace boost::assign;

            Container c;

            // Test empty
            strided_test_impl(c);

            // Test two elements
            c += 1,2;
            strided_test_impl(c);

            // Test many elements
            c += 1,1,1,2,2,3,4,5,6,6,6,7,8,9;
            strided_test_impl(c);
        }

        void strided_test()
        {
            strided_test_impl< std::vector< int > >();
            strided_test_impl< std::deque< int > >();
        }
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.adaptor.strided" );

    test->add( BOOST_TEST_CASE( &boost::strided_test ) );

    return test;
}
