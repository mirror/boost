#ifndef BOOST_PREPROCESSOR_LIST_SIZE_HPP
#define BOOST_PREPROCESSOR_LIST_SIZE_HPP

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

<a href="../../../../boost/preprocessor/list/size.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/fold_left.hpp>
#include <boost/preprocessor/inc.hpp>

//! Expands to the number of elements in the list.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_SIZE(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
\endverbatim</PRE>

expands to 3.
*/
#define BOOST_PP_LIST_SIZE(L) BOOST_PP_LIST_SIZE_D(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_SIZE_D(D,L) BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_SIZE_F,0,L)
#define BOOST_PP_LIST_SIZE_F(D,P,H) BOOST_PP_INC(P)
#endif
#endif
