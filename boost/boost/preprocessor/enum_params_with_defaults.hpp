#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_DEFAULTS_HPP
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_DEFAULTS_HPP

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
#include <boost/preprocessor/enum.hpp>

/** <P>Generates a comma separated list of parameters with defaults.</P>

<P>In other words, expands to the sequence:</P>

<PRE>
  P##0 = D##0, P##1 = D##1, ..., P##N-1 = D##N-1
</PRE>

<H3>Uses</H3>
<UL>
  <LI>BOOST_PP_REPEAT()
</UL>
*/
#define BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS(N,P,D) BOOST_PP_ENUM(N,BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS_F,(P,D))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS_F(I,PD) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,PD),I)=BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,1,PD),I)
#else
#  define BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS_F(I,PD) BOOST_PP_CAT(BOOST_PP_TUPLE2_ELEM0 PD,I)=BOOST_PP_CAT(BOOST_PP_TUPLE2_ELEM1 PD,I)
#endif
#endif

/** <P>Obsolete. Use BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS().</P> */
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_DEFAULTS(N,P,D) BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS(N,P,D)
#endif
