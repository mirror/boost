#ifndef BOOST_PREPROCESSOR_IDENTITY_HPP
#define BOOST_PREPROCESSOR_IDENTITY_HPP

// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/identity.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_EMPTY_HPP
#  include <boost/preprocessor/empty.hpp>
#endif

//! Expands to X once invoked.
/*!
Designed to be used with BOOST_PREPROCESSOR_IF(), when one of the clauses need to be invoked.

Example:

<PRE>\verbatim
  BOOST_PREPROCESSOR_IDENTITY(X)()
  //                            ^^ NOTE!
\endverbatim</PRE>

The above expands to:

<PRE>\verbatim
  X
\endverbatim</PRE>

NOTE: If BOOST_PREPROCESSOR_IDENTITY() is not invoked, the expansion will not be usable.
*/
#define BOOST_PREPROCESSOR_IDENTITY(X) X BOOST_PREPROCESSOR_EMPTY
#endif
