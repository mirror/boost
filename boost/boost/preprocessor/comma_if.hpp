#ifndef BOOST_PREPROCESSOR_COMMA_IF_HPP
#define BOOST_PREPROCESSOR_COMMA_IF_HPP

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

<a href="../../../../boost/preprocessor/comma_if.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_COMMA_HPP
#  include <boost/preprocessor/comma.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_EMPTY_HPP
#  include <boost/preprocessor/empty.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_IF_HPP
#  include <boost/preprocessor/if.hpp>
#endif

//! Expands to a comma if C != 0 and nothing if C == 0.
#define BOOST_PREPROCESSOR_COMMA_IF(C) BOOST_PREPROCESSOR_IF(C,BOOST_PREPROCESSOR_COMMA,BOOST_PREPROCESSOR_EMPTY)()
#endif
