//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <iostream>
#include <typeinfo>

#include <boost/type_traits.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/call_traits.hpp>

using namespace boost;

#ifdef __BORLANDC__
#pragma option -w-ccc -w-rch -w-eff -w-aus
#endif

//
// define tests here
unsigned failures = 0;

#define value_test(v, x) if(v == x) /*std::cout << "checking value of " << #x << "...OK" << std::endl*/;\
                         else{++failures; std::cout << "checking value of " << #x << "...failed" << std::endl;}

#define type_test(v, x) if(is_same<v, x>::value) /*std::cout << "checking type of " << #x << "...OK" << std::endl*/;\
                         else{++failures; std::cout << "checking type of " << #x << "...failed (type was: " << typeid(is_same<v, x>).name() << ")" << std::endl;}

template <typename T, bool isarray = false>
struct call_traits_test
{
   static void assert_construct(call_traits<T>::param_type val);
};

template <typename T, bool isarray>
void call_traits_test<T, isarray>::assert_construct(call_traits<T>::param_type val)
{
   //
   // this is to check that the call_traits assertions are valid:
   T t(val);
   call_traits<T>::value_type v(t);
   call_traits<T>::reference r(t);
   call_traits<T>::const_reference cr(t);
   call_traits<T>::param_type p(t);
   call_traits<T>::value_type v2(v);
   call_traits<T>::value_type v3(r);
   call_traits<T>::value_type v4(p);
   call_traits<T>::reference r2(v);
   call_traits<T>::reference r3(r);
   call_traits<T>::const_reference cr2(v);
   call_traits<T>::const_reference cr3(r);
   call_traits<T>::const_reference cr4(cr);
   call_traits<T>::const_reference cr5(p);
   call_traits<T>::param_type p2(v);
   call_traits<T>::param_type p3(r);
   call_traits<T>::param_type p4(p);
}
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T>
struct call_traits_test<T, true>
{
   static void assert_construct(call_traits<T>::param_type val);
};

template <typename T>
void call_traits_test<T, true>::assert_construct(call_traits<T>::param_type val)
{
   //
   // this is to check that the call_traits assertions are valid:
   T t;
   call_traits<T>::value_type v(t);
   call_traits<T>::reference r(t);
   call_traits<T>::const_reference cr(t);
   call_traits<T>::param_type p(t);
   call_traits<T>::value_type v2(v);
   call_traits<T>::value_type v3(r);
   call_traits<T>::value_type v4(p);
   call_traits<T>::reference r2(v);
   call_traits<T>::reference r3(r);
   call_traits<T>::const_reference cr2(v);
   call_traits<T>::const_reference cr3(r);
   call_traits<T>::const_reference cr4(cr);
   call_traits<T>::const_reference cr5(p);
   call_traits<T>::param_type p2(v);
   call_traits<T>::param_type p3(r);
   call_traits<T>::param_type p4(p);
}
#endif //BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// Since there is no compiler support, we should specialize:
//  is_enum for all enumerations (is_enum implies is_POD)
//  is_union for all unions
//  is_empty for all empty composites
//  is_POD for all PODs (except enums) (is_POD implies has_*)
//  has_* for any UDT that has that trait and is not POD

enum enum_UDT{ one, two, three };
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_enum<enum_UDT>
{ static const bool value = true; };
}
#endif
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

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
struct POD_UDT { int x; };
namespace boost {
template <> struct is_POD<POD_UDT>
{ static const bool value = true; };
}
#endif
struct empty_UDT
{
  ~empty_UDT(){};
};
namespace boost {
//template <> struct is_empty<empty_UDT>
//{ static const bool value = true; };
// this type is not POD, so we have to specialize the has_* individually
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <> struct has_trivial_constructor<empty_UDT>
{ static const bool value = true; };
template <> struct has_trivial_copy<empty_UDT>
{ static const bool value = true; };
template <> struct has_trivial_assign<empty_UDT>
{ static const bool value = true; };
}
#endif

struct empty_POD_UDT{};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_empty<empty_POD_UDT>
{ static const bool value = true; };
template <> struct is_POD<empty_POD_UDT>
{ static const bool value = true; };
}
#endif
union union_UDT
{
  int x;
  double y;
  ~union_UDT();
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_union<union_UDT>
{ static const bool value = true; };
}
#endif
union POD_union_UDT
{
  int x;
  double y;
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_union<POD_union_UDT>
{ static const bool value = true; };
template <> struct is_POD<POD_union_UDT>
{ static const bool value = true; };
}
#endif
union empty_union_UDT
{
  ~empty_union_UDT();
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_union<empty_union_UDT>
{ static const bool value = true; };
template <> struct is_empty<empty_union_UDT>
{ static const bool value = true; };
// this type is not POD, so we have to specialize the has_* individually
template <> struct has_trivial_constructor<empty_union_UDT>
{ static const bool value = true; };
template <> struct has_trivial_copy<empty_union_UDT>
{ static const bool value = true; };
template <> struct has_trivial_assign<empty_union_UDT>
{ static const bool value = true; };
}
#endif
union empty_POD_union_UDT{};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace boost {
template <> struct is_union<empty_POD_union_UDT>
{ static const bool value = true; };
template <> struct is_empty<empty_POD_union_UDT>
{ static const bool value = true; };
template <> struct is_POD<empty_POD_union_UDT>
{ static const bool value = true; };
#endif
}
// Steve: All comments that I (Steve Cleary) have added below are prefixed with
//  "Steve:"  The failures that BCB4 has on the tests are due to Borland's
//  not considering cv-qual's as a part of the type -- they are considered
//  compiler hints only.  These failures should be fixed before long.

