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

#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/for.hpp>

/** <p>Repeats <code>F(R,P,BOOST_PP_LIST_AT(L,I))</code> for each I = [0,
BOOST_PP_LIST_SIZE(L)[.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  F(R,P,BOOST_PP_LIST_AT(L,0))
  F(R,P,BOOST_PP_LIST_AT(L,1))
  ...
  F(R,P,BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L))))
</pre>

<h3>Example</h3>
<ul>
  <li><a href="../../example/catch_builtin.cpp">catch_builtin.cpp</a></li>
</ul>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_FOR()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_FOR_EACH(F,P,L) BOOST_PP_LIST_FOR_EACH_R(0,F,P,L)

#define BOOST_PP_LIST_FOR_EACH_R(R,F,P,L) BOOST_PP_FOR##R((F,P,L),BOOST_PP_LIST_FOR_EACH_C,BOOST_PP_LIST_FOR_EACH_F,BOOST_PP_LIST_FOR_EACH_I)
#define BOOST_PP_LIST_FOR_EACH_C(R,FPL) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_TUPLE_ELEM(3,2,FPL))
#define BOOST_PP_LIST_FOR_EACH_F(R,FPL) (BOOST_PP_TUPLE_ELEM(3,0,FPL),BOOST_PP_TUPLE_ELEM(3,1,FPL),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,FPL)))
#define BOOST_PP_LIST_FOR_EACH_I(R,FPL) BOOST_PP_TUPLE_ELEM(3,0,FPL)(R,BOOST_PP_TUPLE_ELEM(3,1,FPL),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,FPL)))
#endif
