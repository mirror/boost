
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_array)

struct convertible_to_pointer
{
    operator char*() const;
};

TT_TEST_BEGIN(is_array)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const int*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const volatile int*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int*const>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const int*volatile>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const volatile int*const>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const int[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<const volatile int[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int[2][3]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<UDT[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<int(&)[2]>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<f1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<void>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_array<convertible_to_pointer>::value, false);

TT_TEST_END






