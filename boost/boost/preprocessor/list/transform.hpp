#ifndef BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#define BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP

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

<a href="../../../../boost/preprocessor/list/transform.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/fold_right.hpp>

/** Applies the macro F(D,P,X) to each element X of the list producing a new list.

In other words, BOOST_PP_LIST_TRANSFORM(F,P,L) expands to same as:

<PRE>\verbatim
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,0)),
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,1)),
  ...
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L)))),
  BOOST_PP_LIST_NIL) ... ))
\endverbatim</PRE>

For example,

<PRE>\verbatim
  BOOST_PP_LIST_TRANSFORM(BOOST_PP_ADD_D,2,BOOST_PP_TUPLE_TO_LIST(2,(1,2)))
\endverbatim</PRE>

expands to a list containing 3 and 4.
*/
#define BOOST_PP_LIST_TRANSFORM(F,P,L) BOOST_PP_LIST_TRANSFORM_D(0,F,P,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_TRANSFORM_D(D,F,P,L) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_LIST_FOLD_RIGHT_D(D,BOOST_PP_LIST_TRANSFORM_F,L,(F,P,(_,_,0))))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE_ELEM(3,1,P),(BOOST_PP_TUPLE_ELEM(3,0,P)(D,BOOST_PP_TUPLE_ELEM(3,1,P),H),BOOST_PP_TUPLE_ELEM(3,2,P),1))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE3_ELEM1 P,(BOOST_PP_TUPLE_ELEM(3,0,P)(D,BOOST_PP_TUPLE3_ELEM1 P,H),BOOST_PP_TUPLE3_ELEM2 P,1))
#else
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE3_ELEM0 P,BOOST_PP_TUPLE3_ELEM1 P,(BOOST_PP_TUPLE3_ELEM0 P(D,BOOST_PP_TUPLE3_ELEM1 P,H),BOOST_PP_TUPLE3_ELEM2 P,1))
#endif
#endif
#endif
