#ifndef BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP
#define BOOST_PREPROCESSOR_LIST_FOR_EACH_HPP

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

#include <boost/preprocessor/list/for_each_i.hpp>

/** <p>Repeats <code>F(R,P,BOOST_PP_LIST_AT(L,I))</code> for each I = [0,
BOOST_PP_LIST_SIZE(L)[.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  F(R,P,BOOST_PP_LIST_AT(L,0))
  F(R,P,BOOST_PP_LIST_AT(L,1))
  ...
  F(R,P,BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L))))
</pre>

<p>For example,</p>

<pre>
  #define TEST(R,P,X) BOOST_PP_CAT(P,X)();
  BOOST_PP_LIST_FOR_EACH(TEST,prefix_,BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</pre>

<p>expands to:</p>

<pre>
  prefix_A(); prefix_B(); prefix_C();
</pre>

<h3>Example</h3>
<ul>
  <li><a href="../../example/catch_builtin.cpp">catch_builtin.cpp</a></li>
</ul>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_FOR() (see for explanation of the R parameter)</li>
  <li>BOOST_PP_LIST_FOR_EACH_I() </li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_FOR_EACH(F,P,L) BOOST_PP_LIST_FOR_EACH_R(0,F,P,L)

/** <p>Can be used inside BOOST_PP_FOR().</p> */
#define BOOST_PP_LIST_FOR_EACH_R(R,F,P,L) BOOST_PP_LIST_FOR_EACH_I_R(R,BOOST_PP_LIST_FOR_EACH_F,(F,P),L)
#define BOOST_PP_LIST_FOR_EACH_F(R,FP,I,X) BOOST_PP_TUPLE_ELEM(2,0,FP)(R,BOOST_PP_TUPLE_ELEM(2,1,FP),X)
#endif
