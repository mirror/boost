
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
#include TYPE_TRAITS(has_nothrow_constructor)
#include TYPE_TRAITS(has_nothrow_copy)
#include TYPE_TRAITS(has_nothrow_assign)
#include TYPE_TRAITS(has_trivial_destructor)
#include TYPE_TRAITS(is_empty)
#include TYPE_TRAITS(is_compound)

TT_TEST_BEGIN(abstract_type_tricky_tests)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<test_abc1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<test_abc1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<test_abc1 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<test_abc1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_assign<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_constructor<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_copy<test_abc1>::value, false);

TT_TEST_END






