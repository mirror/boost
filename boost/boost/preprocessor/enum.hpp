#ifndef BOOST_PREPROCESSOR_ENUM_HPP
#define BOOST_PREPROCESSOR_ENUM_HPP

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

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/tuple.hpp>

/** <P>Generates a comma separated list.</P>

<P>In other words, expands to the sequence:</P>

<PRE>
  F(0,P), F(1,P), ..., F(N-1,P)
</PRE>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_REPEAT()
</UL>
*/
#define BOOST_PP_ENUM(N,F,P) BOOST_PP_REPEAT(N,BOOST_PP_ENUM_F,(F,P))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_ENUM_F(I,FP) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2,0,FP)(I,BOOST_PP_TUPLE_ELEM(2,1,FP))
#else
#  define BOOST_PP_ENUM_F(I,FP) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE2_ELEM0 FP(I,BOOST_PP_TUPLE2_ELEM1 FP)
#endif
#endif
#endif
