///////////////////////////////////////////////////////////////////////////////
/// \file repeat.hpp
/// Contains macros to ease the generation of repetitious code constructs
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_REPEAT_HPP_EAN_11_24_2008
#define BOOST_PROTO_REPEAT_HPP_EAN_11_24_2008

#include <boost/proto/detail/prefix.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/proto/proto_fwd.hpp> // for BOOST_PROTO_MAX_ARITY
#include <boost/proto/detail/suffix.hpp>

////////////////////////////////////////////
/// INTERNAL ONLY
#define BOOST_PROTO_ref_a_aux(Z, N, DATA)\
  boost::ref(BOOST_PP_CAT(proto_a, N))

/// \brief Generates a sequence like <tt>typename A0, typename A1, ...</tt>
///
#define BOOST_PROTO_typename_A(N)\
  BOOST_PP_ENUM_PARAMS(N, typename proto_A)

/// \brief Generates a sequence like <tt>A0 const &, A1 const &, ...</tt>
///
#define BOOST_PROTO_A_const_ref(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, const & BOOST_PP_INTERCEPT)

/// \brief Generates a sequence like <tt>A0 &, A1 &, ...</tt>
///
#define BOOST_PROTO_A_ref(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, & BOOST_PP_INTERCEPT)

/// \brief Generates a sequence like <tt>A0, A1, ...</tt>
///
#define BOOST_PROTO_A(N)\
  BOOST_PP_ENUM_PARAMS(N, proto_A)

/// \brief Generates a sequence like <tt>A0 const, A1 const, ...</tt>
///
#define BOOST_PROTO_A_const(N)\
  BOOST_PP_ENUM_PARAMS(N, const proto_A)

/// \brief Generates a sequence like <tt>A0 const &a0, A1 const &a0, ...</tt>
///
#define BOOST_PROTO_A_const_ref_a(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, const &proto_a)

/// \brief Generates a sequence like <tt>A0 &a0, A1 &a0, ...</tt>
///
#define BOOST_PROTO_A_ref_a(N)\
  BOOST_PP_ENUM_BINARY_PARAMS(N, proto_A, &proto_a)

/// \brief Generates a sequence like <tt>boost::ref(a0), boost::ref(a1), ...</tt>
///
#define BOOST_PROTO_ref_a(N)\
  BOOST_PP_ENUM(N, BOOST_PROTO_ref_a_aux, ~)

/// \brief Generates a sequence like <tt>a0, a1, ...</tt>
///
#define BOOST_PROTO_a(N)\
  BOOST_PP_ENUM_PARAMS(N, proto_a)

////////////////////////////////////////////
/// INTERNAL ONLY
#define BOOST_PROTO_invoke(Z, N, DATA)\
  BOOST_PP_TUPLE_ELEM(5,0,DATA)(N, BOOST_PP_TUPLE_ELEM(5,1,DATA), BOOST_PP_TUPLE_ELEM(5,2,DATA), BOOST_PP_TUPLE_ELEM(5,3,DATA), BOOST_PP_TUPLE_ELEM(5,4,DATA))

#define BOOST_PROTO_REPEAT_FROM_TO_EX(FROM, TO, MACRO, typename_A, A, A_a, a)\
  BOOST_PP_REPEAT_FROM_TO(FROM, TO, BOOST_PROTO_invoke, (MACRO, typename_A, A, A_a, a))

#define BOOST_PROTO_REPEAT_FROM_TO(FROM, TO, MACRO)\
  BOOST_PROTO_REPEAT_FROM_TO_EX(FROM, TO, MACRO, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)

#define BOOST_PROTO_REPEAT_EX(MACRO, typename_A, A, A_a, a)\
  BOOST_PROTO_REPEAT_FROM_TO_EX(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), MACRO, BOOST_PROTO_typename_A, BOOST_PROTO_A_const_ref, BOOST_PROTO_A_const_ref_a, BOOST_PROTO_ref_a)

#define BOOST_PROTO_REPEAT(MACRO)\
  BOOST_PROTO_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), MACRO)

#define BOOST_PROTO_LOCAL_ITERATE() <boost/proto/detail/local.hpp>

#endif
