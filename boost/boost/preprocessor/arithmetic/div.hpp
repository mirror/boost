#ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP

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
#include <boost/preprocessor/inc.hpp>

/** <P>Expands to the quotient of X and Y.</P>

<P>For example, BOOST_PP_DIV(4,3) expands to 1 (a single token).</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_DIV(X,Y) BOOST_PP_DIV_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_DIV_D(D,X,Y) BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_WHILE##D(BOOST_PP_DIV_C,BOOST_PP_DIV_F,(0,X,Y)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_DIV_C(D,P) BOOST_PP_LESS_EQUAL_D(D,BOOST_PP_TUPLE_ELEM(3,2,P),BOOST_PP_TUPLE_ELEM(3,1,P))
#  define BOOST_PP_DIV_F(D,P) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(3,0,P)),BOOST_PP_SUB_D(D,BOOST_PP_TUPLE_ELEM(3,1,P),BOOST_PP_TUPLE_ELEM(3,2,P)),BOOST_PP_TUPLE_ELEM(3,2,P))
#else
#  define BOOST_PP_DIV_C(D,P) BOOST_PP_LESS_EQUAL_D(D,BOOST_PP_TUPLE3_ELEM2 P,BOOST_PP_TUPLE3_ELEM1 P)
#  define BOOST_PP_DIV_F(D,P) (BOOST_PP_INC(BOOST_PP_TUPLE3_ELEM0 P),BOOST_PP_SUB_D(D,BOOST_PP_TUPLE3_ELEM1 P,BOOST_PP_TUPLE3_ELEM2 P),BOOST_PP_TUPLE3_ELEM2 P)
#endif
#endif

/** Obsolete. Use BOOST_PP_DIV(). */
#define BOOST_PREPROCESSOR_DIV(X,Y) BOOST_PP_DIV(X,Y)
#endif
