
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/transform_traits.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"


int main(int argc, char* argv[])
{
   type_test(int, boost::remove_const<const int>::type)
   type_test(volatile int, boost::remove_const<volatile int>::type)
   type_test(volatile int, boost::remove_const<const volatile int>::type)
   type_test(int, boost::remove_const<int>::type)
   type_test(int*, boost::remove_const<int* const>::type)
   type_test(void, boost::remove_const<const void>::type)
   type_test(void, boost::remove_const<void>::type)

   type_test(int, boost::remove_volatile<volatile int>::type)
   type_test(const int, boost::remove_volatile<const int>::type)
   type_test(const int, boost::remove_volatile<const volatile int>::type)
   type_test(int, boost::remove_volatile<int>::type)
   type_test(int*, boost::remove_volatile<int* volatile>::type)
   type_test(void, boost::remove_volatile<volatile void>::type)
   type_test(void, boost::remove_volatile<void>::type)

   type_test(int, boost::remove_cv<volatile int>::type)
   type_test(int, boost::remove_cv<const int>::type)
   type_test(int, boost::remove_cv<const volatile int>::type)
   type_test(int, boost::remove_cv<int>::type)
   type_test(int*, boost::remove_cv<int* volatile>::type)
   type_test(int*, boost::remove_cv<int* const>::type)
   type_test(int*, boost::remove_cv<int* const volatile>::type)
   type_test(const int *, boost::remove_cv<const int * const>::type)
   type_test(void, boost::remove_cv<volatile void>::type)
   type_test(void, boost::remove_cv<void>::type)

   type_test(int, boost::remove_reference<int>::type)
   type_test(const int, boost::remove_reference<const int>::type)
   type_test(int, boost::remove_reference<int&>::type)
   type_test(const int, boost::remove_reference<const int&>::type)
   type_test(volatile int, boost::remove_reference<volatile int&>::type)
   type_test(int, boost::remove_reference<cr_type>::type)
   type_test(void, boost::remove_reference<void>::type)

   type_test(int, boost::remove_bounds<int>::type)
   type_test(int*, boost::remove_bounds<int*>::type)
   type_test(int, boost::remove_bounds<int[3]>::type)
   type_test(void, boost::remove_bounds<void>::type)
   type_test(int[3], boost::remove_bounds<int[2][3]>::type)

   type_test(int, boost::remove_pointer<int>::type)
   type_test(int, boost::remove_pointer<int*>::type)
   type_test(const int, boost::remove_pointer<const int*>::type)
   type_test(int, boost::remove_pointer<int*const>::type)
   type_test(volatile int, boost::remove_pointer<volatile int*const volatile>::type)
   type_test(int[3], boost::remove_pointer<int[3]>::type)
   type_test(int[2][3], boost::remove_pointer<int[2][3]>::type)
   type_test(void, boost::remove_pointer<void>::type)

   type_test(int&, boost::add_reference<int>::type)
   type_test(const int&, boost::add_reference<const int>::type)
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)
   type_test(int&, boost::add_reference<int&>::type)
   type_test(const int&, boost::add_reference<const int&>::type)
#endif

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef __BORLANDC__
unsigned int expected_failures = 4; // cv-qualifiers
#elif defined(__GNUC__)
unsigned int expected_failures = 1; // cv-qualified references
#else
unsigned int expected_failures = 0;
#endif


