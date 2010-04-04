//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#include <boost/range/algorithm/stable_partition.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include "../test_driver/range_return_test_driver.hpp"
#include <algorithm>
#include <functional>
#include <list>
#include <numeric>
#include <deque>
#include <vector>

namespace boost
{
    namespace
    {
        struct equal_to_5
        {
            typedef bool result_type;
            typedef int argument_type;
            bool operator()(int x) const { return x == 5; }
        };

        // test the 'partition' algorithm
        template<class UnaryPredicate>
        class stable_partition_test_policy
        {
        public:
            template< class Container >
            BOOST_DEDUCED_TYPENAME range_iterator<Container>::type
            test_iter(Container& cont)
            {
                return boost::stable_partition(cont, UnaryPredicate());
            }

	        UnaryPredicate pred() const { return UnaryPredicate(); }

            template< range_return_value return_type >
	        struct test_range
	        {
		        template< class Container, class Policy >
		        BOOST_DEDUCED_TYPENAME range_return<Container,return_type>::type
		        operator()(Policy& policy, Container& cont)
		        {
		            return boost::stable_partition<return_type>(cont, policy.pred());
		        }
            };

            template< class Container >
            BOOST_DEDUCED_TYPENAME range_iterator<Container>::type
            reference(Container& cont)
            {
                return std::stable_partition(cont.begin(), cont.end(), UnaryPredicate());
            }
        };

        template<class Container>
        void test_stable_partition_impl()
        {
            using namespace boost::assign;

            range_test::range_return_test_driver test_driver;

            stable_partition_test_policy< equal_to_5 > policy;

            Container cont;
            test_driver(cont, policy);

            cont.clear();
            cont += 1;
            test_driver(cont, policy);

            cont.clear();
            cont += 1,2,2,2,2,2,3,4,5,6,7,8,9;
            test_driver(cont, policy);

            cont.clear();
            cont += 1,2,2,2,2,2,3,3,3,3,4,4,4,4,4,4,4,5,6,7,8,9;
            test_driver(cont, policy);
        }

        void test_stable_partition()
        {
            test_stable_partition_impl< std::vector<int> >();
            test_stable_partition_impl< std::list<int> >();
            test_stable_partition_impl< std::deque<int> >();
        }
    }
}


boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.algorithm.stable_partition" );

    test->add( BOOST_TEST_CASE( &boost::test_stable_partition ) );

    return test;
}
