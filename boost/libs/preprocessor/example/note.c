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

/* This example shows how BOOST_PP_STRINGIZE() can be used to allow macro
 * expansion before stringization.
 */

#include <boost/preprocessor/stringize.hpp>

#define NOTE(STR)\
  message(__FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) ") : " STR)

#pragma NOTE("Hello, World!")
