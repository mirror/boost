/* Copyright (C) 2002
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

/* This example implements a generalized macro for 2D repetition using
 * the simple repetition primitives of the preprocessor library.
 */

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/repeat_2nd.hpp>

/** Repeats the macro M(X,Y,P) for X = [0,W[ and Y = [0,H[.

In other words, expands to the sequence:

<PRE>\verbatim
  M(  0,  0,  P) M(  1,  0,  P) ... M(W-1,  0,  P)
  M(  0,  1,  P) M(  1,  1,  P) ... M(W-1,  1,  P)
        ...            ...      ...       ...
  M(  0,H-1,  P) M(  1,H-1,  P) ... M(W-1,H-1,  P)
\endverbatim</PRE>

Uses BOOST_PP_REPEAT() and BOOST_PP_REPEAT_2ND().
*/
#define REPEAT_2D(W,H,M,P)\
  /* Here we must use BOOST_PP_REPEAT_2ND(), because\
   * we use BOOST_PP_REPEAT() in REPEAT_2D_ROW().\
   */\
  BOOST_PP_REPEAT_2ND\
  ( H\
  , REPEAT_2D_ROW\
  , (W,M,P)\
  )

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define REPEAT_2D_ROW(Y,WMP)\
  BOOST_PP_REPEAT\
  ( BOOST_PP_TUPLE_ELEM(3,0,WMP)\
  , REPEAT_2D_ELEM\
  , (Y, BOOST_PP_TUPLE_ELEM(3,1,WMP), BOOST_PP_TUPLE_ELEM(3,2,WMP))\
  )
#define REPEAT_2D_ELEM(X,YMP)\
  BOOST_PP_TUPLE_ELEM(3,1,YMP)\
  ( X\
  , BOOST_PP_TUPLE_ELEM(3,0,YMP)\
  , BOOST_PP_TUPLE_ELEM(3,2,YMP)\
  )
#endif

#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/list/cat.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>

/* Here we use the above macro to generate something. */
#define ELEM(X,Y,E) BOOST_PP_COMMA_IF(BOOST_PP_OR(X,Y)) BOOST_PP_LIST_CAT(BOOST_PP_TUPLE_TO_LIST(5,(E,_,X,_,Y)))

enum { REPEAT_2D(3,4,ELEM,elem) };

/* The above expands to:
 *
 * enum { elem_0_0, elem_1_0, elem_2_0,
 *        elem_0_1, elem_1_1, elem_2_1,
 *        elem_0_2, elem_1_2, elem_2_2,
 *        elem_0_3, elem_1_3, elem_2_3 };
 */
