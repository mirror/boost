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

/* This example shows how BOOST_PP_WHILE() can be used for implementing
 * macros.
 */

#include <boost/preprocessor/while.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/list/adt.hpp>
#include <boost/preprocessor/comparison/less_equal.hpp>
#include <stdio.h>

/* First consider the following C implementation of Fibonacci. */

typedef struct linear_fib_state { int a0, a1, n; } linear_fib_state;

static int linear_fib_c( linear_fib_state p )
{
  return p.n;
}

static linear_fib_state linear_fib_f( linear_fib_state p )
{
  linear_fib_state r = { p.a1, p.a0 + p.a1, p.n - 1 };
  return r;
}

static int linear_fib( int n )
{ 
  linear_fib_state p = { 0, 1, n };

  while ( linear_fib_c(p) ) { p = linear_fib_f(p); }

  return p.a0;
}

/* Then consider the following preprocessor implementation of Fibonacci. */

#define LINEAR_FIB(N)\
  LINEAR_FIB_D(0,N)
/* Since the macro is implemented using BOOST_PP_WHILE, the actual
 * implementation takes a depth as a parameter so that it can be called
 * inside a BOOST_PP_WHILE. The above easy-to-use version simply uses 0
 * as the depth and can not be called inside a BOOST_PP_WHILE.
 */

#define LINEAR_FIB_D(D,N)\
  BOOST_PP_TUPLE_ELEM(3,0,BOOST_PP_WHILE##D(LINEAR_FIB_C,LINEAR_FIB_F,(0,1,N)))
/*                    ^^^               ^^^           ^^           ^^ ^^^^^^^
 *                    #1                #2            #3           #3 #1
 *
 * #1) The state is a 3-tuple. After the iteration is finished, the first
 * element of the tuple is the result.
 *
 * #2) The WHILE primitive is "invoked" directly. BOOST_PP_WHILE(D,...)
 * can't be used because it would not be expanded by the C++ preprocessor.
 *
 * #3) ???_C is the condition and ???_F is the iteration macro.
 */

#define LINEAR_FIB_C(D,P)\
  /* p.n */ BOOST_PP_TUPLE_ELEM(3,2,P)

#define LINEAR_FIB_F(D,P)\
  (/* p.a1 */     BOOST_PP_TUPLE_ELEM(3,1,P)\
  ,/* p.a0+p.a1*/ BOOST_PP_ADD_D(D,BOOST_PP_TUPLE_ELEM(3,0,P),BOOST_PP_TUPLE_ELEM(3,1,P))\
                  /*          ^^ ^ \
                   * BOOST_PP_ADD() uses BOOST_PP_WHILE(). Therefore we must\
                   * pass the recursion depth explicitly to BOOST_PP_ADD_D().\
                   */\
  ,/* p.n - 1 */  BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(3,2,P))\
  )

int main()
{
  printf("linear_fib(10) = %d\n", linear_fib(10));
  printf("LINEAR_FIB(10) = %d\n", LINEAR_FIB(10));

  return 0;
}
