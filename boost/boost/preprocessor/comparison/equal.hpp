#ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP

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

#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/logical/not.hpp>

/** <p>Expands to <code>1</code> if <code>X == Y</code> and <code>0</code>
otherwise.</p>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_WHILE()</li>
</ul>
*/
#define BOOST_PP_EQUAL(X,Y) BOOST_PP_EQUAL_D(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_EQUAL_D(D,X,Y) BOOST_PP_NOT(BOOST_PP_NOT_EQUAL_D(D,X,Y))
#endif

/** <p>Obsolete. Use BOOST_PP_EQUAL().</p> */
#define BOOST_PREPROCESSOR_EQUAL(X,Y) BOOST_PP_EQUAL(X,Y)
#endif
