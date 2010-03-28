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
#include <boost/range/algorithm/mismatch.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <algorithm>
#include <list>
#include <set>
#include <vector>

namespace boost
{
    namespace
    {
        template< class Container1, class Container2 >
        void test_mismatch_impl()
        {
            using namespace boost::assign;

            typedef BOOST_DEDUCED_TYPENAME boost::remove_const<Container1>::type MutableContainer1;
            typedef BOOST_DEDUCED_TYPENAME boost::remove_const<Container2>::type MutableContainer2;

            MutableContainer1 cont1;
            const Container1& cref_cont1 = cont1;
            MutableContainer2 cont2;
            const Container2& cref_cont2 = cont2;

            typedef BOOST_DEDUCED_TYPENAME Container1::iterator iterator1_t;
            typedef BOOST_DEDUCED_TYPENAME Container1::const_iterator const_iterator1_t;
            typedef BOOST_DEDUCED_TYPENAME Container2::iterator iterator2_t;
            typedef BOOST_DEDUCED_TYPENAME Container2::const_iterator const_iterator2_t;

            typedef std::pair<iterator1_t,       iterator2_t>       pair_mmit_t;
            typedef std::pair<const_iterator1_t, iterator2_t>       pair_cmit_t;
            typedef std::pair<iterator1_t,       const_iterator2_t> pair_mcit_t;
            typedef std::pair<const_iterator1_t, const_iterator2_t> pair_ccit_t;

            pair_mmit_t pair_mmit = boost::mismatch(cont1, cont2);
            BOOST_CHECK( pair_mmit.first == cont1.end() );
            BOOST_CHECK( pair_mmit.second == cont2.end() );
            pair_mmit = boost::mismatch(cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mmit.first == cont1.end() );
            BOOST_CHECK( pair_mmit.second == cont2.end() );

            pair_cmit_t pair_cmit = boost::mismatch(cref_cont1, cont2);
            BOOST_CHECK( pair_cmit.first == cref_cont1.end() );
            BOOST_CHECK( pair_cmit.second == cont2.end() );
            pair_cmit = boost::mismatch(cref_cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_cmit.first == cref_cont1.end() );
            BOOST_CHECK( pair_cmit.second == cont2.end() );

            pair_mcit_t pair_mcit = boost::mismatch(cont1, cref_cont2);
            BOOST_CHECK( pair_mcit.first == cont1.end() );
            BOOST_CHECK( pair_mcit.second == cref_cont2.end() );
            pair_mcit = boost::mismatch(cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mcit.first == cont1.end() );
            BOOST_CHECK( pair_mcit.second == cref_cont2.end() );

            pair_ccit_t pair_ccit = boost::mismatch(cref_cont1, cref_cont2);
            BOOST_CHECK( pair_ccit.first == cref_cont1.end() );
            BOOST_CHECK( pair_ccit.second == cref_cont2.end() );
            pair_ccit = boost::mismatch(cref_cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_ccit.first == cref_cont1.end() );
            BOOST_CHECK( pair_ccit.second == cref_cont2.end() );

            cont1 += 1,2,3,4;
            cont2 += 1,2,3,4;
            pair_mmit = boost::mismatch(cont1, cont2);
            BOOST_CHECK( pair_mmit.first == cont1.end() );
            BOOST_CHECK( pair_mmit.second == cont2.end() );
            pair_mmit = boost::mismatch(cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mmit.first == cont1.end() );
            BOOST_CHECK( pair_mmit.second == cont2.end() );

            pair_cmit = boost::mismatch(cref_cont1, cont2);
            BOOST_CHECK( pair_cmit.first == cref_cont1.end() );
            BOOST_CHECK( pair_cmit.second == cont2.end() );
            pair_cmit = boost::mismatch(cref_cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_cmit.first == cref_cont1.end() );
            BOOST_CHECK( pair_cmit.second == cont2.end() );

            pair_mcit = boost::mismatch(cont1, cref_cont2);
            BOOST_CHECK( pair_mcit.first == cont1.end() );
            BOOST_CHECK( pair_mcit.second == cref_cont2.end() );
            pair_mcit = boost::mismatch(cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mcit.first == cont1.end() );
            BOOST_CHECK( pair_mcit.second == cref_cont2.end() );

            pair_ccit = boost::mismatch(cref_cont1, cref_cont2);
            BOOST_CHECK( pair_ccit.first == cref_cont1.end() );
            BOOST_CHECK( pair_ccit.second == cref_cont2.end() );
            pair_ccit = boost::mismatch(cref_cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_ccit.first == cref_cont1.end() );
            BOOST_CHECK( pair_ccit.second == cref_cont2.end() );

            cont1.clear();
            cont2.clear();
            cont1 += 1,2,3,4;
            cont2 += 1,2,5,4;
            pair_mmit = boost::mismatch(cont1, cont2);
            BOOST_CHECK( pair_mmit.first != cont1.end() && *pair_mmit.first == 3 );
            BOOST_CHECK( pair_mmit.second != cont2.end() && *pair_mmit.second == 5 );
            pair_mmit = boost::mismatch(cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mmit.first != cont1.end() && *pair_mmit.first == 3 );
            BOOST_CHECK( pair_mmit.second != cont2.end() && *pair_mmit.second == 5 );
            pair_mmit = boost::mismatch(cont1, cont2, std::not_equal_to<int>());
            BOOST_CHECK( pair_mmit.first == cont1.begin() );
            BOOST_CHECK( pair_mmit.second == cont2.begin() );

            pair_cmit = boost::mismatch(cref_cont1, cont2);
            BOOST_CHECK( pair_cmit.first != cref_cont1.end() && *pair_cmit.first == 3 );
            BOOST_CHECK( pair_cmit.second != cont2.end() && *pair_cmit.second == 5 );
            pair_cmit = boost::mismatch(cref_cont1, cont2, std::equal_to<int>());
            BOOST_CHECK( pair_cmit.first != cref_cont1.end() && *pair_cmit.first == 3 );
            BOOST_CHECK( pair_cmit.second != cont2.end() && *pair_cmit.second == 5 );
            pair_cmit = boost::mismatch(cref_cont1, cont2, std::not_equal_to<int>());
            BOOST_CHECK( pair_cmit.first == cref_cont1.begin() );
            BOOST_CHECK( pair_cmit.second == cont2.begin() );

            pair_mcit = boost::mismatch(cont1, cref_cont2);
            BOOST_CHECK( pair_mcit.first != cont1.end() && *pair_mcit.first == 3 );
            BOOST_CHECK( pair_mcit.second != cref_cont2.end() && *pair_mcit.second == 5 );
            pair_mcit = boost::mismatch(cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_mcit.first != cont1.end() && *pair_mcit.first == 3 );
            BOOST_CHECK( pair_mcit.second != cref_cont2.end() && *pair_mcit.second == 5 );
            pair_mcit = boost::mismatch(cont1, cref_cont2, std::not_equal_to<int>());
            BOOST_CHECK( pair_mcit.first == cont1.begin() );
            BOOST_CHECK( pair_mcit.second == cref_cont2.begin() );

            pair_ccit = boost::mismatch(cref_cont1, cref_cont2);
            BOOST_CHECK( pair_ccit.first != cref_cont1.end() && *pair_ccit.first == 3 );
            BOOST_CHECK( pair_ccit.second != cref_cont2.end() && *pair_ccit.second == 5 );
            pair_ccit = boost::mismatch(cref_cont1, cref_cont2, std::equal_to<int>());
            BOOST_CHECK( pair_ccit.first != cref_cont1.end() && *pair_ccit.first == 3 );
            BOOST_CHECK( pair_ccit.second != cref_cont2.end() && *pair_ccit.second == 5 );
            pair_ccit = boost::mismatch(cref_cont1, cref_cont2, std::not_equal_to<int>());
            BOOST_CHECK( pair_ccit.first == cref_cont1.begin() );
            BOOST_CHECK( pair_ccit.second == cref_cont2.begin() );
        }

        void test_mismatch()
        {
            test_mismatch_impl< std::list<int>, std::list<int> >();
            test_mismatch_impl< const std::list<int>, std::list<int> >();
            test_mismatch_impl< std::list<int>, const std::list<int> >();
            test_mismatch_impl< const std::list<int>, const std::list<int> >();

            test_mismatch_impl< std::vector<int>, std::list<int> >();
            test_mismatch_impl< const std::vector<int>, std::list<int> >();
            test_mismatch_impl< std::vector<int>, const std::list<int> >();
            test_mismatch_impl< const std::vector<int>, const std::list<int> >();

            test_mismatch_impl< std::list<int>, std::vector<int> >();
            test_mismatch_impl< const std::list<int>, std::vector<int> >();
            test_mismatch_impl< std::list<int>, const std::vector<int> >();
            test_mismatch_impl< const std::list<int>, const std::vector<int> >();
        }
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.algorithm.mismatch" );

    test->add( BOOST_TEST_CASE( &boost::test_mismatch ) );

    return test;
}
