#ifndef BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

/** \file

<a href="../../../../boost/preprocessor/enum_shifted_params.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum_shifted.hpp>

/** Generates a comma separated list of shifted actual parameters.

In other words, expands to the sequence:

<PRE>\verbatim
  P##1, P##2, ..., P##N-1
\endverbatim</PRE>

NOTE: The implementation uses BOOST_PP_REPEAT().

RATIONALE:
- This macro facilitates a typical usage of the library. Shifted parameter
lists are common in template metaprograms. 
*/
#define BOOST_PP_ENUM_SHIFTED_PARAMS(N,P) BOOST_PP_ENUM_SHIFTED(N,BOOST_PP_ENUM_SHIFTED_PARAMS_F,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_ENUM_SHIFTED_PARAMS_F(I,P) BOOST_PP_CAT(P,I)
#endif

/** Obsolete. Use BOOST_PP_ENUM_SHIFTED_PARAMS(). */
#define BOOST_PREPROCESSOR_ENUM_SHIFTED_PARAMS(N,P) BOOST_PP_ENUM_SHIFTED_PARAMS(N,P)
#endif
