#ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#define BOOST_PREPROCESSOR_LOGICAL_NOR_HPP

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

<a href="../../../../boost/preprocessor/logical/nor.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/logical/bool.hpp>

//! Expands to the logical NEITHER OR of the operands.
/*!
For example, BOOST_PP_NOR(0,5) expands to 0 (a single token).
*/
#define BOOST_PP_NOR(X,Y) BOOST_PP_NOR_BOOL(BOOST_PP_BOOL(X),BOOST_PP_BOOL(Y))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_NOR_BOOL(X,Y) BOOST_PP_NOR_BOOL_DELAY(X,Y)
#define BOOST_PP_NOR_BOOL_DELAY(X,Y) BOOST_PP_NOR_BOOL##X##Y
#define BOOST_PP_NOR_BOOL00 1
#define BOOST_PP_NOR_BOOL01 0
#define BOOST_PP_NOR_BOOL10 0
#define BOOST_PP_NOR_BOOL11 0
#endif

//! Obsolete. Use BOOST_PP_NOR().
#define BOOST_PREPROCESSOR_NOR(X,Y) BOOST_PP_NOR(X,Y)
#endif
