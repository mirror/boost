#ifndef BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP
#define BOOST_PREPROCESSOR_LIST_FOLD_LEFT_HPP

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

#include <boost/preprocessor/detail/auto_rec.hpp>
#include <boost/preprocessor/expand.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/while.hpp>

/** <p>Iterates <code>OP(D,STATE,X)</code> for each element <code>X</code> of the
list <code>LIST</code> (from the left or the start of the list).</p>

<p>In other words, expands to:</p>

<pre>
OP
( D
, ... OP(D, OP(D,STATE,BOOST_PP_LIST_AT(LIST,0)), BOOST_PP_LIST_AT(LIST,1)) ...
, BOOST_PP_LIST_AT(LIST,BOOST_PP_DEC(BOOST_PP_LIST_SIZE(LIST))
)
</pre>

<p>For example,</p>

<pre>
#define TEST(D,STATE,X) BOOST_PP_CAT(STATE,X)
BOOST_PP_LIST_FOLD_LEFT(TEST,_,BOOST_PP_TUPLE_TO_LIST(3,(A,B,C)))
</pre>

<p>expands to:</p>

<pre>
_ABC
</pre>

<h3>Note</h3>
<ul>
  <li>Folding, or accumulation, is a very general pattern of computation.
      Most list operations can be implemented in terms of folding.</li>
</ul>

<h3>See</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_RIGHT()</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/list_test.cpp">list_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_LIST_FOLD_LEFT(OP,STATE,LIST) BOOST_PP_LIST_FOLD_LEFT_D(0,OP,STATE,LIST)

/** <p>Can be used inside BOOST_PP_WHILE() (see for an explanation of the D parameter).</p>

<h3>Note</h3>
<ul>
  <li>BOOST_PP_LIST_FOLD_LEFT_D() implements automatic recursion. You
      can use a fold in the OP macro.</li>
</ul>
*/
#if 0
#  define BOOST_PP_LIST_FOLD_LEFT_D(D,OP,STATE,LIST)
#endif

#define BOOST_PP_LIST_FOLD_LEFT_D\
  BOOST_PP_AUTO_REC_CAT1(BOOST_PP_LIST_FOLD_LEFT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(BOOST_PP_AUTO_REC_ID,(1)))
#define BOOST_PP_LIST_FOLD_LEFT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(M,P)\
  BOOST_PP_AUTO_REC_CAT2(BOOST_PP_LIST_FOLD_LEFT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#define BOOST_PP_LIST_FOLD_LEFT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(M,P)\
  BOOST_PP_AUTO_REC_CAT3(BOOST_PP_LIST_FOLD_LEFT_D,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#define BOOST_PP_LIST_FOLD_LEFT_DBOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(M,P)\
  (TOO MANY NESTED FOLDS!)

#define BOOST_PP_LIST_FOLD_LEFT_D1(D,O,S,L) BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(BOOST_PP_WHILE##D,(BOOST_PP_LIST_FOLD_LEFT_P,BOOST_PP_LIST_FOLD_LEFT_O1,(O,S,L))))
#define BOOST_PP_LIST_FOLD_LEFT_D2(D,O,S,L) BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(BOOST_PP_WHILE##D,(BOOST_PP_LIST_FOLD_LEFT_P,BOOST_PP_LIST_FOLD_LEFT_O2,(O,S,L))))
#define BOOST_PP_LIST_FOLD_LEFT_D3(D,O,S,L) BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(BOOST_PP_WHILE##D,(BOOST_PP_LIST_FOLD_LEFT_P,BOOST_PP_LIST_FOLD_LEFT_O3,(O,S,L))))

#define BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC1(M,P) BOOST_PP_EXPAND(M P)
#define BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC2(M,P) BOOST_PP_EXPAND(M P)
#define BOOST_PP_LIST_FOLD_LEFT_D_AUTO_REC3(M,P) BOOST_PP_EXPAND(M P)

#define BOOST_PP_LIST_FOLD_LEFT_P(D,OSL) BOOST_PP_TUPLE_ELEM(3,2,BOOST_PP_TUPLE_ELEM(3,2,OSL))

#define BOOST_PP_LIST_FOLD_LEFT_O1(D,OSL) (BOOST_PP_TUPLE_ELEM(3,0,OSL),BOOST_PP_TUPLE_ELEM(3,0,OSL)(D,BOOST_PP_TUPLE_ELEM(3,1,OSL),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,OSL))),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,OSL)))
#define BOOST_PP_LIST_FOLD_LEFT_O2(D,OSL) (BOOST_PP_TUPLE_ELEM(3,0,OSL),BOOST_PP_TUPLE_ELEM(3,0,OSL)(D,BOOST_PP_TUPLE_ELEM(3,1,OSL),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,OSL))),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,OSL)))
#define BOOST_PP_LIST_FOLD_LEFT_O3(D,OSL) (BOOST_PP_TUPLE_ELEM(3,0,OSL),BOOST_PP_TUPLE_ELEM(3,0,OSL)(D,BOOST_PP_TUPLE_ELEM(3,1,OSL),BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_TUPLE_ELEM(3,2,OSL))),BOOST_PP_TUPLE_ELEM(3,1,BOOST_PP_TUPLE_ELEM(3,2,OSL)))

/** <p>Obsolete, just use BOOST_PP_LIST_FOLD_LEFT().</p> */
#define BOOST_PP_LIST_FOLD_LEFT_2ND BOOST_PP_LIST_FOLD_LEFT
/** <p>Obsolete, just use BOOST_PP_LIST_FOLD_LEFT_D().</p> */
#define BOOST_PP_LIST_FOLD_LEFT_2ND_D BOOST_PP_LIST_FOLD_LEFT_D
#endif
