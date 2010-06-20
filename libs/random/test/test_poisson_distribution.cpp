/* test_poisson_distribution.cpp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/poisson_distribution.hpp>
#include <boost/random/linear_congruential.hpp>
#include <sstream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_constructors) {
    boost::random::poisson_distribution<> dist;
    BOOST_CHECK_EQUAL(dist.mean(), 1.0);
    boost::random::poisson_distribution<> dist_one(7.5);
    BOOST_CHECK_EQUAL(dist_one.mean(), 7.5);
    boost::random::poisson_distribution<> copy(dist);
    BOOST_CHECK_EQUAL(dist, copy);
    boost::random::poisson_distribution<> copy_one(dist_one);
    BOOST_CHECK_EQUAL(dist_one, copy_one);
}

BOOST_AUTO_TEST_CASE(test_param) {
    boost::random::poisson_distribution<> dist(7.5);
    boost::random::poisson_distribution<>::param_type param = dist.param();
    BOOST_CHECK_EQUAL(param.mean(), 7.5);
    boost::random::poisson_distribution<> copy1(param);
    BOOST_CHECK_EQUAL(dist, copy1);
    boost::random::poisson_distribution<> copy2;
    copy2.param(param);
    BOOST_CHECK_EQUAL(dist, copy2);

    boost::random::poisson_distribution<>::param_type param_copy = param;
    BOOST_CHECK_EQUAL(param, param_copy);
    BOOST_CHECK(param == param_copy);
    BOOST_CHECK(!(param != param_copy));
    boost::random::poisson_distribution<>::param_type param_default;
    BOOST_CHECK_EQUAL(param_default.mean(), 1.0);
    BOOST_CHECK(param != param_default);
    BOOST_CHECK(!(param == param_default));
    boost::random::poisson_distribution<>::param_type param_one(7.5);
    BOOST_CHECK_EQUAL(param_one.mean(), 7.5);
    BOOST_CHECK(param_default != param_one);
    BOOST_CHECK(!(param_default == param_one));
}

BOOST_AUTO_TEST_CASE(test_min_max) {
    boost::random::poisson_distribution<> dist;
    BOOST_CHECK_EQUAL((dist.min)(), 0);
    BOOST_CHECK_EQUAL((dist.max)(), (std::numeric_limits<int>::max)());
    boost::random::poisson_distribution<> dist_one(7.5);
    BOOST_CHECK_EQUAL((dist_one.min)(), 0);
    BOOST_CHECK_EQUAL((dist_one.max)(), (std::numeric_limits<int>::max)());
}

BOOST_AUTO_TEST_CASE(test_comparison) {
    boost::random::poisson_distribution<> dist;
    boost::random::poisson_distribution<> dist_copy(dist);
    boost::random::poisson_distribution<> dist_one(7.5);
    boost::random::poisson_distribution<> dist_one_copy(dist_one);
    BOOST_CHECK(dist == dist_copy);
    BOOST_CHECK(!(dist != dist_copy));
    BOOST_CHECK(dist_one == dist_one_copy);
    BOOST_CHECK(!(dist_one != dist_one_copy));
    BOOST_CHECK(dist != dist_one);
    BOOST_CHECK(!(dist == dist_one));
}

BOOST_AUTO_TEST_CASE(test_streaming) {
    boost::random::poisson_distribution<> dist(7.5);
    std::stringstream stream;
    stream << dist;
    boost::random::poisson_distribution<> restored_dist;
    stream >> restored_dist;
    BOOST_CHECK_EQUAL(dist, restored_dist);
}

BOOST_AUTO_TEST_CASE(test_generation) {
    boost::minstd_rand0 gen;
    boost::random::poisson_distribution<> dist;
    boost::random::poisson_distribution<> dist_1000(1000);
    for(int i = 0; i < 10; ++i) {
        // Basic sanity checks.  Technically these tests are incorrect,
        // since the range of a poisson_distribution is [0, inf), but
        // the probability that there's an error is very small.
        int value = dist(gen);
        BOOST_CHECK_GE(value, 0);
        BOOST_CHECK_LE(value, 10);
        int value_two = dist_1000(gen);
        BOOST_CHECK_GE(value_two, 10);
        int value_param = dist_1000(gen, dist.param());
        BOOST_CHECK_GE(value_param, 0);
        BOOST_CHECK_LE(value_param, 10);
        int value_two_param = dist(gen, dist_1000.param());
        BOOST_CHECK_GE(value_two_param, 10);
    }
}
