#ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
#define BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP

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

<a href="../../../../boost/preprocessor/comparison/greater_equal.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/comparison/less_equal.hpp>

/** Expands to 1 if X>=Y and 0 otherwise. */
#define BOOST_PP_GREATER_EQUAL(X,Y) BOOST_PP_GREATER_EQUAL_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_GREATER_EQUAL_D(D,X,Y) BOOST_PP_LESS_EQUAL_D(D,Y,X)
#endif

/** Obsolete. Use BOOST_PP_GREATER_EQUAL(). */
#define BOOST_PREPROCESSOR_GREATER_EQUAL(X,Y) BOOST_PP_GREATER_EQUAL(X,Y)
#endif
