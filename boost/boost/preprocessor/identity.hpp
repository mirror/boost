#ifndef BOOST_PREPROCESSOR_IDENTITY_HPP
#define BOOST_PREPROCESSOR_IDENTITY_HPP

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

#include <boost/preprocessor/empty.hpp>

/** <P>Expands to X once invoked.</P>

<P>Designed to be used with BOOST_PP_IF(), when one of the clauses need to be
invoked.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_IDENTITY(X)<B>()</B>
</PRE>

<P>expands to:</P>

<PRE>
  X
</PRE>

<P>NOTE: If BOOST_PP_IDENTITY() is not invoked, the expansion will not be
usable.</P>
*/
#define BOOST_PP_IDENTITY(X) X BOOST_PP_EMPTY

/** <P>Obsolete. Use BOOST_PP_IDENTITY().</P> */
#define BOOST_PREPROCESSOR_IDENTITY(X) BOOST_PP_IDENTITY(X)
#endif
