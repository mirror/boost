
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/object_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

NESTED_DECL(is_class)
NESTED_DECL(is_object)
NESTED_DECL(is_scalar)
NESTED_DECL(is_compound)
NESTED_DECL(is_POD)

int main(int argc, char* argv[])
{
   NESTED_TEST(is_class, int)
   NESTED_TEST(is_class, UDT)
   NESTED_TEST(is_object, int)
   NESTED_TEST(is_object, void)
   NESTED_TEST(is_object, UDT)
   NESTED_TEST(is_scalar, void)
   NESTED_TEST(is_scalar, int)
   NESTED_TEST(is_compound, int)
   NESTED_TEST(is_compound, UDT)
   NESTED_TEST(is_POD, int)
   NESTED_TEST(is_POD, UDT)

   value_test(false, boost::is_class<int>::value)
   value_test(false, boost::is_class<const int>::value)
   value_test(false, boost::is_class<volatile int>::value)
   value_test(false, boost::is_class<int*>::value)
   value_test(false, boost::is_class<int* const>::value)
   value_test(false, boost::is_class<int[2]>::value)
   value_test(false, boost::is_class<int&>::value)
   value_test(false, boost::is_class<mf4>::value)
   value_test(false, boost::is_class<f1>::value)
   value_test(false, boost::is_class<enum_UDT>::value)
   value_test(true, boost::is_class<UDT>::value)
   value_test(true, boost::is_class<UDT const>::value)
   value_test(true, boost::is_class<UDT volatile>::value)
   value_test(true, boost::is_class<empty_UDT>::value)
   value_test(true, boost::is_class<std::iostream>::value)
   value_test(false, boost::is_class<UDT*>::value)
   value_test(false, boost::is_class<UDT[2]>::value)
   value_test(false, boost::is_class<UDT&>::value)

   value_test(true, boost::is_object<int>::value)
   value_test(true, boost::is_object<UDT>::value)
   value_test(false, boost::is_object<int&>::value)
   value_test(false, boost::is_object<void>::value)

   value_test(true, boost::is_scalar<int>::value)
   value_test(true, boost::is_scalar<void*>::value)
   value_test(false, boost::is_scalar<void>::value)
   value_test(false, boost::is_scalar<UDT>::value)
   value_test(false, boost::is_scalar<int&>::value)

   value_test(true, boost::is_compound<UDT>::value)
   value_test(true, boost::is_compound<void*>::value)
   value_test(false, boost::is_compound<void>::value)
   value_test(false, boost::is_compound<int>::value)

   value_test(true, boost::is_POD<int>::value)
   value_test(true, boost::is_POD<int*>::value)
   value_test(false, boost::is_POD<int&>::value)
   value_test(true, boost::is_POD<int*const>::value)
   value_test(true, boost::is_POD<const int>::value)
   value_test(true, boost::is_POD<volatile int>::value)
   value_test(false, boost::is_POD<const int&>::value)
   value_test(true, boost::is_POD<int[2]>::value)
   value_test(true, boost::is_POD<int[3][2]>::value)
   value_test(true, boost::is_POD<int[2][4][5][6][3]>::value)
   value_test(true, boost::is_POD<f1>::value)
   value_test(true, boost::is_POD<mf2>::value)
   value_test(false, boost::is_POD<UDT>::value)
   value_test(false, boost::is_POD<empty_UDT>::value)
   value_test(true, boost::is_POD<enum_UDT>::value)

   value_test(true, boost::has_trivial_constructor<int>::value)
   value_test(true, boost::has_trivial_constructor<int*>::value)
   value_test(true, boost::has_trivial_constructor<int*const>::value)
   value_test(true, boost::has_trivial_constructor<const int>::value)
   value_test(true, boost::has_trivial_constructor<volatile int>::value)
   value_test(true, boost::has_trivial_constructor<int[2]>::value)
   value_test(true, boost::has_trivial_constructor<int[3][2]>::value)
   value_test(true, boost::has_trivial_constructor<int[2][4][5][6][3]>::value)
   value_test(true, boost::has_trivial_constructor<f1>::value)
   value_test(true, boost::has_trivial_constructor<mf2>::value)
   value_test(false, boost::has_trivial_constructor<UDT>::value)
   value_test(true, boost::has_trivial_constructor<empty_UDT>::value)
   value_test(true, boost::has_trivial_constructor<enum_UDT>::value)

   value_test(true, boost::has_trivial_copy<int>::value)
   value_test(true, boost::has_trivial_copy<int*>::value)
   value_test(true, boost::has_trivial_copy<int*const>::value)
   value_test(true, boost::has_trivial_copy<const int>::value)
   // Steve: was 'false' -- should be 'true' via 3.9p3, 3.9p10
   value_test(false, boost::has_trivial_copy<volatile int>::value)
   value_test(true, boost::has_trivial_copy<int[2]>::value)
   value_test(true, boost::has_trivial_copy<int[3][2]>::value)
   value_test(true, boost::has_trivial_copy<int[2][4][5][6][3]>::value)
   value_test(true, boost::has_trivial_copy<f1>::value)
   value_test(true, boost::has_trivial_copy<mf2>::value)
   value_test(false, boost::has_trivial_copy<UDT>::value)
   value_test(true, boost::has_trivial_copy<empty_UDT>::value)
   value_test(true, boost::has_trivial_copy<enum_UDT>::value)

   value_test(true, boost::has_trivial_assign<int>::value)
   value_test(true, boost::has_trivial_assign<int*>::value)
   value_test(false, boost::has_trivial_assign<int*const>::value)
   value_test(false, boost::has_trivial_assign<const int>::value)
   // Steve: was 'false' -- should be 'true' via 3.9p3, 3.9p10
   value_test(false, boost::has_trivial_assign<volatile int>::value)
   value_test(true, boost::has_trivial_assign<int[2]>::value)
   value_test(true, boost::has_trivial_assign<int[3][2]>::value)
   value_test(true, boost::has_trivial_assign<int[2][4][5][6][3]>::value)
   value_test(true, boost::has_trivial_assign<f1>::value)
   value_test(true, boost::has_trivial_assign<mf2>::value)
   value_test(false, boost::has_trivial_assign<UDT>::value)
   value_test(true, boost::has_trivial_assign<empty_UDT>::value)
   value_test(true, boost::has_trivial_assign<enum_UDT>::value)

   value_test(true, boost::has_trivial_destructor<int>::value)
   value_test(true, boost::has_trivial_destructor<int*>::value)
   value_test(true, boost::has_trivial_destructor<int*const>::value)
   value_test(true, boost::has_trivial_destructor<const int>::value)
   value_test(true, boost::has_trivial_destructor<volatile int>::value)
   value_test(true, boost::has_trivial_destructor<int[2]>::value)
   value_test(true, boost::has_trivial_destructor<int[3][2]>::value)
   value_test(true, boost::has_trivial_destructor<int[2][4][5][6][3]>::value)
   value_test(true, boost::has_trivial_destructor<f1>::value)
   value_test(true, boost::has_trivial_destructor<mf2>::value)
   value_test(false, boost::has_trivial_destructor<UDT>::value)
   value_test(false, boost::has_trivial_destructor<empty_UDT>::value)
   value_test(true, boost::has_trivial_destructor<enum_UDT>::value)

   soft_value_test(false, boost::is_empty<int>::value)
   soft_value_test(false, boost::is_empty<int*>::value)
   soft_value_test(false, boost::is_empty<int&>::value)
#if defined(__MWERKS__)
   // apparent compiler bug causes this to fail to compile:
   value_fail(false, boost::is_empty<int[2]>::value)
#else
   soft_value_test(false, boost::is_empty<int[2]>::value)
#endif
   soft_value_test(false, boost::is_empty<f1>::value)
   soft_value_test(false, boost::is_empty<mf1>::value)
   soft_value_test(false, boost::is_empty<UDT>::value)
   soft_value_test(true, boost::is_empty<empty_UDT>::value)
   soft_value_test(true, boost::is_empty<empty_POD_UDT>::value)
   // this one will not compile on most compilers,
   // because we can't tell the difference between
   // unions and classes:
   value_fail(true, boost::is_empty<empty_union_UDT>::value)
   soft_value_test(false, boost::is_empty<enum_UDT>::value)
   soft_value_test(true, boost::is_empty<boost::noncopyable>::value)
   soft_value_test(false, boost::is_empty<non_empty>::value)

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
#ifdef __BORLANDC__
// can't handle enum's or classes that are POD's
unsigned int expected_failures = 10;
#elif defined(__GNUC__)
// classes that are POD's, or empty:
unsigned int expected_failures = 4;
#elif defined(BOOST_MSVC)
// can't handle classes that are POD's or arrays that are POD's
unsigned int expected_failures = 19;
#else
unsigned int expected_failures = 4;
#endif


