#ifndef BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP
#define BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP

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

/** \file

<a href="../../../../boost/preprocessor/list/fold_left.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/while.hpp>

/** Iterates F(D,P,X) for each element X of the list L (from the left or the start of the list).

In other words,

<PRE>\verbatim
  BOOST_PP_LIST_FOLD_LEFT(F,P,L)
\endverbatim</PRE>

expands to:

<PRE>\verbatim
  F
  ( D
  , ... F(D, F(D,P,BOOST_PP_LIST_AT(L,0)), BOOST_PP_LIST_AT(L,1)) ...
  , BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L))
  )
\endverbatim</PRE>

Note that folding, or accumulation, is a very general pattern of computation.
Most list operations can be implemented in terms of folding.

<H3>See</H3>
- BOOST_PP_LIST_FOLD_RIGHT()

<H3>Uses</H3>
- BOOST_PP_WHILE()
*/
#define BOOST_PP_LIST_FOLD_LEFT(F,P,L) BOOST_PP_LIST_FOLD_LEFT_D(0,F,P,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_FOLD_LEFT_D(D,F,P,L) BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_WHILE##D(BOOST_PP_LIST_FOLD_LEFT_C,BOOST_PP_LIST_FOLD_LEFT_F,(F,P,L)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_TUPLE_ELEM(3,2,X))
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE_ELEM(3,0,X),BOOST_PP_TUPLE_ELEM(3,0,X)(D,BOOST_PP_TUPLE_ELEM(3,1,X),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,X))),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,X)))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE3_ELEM2 BOOST_PP_TUPLE3_ELEM2 X
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE_ELEM(3,0,X),BOOST_PP_TUPLE3_ELEM0 X(D,BOOST_PP_TUPLE3_ELEM1 X,BOOST_PP_TUPLE3_ELEM0 BOOST_PP_TUPLE3_ELEM2 X),BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE3_ELEM2 X)
#else
#  define BOOST_PP_LIST_FOLD_LEFT_C(D,X) BOOST_PP_TUPLE3_ELEM2 BOOST_PP_TUPLE3_ELEM2 X
#  define BOOST_PP_LIST_FOLD_LEFT_F(D,X) (BOOST_PP_TUPLE3_ELEM0 X,BOOST_PP_TUPLE3_ELEM0 X(D,BOOST_PP_TUPLE3_ELEM1 X,BOOST_PP_TUPLE3_ELEM0 BOOST_PP_TUPLE3_ELEM2 X),BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE3_ELEM2 X)
#endif
#endif
#endif
