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
#include <boost/range/adaptor/uniqued.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/assign.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/sub_range.hpp>

#include <algorithm>
#include <list>
#include <set>
#include <vector>

#include <functional>
namespace boost
{
    namespace range3
    {
        namespace concept
        {
            template<class Range>
            class PopFrontSubRange
            {
            public:
                void constraints()
                {
                    Range copied_range(*m_range);
                    BOOST_DEDUCED_TYPENAME range_value<Range>::type v = copied_range.front();
                    copied_range.pop_front();
                }
            private:
                Range* m_range;
            };

            template<class Range>
            class PopBackSubRange
            {
            public:
                void constraints()
                {
                    Range copied_range(*m_range);
                    BOOST_DEDUCED_TYPENAME range_value<Range>::type v = copied_range.back();
                    copied_range.pop_back();
                }
            private:
                Range* m_range;
            };
        } // namespace concept
        namespace adaptor
        {
            template<class Range, class Pred>
            class adjacent_filter_adaptor
                : private boost::sub_range<Range>
                , private Pred
            {
            public:
                typedef boost::sub_range<Range> range_t;
                typedef Pred pred_t;
                typedef typename range_t::value_type value_type;
                using range_t::reference;
                using range_t::const_reference;
                using range_t::empty;
                using range_t::front;
                using range_t::back;

                adjacent_filter_adaptor(Range& rng, Pred pred)
                : range_t(rng)
                , pred_t(pred)
                {
                }

                void pop_front()
                {
                    BOOST_ASSERT( !empty() );
                    const value_type& old_front = front();
                    range_t::pop_front();
                    while (!empty() && !pred_t::operator()(front(), old_front))
                        range_t::pop_front();
                }

                void pop_back()
                {
                    BOOST_ASSERT( !empty() );
                    const value_type& old_back = back();
                    range_t::pop_back();
                    while (!empty() && !pred_t::operator()(old_back, back()))
                        range_t::pop_back();
                }
            };

            template<class Range>
            class unique_adaptor
                : public adjacent_filter_adaptor<Range, std::not_equal_to< typename range_value<Range>::type > >
            {
                typedef adjacent_filter_adaptor<Range, std::not_equal_to< typename range_value<Range>::type > > base_t;
            public:
                typedef std::not_equal_to< typename range_value<Range>::type > pred_t;
                explicit unique_adaptor(Range& rng) : base_t(rng, pred_t()) {}
            };
        }
    }

    namespace
    {
        template< class Container >
        void new_uniqued_adaptor_test(Container& c)
        {
            std::vector<int> test_result1;
            boost::range3::adaptor::unique_adaptor<Container> rng(c);
            while (!rng.empty())
            {
                test_result1.push_back(rng.front());
                rng.pop_front();
            }

            std::vector<int> test_result2;
            boost::push_back(test_result2, adaptors::unique(c));

            BOOST_CHECK_EQUAL_COLLECTIONS(
                test_result1.begin(), test_result1.end(),
                test_result2.begin(), test_result2.end()
                );
        }

        template< class Container >
        void uniqued_test_impl( Container& c )
        {
            new_uniqued_adaptor_test(c);

            using namespace boost::adaptors;

            std::vector< int > test_result1;
            boost::push_back(test_result1, c | uniqued);

            std::vector< int > test_result2;
            boost::push_back(test_result2, adaptors::unique(c));

            std::vector< int > reference(c.begin(), c.end());
            reference.erase(
                std::unique(reference.begin(), reference.end()),
                reference.end());

            BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                                           test_result1.begin(), test_result1.end() );

            BOOST_CHECK_EQUAL_COLLECTIONS( reference.begin(), reference.end(),
                                           test_result2.begin(), test_result2.end() );
        }

        template< class Container >
        void uniqued_test_impl()
        {
            using namespace boost::assign;

            Container c;

            // Test empty
            uniqued_test_impl(c);

            // Test one
            c += 1;
            uniqued_test_impl(c);

            // Test many
            c += 1,1,1,2,2,2,2,2,3,3,3,3,4,5,6,6,6,7,7,7,8,8,9,9,9,9,9,10;
            uniqued_test_impl(c);
        }

        void uniqued_test()
        {
            uniqued_test_impl< std::vector< int > >();
            uniqued_test_impl< std::list< int > >();
            uniqued_test_impl< std::set< int > >();
            uniqued_test_impl< std::multiset< int > >();
        }
    }
}

boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* test
        = BOOST_TEST_SUITE( "RangeTestSuite.adaptor.uniqued" );

    test->add( BOOST_TEST_CASE( &boost::uniqued_test ) );

    return test;
}
