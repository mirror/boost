/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#include <boost/preprocessor/arithmetic.hpp>
#include <boost/preprocessor/comparison.hpp>
#include <boost/preprocessor/limits.hpp>
#include <boost/preprocessor/min.hpp>
#include <boost/preprocessor/max.hpp>

#include <libs/preprocessor/test/test.hpp>

/* *** */

TEST_B BOOST_PP_ADD(2,3) == 5 TEST_E
TEST_B BOOST_PP_ADD(21,BOOST_PP_SUB(BOOST_PP_LIMIT_MAG,20)) == BOOST_PP_LIMIT_MAG TEST_E

TEST_B BOOST_PP_SUB(11,0) == 11 TEST_E
TEST_B BOOST_PP_SUB(12,1) == 11 TEST_E
TEST_B BOOST_PP_SUB(3,4) == 0 TEST_E

TEST_B BOOST_PP_MUL(0,1) == 0 TEST_E
TEST_B BOOST_PP_MUL(1,0) == 0 TEST_E
TEST_B BOOST_PP_MUL(1,1) == 1 TEST_E
TEST_B BOOST_PP_MUL(4,3) == 12 TEST_E

TEST_B BOOST_PP_DIV(2,1) == 2 TEST_E
TEST_B BOOST_PP_DIV(0,5) == 0 TEST_E
TEST_B BOOST_PP_DIV(7,3) == 2 TEST_E

TEST_B BOOST_PP_EQUAL(1,0) == 0 TEST_E
TEST_B BOOST_PP_EQUAL(10,10) == 1 TEST_E

TEST_B BOOST_PP_NOT_EQUAL(3,4) == 1 TEST_E
TEST_B BOOST_PP_NOT_EQUAL(7,7) == 0 TEST_E

TEST_B BOOST_PP_LESS_EQUAL(6,7) == 1 TEST_E
TEST_B BOOST_PP_LESS_EQUAL(8,1) == 0 TEST_E
TEST_B BOOST_PP_LESS_EQUAL(5,5) == 1 TEST_E

TEST_B BOOST_PP_GREATER_EQUAL(6,7) == 0 TEST_E
TEST_B BOOST_PP_GREATER_EQUAL(10,10) == 1 TEST_E
TEST_B BOOST_PP_GREATER_EQUAL(8,1) == 1 TEST_E

TEST_B BOOST_PP_LESS(2,1) == 0 TEST_E
TEST_B BOOST_PP_LESS(1,1) == 0 TEST_E
TEST_B BOOST_PP_LESS(1,2) == 1 TEST_E

TEST_B BOOST_PP_GREATER(2,1) == 1 TEST_E
TEST_B BOOST_PP_GREATER(1,1) == 0 TEST_E
TEST_B BOOST_PP_GREATER(1,2) == 0 TEST_E

TEST_B BOOST_PP_MIN(1,0) == 0 TEST_E
TEST_B BOOST_PP_MIN(1,2) == 1 TEST_E

TEST_B BOOST_PP_MAX(3,2) == 3 TEST_E
TEST_B BOOST_PP_MAX(4,5) == 5 TEST_E

TEST_B BOOST_PP_MOD(5,5) == 0 TEST_E
TEST_B BOOST_PP_MOD(9,5) == 4 TEST_E
TEST_B BOOST_PP_MOD(7,4) == 3 TEST_E
