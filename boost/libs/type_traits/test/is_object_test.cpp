
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_object)

TT_TEST_BEGIN(is_object)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<int>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<UDT>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_object<void>::value, false);


TT_TEST_END






