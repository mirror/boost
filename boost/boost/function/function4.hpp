// Boost.Function library

// Copyright (C) 2001 Doug Gregor (gregod@cs.rpi.edu)
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

#ifndef BOOST_FUNCTION4_HPP
#define BOOST_FUNCTION4_HPP

#include <boost/function/function_base.hpp>

#define BOOST_FUNCTION_NUM_ARGS 4
#define BOOST_FUNCTION_COMMA ,
#define BOOST_FUNCTION_TEMPLATE_PARMS typename T1, typename T2, typename T3, typename T4
#define BOOST_FUNCTION_TEMPLATE_ARGS T1, T2, T3, T4
#define BOOST_FUNCTION_OTHER_TEMPLATE_PARMS typename OtherT1, typename OtherT2, typename OtherT3, typename OtherT4
#define BOOST_FUNCTION_OTHER_TEMPLATE_ARGS OtherT1, OtherT2, OtherT3, OtherT4
#define BOOST_FUNCTION_PARMS T1 a1, T2 a2, T3 a3, T4 a4
#define BOOST_FUNCTION_ARGS a1, a2, a3, a4
#define BOOST_FUNCTION_FUNCTION function4
#define BOOST_FUNCTION_BASE function4_base
#define BOOST_FUNCTION_INVOKER_BASE invoker_base4
#define BOOST_FUNCTION_FUNCTION_INVOKER function_invoker4
#define BOOST_FUNCTION_VOID_FUNCTION_INVOKER void_function_invoker4
#define BOOST_FUNCTION_FUNCTION_OBJ_INVOKER function_obj_invoker4
#define BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER void_function_obj_invoker4
#define BOOST_FUNCTION_GET_FUNCTION_INVOKER get_function_invoker4
#define BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER get_function_obj_invoker4

#include <boost/function/function_template.hpp>

#undef BOOST_FUNCTION_NUM_ARGS
#undef BOOST_FUNCTION_COMMA
#undef BOOST_FUNCTION_TEMPLATE_PARMS
#undef BOOST_FUNCTION_TEMPLATE_ARGS
#undef BOOST_FUNCTION_OTHER_TEMPLATE_PARMS
#undef BOOST_FUNCTION_OTHER_TEMPLATE_ARGS
#undef BOOST_FUNCTION_PARMS
#undef BOOST_FUNCTION_ARGS
#undef BOOST_FUNCTION_FUNCTION
#undef BOOST_FUNCTION_BASE
#undef BOOST_FUNCTION_INVOKER_BASE
#undef BOOST_FUNCTION_FUNCTION_INVOKER
#undef BOOST_FUNCTION_VOID_FUNCTION_INVOKER
#undef BOOST_FUNCTION_FUNCTION_OBJ_INVOKER
#undef BOOST_FUNCTION_VOID_FUNCTION_OBJ_INVOKER
#undef BOOST_FUNCTION_GET_FUNCTION_INVOKER
#undef BOOST_FUNCTION_GET_FUNCTION_OBJ_INVOKER

#endif // BOOST_FUNCTION4_HPP
