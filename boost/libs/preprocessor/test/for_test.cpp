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

#include <boost/preprocessor/for.hpp>
#include <boost/preprocessor/dec.hpp>

#include <libs/preprocessor/test/test.hpp>

/* *** */

#ifndef FOR_TEST_MAX
#define FOR_TEST_MAX 50
#endif

#define C(D,X) X
#define F(D,X) BOOST_PP_DEC(X)
#define I(D,X) -X

TEST_B (FOR_TEST_MAX*(FOR_TEST_MAX+1)/2)+1 BOOST_PP_FOR(FOR_TEST_MAX,C,F,I) TEST_E
