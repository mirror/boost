#ifndef BOOST_PREPROCESSOR_ENUM_SHIFTED_HPP
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_HPP

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

<a href="../../../../boost/preprocessor/enum_shifted.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/inc.hpp>

//! Generates a comma separated shifted list.
/*!
In other words, expands to the sequence:

<PRE>\verbatim
  F(1,P), F(2,P), ..., F(N-1,P)
\endverbatim</PRE>

NOTE: The implementation uses BOOST_PP_REPEAT().
*/
#define BOOST_PP_ENUM_SHIFTED(N,F,P) BOOST_PP_ENUM(BOOST_PP_DEC(N),BOOST_PP_ENUM_SHIFTED_F,(F,P))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_ENUM_SHIFTED_F(I,FP) BOOST_PP_TUPLE2_ELEM0 FP(BOOST_PP_INC(I),BOOST_PP_TUPLE2_ELEM1 FP)
#endif
#endif
