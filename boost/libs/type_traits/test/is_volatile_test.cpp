
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_volatile)

TT_TEST_BEGIN(is_volatile)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<void>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<volatile void>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<test_abc1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<volatile test_abc1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<volatile int>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<volatile UDT>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_volatile<volatile const UDT>::value, true);

TT_TEST_END






