#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT_HPP
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT_HPP

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

<a href="../../../../boost/preprocessor/enum_params_with_a_default.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_CAT_HPP
#  include <boost/preprocessor/cat.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMMA_IF_HPP
#  include <boost/preprocessor/comma_if.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_REPEAT_HPP
#  include <boost/preprocessor/repeat.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_TUPLE_HPP
#  include <boost/preprocessor/tuple.hpp>
#endif

//! Generates a comma separated list of parameters with a default.
/*!
In other words, expands to the sequence:

<PRE>\verbatim
  P##0 = D, P##1 = D, ..., P##N-1 = D
\endverbatim</PRE>

NOTE: The implementation uses BOOST_PREPROCESSOR_REPEAT().
*/
#define BOOST_PREPROCESSOR_ENUM_PARAMS_WITH_A_DEFAULT(N,P,D) BOOST_PREPROCESSOR_REPEAT(N,BOOST_PREPROCESSOR_PARAM_WITH_A_DEFAULT,(P,D))

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_PARAM_WITH_A_DEFAULT(I,PD) BOOST_PREPROCESSOR_COMMA_IF(I) BOOST_PREPROCESSOR_CAT(BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,PD),I)=BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,PD)
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
