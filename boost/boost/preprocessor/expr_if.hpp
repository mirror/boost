#ifndef BOOST_PREPROCESSOR_EXPR_IF_HPP
#define BOOST_PREPROCESSOR_EXPR_IF_HPP

/* Copyright (C) 2002
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

#include <boost/preprocessor/logical/bool.hpp>

/** <p>Expands to <code>E</code> if <code>C != 0</code> and to nothing if <code>C == 0</code>.</p>

<p>For example, <code>BOOST_PP_EXPR_IF(1,^)</code> expands to <code>^</code>.</p>

<h3>See</h3>
<ul>
  <li>BOOST_PP_IF()</li>
</ul>
*/
#define BOOST_PP_EXPR_IF(C,E) BOOST_PP_EXPR_IF_BOOL(BOOST_PP_BOOL(C),E)

#define BOOST_PP_EXPR_IF_BOOL(C,E) BOOST_PP_EXPR_IF_BOOL_DELAY(C,E)
#define BOOST_PP_EXPR_IF_BOOL_DELAY(C,E) BOOST_PP_EXPR_IF_BOOL##C(E)
#define BOOST_PP_EXPR_IF_BOOL0(E)
#define BOOST_PP_EXPR_IF_BOOL1(E) E
#endif
