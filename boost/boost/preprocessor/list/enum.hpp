#ifndef BOOST_PREPROCESSOR_LIST_ENUM_HPP
#define BOOST_PREPROCESSOR_LIST_ENUM_HPP

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

<a href="../../../../boost/preprocessor/list/enum.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/list/for_each.hpp>

/** Converts the list to a comma separated list.

For example,

<PRE>\verbatim
  BOOST_PP_LIST_ENUM(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
\endverbatim</PRE>

expands to:

<PRE>\verbatim
  A, B, C
\endverbatim</PRE>
*/
#define BOOST_PP_LIST_ENUM(L) BOOST_PP_LIST_ENUM_R(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_ENUM_R(R,L) BOOST_PP_LIST_FOR_EACH_R(R,BOOST_PP_LIST_ENUM_F,_,L)
#define BOOST_PP_LIST_ENUM_F(I,_,X) BOOST_PP_COMMA_IF(I) X
#endif
#endif
