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

/* This is a trivial example of using BOOST_PP_WHILE() that simply
 * counts down from N to 0 ultimately expanding to a 0.
 */

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/while.hpp>

#define COUNT_DOWN(N) BOOST_PP_WHILE(COUNT_DOWN_C,COUNT_DOWN_F,N)
/* Above is the macro we are implementing using BOOST_PP_WHILE(). */

#define COUNT_DOWN_C(D,N) N
/* Above is the condition. It expands to the current N. */

#define COUNT_DOWN_F(D,N) BOOST_PP_DEC(N)
/* Above is the iteration macro. It decrements N. */

enum { x = COUNT_DOWN(50) };
/* The above expands to 0. */
