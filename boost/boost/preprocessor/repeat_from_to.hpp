#ifndef BOOST_PREPROCESSOR_REPEAT_FROM_TO_HPP
#define BOOST_PREPROCESSOR_REPEAT_FROM_TO_HPP

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

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

/** <p>Repeats the macro <code>M(I,P)</code> for <code>I = [S,E[</code>.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  M(S,P) M(BOOST_PP_INC(S),P) ... M(BOOST_PP_DEC(E),P)
</pre>

<p>For example,</p>

<pre>
  #define TEST(I,P) P(I);
  BOOST_PP_REPEAT_FROM_TO(4,7,TEST,X)
</pre>

<p>expands to:</p>

<pre>
  X(4); X(5); X(6);
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_REPEAT()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/repeat_test.cpp">repeat_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_REPEAT_FROM_TO(S,E,M,P) BOOST_PP_REPEAT(BOOST_PP_SUB(E,S),BOOST_PP_REPEAT_FROM_TO_F,(S,M,P))
#define BOOST_PP_REPEAT_FROM_TO_F(I,SMP) BOOST_PP_TUPLE_ELEM(3,1,SMP)(BOOST_PP_ADD(I,BOOST_PP_TUPLE_ELEM(3,0,SMP)),BOOST_PP_TUPLE_ELEM(3,2,SMP))
#endif