int main()
{
   std::cout << "Checking type operations..." << std::endl << std::endl;

   type_test(int, remove_reference<int>::type)
   type_test(const int, remove_reference<const int>::type)
   type_test(int, remove_reference<int&>::type)
   type_test(const int, remove_reference<const int&>::type)
   type_test(volatile int, remove_reference<volatile int&>::type)
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

   type_test(const int, call_traits<int>::param_type)
   type_test(const char, call_traits<char>::param_type)
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   type_test(char&, call_traits<char&>::param_type)
   type_test(const char&, call_traits<const char&>::param_type)
#endif
   std::cout << std::endl << "Checking type properties..." << std::endl << std::endl;

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
   value_test(false, is_void<const void>::value)
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
   value_test(true, is_array<int[2]>::value)
   value_test(true, is_array<int[2][3]>::value)
   value_test(true, is_array<UDT[2]>::value)

   typedef void(*f1)();
   typedef int(*f2)(int);
   typedef int(*f3)(int, bool);
   typedef void (UDT::*mf1)();
   typedef int (UDT::*mf2)();
   typedef int (UDT::*mf3)(int);
   typedef int (UDT::*mf4)(int, float);

   value_test(false, is_pointer<int>::value)
   value_test(false, is_pointer<int&>::value)
   value_test(true, is_pointer<int*>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*const>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*volatile>::value)
   // Steve: was 'true', should be 'false', via 3.9.2p3, 3.9.3p1
   value_test(false, is_pointer<int*const volatile>::value)
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
   value_test(false, is_empty<int[2]>::value)
   value_test(false, is_empty<f1>::value)
   value_test(false, is_empty<mf1>::value)
   value_test(false, is_empty<UDT>::value)
   value_test(false, is_empty<std::iostream>::value)
   value_test(true, is_empty<empty_UDT>::value)
   value_test(false, is_empty<enum_UDT>::value)

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

   compressed_pair<int, double> cp1;
   compressed_pair<int, double> cp1b;
   swap(cp1, cp1b);
   compressed_pair<empty_UDT, int> cp2;
   compressed_pair<int, empty_UDT> cp3;
   compressed_pair<empty_UDT, empty_UDT> cp4;
   compressed_pair<empty_UDT, empty_POD_UDT> cp5;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   int i;
   compressed_pair<int&, int&> cp6(i,i);
   compressed_pair<int, double[2]> cp7;
   cp7.first();
   double* pd = cp7.second();
#endif
   value_test(true, (sizeof(compressed_pair<empty_UDT, int>) < sizeof(std::pair<empty_UDT, int>)))
   value_test(true, (sizeof(compressed_pair<int, empty_UDT>) < sizeof(std::pair<int, empty_UDT>)))
   value_test(true, (sizeof(compressed_pair<empty_UDT, empty_UDT>) < sizeof(std::pair<empty_UDT, empty_UDT>)))
   value_test(true, (sizeof(compressed_pair<empty_UDT, empty_POD_UDT>) < sizeof(std::pair<empty_UDT, empty_POD_UDT>)))

   std::cout << std::endl << "Tests completed (" << failures << " failures)... press any key to exit";
   std::cin.get();
   return 0;
}

//
// instanciate some compressed pairs:
template class boost::compressed_pair<int, double>;
template class boost::compressed_pair<int, int>;
template class boost::compressed_pair<empty_UDT, int>;
template class boost::compressed_pair<int, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_UDT>;
template class boost::compressed_pair<empty_UDT, empty_POD_UDT>;

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//
// now some for which only a few specific members can be instantiated,
// first references:
template double& compressed_pair<double, int&>::first();
template int& compressed_pair<double, int&>::second();
template compressed_pair<double, int&>::compressed_pair(int&);
template compressed_pair<double, int&>::compressed_pair(call_traits<double>::param_type,int&);
//
// and then arrays:
#ifndef __BORLANDC__
template call_traits<int[2]>::reference compressed_pair<double, int[2]>::second();
#endif
template call_traits<double>::reference compressed_pair<double, int[2]>::first();
template compressed_pair<double, int[2]>::compressed_pair(const double&);
template compressed_pair<double, int[2]>::compressed_pair();
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
//
// now check call_traits assertions by instantiating call_traits_test:
template struct call_traits_test<int>;
template struct call_traits_test<const int>;
template struct call_traits_test<int*>;
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template struct call_traits_test<int&>;
template struct call_traits_test<const int&>;
// this doesn't work (yet) (JM):
template struct call_traits_test<int[2], true>;
#endif


