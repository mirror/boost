#ifndef BOOST_PREPROCESSOR_LIST_REVERSE_HPP
#define BOOST_PREPROCESSOR_LIST_REVERSE_HPP

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

<a href="../../../../boost/preprocessor/list/reverse.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/fold_left.hpp>

/** List reversal.

For example,

<PRE>\verbatim
  BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
\endverbatim</PRE>

expands to a list containing C, B and A.

<H3>Uses</H3>
- BOOST_PP_WHILE()
*/
#define BOOST_PP_LIST_REVERSE(L) BOOST_PP_LIST_REVERSE_D(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_REVERSE_D(D,L) BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_REVERSE_F,(_,_,0),L)
#define BOOST_PP_LIST_REVERSE_F(D,P,H) (H,P,1)
#endif
#endif
