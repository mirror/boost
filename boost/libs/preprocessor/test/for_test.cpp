// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

#include <boost/preprocessor/for.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/inc.hpp>

#include <libs/preprocessor/test/test.hpp>

// ***

#define C(D,X) BOOST_PP_LESS_EQUAL(X,4)
#define F(D,X) BOOST_PP_INC(X)
#define I(D,X) -X

TEST(11 BOOST_PP_FOR(0,C,F,I))
