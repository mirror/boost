
// Copyright 2006-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include "../helpers/test.hpp"
#include "../objects/test.hpp"

UNORDERED_AUTO_TEST(needless_copies_1) {
    std::vector<std::pair<test::object, int> > src;
    src.push_back(std::pair<test::object, int>(test::object(1, 2), 0));

    boost::unordered_map<test::object, double> dst;
    dst[test::object(1, 2)] = 0;

    test::object_count count = test::global_object_count;
    dst.insert(src.begin(), src.end());
    BOOST_TEST(count == test::global_object_count);
}

UNORDERED_AUTO_TEST(needless_copies_2) {
    test::object x(1, 2);
    std::pair<test::object&, int> src(x, 0);

    boost::unordered_map<test::object, double> dst;

    test::object_count count = test::global_object_count;
    dst.emplace(src);
    BOOST_TEST(test::global_object_count.instances == count.instances + 1);
    BOOST_TEST_EQ(test::global_object_count.constructions, count.constructions + 1);

    count = test::global_object_count;
    dst.emplace(src);
    BOOST_TEST_EQ(test::global_object_count, count);
}

RUN_TESTS()
