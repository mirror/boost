
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/cv_traits.hpp>
#include <boost/utility.hpp>
#include <boost/test/cpp_main.cpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

NESTED_DECL(is_const)
NESTED_DECL(is_volatile)

int cpp_main(int argc, char* argv[])
{
   NESTED_TEST(is_const, int)
   NESTED_TEST(is_const, const int)
   NESTED_TEST(is_const, volatile int)
   NESTED_TEST(is_volatile, int)
   NESTED_TEST(is_volatile, const int)
   NESTED_TEST(is_volatile, volatile int)

   value_test(false, boost::is_const<void>::value)
   value_test(true, boost::is_const<const void>::value)
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC)
   value_test(false, boost::is_const<test_abc1>::value)
   value_test(true, boost::is_const<const test_abc1>::value)
#endif
   value_test(false, boost::is_const<int>::value)
   value_test(true, boost::is_const<const int>::value)
   value_test(true, boost::is_const<const UDT>::value)
   value_test(true, boost::is_const<const volatile UDT>::value)
   value_test(false, boost::is_const<const int&>::value)
#ifndef __GNUC__
   value_test(false, boost::is_const<cr_type>::value)
#else
   value_fail(false, boost::is_const<cr_type>::value)
#endif


   value_test(false, boost::is_volatile<void>::value)
   value_test(true, boost::is_volatile<volatile void>::value)
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC)
   value_test(false, boost::is_volatile<test_abc1>::value)
   value_test(true, boost::is_volatile<volatile test_abc1>::value)
#endif
   value_test(false, boost::is_volatile<int>::value)
   value_test(true, boost::is_volatile<volatile int>::value)
   value_test(true, boost::is_volatile<volatile UDT>::value)
   value_test(true, boost::is_volatile<volatile UDT>::value)

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef BOOST_MSVC
unsigned int expected_failures = 3;
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x530)
unsigned int expected_failures = 1;
#elif defined(__GNUC__)
unsigned int expected_failures = 1; // cr_type doesn't compile
#else
unsigned int expected_failures = 0;
#endif



