
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include "test.hpp"
#include "check_integral_constant.hpp"
#include TYPE_TRAITS(is_pod)

TT_TEST_BEGIN(is_POD)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<bool>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<bool const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<bool volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<bool const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<signed char>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<signed char const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<signed char volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<signed char const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned char>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<char>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned char const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<char const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned char volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<char volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned char const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<char const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned short>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<short>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned short const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<short const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned short volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<short volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned short const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<short const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned int>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned int const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned int volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned int const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long const volatile>::value, true);

#ifdef BOOST_HAS_LONG_LONG

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long long>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long long>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long long const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long long const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long long volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long long volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned long long const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long long const volatile>::value, true);

#endif

#ifdef BOOST_HAS_MS_INT64

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int8>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int8>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int8 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int8 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int8 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int8 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int8 const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int8 const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int16>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int16>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int16 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int16 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int16 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int16 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int16 const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int16 const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int32>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int32>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int32 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int32 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int32 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int32 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int32 const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int32 const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int64>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int64>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int64 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int64 const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int64 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int64 volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<unsigned __int64 const volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<__int64 const volatile>::value, true);

#endif

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<float>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<float const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<float volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<float const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<double>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<double const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<double volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<double const volatile>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long double>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long double const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long double volatile>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<long double const volatile>::value, true);


BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<void*>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int*const>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<f1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<f2>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<f3>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<mf1>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<mf2>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<mf3>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<mp>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<cmf>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<enum_UDT>::value, true);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<const int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int[2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int[3][2]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<int[2][4][5][6][3]>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<UDT>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<empty_UDT>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_POD<void>::value, true);

TT_TEST_END







