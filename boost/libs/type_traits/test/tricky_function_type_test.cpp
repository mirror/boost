
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

typedef void foo0_t();
typedef void foo1_t(int);
typedef void foo2_t(int&, double);
typedef void foo3_t(int&, bool, int, int);
typedef void foo4_t(int, bool, int*, int[], int, int, int, int, int);

TT_TEST_BEGIN(is_function)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<const int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<int (&)(int)>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<foo0_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<foo1_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<foo2_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<foo3_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pointer<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_void<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_integral<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_float<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_arithmetic<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_fundamental<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_member_pointer<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_union<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_empty<foo4_t>::value, false);


TT_TEST_END






