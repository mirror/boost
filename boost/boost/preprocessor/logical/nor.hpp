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

#ifndef BOOST_PREPROCESSOR_LOGICAL_BOOL_HPP
#  include <boost/preprocessor/logical/bool.hpp>
#endif

//! Expands to the logical NEITHER OR of the operands. 
#define BOOST_PREPROCESSOR_NOR(X,Y) BOOST_PREPROCESSOR_NOR_BOOL(BOOST_PREPROCESSOR_BOOL(X),BOOST_PREPROCESSOR_BOOL(Y))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_NOR_BOOL(X,Y) BOOST_PREPROCESSOR_NOR_BOOL_DELAY(X,Y)
#define BOOST_PREPROCESSOR_NOR_BOOL_DELAY(X,Y) BOOST_PREPROCESSOR_NOR_BOOL##X##Y
#define BOOST_PREPROCESSOR_NOR_BOOL00 1
#define BOOST_PREPROCESSOR_NOR_BOOL01 0
#define BOOST_PREPROCESSOR_NOR_BOOL10 0
#define BOOST_PREPROCESSOR_NOR_BOOL11 0
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
