#ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP
#define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_HPP

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

#include <boost/preprocessor/list/reverse.hpp>

/** <p>Iterates <code>F(D,X,P)</code> for each element <code>X</code> of the
list <code>L</code> (from the right or the end of the list).</p>

<p>In other words, expands to:</p>

<pre>
  F
  ( D
  , BOOST_PP_LIST_AT(L,0)
  , ... F
        ( D
        , BOOST_PP_LIST_AT(L,BOOST_PP_SUB(BOOST_PP_LIST_SIZE(L),2))
        , F
          ( D
          , BOOST_PP_LIST_AT(L,BOOST_PP_SUB(BOOST_PP_LIST_SIZE(L),1))
          , P
          )
        ) ...
  )
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_LEFT()</li>
</ul>
*/
#define BOOST_PP_LIST_FOLD_RIGHT(F,L,P) BOOST_PP_LIST_FOLD_RIGHT_D(0,F,L,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_LIST_FOLD_RIGHT_D(D,F,L,P) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_FOLD_RIGHT_F,(F,P),BOOST_PP_LIST_REVERSE_D(D,L)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FOLD_RIGHT_F(D,P,H) (BOOST_PP_TUPLE_ELEM(2,0,P),BOOST_PP_TUPLE_ELEM(2,0,P)(D,H,BOOST_PP_TUPLE_ELEM(2,1,P)))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_FOLD_RIGHT_F(D,P,H) (BOOST_PP_TUPLE_ELEM(2,0,P),BOOST_PP_TUPLE_ELEM(2,0,P)(D,H,BOOST_PP_TUPLE2_ELEM1 P))
#else
#  define BOOST_PP_LIST_FOLD_RIGHT_F(D,P,H) (BOOST_PP_TUPLE2_ELEM0 P,BOOST_PP_TUPLE2_ELEM0 P(D,H,BOOST_PP_TUPLE2_ELEM1 P))
#endif
#endif
#endif
