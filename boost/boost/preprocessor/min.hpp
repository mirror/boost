#ifndef BOOST_PREPROCESSOR_MIN_HPP
#define BOOST_PREPROCESSOR_MIN_HPP

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

/** \file

<a href="../../../../boost/preprocessor/min.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/comparison/less_equal.hpp>
#include <boost/preprocessor/if.hpp>

/** Expands to the minimum of X and Y.

For example, BOOST_PP_MIN(5,7) expands to 5 (a single token).

<H3>Uses</H3>
- BOOST_PP_WHILE()
*/
#define BOOST_PP_MIN(X,Y) BOOST_PP_MIN_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_MIN_D(D,X,Y) BOOST_PP_IF(BOOST_PP_LESS_EQUAL_D(D,Y,X),Y,X)
#endif

/** Obsolete. Use BOOST_PP_MIN(). */
#define BOOST_PREPROCESSOR_MIN(X,Y) BOOST_PP_MIN(X,Y)
#endif
