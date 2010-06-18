/* test_binomial_distribution.cpp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/binomial_distribution.hpp>
#include <boost/random/linear_congruential.hpp>
#include <sstream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_constructors) {
    boost::random::binomial_distribution<> dist;
    BOOST_CHECK_EQUAL(dist.t(), 1);
    BOOST_CHECK_EQUAL(dist.p(), 0.5);
    boost::random::binomial_distribution<> dist_one(10);
    BOOST_CHECK_EQUAL(dist_one.t(), 10);
    BOOST_CHECK_EQUAL(dist_one.p(), 0.5);
    boost::random::binomial_distribution<> dist_two(10, 0.25);
    BOOST_CHECK_EQUAL(dist_two.t(), 10);
    BOOST_CHECK_EQUAL(dist_two.p(), 0.25);
    boost::random::binomial_distribution<> copy(dist);
    BOOST_CHECK_EQUAL(dist, copy);
    boost::random::binomial_distribution<> copy_one(dist_one);
    BOOST_CHECK_EQUAL(dist_one, copy_one);
    boost::random::binomial_distribution<> copy_two(dist_two);
    BOOST_CHECK_EQUAL(dist_two, copy_two);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor) {
    boost::random::binomial_distribution<> dist(10, 0.25);
}

BOOST_AUTO_TEST_CASE(test_param) {
    boost::random::binomial_distribution<> dist(10, 0.25);
    boost::random::binomial_distribution<>::param_type param = dist.param();
    BOOST_CHECK_EQUAL(param.t(), 10);
    BOOST_CHECK_EQUAL(param.p(), 0.25);
    boost::random::binomial_distribution<> copy1(param);
    BOOST_CHECK_EQUAL(dist, copy1);
    boost::random::binomial_distribution<> copy2;
    copy2.param(param);
    BOOST_CHECK_EQUAL(dist, copy2);

    boost::random::binomial_distribution<>::param_type param_copy = param;
    BOOST_CHECK_EQUAL(param, param_copy);
    BOOST_CHECK(param == param_copy);
    BOOST_CHECK(!(param != param_copy));
    boost::random::binomial_distribution<>::param_type param_default;
    BOOST_CHECK_EQUAL(param_default.t(), 1);
    BOOST_CHECK_EQUAL(param_default.p(), 0.5);
    BOOST_CHECK(param != param_default);
    BOOST_CHECK(!(param == param_default));
    boost::random::binomial_distribution<>::param_type param_one(10);
    BOOST_CHECK_EQUAL(param_one.t(), 10);
    BOOST_CHECK_EQUAL(param_one.p(), 0.5);
    BOOST_CHECK(param != param_one);
    BOOST_CHECK(!(param == param_one));
    BOOST_CHECK(param_default != param_one);
    BOOST_CHECK(!(param_default == param_one));
    boost::random::binomial_distribution<>::param_type param_two(10, 0.25);
    BOOST_CHECK_EQUAL(param_two.t(), 10);
    BOOST_CHECK_EQUAL(param_two.p(), 0.25);
}

BOOST_AUTO_TEST_CASE(test_min_max) {
    boost::random::binomial_distribution<> dist;
    BOOST_CHECK_EQUAL((dist.min)(), 0);
    BOOST_CHECK_EQUAL((dist.max)(), 1);
    boost::random::binomial_distribution<> dist_one(10);
    BOOST_CHECK_EQUAL((dist_one.min)(), 0);
    BOOST_CHECK_EQUAL((dist_one.max)(), 10);
    boost::random::binomial_distribution<> dist_two(10, 0.25);
    BOOST_CHECK_EQUAL((dist_two.min)(), 0);
    BOOST_CHECK_EQUAL((dist_two.max)(), 10);
}

BOOST_AUTO_TEST_CASE(test_comparison) {
    boost::random::binomial_distribution<> dist;
    boost::random::binomial_distribution<> dist_copy(dist);
    boost::random::binomial_distribution<> dist_one(10);
    boost::random::binomial_distribution<> dist_one_copy(dist_one);
    boost::random::binomial_distribution<> dist_two(10, 0.25);
    boost::random::binomial_distribution<> dist_two_copy(dist_two);
    BOOST_CHECK(dist == dist_copy);
    BOOST_CHECK(!(dist != dist_copy));
    BOOST_CHECK(dist_one == dist_one_copy);
    BOOST_CHECK(!(dist_one != dist_one_copy));
    BOOST_CHECK(dist_two == dist_two_copy);
    BOOST_CHECK(!(dist_two != dist_two_copy));
    BOOST_CHECK(dist != dist_one);
    BOOST_CHECK(!(dist == dist_one));
    BOOST_CHECK(dist != dist_two);
    BOOST_CHECK(!(dist == dist_two));
    BOOST_CHECK(dist_one != dist_two);
    BOOST_CHECK(!(dist_one == dist_two));
}

BOOST_AUTO_TEST_CASE(test_streaming) {
    boost::random::binomial_distribution<> dist(10, 0.25);
    std::stringstream stream;
    stream << dist;
    boost::random::binomial_distribution<> restored_dist;
    stream >> restored_dist;
    BOOST_CHECK_EQUAL(dist, restored_dist);
}

BOOST_AUTO_TEST_CASE(test_generation) {
    boost::minstd_rand0 gen;
    boost::random::binomial_distribution<> dist;
    boost::random::binomial_distribution<> dist_two(10, 0.25);
    for(int i = 0; i < 10; ++i) {
        int value = dist(gen);
        BOOST_CHECK_GE(value, (dist.min)());
        BOOST_CHECK_LE(value, (dist.max)());
        int value_two = dist_two(gen);
        BOOST_CHECK_GE(value_two, (dist_two.min)());
        BOOST_CHECK_LE(value_two, (dist_two.max)());
        int value_param = dist_two(gen, dist.param());
        BOOST_CHECK_GE(value_param, (dist.min)());
        BOOST_CHECK_LE(value_param, (dist.max)());
        int value_two_param = dist(gen, dist_two.param());
        BOOST_CHECK_GE(value_two_param, (dist_two.min)());
        BOOST_CHECK_LE(value_two_param, (dist_two.max)());
    }
}
