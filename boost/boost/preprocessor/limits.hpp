#ifndef BOOST_PREPROCESSOR_LIMITS_HPP
#define BOOST_PREPROCESSOR_LIMITS_HPP

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

/** <P>Expands to the number of dimensions of repeat supported by the
library.</P>

<P>The repeat macros are named BOOST_PP_REPEAT(), BOOST_PP_REPEAT_2ND(),
BOOST_PP_REPEAT_3RD(), ...</P>
*/
#define BOOST_PP_LIMIT_DIM 3

/** <P>Expands to the maximum straight numeric literal supported by the
library.</P>

<P>This is also the limit of the repetition primitives (BOOST_PP_ENUM family
and BOOST_PP_REPEAT family).</P>

<P>NOTES:</P>
<UL>
  <LI>Only decimal integer literals in the range [0,BOOST_PP_LIMIT_MAG]
      are supported.
  <LI>All arithmetic operations (ADD,SUB,MUL,DIV) use saturation arithmetic.
  <LI>The maximum repetition count supported by the library may not be reached
      due to compiler limitations.
</UL>
*/
#define BOOST_PP_LIMIT_MAG 128

/** <P>Expands to the maximum tuple length supported by the library.</P> */
#define BOOST_PP_LIMIT_TUPLE 16

/** <P>Obsolete. Use BOOST_PP_LIMIT_DIM.</P> */
#define BOOST_PREPROCESSOR_LIMIT_DIM BOOST_PP_LIMIT_DIM

/** <P>Obsolete. Use BOOST_PP_LIMIT_MAG.</P> */
#define BOOST_PREPROCESSOR_LIMIT_MAG BOOST_PP_LIMIT_MAG

/** <P>Obsolete. Use BOOST_PP_LIMIT_TUPLE.</P> */
#define BOOST_PREPROCESSOR_LIMIT_TUPLE BOOST_PP_LIMIT_TUPLE
#endif
