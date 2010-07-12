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
#include <boost/range/algorithm/search_n.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <algorithm>
#include <list>
#include <set>
#include <vector>

namespace
{
    template< class Container1, class Value >
    void test_search_n_impl(Container1& cont1, Value value)
    {
        typedef BOOST_DEDUCED_TYPENAME Container1::const_iterator const_iterator1_t;
        typedef BOOST_DEDUCED_TYPENAME Container1::iterator iterator1_t;

        const Container1& ccont1 = cont1;

        for (std::size_t n = 0; n < cont1.size(); ++n)
        {
            iterator1_t it = boost::search_n(cont1, n, value);
            BOOST_CHECK( it == boost::search_n(boost::make_iterator_range(cont1), n, value) );
            BOOST_CHECK( it == std::search_n(cont1.begin(), cont1.end(), n, value) );

            const_iterator1_t cit = boost::search_n(ccont1, n, value);
            BOOST_CHECK( cit == boost::search_n(boost::make_iterator_range(ccont1), n, value) );
            BOOST_CHECK( cit == std::search_n(ccont1.begin(), ccont1.end(), n, value) );
        }
    }

    template< class Container1, class Container2 >
    void test_search_n_impl()
    {
        using namespace boost::assign;

        Container1 cont1;

        test_search_n_impl(cont1, 1);

        cont1 += 1;
        test_search_n_impl(cont1, 1);
        test_search_n_impl(cont1, 0);

        cont1.clear();
        cont1 += 1,1;
        test_search_n_impl(cont1, 1);
        test_search_n_impl(cont1, 0);

        cont1 += 1,1,1;
        test_search_n_impl(cont1, 1);
        test_search_n_impl(cont1, 0);

        cont1.clear();
        cont1 += 1,2,3,4,5,6,7,8,9;
        test_search_n_impl(cont1, 1);
        test_search_n_impl(cont1, 2);
        test_search_n_impl(cont1, 5);
        test_search_n_impl(cont1, 9);
    }

    void test_search_n()
    {
        test_search_n_impl< std::list<int>, std::list<int> >();
        test_search_n_impl< std::vector<int>, std::vector<int> >();
        test_search_n_impl< std::set<int>, std::set<int> >();
        test_search_n_impl< std::list<int>, std::vector<int> >();
        test_search_n_impl< std::vector<int>, std::list<int> >();
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.algorithm.search_n" );

    test->add( BOOST_TEST_CASE( &test_search_n ) );

    return test;
}
