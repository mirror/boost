//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This checks that template code implemented using hash_fwd will work.

#include "./hash_fwd_test.hpp"

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#if defined(TEST_EXTENSIONS) && !defined(TEST_STD_INCLUDES)

#include <boost/functional/hash.hpp>
#include <string>

BOOST_AUTO_TEST_CASE(fwd_test1)
{
    test_type1<int> x(5);
    test_type1<std::string> y("Test");

    BOOST_CHECK_EQUAL(
            boost::hash<int>()(5),
            boost::hash<test_type1<int> >()(x));

    BOOST_CHECK_EQUAL(
            boost::hash<std::string>()("Test"),
            boost::hash<test_type1<std::string> >()(y));
}

BOOST_AUTO_TEST_CASE(fwd_test2)
{
    test_type2<int> x(5, 10);
    test_type2<std::string> y("Test1", "Test2");

    std::size_t seed1 = 0;
    boost::hash_combine(seed1, 5);
    boost::hash_combine(seed1, 10);

    std::size_t seed2 = 0;
    boost::hash_combine(seed2, std::string("Test1"));
    boost::hash_combine(seed2, std::string("Test2"));

    BOOST_CHECK_EQUAL(seed1,
            boost::hash<test_type2<int> >()(x));
    BOOST_CHECK_EQUAL(seed2,
            boost::hash<test_type2<std::string> >()(y));
}

BOOST_AUTO_TEST_CASE(fwd_test3)
{
    std::vector<int> values1;
    values1.push_back(10);
    values1.push_back(15);
    values1.push_back(20);
    values1.push_back(3);

    std::vector<std::string> values2;
    values2.push_back("Chico");
    values2.push_back("Groucho");
    values2.push_back("Harpo");
    values2.push_back("Gummo");
    values2.push_back("Zeppo");

    test_type3<int> x(values1.begin(), values1.end());
    test_type3<std::string> y(values2.begin(), values2.end());

    std::size_t seed1 = boost::hash_range(values1.begin(), values1.end());
    boost::hash_range(seed1, values1.begin(), values1.end());

    std::size_t seed2 = boost::hash_range(values2.begin(), values2.end());
    boost::hash_range(seed2, values2.begin(), values2.end());

    BOOST_CHECK_EQUAL(seed1,
            boost::hash<test_type3<int> >()(x));
    BOOST_CHECK_EQUAL(seed2,
            boost::hash<test_type3<std::string> >()(y));
}

#endif
