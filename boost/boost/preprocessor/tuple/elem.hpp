#ifndef BOOST_PREPROCESSOR_TUPLE_ELEM_HPP
#define BOOST_PREPROCESSOR_TUPLE_ELEM_HPP

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

#include <boost/preprocessor/detail/cat.hpp>
#include <boost/preprocessor/detail/expand.hpp>

/** <p>Expands to the <code>INDEX</code>:th element of an <code>SIZE_OF_TUPLE</code>-tuple.</p>

<p>For example,</p>

<pre>
BOOST_PP_TUPLE_ELEM(2,1,(A,B))
</pre>

<p>expands to <code>B</code>.</p>

<h3>See</h3>
<ul>
  <li>BOOST_PP_LIMIT_TUPLE</li>
</ul>
*/
#define BOOST_PP_TUPLE_ELEM(SIZE_OF_TUPLE,INDEX,TUPLE) BOOST_PP_DETAIL_EXPAND(BOOST_PP_DETAIL_CAT2(BOOST_PP_TUPLE16_ELEM,INDEX) BOOST_PP_DETAIL_CAT2(BOOST_PP_TUPLE_ELEM_EX,SIZE_OF_TUPLE) TUPLE)

#define BOOST_PP_TUPLE_ELEM_EX1(A) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX2(A,B) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX3(A,B,C) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX4(A,B,C,D) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX5(A,B,C,D,E) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX6(A,B,C,D,E,F) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX7(A,B,C,D,E,F,G) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX8(A,B,C,D,E,F,G,H) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX9(A,B,C,D,E,F,G,H,I) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX10(A,B,C,D,E,F,G,H,I,J) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX11(A,B,C,D,E,F,G,H,I,J,K) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX12(A,B,C,D,E,F,G,H,I,J,K,L) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX13(A,B,C,D,E,F,G,H,I,J,K,L,M) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX14(A,B,C,D,E,F,G,H,I,J,K,L,M,N) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)
#define BOOST_PP_TUPLE_ELEM_EX16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) (A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)

#define BOOST_PP_TUPLE16_ELEM0(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) A
#define BOOST_PP_TUPLE16_ELEM1(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) B
#define BOOST_PP_TUPLE16_ELEM2(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) C
#define BOOST_PP_TUPLE16_ELEM3(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) D
#define BOOST_PP_TUPLE16_ELEM4(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) E
#define BOOST_PP_TUPLE16_ELEM5(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) F
#define BOOST_PP_TUPLE16_ELEM6(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) G
#define BOOST_PP_TUPLE16_ELEM7(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) H
#define BOOST_PP_TUPLE16_ELEM8(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) I
#define BOOST_PP_TUPLE16_ELEM9(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) J
#define BOOST_PP_TUPLE16_ELEM10(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) K
#define BOOST_PP_TUPLE16_ELEM11(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) L
#define BOOST_PP_TUPLE16_ELEM12(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) M
#define BOOST_PP_TUPLE16_ELEM13(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) N
#define BOOST_PP_TUPLE16_ELEM14(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) O
#define BOOST_PP_TUPLE16_ELEM15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P) P
#endif
