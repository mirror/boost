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

#include <boost/preprocessor/comparison/less_equal.hpp>

/** <p>Expands to <code>1</code> if <code>X &gt;= Y</code> and <code>0</code>
otherwise.</p>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_WHILE()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/arithmetic_test.cpp">arithmetic_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_GREATER_EQUAL(X,Y) BOOST_PP_GREATER_EQUAL_D(0,X,Y)

#define BOOST_PP_GREATER_EQUAL_D(D,X,Y) BOOST_PP_LESS_EQUAL_D(D,Y,X)

/** <p>Obsolete. Use BOOST_PP_GREATER_EQUAL().</p> */
#define BOOST_PREPROCESSOR_GREATER_EQUAL(X,Y) BOOST_PP_GREATER_EQUAL(X,Y)
#endif
