#ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#define BOOST_PREPROCESSOR_LOGICAL_OR_HPP

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

<a href="../../../../boost/preprocessor/logical/or.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/logical/not.hpp>

//! Expands to the logical OR of the operands.
/*!
For example, BOOST_PP_OR(0,2) expands to 1 (a single token).
*/
#define BOOST_PP_OR(X,Y) BOOST_PP_NOT(BOOST_PP_NOR(X,Y))

//! Obsolete. Use BOOST_PP_OR().
#define BOOST_PREPROCESSOR_OR(X,Y) BOOST_PP_OR(X,Y)
#endif
