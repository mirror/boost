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

/* This example shows how BOOST_PP_CAT() can be used to allow macro
 * expansion before token concatenation.
 */

#include <boost/preprocessor/cat.hpp>

/* Use of BOOST_PP_CAT() below allows macro expansion of __LINE__. */
#define STATIC_ASSERT(EXPR)\
  typedef char BOOST_PP_CAT(static_assert_,__LINE__)[ (EXPR) ? 1 : -1 ]

STATIC_ASSERT(sizeof(int) <= sizeof(long));

/* This static assert is broken. The __LINE__ is not expanded as desired. */
#define BROKEN_STATIC_ASSERT(EXPR)\
  typedef char static_assert_##__LINE__[ (EXPR) ? 1 : -1 ]

BROKEN_STATIC_ASSERT(sizeof(int) <= sizeof(long));
