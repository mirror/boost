#ifndef BOOST_PREPROCESSOR_LIST_REST_N_HPP
#define BOOST_PREPROCESSOR_LIST_REST_N_HPP

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

<a href="../../../../boost/preprocessor/list/rest_n.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/while.hpp>

//! Expands to a list of all but the first N elements of the list.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_REST_N(2,BOOST_PP_TUPLE_TO_LIST(4,(+,-,*,/)))
\endverbatim</PRE>

expands to a list containing * and /.
*/
#define BOOST_PP_LIST_REST_N(N,L) BOOST_PP_LIST_REST_N_D(0,N,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_REST_N_D(D,N,L) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_WHILE##D(BOOST_PP_LIST_REST_N_C,BOOST_PP_LIST_REST_N_F,(L,N)))
#define BOOST_PP_LIST_REST_N_C(D,X) BOOST_PP_TUPLE2_ELEM1 X
#define BOOST_PP_LIST_REST_N_F(D,X) (BOOST_PP_TUPLE3_ELEM1 BOOST_PP_TUPLE2_ELEM0 X,BOOST_PP_DEC(BOOST_PP_TUPLE2_ELEM1 X))
#endif
#endif
