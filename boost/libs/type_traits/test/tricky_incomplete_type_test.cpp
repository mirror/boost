
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_function)
#include TYPE_TRAITS(is_pointer)
#include TYPE_TRAITS(is_void)
#include TYPE_TRAITS(is_integral)
#include TYPE_TRAITS(is_float)
#include TYPE_TRAITS(is_arithmetic)
#include TYPE_TRAITS(is_fundamental)
#include TYPE_TRAITS(is_member_pointer)
#include TYPE_TRAITS(is_enum)
#include TYPE_TRAITS(is_object)
#include TYPE_TRAITS(is_scalar)
#include TYPE_TRAITS(is_class)
#include TYPE_TRAITS(is_POD)
#include TYPE_TRAITS(has_trivial_constructor)
#include TYPE_TRAITS(has_trivial_copy)
#include TYPE_TRAITS(has_trivial_assign)
#include TYPE_TRAITS(has_trivial_destructor)
#include TYPE_TRAITS(is_empty)
#include TYPE_TRAITS(is_compound)

TT_TEST_BEGIN(incomplete_type_tricky_tests)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<incomplete_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<incomplete_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<incomplete_type>::value, false);

// this one is only partly correct:
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<incomplete_type>::value, true);

TT_TEST_END







