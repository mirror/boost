//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// standalone test program for <boost/type_traits.hpp>

/* Release notes:
   31st July 2000:
      Added extra tests for is_empty, is_convertible, alignment_of.
   23rd July 2000:
      Removed all call_traits tests to call_traits_test.cpp
      Removed all compressed_pair tests to compressed_pair_tests.cpp
      Improved tests macros
      Tidied up specialistions of type_types classes for test cases.
*/

#include <iostream>
#include <typeinfo>

#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include "type_traits_test.hpp"

using namespace boost;

// Since there is no compiler support, we should specialize:
//  is_enum for all enumerations (is_enum implies is_POD)
//  is_union for all unions
//  is_empty for all empty composites
//  is_POD for all PODs (except enums) (is_POD implies has_*)
//  has_* for any UDT that has that trait and is not POD

enum enum_UDT{ one, two, three };
struct UDT
{
   UDT();
   ~UDT();
   UDT(const UDT&);
   UDT& operator=(const UDT&);
   int i;

   void f1();
   int f2();
   int f3(int);
   int f4(int, float);
};

struct POD_UDT { int x; };
struct empty_UDT{ ~empty_UDT(){}; };
struct empty_POD_UDT{};
union union_UDT
{
  int x;
  double y;
  ~union_UDT();
};
union POD_union_UDT
{
  int x;
  double y;
};
union empty_union_UDT
{
  ~empty_union_UDT();
};
union empty_POD_union_UDT{};
#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
namespace boost {
template <> struct is_enum<enum_UDT>
{ static const bool value = true; };
template <> struct is_POD<POD_UDT>
{ static const bool value = true; };
// this type is not POD, so we have to specialize the has_* individually
template <> struct has_trivial_constructor<empty_UDT>
{ static const bool value = true; };
template <> struct has_trivial_copy<empty_UDT>
{ static const bool value = true; };
template <> struct has_trivial_assign<empty_UDT>
{ static const bool value = true; };
template <> struct is_POD<empty_POD_UDT>
{ static const bool value = true; };
template <> struct is_union<union_UDT>
{ static const bool value = true; };
template <> struct is_union<POD_union_UDT>
{ static const bool value = true; };
template <> struct is_POD<POD_union_UDT>
{ static const bool value = true; };
template <> struct is_union<empty_union_UDT>
{ static const bool value = true; };
// this type is not POD, so we have to specialize the has_* individually
template <> struct has_trivial_constructor<empty_union_UDT>
{ static const bool value = true; };
template <> struct has_trivial_copy<empty_union_UDT>
{ static const bool value = true; };
template <> struct has_trivial_assign<empty_union_UDT>
{ static const bool value = true; };
template <> struct is_union<empty_POD_union_UDT>
{ static const bool value = true; };
template <> struct is_POD<empty_POD_union_UDT>
{ static const bool value = true; };
}
#else
namespace boost {
template <> struct is_enum<enum_UDT>
{ enum{ value = true }; };
template <> struct is_POD<POD_UDT>
{ enum{ value = true }; };
// this type is not POD, so we have to specialize the has_* individually
template <> struct has_trivial_constructor<empty_UDT>
{ enum{ value = true }; };
template <> struct has_trivial_copy<empty_UDT>
{ enum{ value = true }; };
template <> struct has_trivial_assign<empty_UDT>
{ enum{ value = true }; };
template <> struct is_POD<empty_POD_UDT>
{ enum{ value = true }; };
template <> struct is_union<union_UDT>
{ enum{ value = true }; };
template <> struct is_union<POD_union_UDT>
{ enum{ value = true }; };
template <> struct is_POD<POD_union_UDT>
{ enum{ value = true }; };
template <> struct is_union<empty_union_UDT>
{ enum{ value = true }; };
// this type is not POD, so we have to specialize the has_* individually
template <> struct has_trivial_constructor<empty_union_UDT>
{ enum{ value = true }; };
template <> struct has_trivial_copy<empty_union_UDT>
{ enum{ value = true }; };
template <> struct has_trivial_assign<empty_union_UDT>
{ enum{ value = true }; };
template <> struct is_union<empty_POD_union_UDT>
{ enum{ value = true }; };
template <> struct is_POD<empty_POD_union_UDT>
{ enum{ value = true }; };
}
#endif

