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

#include <boost/preprocessor/list.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <libs/preprocessor/test/test.hpp>

/* *** */

#define TEST_LIST BOOST_PP_TUPLE_TO_LIST(4,(4,1,5,2))

TEST_B BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_SUB_D,22,TEST_LIST) == 10 TEST_E
TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_REVERSE(TEST_LIST)) == 2514 TEST_E
TEST_B BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_SUB_D,TEST_LIST,0) == 4 TEST_E

TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_REST_N(2,TEST_LIST)) == 52 TEST_E
TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_FIRST_N(2,TEST_LIST)) == 41 TEST_E

TEST_B BOOST_PP_LIST_AT(TEST_LIST,2) == 5 TEST_E

TEST_B BOOST_PP_LIST_SIZE(TEST_LIST) == 4 TEST_E

TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_TRANSFORM(BOOST_PP_ADD_D,2,TEST_LIST)) == 6374 TEST_E

TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_APPEND(BOOST_PP_LIST_REST(TEST_LIST),TEST_LIST)) == 1524152 TEST_E

#define F(I,P,X) +X+P
TEST_B BOOST_PP_LIST_FOR_EACH(F,1,TEST_LIST) == 16 TEST_E
#undef F

TEST_B BOOST_PP_TUPLE_ELEM(4,3,BOOST_PP_LIST_TO_TUPLE(TEST_LIST)) == 2 TEST_E

TEST_B BOOST_PP_LIST_CAT(BOOST_PP_LIST_FILTER(BOOST_PP_LESS_D,3,TEST_LIST)) == 45 TEST_E

#define F(R,X) +BOOST_PP_TUPLE_ELEM(2,0,X)+2-BOOST_PP_TUPLE_ELEM(2,1,X)
TEST_B BOOST_PP_LIST_FOR_EACH_PRODUCT(F,2,(BOOST_PP_TUPLE_TO_LIST(2,(1,0)),BOOST_PP_TUPLE_TO_LIST(2,(2,3)))) == 0 TEST_E
#undef F
