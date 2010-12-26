// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//


#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/range.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include <list>
#include <vector>

namespace boost_range_extension_size_test
{
    class FooWithoutMemberSize
    {
        typedef std::list<int> impl_t;
        typedef impl_t::const_iterator const_iterator;
        typedef impl_t::iterator iterator;

    public:
        friend inline const_iterator range_begin(const FooWithoutMemberSize& obj) { return obj.m_impl.begin(); }
        friend inline iterator range_begin(FooWithoutMemberSize& obj) { return obj.m_impl.begin(); }
        friend inline const_iterator range_end(const FooWithoutMemberSize& obj) { return obj.m_impl.end(); }
        friend inline iterator range_end(FooWithoutMemberSize& obj){ return obj.m_impl.end(); }

    private:
        impl_t m_impl;
    };

    boost::range_difference<std::list<int> >::type
    inline range_calculate_size(const FooWithoutMemberSize& rng)
    {
        return 2u;
    }
}

namespace boost
{
    template<> struct range_iterator<const ::boost_range_extension_size_test::FooWithoutMemberSize>
    {
        typedef std::list<int>::const_iterator type;
    };

    template<> struct range_iterator< ::boost_range_extension_size_test::FooWithoutMemberSize >
    {
        typedef std::list<int>::iterator type;
    };
}

namespace
{

void check_size_works_with_less_than_random_access()
{
    std::list<int> container;
    container.push_back(1);
    BOOST_CHECK_EQUAL( boost::size(container), 1u );
}

void check_size_works_with_random_access()
{
    std::vector<int> container;
    container.push_back(1);
    BOOST_CHECK_EQUAL( boost::size(container), 1u );
}

class FooWithMemberSize
{
public:
    typedef std::list<int> impl_t;
    typedef impl_t::const_iterator const_iterator;
    typedef impl_t::iterator iterator;
    typedef impl_t::value_type value_type;

    std::size_t size() const { return 1u; }
    const_iterator begin() const { return m_impl.begin(); }
    iterator begin() { return m_impl.begin(); }
    const_iterator end() const { return m_impl.end(); }
    iterator end() { return m_impl.end(); }

private:
    std::list<int> m_impl;
};

void check_extension_size()
{
    BOOST_CHECK_EQUAL( boost::size(FooWithMemberSize()), 1u );
    BOOST_CHECK_EQUAL( boost::size(boost_range_extension_size_test::FooWithoutMemberSize()), 2u );
}

} // anonymous namespace

using boost::unit_test::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_size_works_with_less_than_random_access ));
    test->add( BOOST_TEST_CASE( &check_size_works_with_random_access ));
    test->add( BOOST_TEST_CASE( &check_extension_size ) );

    return test;
}





