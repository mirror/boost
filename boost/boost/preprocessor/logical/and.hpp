#ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#define BOOST_PREPROCESSOR_LOGICAL_AND_HPP

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

<a href="../../../../boost/preprocessor/logical/and.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#  include <boost/preprocessor/logical/nor.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#  include <boost/preprocessor/logical/not.hpp>
#endif

//! Expands to the logical AND of the operands.
#define BOOST_PREPROCESSOR_AND(X,Y) BOOST_PREPROCESSOR_NOR(BOOST_PREPROCESSOR_NOT(X),BOOST_PREPROCESSOR_NOT(Y))
#endif
