#ifndef BOOST_PREPROCESSOR_LIST_APPEND_HPP
#define BOOST_PREPROCESSOR_LIST_APPEND_HPP

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

#include <boost/preprocessor/list/fold_right.hpp>

/** <P>Catenates two lists together.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_LIST_APPEND
  ( BOOST_PP_TUPLE_TO_LIST(2,(1,2))
  , BOOST_PP_TUPLE_TO_LIST(2,(3,4))
  )
</PRE>

<P>produces a list containing 1, 2, 3 and 4.</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_LIST_APPEND(L,P) BOOST_PP_LIST_APPEND_D(0,L,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_APPEND_D(D,L,P) BOOST_PP_LIST_FOLD_RIGHT_D(D,BOOST_PP_LIST_APPEND_F,L,P)
#define BOOST_PP_LIST_APPEND_F(D,H,P) (H,P,1)
#endif
#endif
