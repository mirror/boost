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

/** <p>Iterates <code>OP(D,X,STATE)</code> for each element <code>X</code> of the
list <code>LIST</code> (from the right or the end of the list).</p>

<p>In other words, expands to:</p>

<pre>
OP
( D
, BOOST_PP_LIST_AT(LIST,0)
, ... OP
      ( D
      , BOOST_PP_LIST_AT(LIST,BOOST_PP_SUB(BOOST_PP_LIST_SIZE(LIST),2))
      , OP
        ( D
        , BOOST_PP_LIST_AT(LIST,BOOST_PP_SUB(BOOST_PP_LIST_SIZE(LIST),1))
        , STATE
        )
      ) ...
)
</pre>

<p>For example,</p>

<pre>
#define TEST(D,X,STATE) BOOST_PP_CAT(STATE,X)
BOOST_PP_LIST_FOLD_RIGHT(TEST,_,BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</pre>

<p>expands to:</p>

<pre>
_CBA
</pre>

<h3>Note</h3>
<ul>
  <li>Folding, or accumulation, is a very general pattern of computation.
      Most list operations can be implemented in terms of folding.</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_FOLD_RIGHT(OP,LIST,STATE) BOOST_PP_LIST_FOLD_RIGHT_D(0,OP,LIST,STATE)

/** <p>Can be used inside BOOST_PP_WHILE() (see for an explanation of the D parameter).</p>

<h3>Note</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_RIGHT_D() implements automatic recursion. You
      can use a fold in the OP macro.</li>
</ul>
*/
#if 0
#  define BOOST_PP_LIST_FOLD_RIGHT_D(D,OP,LIST,STATE)
#endif

#define BOOST_PP_LIST_FOLD_RIGHT_D\
  BOOST_PP_AUTO_REC_CAT1(BOOST_PP_LIST_FOLD_RIGHT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(BOOST_PP_AUTO_REC_ID,(1)))
#define BOOST_PP_LIST_FOLD_RIGHT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(M,P)\
  BOOST_PP_AUTO_REC_CAT2(BOOST_PP_LIST_FOLD_RIGHT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#define BOOST_PP_LIST_FOLD_RIGHT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(M,P)\
  BOOST_PP_AUTO_REC_CAT3(BOOST_PP_LIST_FOLD_RIGHT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#define BOOST_PP_LIST_FOLD_RIGHT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(M,P)\
  (TOO MANY NESTED FOLDS!)

#define BOOST_PP_LIST_FOLD_RIGHT_D1(D,O,L,S) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_FOLD_RIGHT_O1,(O,S),BOOST_PP_LIST_REVERSE_D(D,L)))
#define BOOST_PP_LIST_FOLD_RIGHT_D2(D,O,L,S) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_FOLD_RIGHT_O2,(O,S),BOOST_PP_LIST_REVERSE_D(D,L)))
#define BOOST_PP_LIST_FOLD_RIGHT_D3(D,O,L,S) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_LIST_FOLD_LEFT_D(D,BOOST_PP_LIST_FOLD_RIGHT_O3,(O,S),BOOST_PP_LIST_REVERSE_D(D,L)))

#define BOOST_PP_LIST_FOLD_RIGHT_O1(D,OS,X) (BOOST_PP_TUPLE_ELEM(2,0,OS),BOOST_PP_TUPLE_ELEM(2,0,OS)(D,X,BOOST_PP_TUPLE_ELEM(2,1,OS)))
#define BOOST_PP_LIST_FOLD_RIGHT_O2(D,OS,X) (BOOST_PP_TUPLE_ELEM(2,0,OS),BOOST_PP_TUPLE_ELEM(2,0,OS)(D,X,BOOST_PP_TUPLE_ELEM(2,1,OS)))
#define BOOST_PP_LIST_FOLD_RIGHT_O3(D,OS,X) (BOOST_PP_TUPLE_ELEM(2,0,OS),BOOST_PP_TUPLE_ELEM(2,0,OS)(D,X,BOOST_PP_TUPLE_ELEM(2,1,OS)))

/** <p>Obsolete, just use BOOST_PP_LIST_FOLD_RIGHT().</p> */
#define BOOST_PP_LIST_FOLD_RIGHT_2ND BOOST_PP_LIST_FOLD_RIGHT
/** <p>Obsolete, just use BOOST_PP_LIST_FOLD_RIGHT_D().</p> */
#define BOOST_PP_LIST_FOLD_RIGHT_2ND_D BOOST_PP_LIST_FOLD_RIGHT_D 
#endif
