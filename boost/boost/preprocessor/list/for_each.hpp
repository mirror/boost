#ifndef BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
#define BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP

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

<a href="../../../../boost/preprocessor/list/for_each.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/for.hpp>

//! Repeats F(R,P,BOOST_PP_LIST_AT(L,I)) for each I = [0,BOOST_PP_LIST_SIZE(L)[.
/*!
In other words, expands to the sequence:

<PRE>\verbatim
  F(R,P,BOOST_PP_LIST_AT(L,0))
  F(R,P,BOOST_PP_LIST_AT(L,1))
  ...
  F(R,P,BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L))))
\endverbatim</PRE>

See BOOST_PP_FOR() for an explanation of the R parameter.
*/
#define BOOST_PP_LIST_FOR_EACH(F,P,L) BOOST_PP_LIST_FOR_EACH_R(0,F,P,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_FOR_EACH_R(R,F,P,L) BOOST_PP_FOR##R((F,P,L,0),BOOST_PP_LIST_FOR_EACH_C,BOOST_PP_LIST_FOR_EACH_F,BOOST_PP_LIST_FOR_EACH_I)
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_FOR_EACH_C(R,FPL) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE4_ELEM2 FPL)
#else
#  define BOOST_PP_LIST_FOR_EACH_C(R,FPL) BOOST_PP_TUPLE3_ELEM2 BOOST_PP_TUPLE4_ELEM2 FPL
#endif
#define BOOST_PP_LIST_FOR_EACH_F(R,FPL) (BOOST_PP_TUPLE_ELEM(4,0,FPL),BOOST_PP_TUPLE4_ELEM1 FPL,BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE4_ELEM2 FPL,BOOST_PP_INC(BOOST_PP_TUPLE4_ELEM3 FPL))
#define BOOST_PP_LIST_FOR_EACH_I(R,FPL) BOOST_PP_TUPLE4_ELEM0 FPL(BOOST_PP_TUPLE4_ELEM3 FPL,BOOST_PP_TUPLE4_ELEM1 FPL,BOOST_PP_TUPLE3_ELEM0 BOOST_PP_TUPLE4_ELEM2 FPL)
#endif
#endif
