#ifndef BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP

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

#include <boost/preprocessor/arithmetic/add.hpp>

/** <P>Expands to the product of X and Y.</P>

<P>For example, BOOST_PP_MUL(4,3) expands to 12 (a single token).</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_MUL(X,Y) BOOST_PP_MUL_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_MUL_D(D,X,Y) BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_WHILE##D(BOOST_PP_MUL_C,BOOST_PP_MUL_F,(0,X,Y)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_MUL_C(D,P) BOOST_PP_TUPLE_ELEM(3,2,P)
#  define BOOST_PP_MUL_F(D,P) (BOOST_PP_ADD_D(D,BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE_ELEM(3,1,P)),BOOST_PP_TUPLE_ELEM(3,1,P),BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(3,2,P)))
#else
#  define BOOST_PP_MUL_C(D,P) BOOST_PP_TUPLE3_ELEM2 P
#  define BOOST_PP_MUL_F(D,P) (BOOST_PP_ADD_D(D,BOOST_PP_TUPLE3_ELEM0 P,BOOST_PP_TUPLE3_ELEM1 P),BOOST_PP_TUPLE3_ELEM1 P,BOOST_PP_DEC(BOOST_PP_TUPLE3_ELEM2 P))
#endif
#endif

/** <P>Obsolete. Use BOOST_PP_MUL().</P> */
#define BOOST_PREPROCESSOR_MUL(X,Y) BOOST_PP_MUL(X,Y)
#endif
