// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_params_with_a_default.hpp>
#include <boost/preprocessor/enum_params_with_defaults.hpp>

// ***

// RATIONALE:
// - All forms of ENUM_PARAMS must be tested with 0 and n, where n is
// sufficiently large to exceed imaginable usage like. 50 should be
// suffient in this case. 

#ifndef ENUM_PARAMS_TEST_MAX
#define ENUM_PARAMS_TEST_MAX 50
#endif

#define CONSTANT(I,A) const A##I = I;
BOOST_PP_REPEAT(ENUM_PARAMS_TEST_MAX, CONSTANT, int default_param_)
#undef CONSTANT

#define TEST_ENUM_PARAMS(N)\
  void BOOST_PP_CAT(test_enum_params,N)(\
    BOOST_PP_ENUM_PARAMS(N, double x));\
  void BOOST_PP_CAT(test_enum_params_with_a_default,N)(\
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(N, double x, 0));\
  void BOOST_PP_CAT(test_enum_params_with_defaults,N)(\
    BOOST_PP_ENUM_PARAMS_WITH_DEFAULTS(N, double x, default_param_));

TEST_ENUM_PARAMS(0)
TEST_ENUM_PARAMS(ENUM_PARAMS_TEST_MAX)

#undef TEST_ENUM_PARAMS
