#ifndef BOOST_PREPROCESSOR_LIST_FILTER_HPP
#define BOOST_PREPROCESSOR_LIST_FILTER_HPP

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

<a href="../../../../boost/preprocessor/list/filter.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/fold_right.hpp>

//! Expands to a list containing all the elements X of the list for which F(D,P,X) is true.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_FILTER(BOOST_PP_NOT_EQUAL_D,2,BOOST_PP_TUPLE_TO_LIST(3,(1,2,3)))
\endverbatim</PRE>

expands to a list containing 1 and 3.
*/
#define BOOST_PP_LIST_FILTER(F,P,L) BOOST_PP_LIST_FILTER_D(0,F,P,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_FILTER_D(D,F,P,L) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_LIST_FOLD_RIGHT_D(D,BOOST_PP_LIST_FILTER_F,L,(F,P,(_,_,0))))
#define BOOST_PP_LIST_FILTER_F(D,H,P) (BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE3_ELEM1 P,BOOST_PP_IF(BOOST_PP_TUPLE3_ELEM0 P(D,BOOST_PP_TUPLE3_ELEM1 P,H),BOOST_PP_LIST_CONS,BOOST_PP_TUPLE2_ELEM1)(H,BOOST_PP_TUPLE3_ELEM2 P))
#endif
#endif
