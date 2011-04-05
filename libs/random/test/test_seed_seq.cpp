/* boost test_seed_seq.cpp
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 */

#include <boost/random/seed_seq.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/config.hpp>
#include <vector>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using boost::assign::list_of;

BOOST_AUTO_TEST_CASE(test_seed_seq) {
    boost::uint32_t expected_param[4] = { 2, 3, 4, 0xdeadbeaf };
    boost::uint32_t param[4] = { 2, 3, 4, 0xdeadbeaf };
    boost::uint32_t store32[10];
    boost::uint64_t store64[10];
    boost::uint32_t expected[10] = {
        2571534471u,
        852093106u,
        3994144234u,
        904246505u,
        3404579686u,
        1508446734u,
        3679033230u,
        2550178480u,
        4205639301u,
        268720383u
    };
    std::fill_n(&store32[0], 10, 0);
    std::fill_n(&store64[0], 10, 0);
    boost::random::seed_seq seq;
    seq.generate(&store32[0], &store32[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store32[0], &store32[0] + 10, &expected[0], &expected[0] + 10);
    seq.generate(&store64[0], &store64[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store64[0], &store64[0] + 10, &expected[0], &expected[0] + 10);
    BOOST_CHECK_EQUAL(seq.size(), 0u);
    seq.param(&param[0]);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &param[0], &param[0] + 4, &expected_param[0], &expected_param[0] + 4);

    boost::uint32_t expected_r[10] = {
        249299179u,
        1602610063u,
        745496312u,
        3444440002u,
        1462959439u,
        4120764957u,
        2551678045u,
        2909251680u,
        3652199668u,
        1330108271u
    };

    std::vector<int> data = list_of(2)(3)(4);
    
    std::fill_n(&store32[0], 10, 0);
    std::fill_n(&store64[0], 10, 0);
    std::fill_n(&param[0], 3, 0);
    boost::random::seed_seq seq_r(data);
    seq_r.generate(&store32[0], &store32[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store32[0], &store32[0] + 10, &expected_r[0], &expected_r[0] + 10);
    seq_r.generate(&store64[0], &store64[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store64[0], &store64[0] + 10, &expected_r[0], &expected_r[0] + 10);
    BOOST_CHECK_EQUAL(seq_r.size(), 3u);
    seq_r.param(&param[0]);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &param[0], &param[0] + 4, &expected_param[0], &expected_param[0] + 4);
    
    std::fill_n(&store32[0], 10, 0);
    std::fill_n(&store64[0], 10, 0);
    std::fill_n(&param[0], 3, 0);
    boost::random::seed_seq seq_it(data.begin(), data.end());
    seq_it.generate(&store32[0], &store32[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store32[0], &store32[0] + 10, &expected_r[0], &expected_r[0] + 10);
    seq_it.generate(&store64[0], &store64[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store64[0], &store64[0] + 10, &expected_r[0], &expected_r[0] + 10);
    BOOST_CHECK_EQUAL(seq_it.size(), 3u);
    seq_it.param(&param[0]);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &param[0], &param[0] + 4, &expected_param[0], &expected_param[0] + 4);
    
#ifndef BOOST_NO_INITIALIZER_LISTS
    std::fill_n(&store32[0], 10, 0);
    std::fill_n(&store64[0], 10, 0);
    std::fill_n(&param[0], 3, 0);
    boost::random::seed_seq seq_il = {2, 3, 4};
    seq_il.generate(&store32[0], &store32[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store32[0], &store32[0] + 10, &expected_r[0], &expected_r[0] + 10);
    seq_il.generate(&store64[0], &store64[0] + 10);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &store64[0], &store64[0] + 10, &expected_r[0], &expected_r[0] + 10);
    BOOST_CHECK_EQUAL(seq_il.size(), 3u);
    seq_il.param(&param[0]);
    BOOST_CHECK_EQUAL_COLLECTIONS(
        &param[0], &param[0] + 4, &expected_param[0], &expected_param[0] + 4);
#endif
}
