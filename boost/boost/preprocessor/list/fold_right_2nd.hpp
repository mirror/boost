#ifndef BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_2ND_HPP
#define BOOST_PREPROCESSOR_LIST_FOLD_RIGHT_2ND_HPP

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

#include <boost/preprocessor/list/fold_left_2nd.hpp>
#include <boost/preprocessor/list/reverse.hpp>

/** <p>Same as BOOST_PP_LIST_FOLD_RIGHT(), but implemented independently.</p>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_LEFT_2ND()</li>
</ul>
*/
#define BOOST_PP_LIST_FOLD_RIGHT_2ND(F,L,P) BOOST_PP_LIST_FOLD_RIGHT_2ND_D(0,F,L,P)

/** <p>Can be used inside BOOST_PP_WHILE().</p> */
#define BOOST_PP_LIST_FOLD_RIGHT_2ND_D(D,F,L,P) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_LIST_FOLD_LEFT_2ND_D(D,BOOST_PP_LIST_FOLD_RIGHT_2ND_F,(F,P),BOOST_PP_LIST_FOLD_LEFT_2ND_D(D,BOOST_PP_LIST_REVERSE_F,(_,_,0),L)))
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FOLD_RIGHT_2ND_F(D,P,H) (BOOST_PP_TUPLE_ELEM(2,0,P),BOOST_PP_TUPLE_ELEM(2,0,P)(D,H,BOOST_PP_TUPLE_ELEM(2,1,P)))
#elif !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)
#  define BOOST_PP_LIST_FOLD_RIGHT_2ND_F(D,P,H) (BOOST_PP_TUPLE_ELEM(2,0,P),BOOST_PP_TUPLE_ELEM(2,0,P)(D,H,BOOST_PP_TUPLE2_ELEM1 P))
#else
#  define BOOST_PP_LIST_FOLD_RIGHT_2ND_F(D,P,H) (BOOST_PP_TUPLE2_ELEM0 P,BOOST_PP_TUPLE2_ELEM0 P(D,H,BOOST_PP_TUPLE2_ELEM1 P))
#endif
#endif
