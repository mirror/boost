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

/** \file

<a href="../../../../boost/preprocessor/identity.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/empty.hpp>

/** Expands to X once invoked.

Designed to be used with BOOST_PP_IF(), when one of the clauses need to be invoked.

For example,

<PRE>\verbatim
  BOOST_PP_IDENTITY(X)()
  //                  ^^ NOTE!
\endverbatim</PRE>

expands to:

<PRE>\verbatim
  X
\endverbatim</PRE>

NOTE: If BOOST_PP_IDENTITY() is not invoked, the expansion will not be usable.
*/
#define BOOST_PP_IDENTITY(X) X BOOST_PP_EMPTY

/** Obsolete. Use BOOST_PP_IDENTITY(). */
#define BOOST_PREPROCESSOR_IDENTITY(X) BOOST_PP_IDENTITY(X)
#endif
