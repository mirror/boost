//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash/hash.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/assign/list_inserter.hpp>

BOOST_AUTO_UNIT_TEST(hash_range_tests)
{
    using namespace boost::assign;

    std::vector<int> empty, values1, values2, values3, values4, values5;
    push_back(values1)(0);
    push_back(values2)(10);
    push_back(values3)(10)(20);
    push_back(values4)(15)(75);
    push_back(values5)(10)(20)(15)(75)(10)(20);

    std::vector<int> x;
    BOOST_CHECK(boost::hash_range(empty) == boost::hash_range(x));
    BOOST_CHECK(boost::hash_range(empty) == boost::hash_range(x.begin(), x.end()));
    BOOST_CHECK(boost::hash_range(empty) != boost::hash_range(values1));

    x.push_back(10);
    BOOST_CHECK(boost::hash_range(empty) != boost::hash_range(x));
    BOOST_CHECK(boost::hash_range(values2) == boost::hash_range(x));
    BOOST_CHECk(boost::hash_range(values2) == boost::hash_range(x.begin(), x.end()));

    x.push_back(20);
    BOOST_CHECK(boost::hash_range(empty) != boost::hash_range(x));
    BOOST_CHECK(boost::hash_range(values2) != boost::hash_range(x));
    BOOST_CHECK(boost::hash_range(values3) == boost::hash_range(x));

    std::size_t seed = boost::hash_range(values3);
    boost::hash_range(seed, boost::const_begin(values4), boost::const_end(values4));
    boost::hash_range(seed, x);
    BOOST_CHECK(seed == boost::hash_range(values5));
}
