
//  (C) Copyright John Maddock 2000. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"
#include <boost/type_traits.hpp>

TT_TEST_BEGIN(tricky_incomplete_type_test)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_assign<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_constructor<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_nothrow_copy<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<incomplete_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<incomplete_type>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<incomplete_type>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<incomplete_type>::value, false);

TT_TEST_END


