
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_polymorphic)

TT_TEST_BEGIN(is_polymorphic)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<const int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<volatile int>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<int*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<int* const>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<int[2]>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<mf4>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<f1>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<enum_UDT>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT const>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT volatile>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<empty_UDT>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT*>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT[2]>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<UDT&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<void>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<VB>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<VD>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<test_abc1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<test_abc2>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<std::iostream>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<std::ios_base>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<std::basic_streambuf<char> >::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<std::basic_ios<char> >::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_polymorphic<std::basic_istream<char> >::value, true);

TT_TEST_END








