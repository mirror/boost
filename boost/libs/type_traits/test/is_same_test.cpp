
#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_COMPARE(is_same)

TT_TEST_BEGIN(is_same)

BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int, int>::value), true);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int, const int>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int, int&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<const int, int&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int, const int&>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int*, const int*>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int*, int*const>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int, int[2]>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int*, int[2]>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_same<int[4], int[2]>::value), false);

TT_TEST_END






