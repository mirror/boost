#ifndef BOOST_PREPROCESSOR_TUPLE_ELEM_HPP
#define BOOST_PREPROCESSOR_TUPLE_ELEM_HPP

// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/tuple/elem.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/expand.hpp>

//! Expands to the I:th element of an N-tuple.
/*!
Tuples can be used for representing structured data.

Examples of tuples:

<PRE>\verbatim
  2-tuple: (A, B)
  3-tuple: (1, 2, 3)
  4-tuple: (A B C, D, EF, 34)
\endverbatim</PRE>

Example:

<PRE>\verbatim
  BOOST_PP_TUPLE_ELEM(2,1,(A,B))
\endverbatim</PRE>

The above expands to B.

See also BOOST_PP_LIMIT_TUPLE.
*/
#define BOOST_PP_TUPLE_ELEM(N,I,T) BOOST_PP_TUPLE_ELEM_DELAY(N,I,T)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
// This is a workaround for a CodeWarrior PP bug. Strictly speaking
// this workaround invokes undefined behavior, but it works as desired.
#  define BOOST_PP_TUPLE_ELEM_DELAY(N,I,T) BOOST_PP_TUPLE##N##_ELEM##I##T
#else
#  define BOOST_PP_TUPLE_ELEM_DELAY(N,I,T) BOOST_PP_EXPAND(BOOST_PP_TUPLE##N##_ELEM##I T)
#endif

// NOTE: TUPLE_ELEM can be implemented in O(N*N) space and O(N) time instead
// of O(N*N*N) space and O(1) time. The current trade-off seems better.

#define BOOST_PP_TUPLE1_ELEM0(A) A

#define BOOST_PP_TUPLE2_ELEM0(A,B) A
#define BOOST_PP_TUPLE2_ELEM1(A,B) B

#define BOOST_PP_TUPLE3_ELEM0(A,B,C) A
#define BOOST_PP_TUPLE3_ELEM1(A,B,C) B
#define BOOST_PP_TUPLE3_ELEM2(A,B,C) C

#define BOOST_PP_TUPLE4_ELEM0(A,B,C,D) A
#define BOOST_PP_TUPLE4_ELEM1(A,B,C,D) B
#define BOOST_PP_TUPLE4_ELEM2(A,B,C,D) C
#define BOOST_PP_TUPLE4_ELEM3(A,B,C,D) D

#define BOOST_PP_TUPLE5_ELEM0(A,B,C,D,E) A
#define BOOST_PP_TUPLE5_ELEM1(A,B,C,D,E) B
#define BOOST_PP_TUPLE5_ELEM2(A,B,C,D,E) C
#define BOOST_PP_TUPLE5_ELEM3(A,B,C,D,E) D
#define BOOST_PP_TUPLE5_ELEM4(A,B,C,D,E) E

#define BOOST_PP_TUPLE6_ELEM0(A,B,C,D,E,F) A
#define BOOST_PP_TUPLE6_ELEM1(A,B,C,D,E,F) B
#define BOOST_PP_TUPLE6_ELEM2(A,B,C,D,E,F) C
#define BOOST_PP_TUPLE6_ELEM3(A,B,C,D,E,F) D
#define BOOST_PP_TUPLE6_ELEM4(A,B,C,D,E,F) E
#define BOOST_PP_TUPLE6_ELEM5(A,B,C,D,E,F) F

#define BOOST_PP_TUPLE7_ELEM0(A,B,C,D,E,F,G) A
#define BOOST_PP_TUPLE7_ELEM1(A,B,C,D,E,F,G) B
#define BOOST_PP_TUPLE7_ELEM2(A,B,C,D,E,F,G) C
#define BOOST_PP_TUPLE7_ELEM3(A,B,C,D,E,F,G) D
#define BOOST_PP_TUPLE7_ELEM4(A,B,C,D,E,F,G) E
#define BOOST_PP_TUPLE7_ELEM5(A,B,C,D,E,F,G) F
#define BOOST_PP_TUPLE7_ELEM6(A,B,C,D,E,F,G) G

#define BOOST_PP_TUPLE8_ELEM0(A,B,C,D,E,F,G,H) A
#define BOOST_PP_TUPLE8_ELEM1(A,B,C,D,E,F,G,H) B
#define BOOST_PP_TUPLE8_ELEM2(A,B,C,D,E,F,G,H) C
#define BOOST_PP_TUPLE8_ELEM3(A,B,C,D,E,F,G,H) D
#define BOOST_PP_TUPLE8_ELEM4(A,B,C,D,E,F,G,H) E
#define BOOST_PP_TUPLE8_ELEM5(A,B,C,D,E,F,G,H) F
#define BOOST_PP_TUPLE8_ELEM6(A,B,C,D,E,F,G,H) G
#define BOOST_PP_TUPLE8_ELEM7(A,B,C,D,E,F,G,H) H
#endif

//! Obsolete. Use BOOST_PP_TUPLE_ELEM().
#define BOOST_PREPROCESSOR_TUPLE_ELEM(N,I,T) BOOST_PP_TUPLE_ELEM(N,I,T)
#endif
