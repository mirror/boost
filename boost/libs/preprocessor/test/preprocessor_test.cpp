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

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/identity.hpp>
#include <boost/preprocessor/if.hpp>
#include <boost/preprocessor/expr_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <libs/preprocessor/test/test.hpp>

/* *** */

struct Container
{
#define BOOST_PP_DEF(CV)\
  CV() int& operator[](int i) CV();

  BOOST_PP_DEF(BOOST_PP_EMPTY)
  BOOST_PP_DEF(BOOST_PP_IDENTITY(const))
  BOOST_PP_DEF(BOOST_PP_IDENTITY(volatile))
  BOOST_PP_DEF(BOOST_PP_IDENTITY(const volatile))

#undef BOOST_PP_DEF
};

/* *** */

TEST_B BOOST_PP_IF(BOOST_PP_IF(1,1,1),true,false) &&
  BOOST_PP_IF(BOOST_PP_IF(0,0,0),false,true) TEST_E

/* *** */

TEST_B BOOST_PP_EXPR_IF(1,1) TEST_E

/* *** */

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_CAT(BOOST_PP_IF(1,tru,fals), MACRO MACRO_ARGS(e)) TEST_E
#endif

/* *** */

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
char stringize_test[2] = BOOST_PP_STRINGIZE(MACRO MACRO_ARGS(X));
#endif

/* *** */

TEST_B BOOST_PP_TUPLE_ELEM(2,0,(1,0)) TEST_E
