#ifndef BOOST_PREPROCESSOR_LIST_SIZE_HPP
#define BOOST_PREPROCESSOR_LIST_SIZE_HPP

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
#include <boost/preprocessor/inc.hpp>

/** <P>Expands to the number of elements in the list.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_LIST_SIZE(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</PRE>

<P>expands to 3.</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_LIST_SIZE(L) BOOST_PP_LIST_SIZE_D(0,L)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_SIZE_D(D,L) BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_SIZE_F,0,L)
#define BOOST_PP_LIST_SIZE_F(D,P,H) BOOST_PP_INC(P)
#endif
#endif
