
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_reference)

TT_TEST_BEGIN(is_reference)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<int&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<const int&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<volatile int &>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<const volatile int &>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<r_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<cr_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<UDT&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<const UDT&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<volatile UDT&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<const volatile UDT&>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<int (&)(int)>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<int (&)[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<bool>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<void>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_reference<test_abc1>::value, false);

TT_TEST_END






