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

#include <boost/preprocessor/list/fold_left.hpp>

/** <P>List reversal.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_LIST_REVERSE(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</PRE>

<P>expands to a list containing C, B and A.</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_LIST_REVERSE(L) BOOST_PP_LIST_REVERSE_D(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_REVERSE_D(D,L) BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_REVERSE_F,(_,_,0),L)
#define BOOST_PP_LIST_REVERSE_F(D,P,H) (H,P,1)
#endif
#endif
