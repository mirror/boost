#ifndef BOOST_PREPROCESSOR_LIMITS_HPP
#define BOOST_PREPROCESSOR_LIMITS_HPP

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

<a href="../../../../boost/preprocessor/limits.hpp">Click here to see the header.</a>
*/

//! Expands to the number of dimensions of repeat supported by the library.
/*!
The repeat macros are named BOOST_PP_REPEAT(), BOOST_PP_REPEAT_2ND(),
BOOST_PP_REPEAT_3RD(), ...
*/
#define BOOST_PP_LIMIT_DIM 3

//! Expands to the maximum straight numeric literal supported by the library.
/*!
This is also the limit of the repetition primitives (BOOST_PP_ENUM family and
BOOST_PP_REPEAT family).

NOTES:
- Only decimal integer literals in the range [0,BOOST_PP_LIMIT_MAG]
are supported.
- All arithmetic operations (ADD,SUB,MUL,DIV) use saturation arithmetic.
- The maximum repetition count supported by the library may not be reached
due to compiler limitations.
*/
#define BOOST_PP_LIMIT_MAG 128

//! Expands to the maximum tuple length supported by the library.
#define BOOST_PP_LIMIT_TUPLE 8

//! Obsolete. Use BOOST_PP_LIMIT_DIM.
#define BOOST_PREPROCESSOR_LIMIT_DIM BOOST_PP_LIMIT_DIM

//! Obsolete. Use BOOST_PP_LIMIT_MAG.
#define BOOST_PREPROCESSOR_LIMIT_MAG BOOST_PP_LIMIT_MAG

//! Obsolete. Use BOOST_PP_LIMIT_TUPLE.
#define BOOST_PREPROCESSOR_LIMIT_TUPLE BOOST_PP_LIMIT_TUPLE
#endif
