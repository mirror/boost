// Boost.Function library

// Copyright (C) 2001, 2002 Doug Gregor (gregod@cs.rpi.edu)
//
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.
 
// For more information, see http://www.boost.org
 
// William Kempf, Jesse Jones and Karl Nelson were all very helpful in the
// design of this library.

#include <boost/preprocessor/iterate.hpp>

#ifndef BOOST_FUNCTION_MAX_ARGS
#  define BOOST_FUNCTION_MAX_ARGS 10
#endif // BOOST_FUNCTION_MAX_ARGS

// Include the prologue here so that the use of file-level iteration
// in anything that may be included by function_template.hpp doesn't break
#include <boost/function/detail/prologue.hpp>

// What is the '3' for?
#define BOOST_PP_ITERATION_PARAMS_1 (3,(0,BOOST_FUNCTION_MAX_ARGS,<boost/function/detail/function_iterate.hpp>))
#include BOOST_PP_ITERATE()

