#ifndef BOOST_PREPROCESSOR_ASSERT_MSG_HPP
#define BOOST_PREPROCESSOR_ASSERT_MSG_HPP

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

/** \file

<a href="../../../../boost/preprocessor/assert_msg.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/if.hpp>

/** Expands to nothing if C != 0 and to MSG if C == 0. */
#define BOOST_PP_ASSERT_MSG(C,MSG) BOOST_PP_IF(C,BOOST_PP_EMPTY,MSG BOOST_PP_EMPTY)()

/** Obsolete. Use BOOST_PP_ASSERT_MSG(). */
#define BOOST_PREPROCESSOR_ASSERT_MSG(C,MSG) BOOST_PP_ASSERT_MSG(C,MSG)
#endif
