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

/** <p>Expands to the number of dimensions of repeat supported by the
library.</p>

<p>This concerns the repetition primitives (BOOST_PP_ENUM(),
BOOST_PP_REPEAT() and BOOST_PP_REPEAT_FROM_TO()).</p>
*/
#define BOOST_PP_LIMIT_DIM 3

/** <p>Expands to the maximum straight numeric literal supported by the
library.</p>

<p>This is also the limit of the repetition primitives (BOOST_PP_ENUM(),
BOOST_PP_REPEAT() and BOOST_PP_REPEAT_FROM_TO()).</p>

<h3>Note</h3>
<ul>
  <li>Only decimal integer literals in the range [0, BOOST_PP_LIMIT_MAG]
      are supported.</li>
  <li>All arithmetic operations (BOOST_PP_ADD(), BOOST_PP_SUB(),
      BOOST_PP_MUL(), BOOST_PP_DIV()) use saturation arithmetic.</li>
  <li>The maximum repetition count supported by the library may not be reached
      due to compiler limitations.</li>
</ul>
*/
#define BOOST_PP_LIMIT_MAG 128

/** <p>Expands to the maximum tuple size supported by the library.</p> */
#define BOOST_PP_LIMIT_TUPLE 32
#endif
