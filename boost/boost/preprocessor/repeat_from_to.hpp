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

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/repeat.hpp>

/** <p>Repeats the macro <code>MACRO(INDEX,DATA)</code> for <code>INDEX = [FIRST,LAST)</code>.</p>

<p>In other words, expands to the sequence:</p>

<pre>
MACRO(FIRST,DATA) MACRO(BOOST_PP_INC(FIRST),DATA) ... MACRO(BOOST_PP_DEC(LAST),DATA)
</pre>

<p>For example,</p>

<pre>
#define TEST(INDEX,DATA) DATA(INDEX);
BOOST_PP_REPEAT_FROM_TO(4,7,TEST,X)
</pre>

<p>expands to:</p>

<pre>
X(4); X(5); X(6);
</pre>

<h3>2D and 3D repetition</h3>

<p>BOOST_PP_REPEAT_FROM_TO() implements automatic recursion. 2D and 3D repetition
are directly supported.</p>

<h3>See</h3>
<ul>
  <li>BOOST_PP_FOR()</li>
  <li>BOOST_PP_LIMIT_DIM</li>
  <li>BOOST_PP_LIMIT_MAG</li>
</ul>

<h3>Test</h3>
<ul>
  <li><a href="../../test/repeat_test.cpp">repeat_test.cpp</a></li>
  <li><a href="../../test/repeat_2nd_test.cpp">repeat_2nd_test.cpp</a></li>
</ul>
*/
#if 0
#  define BOOST_PP_REPEAT_FROM_TO(FIRST,LAST,MACRO,DATA)
#endif

#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)

/* This is a workaround for a MSVC++ PP bug. You'll need to add further
 * BOOST_PP_REPEAT_FT_AUTO_REC3/4/etc. wrapping as the maximum level of 
 * nesting REPEATS increases
 */
#  define BOOST_PP_REPEAT_FROM_TO\
    BOOST_PP_AUTO_REC_CAT1(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_FT_AUTO_REC2(\
      BOOST_PP_REPEAT_FT_AUTO_REC1,(BOOST_PP_AUTO_REC_ID,(1))\
      ))

#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_FT_AUTO_REC1(M,P)\
    BOOST_PP_AUTO_REC_CAT2(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_FT_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_FT_AUTO_REC2(M,P)\
    BOOST_PP_AUTO_REC_CAT3(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_FT_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_FT_AUTO_REC3(M,P)\
    (TOO MANY NESTED REPEATS!)

#  define BOOST_PP_REPEAT_FT_AUTO_REC1(M,P) BOOST_PP_EXPAND(M P)
#  define BOOST_PP_REPEAT_FT_AUTO_REC2(M,P) BOOST_PP_EXPAND(M P)
#  define BOOST_PP_REPEAT_FT_AUTO_REC3(M,P) BOOST_PP_EXPAND(M P)

#  define BOOST_PP_REPEAT_FROM_TO_1(F,L,M,D) BOOST_PP_REPEAT_FT_AUTO_REC1(BOOST_PP_REPEAT,(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M1,(F,M,D)))
#  define BOOST_PP_REPEAT_FROM_TO_2(F,L,M,D) BOOST_PP_REPEAT_FT_AUTO_REC2(BOOST_PP_REPEAT,(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M2,(F,M,D)))
#  define BOOST_PP_REPEAT_FROM_TO_3(F,L,M,D) BOOST_PP_REPEAT_FT_AUTO_REC3(BOOST_PP_REPEAT,(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M3,(F,M,D)))

#else

#  define BOOST_PP_REPEAT_FROM_TO\
    BOOST_PP_AUTO_REC_CAT1(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_AUTO_REC1(BOOST_PP_AUTO_REC_ID,(1)))
#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_AUTO_REC1(M,P)\
    BOOST_PP_AUTO_REC_CAT2(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_AUTO_REC2(M,P)\
    BOOST_PP_AUTO_REC_CAT3(BOOST_PP_REPEAT_FROM_TO_,BOOST_PP_REPEAT_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#  define BOOST_PP_REPEAT_FROM_TO_BOOST_PP_REPEAT_AUTO_REC3(M,P)\
    (TOO MANY NESTED REPEATS!)

#  define BOOST_PP_REPEAT_FROM_TO_1(F,L,M,D) BOOST_PP_REPEAT(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M1,(F,M,D))
#  define BOOST_PP_REPEAT_FROM_TO_2(F,L,M,D) BOOST_PP_REPEAT(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M2,(F,M,D))
#  define BOOST_PP_REPEAT_FROM_TO_3(F,L,M,D) BOOST_PP_REPEAT(BOOST_PP_SUB(L,F),BOOST_PP_REPEAT_FROM_TO_M3,(F,M,D))

#endif

#define BOOST_PP_REPEAT_FROM_TO_M1(I,FMD) BOOST_PP_TUPLE_ELEM(3,1,FMD)(BOOST_PP_ADD(I,BOOST_PP_TUPLE_ELEM(3,0,FMD)),BOOST_PP_TUPLE_ELEM(3,2,FMD))
#define BOOST_PP_REPEAT_FROM_TO_M2(I,FMD) BOOST_PP_TUPLE_ELEM(3,1,FMD)(BOOST_PP_ADD(I,BOOST_PP_TUPLE_ELEM(3,0,FMD)),BOOST_PP_TUPLE_ELEM(3,2,FMD))
#define BOOST_PP_REPEAT_FROM_TO_M3(I,FMD) BOOST_PP_TUPLE_ELEM(3,1,FMD)(BOOST_PP_ADD(I,BOOST_PP_TUPLE_ELEM(3,0,FMD)),BOOST_PP_TUPLE_ELEM(3,2,FMD))

/** <p>Obsolete, just use BOOST_PP_REPEAT_FROM_TO().</p> */
#define BOOST_PP_REPEAT_FROM_TO_2ND BOOST_PP_REPEAT_FROM_TO
/** <p>Obsolete, just use BOOST_PP_REPEAT_FROM_TO().</p> */
#define BOOST_PP_REPEAT_FROM_TO_3RD BOOST_PP_REPEAT_FROM_TO
#endif
