#ifndef BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP

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

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum_shifted.hpp>

/** <P>Generates a comma separated list of shifted actual parameters.</P>

<P>In other words, expands to the sequence:</P>

<PRE>
  P##1, P##2, ..., P##N-1
</PRE>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_REPEAT()
</UL>

<H3>Rationale</H3>
<UL>
  <LI>This macro facilitates a typical usage of the library. Shifted parameter
      lists are common in template metaprograms.
</UL>
*/
#define BOOST_PP_ENUM_SHIFTED_PARAMS(N,P) BOOST_PP_ENUM_SHIFTED(N,BOOST_PP_ENUM_SHIFTED_PARAMS_F,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_ENUM_SHIFTED_PARAMS_F(I,P) BOOST_PP_CAT(P,I)
#endif

/** <P>Obsolete. Use BOOST_PP_ENUM_SHIFTED_PARAMS().</P> */
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS(N,P) BOOST_PP_ENUM_SHIFTED_PARAMS(N,P)
#endif
