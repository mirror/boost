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

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_shifted_params.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/repeat_2nd.hpp>

/* *** */

/* RATIONALE:
 * - BOOST_PP_REPEAT, BOOST_PP_REPEAT_2ND, ... must work
 * together.
 * - BOOST_PP_REPEAT is already tested with
 * BOOST_PP_ENUM_PARAMS.
 * - The tested repeat count should exceed imaginable usage.
 * - Testing the generation of is_function_helper()s upto 40 arguments should
 * be sufficient in this case. Many compilers may fail the repetition tests
 * (at least with higher counts). However, the primary purpose of the
 * repetition primitives is to enable configurability with reasonable
 * defaults, and not necessarily "the most impressive repetition".
 * - ENUM_SHIFTED_PARAMS must be tested so that the shifted range is shown to
 * be correct.
 */

#ifndef IS_FUNCTION_HELPER_TEST_MAX
#define IS_FUNCTION_HELPER_TEST_MAX 40
#endif

typedef char yes_type;

#define IS_FUNCTION_HELPER(I,A)\
  template\
  <BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(I),class P)>\
  yes_type is_function_helper(\
    P0 (*)(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(I),P)));

BOOST_PP_REPEAT_2ND(BOOST_PP_INC(IS_FUNCTION_HELPER_TEST_MAX),IS_FUNCTION_HELPER,A)

#undef IS_FUNCTION_HELPER
