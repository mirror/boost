#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS_HPP
#define BOOST_PREPROCESSOR_ENUM_PARAMS_HPP

//  Copyright (C) 2001
//  Housemarque, Inc.
//  http://www.housemarque.com
//  
//  Permission to copy, use, modify, sell and distribute this software is
//  granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/enum_params.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_COMMA_IF_HPP
#  include <boost/preprocessor/comma_if.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_REPEAT_HPP
#  include <boost/preprocessor/repeat.hpp>
#endif

//! Generates a comma separated list of parameters.
/*!
In other words, expands to the sequence:

<PRE>\verbatim
  P##0, P##1, ..., P##N-1
\endverbatim</PRE>

NOTE: The implementation uses BOOST_PREPROCESSOR_REPEAT().
*/
#define BOOST_PREPROCESSOR_ENUM_PARAMS(N,P) BOOST_PREPROCESSOR_REPEAT(N,BOOST_PREPROCESSOR_PARAM,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_PARAM(I,P) BOOST_PREPROCESSOR_COMMA_IF(I) P##I
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
