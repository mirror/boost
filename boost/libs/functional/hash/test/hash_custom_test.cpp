
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash/hash.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <vector>
#include <string>
#include <cctype>

namespace test
{
    struct custom
    {
        int value_;

        custom(int x) : value_(x) {}
        std::size_t hash() const { return value_ * 10; }
    };
}

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
namespace test
#else
namespace boost
#endif
{
    std::size_t hash_value(test::custom x)
    {
        return x.hash();
    }
}

BOOST_AUTO_UNIT_TEST(custom_tests)
{
    boost::hash<test::custom> custom_hasher;
    BOOST_CHECK_EQUAL(custom_hasher(10), 100u);
    test::custom x(55);
    BOOST_CHECK_EQUAL(custom_hasher(x), 550u);

    std::vector<test::custom> custom_vector;
    custom_vector.push_back(5);
    custom_vector.push_back(25);
    custom_vector.push_back(35);

    std::size_t seed = 0;
    boost::hash_combine(seed, test::custom(5));
    boost::hash_combine(seed, test::custom(25));
    boost::hash_combine(seed, test::custom(35));

    BOOST_CHECK_EQUAL(seed,
            boost::hash_range(custom_vector.begin(), custom_vector.end()));
}

