
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/arithmetic_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

NESTED_DECL(is_void)
NESTED_DECL(is_integral)
NESTED_DECL(is_float)
NESTED_DECL(is_arithmetic)
NESTED_DECL(is_fundamental)

int main(int argc, char* argv[])
{
   NESTED_TEST(is_void, void)
   NESTED_TEST(is_void, int)
   NESTED_TEST(is_integral, int)
   NESTED_TEST(is_integral, float)
   NESTED_TEST(is_float, void)
   NESTED_TEST(is_float, double)
   NESTED_TEST(is_arithmetic, void)
   NESTED_TEST(is_arithmetic, int)
   NESTED_TEST(is_fundamental, UDT)
   NESTED_TEST(is_fundamental, int)

   value_test(true, boost::is_void<void>::value)
   value_test(true, boost::is_void<const void>::value)
   value_test(true, boost::is_void<volatile void>::value)
   value_test(true, boost::is_void<const volatile void>::value)
   value_test(false, boost::is_void<int>::value)

   value_test(false, boost::is_integral<UDT>::value)
   value_test(false, boost::is_integral<void>::value)
   value_test(true, boost::is_integral<bool>::value)
   value_test(true, boost::is_integral<char>::value)
   value_test(true, boost::is_integral<signed char>::value)
   value_test(true, boost::is_integral<unsigned char>::value)
   value_test(true, boost::is_integral<wchar_t>::value)
   value_test(true, boost::is_integral<short>::value)
   value_test(true, boost::is_integral<unsigned short>::value)
   value_test(true, boost::is_integral<int>::value)
   value_test(true, boost::is_integral<unsigned int>::value)
   value_test(true, boost::is_integral<long>::value)
   value_test(true, boost::is_integral<unsigned long>::value)
   value_test(false, boost::is_integral<float>::value)
   value_test(false, boost::is_integral<double>::value)
   value_test(false, boost::is_integral<long double>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_integral<long long>::value)
   value_test(true, boost::is_integral<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_integral<__int64>::value)
   value_test(true, boost::is_integral<unsigned __int64>::value)
   #endif
   //const qualified ints:
   value_test(true, boost::is_integral<const bool>::value)
   value_test(true, boost::is_integral<const char>::value)
   value_test(true, boost::is_integral<const signed char>::value)
   value_test(true, boost::is_integral<const unsigned char>::value)
   value_test(true, boost::is_integral<const wchar_t>::value)
   value_test(true, boost::is_integral<const short>::value)
   value_test(true, boost::is_integral<const unsigned short>::value)
   value_test(true, boost::is_integral<const int>::value)
   value_test(true, boost::is_integral<const unsigned int>::value)
   value_test(true, boost::is_integral<const long>::value)
   value_test(true, boost::is_integral<const unsigned long>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_integral<const long long>::value)
   value_test(true, boost::is_integral<const unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_integral<const __int64>::value)
   value_test(true, boost::is_integral<const unsigned __int64>::value)
   #endif
   // volatile qualified ints:
   value_test(true, boost::is_integral<volatile bool>::value)
   value_test(true, boost::is_integral<volatile char>::value)
   value_test(true, boost::is_integral<volatile signed char>::value)
   value_test(true, boost::is_integral<volatile unsigned char>::value)
   value_test(true, boost::is_integral<volatile wchar_t>::value)
   value_test(true, boost::is_integral<volatile short>::value)
   value_test(true, boost::is_integral<volatile unsigned short>::value)
   value_test(true, boost::is_integral<volatile int>::value)
   value_test(true, boost::is_integral<volatile unsigned int>::value)
   value_test(true, boost::is_integral<volatile long>::value)
   value_test(true, boost::is_integral<volatile unsigned long>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_integral<volatile long long>::value)
   value_test(true, boost::is_integral<volatile unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_integral<volatile __int64>::value)
   value_test(true, boost::is_integral<volatile unsigned __int64>::value)
   #endif
   //const qualified ints:
   value_test(true, boost::is_integral<const volatile bool>::value)
   value_test(true, boost::is_integral<const volatile char>::value)
   value_test(true, boost::is_integral<const volatile signed char>::value)
   value_test(true, boost::is_integral<const volatile unsigned char>::value)
   value_test(true, boost::is_integral<const volatile wchar_t>::value)
   value_test(true, boost::is_integral<const volatile short>::value)
   value_test(true, boost::is_integral<const volatile unsigned short>::value)
   value_test(true, boost::is_integral<const volatile int>::value)
   value_test(true, boost::is_integral<const volatile unsigned int>::value)
   value_test(true, boost::is_integral<const volatile long>::value)
   value_test(true, boost::is_integral<const volatile unsigned long>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_integral<const volatile long long>::value)
   value_test(true, boost::is_integral<const volatile unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_integral<const volatile __int64>::value)
   value_test(true, boost::is_integral<const volatile unsigned __int64>::value)
   #endif
   value_test(true, boost::is_float<const volatile float>::value)
   value_test(true, boost::is_float<const volatile double>::value)
   value_test(true, boost::is_float<const volatile long double>::value)
   value_test(true, boost::is_float<volatile float>::value)
   value_test(true, boost::is_float<volatile double>::value)
   value_test(true, boost::is_float<volatile long double>::value)
   value_test(true, boost::is_float<const float>::value)
   value_test(true, boost::is_float<const double>::value)
   value_test(true, boost::is_float<const long double>::value)
   value_test(true, boost::is_float<float>::value)
   value_test(true, boost::is_float<double>::value)
   value_test(true, boost::is_float<long double>::value)
   value_test(false, boost::is_float<int>::value)
   value_test(false, boost::is_float<void>::value)
   value_test(false, boost::is_float<UDT>::value)


   value_test(false, boost::is_arithmetic<UDT>::value)
   value_test(false, boost::is_arithmetic<void>::value)
   value_test(true, boost::is_arithmetic<bool>::value)
   value_test(true, boost::is_arithmetic<char>::value)
   value_test(true, boost::is_arithmetic<signed char>::value)
   value_test(true, boost::is_arithmetic<unsigned char>::value)
   value_test(true, boost::is_arithmetic<wchar_t>::value)
   value_test(true, boost::is_arithmetic<short>::value)
   value_test(true, boost::is_arithmetic<unsigned short>::value)
   value_test(true, boost::is_arithmetic<int>::value)
   value_test(true, boost::is_arithmetic<unsigned int>::value)
   value_test(true, boost::is_arithmetic<long>::value)
   value_test(true, boost::is_arithmetic<unsigned long>::value)
   value_test(true, boost::is_arithmetic<float>::value)
   value_test(true, boost::is_arithmetic<double>::value)
   value_test(true, boost::is_arithmetic<long double>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_arithmetic<long long>::value)
   value_test(true, boost::is_arithmetic<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_arithmetic<__int64>::value)
   value_test(true, boost::is_arithmetic<unsigned __int64>::value)
   #endif

   value_test(false, boost::is_fundamental<UDT>::value)
   value_test(true, boost::is_fundamental<void>::value)
   value_test(true, boost::is_fundamental<bool>::value)
   value_test(true, boost::is_fundamental<char>::value)
   value_test(true, boost::is_fundamental<signed char>::value)
   value_test(true, boost::is_fundamental<unsigned char>::value)
   value_test(true, boost::is_fundamental<wchar_t>::value)
   value_test(true, boost::is_fundamental<short>::value)
   value_test(true, boost::is_fundamental<unsigned short>::value)
   value_test(true, boost::is_fundamental<int>::value)
   value_test(true, boost::is_fundamental<unsigned int>::value)
   value_test(true, boost::is_fundamental<long>::value)
   value_test(true, boost::is_fundamental<unsigned long>::value)
   value_test(true, boost::is_fundamental<float>::value)
   value_test(true, boost::is_fundamental<double>::value)
   value_test(true, boost::is_fundamental<long double>::value)
   #ifdef ULLONG_MAX
   value_test(true, boost::is_fundamental<long long>::value)
   value_test(true, boost::is_fundamental<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, boost::is_fundamental<__int64>::value)
   value_test(true, boost::is_fundamental<unsigned __int64>::value)
   #endif

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
unsigned int expected_failures = 0;

