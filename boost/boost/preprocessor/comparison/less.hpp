#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP

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
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/logical/and.hpp>

/** <p>Expands to <code>1</code> if <code>X &lt; Y</code> and <code>0</code>
otherwise.</p>

<p>Both <code>X</code> and <code>Y</code> must expand to integer literals
in the range [0, BOOST_PP_LIMIT_MAG].</p>

<p>For example, <code>BOOST_PP_LESS(2,6)</code> expands to <code>1</code>.</p>

<h3>Test</h3>
<ul>
  <li><a href="../../test/arithmetic_test.cpp">arithmetic_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LESS(X,Y) BOOST_PP_LESS_D(0,X,Y)

/** <p>Can be used inside BOOST_PP_WHILE() (see for an explanation of the D parameter).</p> */
#define BOOST_PP_LESS_D(D,X,Y) BOOST_PP_AND(BOOST_PP_NOT_EQUAL_D(D,X,Y),BOOST_PP_LESS_EQUAL_D(D,X,Y))
#endif
