#ifndef BOOST_PREPROCESSOR_LIST_CAT_HPP
#define BOOST_PREPROCESSOR_LIST_CAT_HPP

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

<a href="../../../../boost/preprocessor/list/cat.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/list/fold_left.hpp>

//! Catenates all elements of the list.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_CAT(BOOST_PP_TUPLE_TO_LIST(3,(1,2,3)))
\endverbatim</PRE>

expands to 123.
*/
#define BOOST_PP_LIST_CAT(L) BOOST_PP_LIST_CAT_D(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_CAT_D(D,L) BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_CAT_F,BOOST_PP_TUPLE3_ELEM0 L,BOOST_PP_TUPLE3_ELEM1 L)
#define BOOST_PP_LIST_CAT_F(D,P,H) BOOST_PP_CAT(P,H)
#endif
#endif
