
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_void)

TT_TEST_BEGIN(is_void)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<void>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<void const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<void volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<void const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<void*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::boost::is_void<int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::boost::is_void<test_abc1>::value, false);

TT_TEST_END







