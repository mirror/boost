
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_compound)

TT_TEST_BEGIN(is_compound)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<UDT>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<void*>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<void>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<int>::value, false);
//#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<test_abc1>::value, true);
//#endif

TT_TEST_END






