#ifndef BOOST_PREPROCESSOR_MAX_HPP
#define BOOST_PREPROCESSOR_MAX_HPP

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

<a href="../../../../boost/preprocessor/max.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#  include <boost/preprocessor/comparison/less.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_IF_HPP
#  include <boost/preprocessor/if.hpp>
#endif

//! Expands to the maximum of X and Y.
#define BOOST_PREPROCESSOR_MAX(X,Y) BOOST_PREPROCESSOR_IF(BOOST_PREPROCESSOR_LESS(X,Y),Y,X)
#endif
