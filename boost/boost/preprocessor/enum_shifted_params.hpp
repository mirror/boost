#ifndef BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP

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

<a href="../../../../boost/preprocessor/enum_shifted_params.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_CAT_HPP
#  include <boost/preprocessor/cat.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMMA_IF_HPP
#  include <boost/preprocessor/comma_if.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_DEC_HPP
#  include <boost/preprocessor/dec.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_INC_HPP
#  include <boost/preprocessor/inc.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_REPEAT_HPP
#  include <boost/preprocessor/repeat.hpp>
#endif

//! Generates a comma separated list of shifted actual parameters.
/*!
In other words, expands to the sequence:

<PRE>\verbatim
  P##1, P##2, ..., P##N-1
\endverbatim</PRE>

NOTE: The implementation uses BOOST_PREPROCESSOR_REPEAT().

RATIONALE:
- This macro facilitates a typical usage of the library. Shifted parameter
lists are common in template metaprograms. 
- ENUM_SHIFTED_PARAMS must be tested so that the shifted range is shown to be
correct.
*/
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS(N,P) BOOST_PREPROCESSOR_REPEAT(BOOST_PREPROCESSOR_DEC(N),BOOST_PREPROCESSOR_SHIFTED_PARAM,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_SHIFTED_PARAM(I,P) BOOST_PREPROCESSOR_COMMA_IF(I) BOOST_PREPROCESSOR_CAT(P,BOOST_PREPROCESSOR_INC(I))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
