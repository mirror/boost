#ifndef BOOST_PREPROCESSOR_ENUM_HPP
#define BOOST_PREPROCESSOR_ENUM_HPP

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

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/tuple.hpp>

/** <p>Generates a comma separated list.</p>

<p>In other words, expands to the sequence:</p>

<pre>
MACRO(0,DATA), MACRO(1,DATA), ..., MACRO(BOOST_PP_DEC(COUNT),DATA)
</pre>

<p>For example,</p>

<pre>
#define TYPED_PARAM(INDEX,DATA)\
  BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,DATA),INDEX) BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,1,DATA),INDEX)
BOOST_PP_ENUM(3,TYPED_PARAM,(X,x))
</pre>

<p>expands to:</p>

<pre>
X0 x0, X1 x1, X2 x2
</pre>

<h3>2D and 3D repetition</h3>

<p>BOOST_PP_ENUM() implements automatic recursion. 2D and 3D repetition
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
</ul>
*/
#if 0
#  define BOOST_PP_ENUM(COUNT,MACRO,DATA)
#endif

#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(_MSC_VER)

/* This is a workaround for a MSVC++ PP bug. You'll need to add further
 * BOOST_PP_ENUM_AUTO_REC3/4/etc. wrapping as the maximum level of 
 * nesting REPEATS increases
 */
#  define BOOST_PP_ENUM\
    BOOST_PP_AUTO_REC_CAT1(BOOST_PP_ENUM_,BOOST_PP_ENUM_AUTO_REC2(\
      BOOST_PP_ENUM_AUTO_REC1,(BOOST_PP_AUTO_REC_ID,(1))\
      ))

#  define BOOST_PP_ENUM_BOOST_PP_ENUM_AUTO_REC1(M,P)\
    BOOST_PP_AUTO_REC_CAT2(BOOST_PP_ENUM_,BOOST_PP_ENUM_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#  define BOOST_PP_ENUM_BOOST_PP_ENUM_AUTO_REC2(M,P)\
    BOOST_PP_AUTO_REC_CAT3(BOOST_PP_ENUM_,BOOST_PP_ENUM_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#  define BOOST_PP_ENUM_BOOST_PP_ENUM_AUTO_REC3(M,P)\
    (TOO MANY NESTED REPEATS!)

#  define BOOST_PP_ENUM_AUTO_REC1(M,P) BOOST_PP_EXPAND(M P)
#  define BOOST_PP_ENUM_AUTO_REC2(M,P) BOOST_PP_EXPAND(M P)
#  define BOOST_PP_ENUM_AUTO_REC3(M,P) BOOST_PP_EXPAND(M P)

#  define BOOST_PP_ENUM_1(C,M,D) BOOST_PP_ENUM_AUTO_REC1(BOOST_PP_REPEAT,(C,BOOST_PP_ENUM_M1,(M,D)))
#  define BOOST_PP_ENUM_2(C,M,D) BOOST_PP_ENUM_AUTO_REC2(BOOST_PP_REPEAT,(C,BOOST_PP_ENUM_M2,(M,D)))
#  define BOOST_PP_ENUM_3(C,M,D) BOOST_PP_ENUM_AUTO_REC3(BOOST_PP_REPEAT,(C,BOOST_PP_ENUM_M3,(M,D)))

#else

#  define BOOST_PP_ENUM\
    BOOST_PP_AUTO_REC_CAT1(BOOST_PP_ENUM,BOOST_PP_REPEAT_AUTO_REC1(BOOST_PP_AUTO_REC_ID,(1)))
#  define BOOST_PP_ENUMBOOST_PP_REPEAT_AUTO_REC1(M,P)\
    BOOST_PP_AUTO_REC_CAT2(BOOST_PP_ENUM,BOOST_PP_REPEAT_AUTO_REC2(BOOST_PP_AUTO_REC_ID,(2)))
#  define BOOST_PP_ENUMBOOST_PP_REPEAT_AUTO_REC2(M,P)\
    BOOST_PP_AUTO_REC_CAT3(BOOST_PP_ENUM,BOOST_PP_REPEAT_AUTO_REC3(BOOST_PP_AUTO_REC_ID,(3)))
#  define BOOST_PP_ENUMBOOST_PP_REPEAT_AUTO_REC3(M,P)\
    (TOO MANY NESTED REPEATS!)

#  define BOOST_PP_ENUM1(C,M,D) BOOST_PP_REPEAT(C,BOOST_PP_ENUM_M1,(M,D))
#  define BOOST_PP_ENUM2(C,M,D) BOOST_PP_REPEAT(C,BOOST_PP_ENUM_M2,(M,D))
#  define BOOST_PP_ENUM3(C,M,D) BOOST_PP_REPEAT(C,BOOST_PP_ENUM_M3,(M,D))

#endif


#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__)
#  define BOOST_PP_ENUM_M1(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2,0,MD)(I,BOOST_PP_TUPLE_ELEM(2,1,MD))
#  define BOOST_PP_ENUM_M2(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2,0,MD)(I,BOOST_PP_TUPLE_ELEM(2,1,MD))
#  define BOOST_PP_ENUM_M3(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE_ELEM(2,0,MD)(I,BOOST_PP_TUPLE_ELEM(2,1,MD))
#else
#  define BOOST_PP_ENUM_M1(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE2_ELEM0 MD(I,BOOST_PP_TUPLE2_ELEM1 MD)
#  define BOOST_PP_ENUM_M2(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE2_ELEM0 MD(I,BOOST_PP_TUPLE2_ELEM1 MD)
#  define BOOST_PP_ENUM_M3(I,MD) BOOST_PP_COMMA_IF(I) BOOST_PP_TUPLE2_ELEM0 MD(I,BOOST_PP_TUPLE2_ELEM1 MD)
#endif
#endif
