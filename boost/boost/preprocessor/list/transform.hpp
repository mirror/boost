#ifndef BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP
#define BOOST_PREPROCESSOR_LIST_TRANSFORM_HPP

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

#include <boost/preprocessor/list/fold_right.hpp>

/** <p>Applies the macro <code>F(D,P,X)</code> to each element <code>X</code>
of the list producing a new list.</p>

<p>In other words, expands to:</p>

<pre>
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,0)),
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,1)),
  ...
  BOOST_PP_LIST_CONS(F(D,P,BOOST_PP_LIST_AT(L,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(L)))),
  BOOST_PP_LIST_NIL) ... ))
</pre>

<p>For example,</p>

<pre>
  BOOST_PP_LIST_TRANSFORM(BOOST_PP_ADD_D,2,BOOST_PP_TUPLE_TO_LIST(2,(1,2)))
</pre>

<p>expands to the same as:</p>

<pre>
  BOOST_PP_TUPLE_TO_LIST(2,(3,4))
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_RIGHT()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_TRANSFORM(F,P,L) BOOST_PP_LIST_TRANSFORM_D(0,F,P,L)

/** <p>Can be used inside BOOST_PP_WHILE().</p> */
#define BOOST_PP_LIST_TRANSFORM_D(D,F,P,L) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_LIST_FOLD_RIGHT_D(D,BOOST_PP_LIST_TRANSFORM_F,L,(F,P,(_,_,0))))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE_ELEM(3,1,P),(BOOST_PP_TUPLE_ELEM(3,0,P)(D,BOOST_PP_TUPLE_ELEM(3,1,P),H),BOOST_PP_TUPLE_ELEM(3,2,P),1))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE3_ELEM1 P,(BOOST_PP_TUPLE_ELEM(3,0,P)(D,BOOST_PP_TUPLE3_ELEM1 P,H),BOOST_PP_TUPLE3_ELEM2 P,1))
#else
#  define BOOST_PP_LIST_TRANSFORM_F(D,H,P) (BOOST_PP_TUPLE3_ELEM0 P,BOOST_PP_TUPLE3_ELEM1 P,(BOOST_PP_TUPLE3_ELEM0 P(D,BOOST_PP_TUPLE3_ELEM1 P,H),BOOST_PP_TUPLE3_ELEM2 P,1))
#endif
#endif
