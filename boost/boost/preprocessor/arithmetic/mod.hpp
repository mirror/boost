#ifndef BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP

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

#include <boost/preprocessor/comparison/less_equal.hpp>

/** <P>Expands to the remainder of X and Y.</P>

<P>For example, BOOST_PP_MOD(4,3) expands to 1 (a single token).</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_MOD(X,Y) BOOST_PP_MOD_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_MOD_D(D,X,Y) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_WHILE##D(BOOST_PP_MOD_C,BOOST_PP_MOD_F,(X,Y)))
#define BOOST_PP_MOD_C(D,P) BOOST_PP_LESS_EQUAL_D(D,BOOST_PP_TUPLE2_ELEM1 P,BOOST_PP_TUPLE2_ELEM0 P)
#define BOOST_PP_MOD_F(D,P) (BOOST_PP_SUB_D(D,BOOST_PP_TUPLE2_ELEM0 P,BOOST_PP_TUPLE2_ELEM1 P),BOOST_PP_TUPLE2_ELEM1 P)
#endif

/** Obsolete. Use BOOST_PP_MOD(). */
#define BOOST_PREPROCESSOR_MOD(X,Y) BOOST_PP_MOD(X,Y)
#endif
