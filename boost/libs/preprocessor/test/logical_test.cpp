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

#include <boost/preprocessor/logical.hpp>

#include <libs/preprocessor/test/test.hpp>

/* *** */

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_NOT(MACRO MACRO_ARGS(0)) == 1 TEST_E
#endif
TEST_B BOOST_PP_NOT(1) == 0 TEST_E

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_AND(0,MACRO MACRO_ARGS(0)) == 0 TEST_E
#endif
TEST_B BOOST_PP_AND(0,1) == 0 TEST_E
TEST_B BOOST_PP_AND(1,0) == 0 TEST_E
TEST_B BOOST_PP_AND(1,1) == 1 TEST_E

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_OR(0,MACRO MACRO_ARGS(0)) == 0 TEST_E
#endif
TEST_B BOOST_PP_OR(0,1) == 1 TEST_E
TEST_B BOOST_PP_OR(1,0) == 1 TEST_E
TEST_B BOOST_PP_OR(1,1) == 1 TEST_E

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_XOR(0,MACRO MACRO_ARGS(0)) == 0 TEST_E
#endif
TEST_B BOOST_PP_XOR(0,1) == 1 TEST_E
TEST_B BOOST_PP_XOR(1,0) == 1 TEST_E
TEST_B BOOST_PP_XOR(1,1) == 0 TEST_E

#if !(!defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__))
TEST_B BOOST_PP_NOR(0,MACRO MACRO_ARGS(0)) == 1 TEST_E
#endif
TEST_B BOOST_PP_NOR(0,1) == 0 TEST_E
TEST_B BOOST_PP_NOR(1,0) == 0 TEST_E
TEST_B BOOST_PP_NOR(1,1) == 0 TEST_E
