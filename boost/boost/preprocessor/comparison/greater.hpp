#ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP
#define BOOST_PREPROCESSOR_COMPARISON_GREATER_HPP

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

<a href="../../../../boost/preprocessor/comparison/greater.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#  include <boost/preprocessor/comparison/less.hpp>
#endif

//! Expands to 1 if X>Y and 0 otherwise.
#define BOOST_PREPROCESSOR_GREATER(X,Y) BOOST_PREPROCESSOR_LESS(Y,X)
#endif
