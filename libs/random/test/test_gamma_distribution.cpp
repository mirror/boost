/* test_gamma_distribution.cpp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/gamma_distribution.hpp>
#include <boost/random/linear_congruential.hpp>
#include <sstream>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_constructors) {
    boost::random::gamma_distribution<> dist;
    BOOST_CHECK_EQUAL(dist.alpha(), 1.0);
    BOOST_CHECK_EQUAL(dist.beta(), 1.0);
    boost::random::gamma_distribution<> dist_one(7.5);
    BOOST_CHECK_EQUAL(dist_one.alpha(), 7.5);
    BOOST_CHECK_EQUAL(dist_one.beta(), 1.0);
    boost::random::gamma_distribution<> dist_two(7.5, 0.25);
    BOOST_CHECK_EQUAL(dist_two.alpha(), 7.5);
    BOOST_CHECK_EQUAL(dist_two.beta(), 0.25);
    boost::random::gamma_distribution<> copy(dist);
    BOOST_CHECK_EQUAL(dist, copy);
    boost::random::gamma_distribution<> copy_one(dist_one);
    BOOST_CHECK_EQUAL(dist_one, copy_one);
    boost::random::gamma_distribution<> copy_two(dist_two);
    BOOST_CHECK_EQUAL(dist_two, copy_two);
}

BOOST_AUTO_TEST_CASE(test_param) {
    boost::random::gamma_distribution<> dist(7.5, 0.25);
    boost::random::gamma_distribution<>::param_type param = dist.param();
    BOOST_CHECK_EQUAL(param.alpha(), 7.5);
    BOOST_CHECK_EQUAL(param.beta(), 0.25);
    boost::random::gamma_distribution<> copy1(param);
    BOOST_CHECK_EQUAL(dist, copy1);
    boost::random::gamma_distribution<> copy2;
    copy2.param(param);
    BOOST_CHECK_EQUAL(dist, copy2);

    boost::random::gamma_distribution<>::param_type param_copy = param;
    BOOST_CHECK_EQUAL(param, param_copy);
    BOOST_CHECK(param == param_copy);
    BOOST_CHECK(!(param != param_copy));
    boost::random::gamma_distribution<>::param_type param_default;
    BOOST_CHECK_EQUAL(param_default.alpha(), 1.0);
    BOOST_CHECK_EQUAL(param_default.beta(), 1.0);
    BOOST_CHECK(param != param_default);
    BOOST_CHECK(!(param == param_default));
    boost::random::gamma_distribution<>::param_type param_one(7.5);
    BOOST_CHECK_EQUAL(param_one.alpha(), 7.5);
    BOOST_CHECK_EQUAL(param_one.beta(), 1.0);
    BOOST_CHECK(param != param_one);
    BOOST_CHECK(!(param == param_one));
    BOOST_CHECK(param_default != param_one);
    BOOST_CHECK(!(param_default == param_one));
    boost::random::gamma_distribution<>::param_type param_two(7.5, 0.25);
    BOOST_CHECK_EQUAL(param_two.alpha(), 7.5);
    BOOST_CHECK_EQUAL(param_two.beta(), 0.25);
}

BOOST_AUTO_TEST_CASE(test_min_max) {
    boost::random::gamma_distribution<> dist;
    BOOST_CHECK_EQUAL((dist.min)(), 0);
    BOOST_CHECK_EQUAL((dist.max)(), (std::numeric_limits<double>::max)());
    boost::random::gamma_distribution<> dist_one(7.5);
    BOOST_CHECK_EQUAL((dist_one.min)(), 0);
    BOOST_CHECK_EQUAL((dist_one.max)(), (std::numeric_limits<double>::max)());
    boost::random::gamma_distribution<> dist_two(7.5, 0.25);
    BOOST_CHECK_EQUAL((dist_two.min)(), 0);
    BOOST_CHECK_EQUAL((dist_two.max)(), (std::numeric_limits<double>::max)());
}

BOOST_AUTO_TEST_CASE(test_comparison) {
    boost::random::gamma_distribution<> dist;
    boost::random::gamma_distribution<> dist_copy(dist);
    boost::random::gamma_distribution<> dist_one(7.5);
    boost::random::gamma_distribution<> dist_one_copy(dist_one);
    boost::random::gamma_distribution<> dist_two(7.5, 0.25);
    boost::random::gamma_distribution<> dist_two_copy(dist_two);
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
    boost::random::gamma_distribution<> dist(7.5, 0.25);
    std::stringstream stream;
    stream << dist;
    boost::random::gamma_distribution<> restored_dist;
    stream >> restored_dist;
    BOOST_CHECK_EQUAL(dist, restored_dist);
}

BOOST_AUTO_TEST_CASE(test_generation) {
    boost::minstd_rand0 gen;
    boost::random::gamma_distribution<> dist;
    boost::random::gamma_distribution<> dist_two(1.0, 1000000.0);
    for(int i = 0; i < 10; ++i) {
        // This test is not guaranteed to work, since
        // a gamma distribution with a large scale parameter
        // can produce small values and a distribution with
        // a small scale can produce large values, but the
        // chances of failure are small.
        double value = dist(gen);
        BOOST_CHECK_GE(value, 0.0);
        BOOST_CHECK_LE(value, 100.0);
        double value_two = dist_two(gen);
        BOOST_CHECK_GE(value_two, 100.0);
        double value_param = dist_two(gen, dist.param());
        BOOST_CHECK_GE(value_param, 0);
        BOOST_CHECK_LE(value_param, 100.0);
        double value_two_param = dist(gen, dist_two.param());
        BOOST_CHECK_GE(value_two_param, 100.0);
    }
}
