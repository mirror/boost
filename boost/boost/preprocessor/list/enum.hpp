#ifndef BOOST_PREPROCESSOR_LIST_ENUM_HPP
#define BOOST_PREPROCESSOR_LIST_ENUM_HPP

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

#include <boost/preprocessor/comma.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/for.hpp>
#include <boost/preprocessor/list/adt.hpp>

/** <p>Converts the list to a comma separated list.</p>

<p>For example,</p>

<pre>
  BOOST_PP_LIST_ENUM(BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</pre>

<p>expands to:</p>

<pre>
  A,B,C
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_FOR()</li>
</ul>
*/
#define BOOST_PP_LIST_ENUM(L) BOOST_PP_LIST_ENUM_R(0,L)

#define BOOST_PP_LIST_ENUM_R(R,L) BOOST_PP_FOR##R((L,BOOST_PP_EMPTY),BOOST_PP_LIST_ENUM_C,BOOST_PP_LIST_ENUM_F,BOOST_PP_LIST_ENUM_I)
#define BOOST_PP_LIST_ENUM_C(R,P) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_TUPLE_ELEM(2,0,P))
#define BOOST_PP_LIST_ENUM_F(R,P) (BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(2,0,P)),BOOST_PP_COMMA)
#define BOOST_PP_LIST_ENUM_I(R,P) BOOST_PP_TUPLE_ELEM(2,1,P)() BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(2,0,P))
#endif
