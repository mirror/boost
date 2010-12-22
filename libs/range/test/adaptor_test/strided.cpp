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
        template< class Container >
        void strided_test_impl( Container& c, int stride_size )
        {
            using namespace boost::adaptors;

            // Rationale:
            // This requirement was too restrictive. It makes the use of the
            // strided adaptor too dangerous, and a simple solution existed
            // to make it safe, hence the strided adaptor has been modified
            // and this restriction no longer applies.
            //BOOST_ASSERT( c.size() % STRIDE_SIZE == 0 );

            Container reference;

            {
                typedef BOOST_DEDUCED_TYPENAME Container::const_iterator iterator_t;
                typedef BOOST_DEDUCED_TYPENAME Container::difference_type diff_t;
                typedef BOOST_DEDUCED_TYPENAME Container::size_type size_type;
                iterator_t it = c.begin();

                size_type count = c.size();
                size_type unreachable_element_count = c.size() - ((count / stride_size) * stride_size);
                diff_t offset = -static_cast<diff_t>(unreachable_element_count);
                iterator_t last = c.end();
                std::advance(last, offset);

                for (; it != last; std::advance(it, stride_size))
                {
                    reference.push_back(*it);
                }
            }

            Container test;
            boost::push_back( test, c | strided(stride_size) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test.begin(), test.end(),
                reference.begin(), reference.end() );

            Container test2;
            boost::push_back( test2, adaptors::stride(c, stride_size) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test2.begin(), test2.end(),
                reference.begin(), reference.end() );

            // Test the const versions:
            const Container& cc = c;
            Container test3;
            boost::push_back( test3, cc | strided(stride_size) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test3.begin(), test3.end(),
                reference.begin(), reference.end() );

            Container test4;
            boost::push_back( test4, adaptors::stride(cc, stride_size) );

            BOOST_CHECK_EQUAL_COLLECTIONS( test4.begin(), test4.end(),
                reference.begin(), reference.end() );
        }

        template< class Container >
        void strided_test_impl(int stride_size)
        {
            using namespace boost::assign;

            Container c;

            // Test empty
            strided_test_impl(c, stride_size);

            // Test two elements
            c += 1,2;
            strided_test_impl(c, stride_size);

            // Test many elements
            c += 1,1,1,2,2,3,4,5,6,6,6,7,8,9;
            strided_test_impl(c, stride_size);

            // Test an odd number of elements to determine that the relaxation
            // of the requirements has been successful
            // Test a sequence of length 1 with a stride of 2
            c.clear();
            c += 1;
            strided_test_impl(c, stride_size);

            // Test a sequence of length 2 with a stride of 2
            c.clear();
            c += 1,2;
            strided_test_impl(c, stride_size);

            // Test a sequence of length 3 with a stride of 2
            c.clear();
            c += 1,2,3;
            strided_test_impl(c, stride_size);
        }

        template<typename Container>
        void strided_test_zero_stride()
        {
            Container c;
            c.push_back(1);

            typedef boost::strided_range<Container> strided_range_t;
            strided_range_t rng( boost::adaptors::stride(c, 0) );
            typedef typename boost::range_iterator<strided_range_t>::type iter_t;

            iter_t first(boost::begin(c), 0);
            iter_t last(boost::end(c), 0);

            iter_t it = first;
            for (int i = 0; i < 10; ++i, ++it)
            {
                BOOST_CHECK(it == first);
            }
        }

        template<typename Container>
        void strided_test_impl()
        {
            strided_test_zero_stride< Container >();

            const int MAX_STRIDE_SIZE = 10;
            for (int stride_size = 1; stride_size <= MAX_STRIDE_SIZE; ++stride_size)
            {
                strided_test_impl< Container >(stride_size);
            }
        }

        void strided_test()
        {
            strided_test_impl< std::vector<int> >();
            strided_test_impl< std::deque<int> >();
            strided_test_impl< std::list<int> >();
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