class Base { };

class Deriverd : public Base { };

class NonDerived { };

enum enum1
{
   one_,two_
};

enum enum2
{
   three_,four_
};

struct VB
{
   virtual ~VB(){};
};

struct VD : VB
{
   ~VD(){};
};
//
// struct non_pointer:
// used to verify that is_pointer does not return
// true for class types that implement operator void*()
//
struct non_pointer
{
   operator void*(){return this;}
};
//
// struct non_empty:
// used to verify that is_empty does not emit
// spurious warnings or errors.
//
struct non_empty : boost::noncopyable
{
   int i;
};

// Steve: All comments that I (Steve Cleary) have added below are prefixed with
//  "Steve:"  The failures that BCB4 has on the tests are due to Borland's
//  not considering cv-qual's as a part of the type -- they are considered
//  compiler hints only.  These failures should be fixed before long.

int main()
{
   std::cout << "Checking type operations..." << std::endl << std::endl;

   // cv-qualifiers applied to reference types should have no effect
   // declare these here for later use with is_reference and remove_reference:
   typedef int& r_type;
   typedef const r_type cr_type;

   type_test(int, remove_reference<int>::type)
   type_test(const int, remove_reference<const int>::type)
   type_test(int, remove_reference<int&>::type)
   type_test(const int, remove_reference<const int&>::type)
   type_test(volatile int, remove_reference<volatile int&>::type)
   type_test(int, remove_reference<cr_type>::type)

   type_test(int, remove_const<const int>::type)
   // Steve: fails on BCB4
   type_test(volatile int, remove_const<volatile int>::type)
   // Steve: fails on BCB4
   type_test(volatile int, remove_const<const volatile int>::type)
   type_test(int, remove_const<int>::type)
   type_test(int*, remove_const<int* const>::type)
   type_test(int, remove_volatile<volatile int>::type)
   // Steve: fails on BCB4
   type_test(const int, remove_volatile<const int>::type)
   // Steve: fails on BCB4
   type_test(const int, remove_volatile<const volatile int>::type)
   type_test(int, remove_volatile<int>::type)
   type_test(int*, remove_volatile<int* volatile>::type)
   type_test(int, remove_cv<volatile int>::type)
   type_test(int, remove_cv<const int>::type)
   type_test(int, remove_cv<const volatile int>::type)
   type_test(int, remove_cv<int>::type)
   type_test(int*, remove_cv<int* volatile>::type)
   type_test(int*, remove_cv<int* const>::type)
   type_test(int*, remove_cv<int* const volatile>::type)
   type_test(const int *, remove_cv<const int * const>::type)
   type_test(int, remove_bounds<int>::type)
   type_test(int*, remove_bounds<int*>::type)
   type_test(int, remove_bounds<int[3]>::type)
   type_test(int[3], remove_bounds<int[2][3]>::type)

   std::cout << std::endl << "Checking type properties..." << std::endl << std::endl;

   value_test(true, (is_same<int, int>::value))
   value_test(false, (is_same<int, const int>::value))
   value_test(false, (is_same<int, int&>::value))
   value_test(false, (is_same<int*, const int*>::value))
   value_test(false, (is_same<int*, int*const>::value))
   value_test(false, (is_same<int, int[2]>::value))
   value_test(false, (is_same<int*, int[2]>::value))
   value_test(false, (is_same<int[4], int[2]>::value))

   value_test(false, is_const<int>::value)
   value_test(true, is_const<const int>::value)
   value_test(false, is_const<volatile int>::value)
   value_test(true, is_const<const volatile int>::value)

   value_test(false, is_volatile<int>::value)
   value_test(false, is_volatile<const int>::value)
   value_test(true, is_volatile<volatile int>::value)
   value_test(true, is_volatile<const volatile int>::value)

   value_test(true, is_void<void>::value)
   // Steve: fails on BCB4
   // JM: but looks as though it should according to [3.9.3p1]?
   //value_test(false, is_void<const void>::value)
   value_test(false, is_void<int>::value)

   value_test(false, is_standard_unsigned_integral<UDT>::value)
   value_test(false, is_standard_unsigned_integral<void>::value)
   value_test(false, is_standard_unsigned_integral<bool>::value)
   value_test(false, is_standard_unsigned_integral<char>::value)
   value_test(false, is_standard_unsigned_integral<signed char>::value)
   value_test(true, is_standard_unsigned_integral<unsigned char>::value)
   value_test(false, is_standard_unsigned_integral<wchar_t>::value)
   value_test(false, is_standard_unsigned_integral<short>::value)
   value_test(true, is_standard_unsigned_integral<unsigned short>::value)
   value_test(false, is_standard_unsigned_integral<int>::value)
   value_test(true, is_standard_unsigned_integral<unsigned int>::value)
   value_test(false, is_standard_unsigned_integral<long>::value)
   value_test(true, is_standard_unsigned_integral<unsigned long>::value)
   value_test(false, is_standard_unsigned_integral<float>::value)
   value_test(false, is_standard_unsigned_integral<double>::value)
   value_test(false, is_standard_unsigned_integral<long double>::value)
   #ifdef ULLONG_MAX
   value_test(false, is_standard_unsigned_integral<long long>::value)
   value_test(false, is_standard_unsigned_integral<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(false, is_standard_unsigned_integral<__int64>::value)
   value_test(false, is_standard_unsigned_integral<unsigned __int64>::value)
   #endif

   value_test(false, is_standard_signed_integral<UDT>::value)
   value_test(false, is_standard_signed_integral<void>::value)
   value_test(false, is_standard_signed_integral<bool>::value)
   value_test(false, is_standard_signed_integral<char>::value)
   value_test(true, is_standard_signed_integral<signed char>::value)
   value_test(false, is_standard_signed_integral<unsigned char>::value)
   value_test(false, is_standard_signed_integral<wchar_t>::value)
   value_test(true, is_standard_signed_integral<short>::value)
   value_test(false, is_standard_signed_integral<unsigned short>::value)
   value_test(true, is_standard_signed_integral<int>::value)
   value_test(false, is_standard_signed_integral<unsigned int>::value)
   value_test(true, is_standard_signed_integral<long>::value)
   value_test(false, is_standard_signed_integral<unsigned long>::value)
   value_test(false, is_standard_signed_integral<float>::value)
   value_test(false, is_standard_signed_integral<double>::value)
   value_test(false, is_standard_signed_integral<long double>::value)
   #ifdef ULLONG_MAX
   value_test(false, is_standard_signed_integral<long long>::value)
   value_test(false, is_standard_signed_integral<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(false, is_standard_signed_integral<__int64>::value)
   value_test(false, is_standard_signed_integral<unsigned __int64>::value)
   #endif

   value_test(false, is_standard_arithmetic<UDT>::value)
   value_test(false, is_standard_arithmetic<void>::value)
   value_test(true, is_standard_arithmetic<bool>::value)
   value_test(true, is_standard_arithmetic<char>::value)
   value_test(true, is_standard_arithmetic<signed char>::value)
   value_test(true, is_standard_arithmetic<unsigned char>::value)
   value_test(true, is_standard_arithmetic<wchar_t>::value)
   value_test(true, is_standard_arithmetic<short>::value)
   value_test(true, is_standard_arithmetic<unsigned short>::value)
   value_test(true, is_standard_arithmetic<int>::value)
   value_test(true, is_standard_arithmetic<unsigned int>::value)
   value_test(true, is_standard_arithmetic<long>::value)
   value_test(true, is_standard_arithmetic<unsigned long>::value)
   value_test(true, is_standard_arithmetic<float>::value)
   value_test(true, is_standard_arithmetic<double>::value)
   value_test(true, is_standard_arithmetic<long double>::value)
   #ifdef ULLONG_MAX
   value_test(false, is_standard_arithmetic<long long>::value)
   value_test(false, is_standard_arithmetic<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(false, is_standard_arithmetic<__int64>::value)
   value_test(false, is_standard_arithmetic<unsigned __int64>::value)
   #endif

   value_test(false, is_standard_fundamental<UDT>::value)
   value_test(true, is_standard_fundamental<void>::value)
   value_test(true, is_standard_fundamental<bool>::value)
   value_test(true, is_standard_fundamental<char>::value)
   value_test(true, is_standard_fundamental<signed char>::value)
   value_test(true, is_standard_fundamental<unsigned char>::value)
   value_test(true, is_standard_fundamental<wchar_t>::value)
   value_test(true, is_standard_fundamental<short>::value)
   value_test(true, is_standard_fundamental<unsigned short>::value)
   value_test(true, is_standard_fundamental<int>::value)
   value_test(true, is_standard_fundamental<unsigned int>::value)
   value_test(true, is_standard_fundamental<long>::value)
   value_test(true, is_standard_fundamental<unsigned long>::value)
   value_test(true, is_standard_fundamental<float>::value)
   value_test(true, is_standard_fundamental<double>::value)
   value_test(true, is_standard_fundamental<long double>::value)
   #ifdef ULLONG_MAX
   value_test(false, is_standard_fundamental<long long>::value)
   value_test(false, is_standard_fundamental<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(false, is_standard_fundamental<__int64>::value)
   value_test(false, is_standard_fundamental<unsigned __int64>::value)
   #endif

   value_test(false, is_arithmetic<UDT>::value)
   value_test(true, is_arithmetic<char>::value)
   value_test(true, is_arithmetic<signed char>::value)
   value_test(true, is_arithmetic<unsigned char>::value)
   value_test(true, is_arithmetic<wchar_t>::value)
   value_test(true, is_arithmetic<short>::value)
   value_test(true, is_arithmetic<unsigned short>::value)
   value_test(true, is_arithmetic<int>::value)
   value_test(true, is_arithmetic<unsigned int>::value)
   value_test(true, is_arithmetic<long>::value)
   value_test(true, is_arithmetic<unsigned long>::value)
   value_test(true, is_arithmetic<float>::value)
   value_test(true, is_arithmetic<double>::value)
   value_test(true, is_arithmetic<long double>::value)
   value_test(true, is_arithmetic<bool>::value)
   #ifdef ULLONG_MAX
   value_test(true, is_arithmetic<long long>::value)
   value_test(true, is_arithmetic<unsigned long long>::value)
   #endif
   #if defined(__BORLANDC__) || defined(_MSC_VER)
   value_test(true, is_arithmetic<__int64>::value)
   value_test(true, is_arithmetic<unsigned __int64>::value)
   #endif

   value_test(false, is_array<int>::value)
   value_test(false, is_array<int*>::value)
   value_test(false, is_array<const int*>::value)
   value_test(false, is_array<const volatile int*>::value)
   value_test(true, is_array<int[2]>::value)
   value_test(true, is_array<const int[2]>::value)
   value_test(true, is_array<const volatile int[2]>::value)
   value_test(true, is_array<int[2][3]>::value)
   value_test(true, is_array<UDT[2]>::value)
   value_test(false, is_array<int(&)[2]>::value)

   typedef void(*f1)();
   typedef int(*f2)(int);
   typedef int(*f3)(int, bool);
   typedef void (UDT::*mf1)();
   typedef int (UDT::*mf2)();
   typedef int (UDT::*mf3)(int);
   typedef int (UDT::*mf4)(int, float);
   
   value_test(false, is_const<f1>::value)
   value_test(false, is_reference<f1>::value)
   value_test(false, is_array<f1>::value)
   value_test(false, is_pointer<int>::value)
   value_test(false, is_pointer<int&>::value)
   value_test(true, is_pointer<int*>::value)
   value_test(true, is_pointer<const int*>::value)
   value_test(true, is_pointer<volatile int*>::value)
   value_test(true, is_pointer<non_pointer*>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*const>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*volatile>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*const volatile>::value)
   // JM 02 Oct 2000:
   value_test(false, is_pointer<non_pointer>::value)
   value_test(false, is_pointer<int*&>::value)
   value_test(false, is_pointer<int(&)[2]>::value)
   value_test(false, is_pointer<int[2]>::value)
   value_test(false, is_pointer<char[sizeof(void*)]>::value)

   value_test(true, is_pointer<f1>::value)
   value_test(true, is_pointer<f2>::value)
   value_test(true, is_pointer<f3>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3
   value_test(false, is_pointer<mf1>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3
   value_test(false, is_pointer<mf2>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3
   value_test(false, is_pointer<mf3>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3
   value_test(false, is_pointer<mf4>::value)

   value_test(false, is_reference<bool>::value)
   value_test(true, is_reference<int&>::value)
   value_test(true, is_reference<const int&>::value)
   value_test(true, is_reference<volatile int &>::value)
   value_test(true, is_reference<r_type>::value)
   value_test(true, is_reference<cr_type>::value)

   value_test(false, is_class<int>::value)
   value_test(false, is_class<const int>::value)
   value_test(false, is_class<volatile int>::value)
   value_test(false, is_class<int*>::value)
   value_test(false, is_class<int* const>::value)
   value_test(false, is_class<int[2]>::value)
   value_test(false, is_class<int&>::value)
   value_test(false, is_class<mf4>::value)
   value_test(false, is_class<f1>::value)
   value_test(false, is_class<enum_UDT>::value)
   value_test(true, is_class<UDT>::value)
   value_test(true, is_class<UDT const>::value)
   value_test(true, is_class<UDT volatile>::value)
   value_test(true, is_class<empty_UDT>::value)
   value_test(true, is_class<std::iostream>::value)
   value_test(false, is_class<UDT*>::value)
   value_test(false, is_class<UDT[2]>::value)
   value_test(false, is_class<UDT&>::value)

   value_test(true, is_object<int>::value)
   value_test(true, is_object<UDT>::value)
   value_test(false, is_object<int&>::value)
   value_test(false, is_object<void>::value)
   value_test(true, is_standard_scalar<int>::value)
   value_test(true, is_extension_scalar<void*>::value)

   value_test(false, is_enum<int>::value)
   value_test(true, is_enum<enum_UDT>::value)

   value_test(false, is_member_pointer<f1>::value)
   value_test(false, is_member_pointer<f2>::value)
   value_test(false, is_member_pointer<f3>::value)
   value_test(true, is_member_pointer<mf1>::value)
   value_test(true, is_member_pointer<mf2>::value)
   value_test(true, is_member_pointer<mf3>::value)
   value_test(true, is_member_pointer<mf4>::value)

   value_test(false, is_empty<int>::value)
   value_test(false, is_empty<int*>::value)
   value_test(false, is_empty<int&>::value)
#if defined(__MWERKS__) || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   // apparent compiler bug causes this to fail to compile:
   value_fail(false, is_empty<int[2]>::value)
#else
   value_test(false, is_empty<int[2]>::value)
#endif
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   value_fail(false, is_empty<f1>::value)
#else
   value_test(false, is_empty<f1>::value)
#endif
   value_test(false, is_empty<mf1>::value)
   value_test(false, is_empty<UDT>::value)
   value_test(true, is_empty<empty_UDT>::value)
   value_test(true, is_empty<empty_POD_UDT>::value)
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   value_fail(true, is_empty<empty_union_UDT>::value)
#else
   value_test(true, is_empty<empty_union_UDT>::value)
#endif
   value_test(false, is_empty<enum_UDT>::value)
   value_test(true, is_empty<boost::noncopyable>::value)
   value_test(false, is_empty<non_empty>::value)

   value_test(true, has_trivial_constructor<int>::value)
   value_test(true, has_trivial_constructor<int*>::value)
   value_test(true, has_trivial_constructor<int*const>::value)
   value_test(true, has_trivial_constructor<const int>::value)
   value_test(true, has_trivial_constructor<volatile int>::value)
   value_test(true, has_trivial_constructor<int[2]>::value)
   value_test(true, has_trivial_constructor<int[3][2]>::value)
   value_test(true, has_trivial_constructor<int[2][4][5][6][3]>::value)
   value_test(true, has_trivial_constructor<f1>::value)
   value_test(true, has_trivial_constructor<mf2>::value)
   value_test(false, has_trivial_constructor<UDT>::value)
   value_test(true, has_trivial_constructor<empty_UDT>::value)
   value_test(true, has_trivial_constructor<enum_UDT>::value)

   value_test(true, has_trivial_copy<int>::value)
   value_test(true, has_trivial_copy<int*>::value)
   value_test(true, has_trivial_copy<int*const>::value)
   value_test(true, has_trivial_copy<const int>::value)
   // Steve: was 'false' -- should be 'true' via 3.9p3, 3.9p10
   value_test(true, has_trivial_copy<volatile int>::value)
   value_test(true, has_trivial_copy<int[2]>::value)
   value_test(true, has_trivial_copy<int[3][2]>::value)
   value_test(true, has_trivial_copy<int[2][4][5][6][3]>::value)
   value_test(true, has_trivial_copy<f1>::value)
   value_test(true, has_trivial_copy<mf2>::value)
   value_test(false, has_trivial_copy<UDT>::value)
   value_test(true, has_trivial_copy<empty_UDT>::value)
   value_test(true, has_trivial_copy<enum_UDT>::value)

   value_test(true, has_trivial_assign<int>::value)
   value_test(true, has_trivial_assign<int*>::value)
   value_test(true, has_trivial_assign<int*const>::value)
   value_test(true, has_trivial_assign<const int>::value)
   // Steve: was 'false' -- should be 'true' via 3.9p3, 3.9p10
   value_test(true, has_trivial_assign<volatile int>::value)
   value_test(true, has_trivial_assign<int[2]>::value)
   value_test(true, has_trivial_assign<int[3][2]>::value)
   value_test(true, has_trivial_assign<int[2][4][5][6][3]>::value)
   value_test(true, has_trivial_assign<f1>::value)
   value_test(true, has_trivial_assign<mf2>::value)
   value_test(false, has_trivial_assign<UDT>::value)
   value_test(true, has_trivial_assign<empty_UDT>::value)
   value_test(true, has_trivial_assign<enum_UDT>::value)

   value_test(true, has_trivial_destructor<int>::value)
   value_test(true, has_trivial_destructor<int*>::value)
   value_test(true, has_trivial_destructor<int*const>::value)
   value_test(true, has_trivial_destructor<const int>::value)
   value_test(true, has_trivial_destructor<volatile int>::value)
   value_test(true, has_trivial_destructor<int[2]>::value)
   value_test(true, has_trivial_destructor<int[3][2]>::value)
   value_test(true, has_trivial_destructor<int[2][4][5][6][3]>::value)
   value_test(true, has_trivial_destructor<f1>::value)
   value_test(true, has_trivial_destructor<mf2>::value)
   value_test(false, has_trivial_destructor<UDT>::value)
   value_test(false, has_trivial_destructor<empty_UDT>::value)
   value_test(true, has_trivial_destructor<enum_UDT>::value)

   value_test(true, is_POD<int>::value)
   value_test(true, is_POD<int*>::value)
   // Steve: was 'true', should be 'false', via 3.9p10
   value_test(false, is_POD<int&>::value)
   value_test(true, is_POD<int*const>::value)
   value_test(true, is_POD<const int>::value)
   // Steve: was 'false', should be 'true', via 3.9p10
   value_test(true, is_POD<volatile int>::value)
   // Steve: was 'true', should be 'false', via 3.9p10
   value_test(false, is_POD<const int&>::value)
   value_test(true, is_POD<int[2]>::value)
   value_test(true, is_POD<int[3][2]>::value)
   value_test(true, is_POD<int[2][4][5][6][3]>::value)
   value_test(true, is_POD<f1>::value)
   value_test(true, is_POD<mf2>::value)
   value_test(false, is_POD<UDT>::value)
   value_test(false, is_POD<empty_UDT>::value)
   value_test(true, is_POD<enum_UDT>::value)

   value_test(true, (boost::is_convertible<Deriverd,Base>::value));
   value_test(true, (boost::is_convertible<Deriverd,Deriverd>::value));
   value_test(true, (boost::is_convertible<Base,Base>::value));
   value_test(false, (boost::is_convertible<Base,Deriverd>::value));
   value_test(true, (boost::is_convertible<Deriverd,Deriverd>::value));
   value_test(false, (boost::is_convertible<NonDerived,Base>::value));
   value_test(false, (boost::is_convertible<boost::noncopyable, int>::value));
   value_test(true, (boost::is_convertible<float,int>::value));
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   value_test(false, (boost::is_convertible<float,void>::value));
   value_test(false, (boost::is_convertible<void,float>::value));
   value_test(true, (boost::is_convertible<void,void>::value));
#endif
   value_test(true, (boost::is_convertible<enum1, int>::value));
   value_test(true, (boost::is_convertible<Deriverd*, Base*>::value));
   value_test(false, (boost::is_convertible<Base*, Deriverd*>::value));
   value_test(true, (boost::is_convertible<Deriverd&, Base&>::value));
   value_test(false, (boost::is_convertible<Base&, Deriverd&>::value));
   value_test(true, (boost::is_convertible<const Deriverd*, const Base*>::value));
   value_test(false, (boost::is_convertible<const Base*, const Deriverd*>::value));
   value_test(true, (boost::is_convertible<const Deriverd&, const Base&>::value));
   value_test(false, (boost::is_convertible<const Base&, const Deriverd&>::value));

   value_test(false, (boost::is_convertible<const int *, int*>::value));
   value_test(false, (boost::is_convertible<const int&, int&>::value));
   value_test(false, (boost::is_convertible<int*, int[2]>::value));
   value_test(false, (boost::is_convertible<const int*, int[3]>::value));
   value_test(true, (boost::is_convertible<const int&, int>::value));
   value_test(true, (boost::is_convertible<int(&)[4], const int*>::value));
   value_test(true, (boost::is_convertible<int(&)(int), int(*)(int)>::value));
   value_test(true, (boost::is_convertible<int *, const int*>::value));
   value_test(true, (boost::is_convertible<int&, const int&>::value));
   value_test(true, (boost::is_convertible<int[2], int*>::value));
   value_test(true, (boost::is_convertible<int[2], const int*>::value));
   value_test(false, (boost::is_convertible<const int[2], int*>::value));

   align_test(int);
   align_test(char);
   align_test(double);
   align_test(int[4]);
   align_test(int(*)(int));
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   align_test(char&);
   align_test(char (&)(int));
   align_test(char(&)[4]);
#endif
   align_test(int*);
   //align_test(const int);
   align_test(VB);
   align_test(VD);

   std::cout << std::endl << test_count << " tests completed (" << failures << " failures)... press any key to exit";
   std::cin.get();
   return failures;
}




