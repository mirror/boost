#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP

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

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/while.hpp>

/** <P>Expands to the difference of X and Y.</P>

<P>For example, BOOST_PP_SUB(4,3) expands to 1 (a single token).</P>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_WHILE()
</UL>
*/
#define BOOST_PP_SUB(X,Y) BOOST_PP_SUB_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_SUB_D(D,X,Y) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_WHILE##D(BOOST_PP_SUB_C,BOOST_PP_SUB_F,(X,Y)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_SUB_C(D,P) BOOST_PP_TUPLE_ELEM(2,1,P)
#  define BOOST_PP_SUB_F(D,P) (BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,0,P)),BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,1,P)))
#else
#  define BOOST_PP_SUB_C(D,P) BOOST_PP_TUPLE2_ELEM1 P
#  define BOOST_PP_SUB_F(D,P) (BOOST_PP_DEC(BOOST_PP_TUPLE2_ELEM0 P),BOOST_PP_DEC(BOOST_PP_TUPLE2_ELEM1 P))
#endif
#endif

/** <P>Obsolete. Use BOOST_PP_SUB(X,Y).</P> */
#define BOOST_PREPROCESSOR_SUB(X,Y) BOOST_PP_SUB(X,Y)
#endif
