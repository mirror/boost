//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
//  defines traits classes for composite types:
//  is_array, is_pointer, is_reference, is_member_pointer, is_enum, is_union.
//
//    Fixed is_pointer, is_reference, is_const, is_volatile, is_same, 
//    is_member_pointer based on the Simulated Partial Specialization work 
//    of Mat Marcus and Jesse Jones. See 	http://opensource.adobe.com or 
//    http://groups.yahoo.com/group/boost/message/5441 
//    Some workarounds in here use ideas suggested from "Generic<Programming>: 
//    Mappings between Types and Values" 
//    by Andrei Alexandrescu (see http://www.cuj.com/experts/1810/alexandr.html).
//    Fixes for is_array are based on a newgroup posting by Jonathan Lundquist.

//
// Revision History:
// 21st March 2001:
//   Fixed is_enum so that it works with incomplete types.

#ifndef BOOST_COMPOSITE_TYPE_TRAITS_HPP
#define BOOST_COMPOSITE_TYPE_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif
#ifndef BOOST_CONVERSION_TYPE_TRAITS_HPP
#include <boost/type_traits/conversion_traits.hpp>
#endif
#ifndef BOOST_CV_TYPE_TRAITS_HPP
#include <boost/type_traits/cv_traits.hpp>
#endif
#ifndef BOOST_ARITHMETIC_TYPE_TRAITS_HPP
#include <boost/type_traits/arithmetic_traits.hpp>
#endif
#ifndef BOOST_TRANSFORM_TRAITS_HPP
#include <boost/type_traits/transform_traits.hpp>
#endif

namespace boost{

/**********************************************
 *
 * is_array
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T> struct is_array
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T, std::size_t N> struct is_array<T[N]>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T, std::size_t N> struct is_array<const T[N]>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T, std::size_t N> struct is_array<volatile T[N]>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T, std::size_t N> struct is_array<const volatile T[N]>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail{
   struct pointer_helper
   {
      pointer_helper(const volatile void*);
   };
   yes_type is_pointer_helper(pointer_helper);
   no_type is_pointer_helper(...);

::boost::type_traits::no_type is_function_tester(...);
template <class R>
::boost::type_traits::yes_type is_function_tester(R (*)(void));
template <class R, class A0>
::boost::type_traits::yes_type is_function_tester(R (*)(A0));
template <class R, class A0, class A1>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1));
template <class R, class A0, class A1, class A2>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2));
template <class R, class A0, class A1, class A2, class A3>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3));
template <class R, class A0, class A1, class A2, class A3, class A4>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27, class A28>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28));
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27, class A28, class A29>
::boost::type_traits::yes_type is_function_tester(R (*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29));


   yes_type is_array_helper(const volatile void*, const volatile void*);
   template <class T>
   no_type is_array_helper(T*const volatile*, const volatile void*);
   no_type is_array_helper(...);
} // namespace detail
template <typename T> 
struct is_array
{ 
private:
   static T t;
public:
   BOOST_STATIC_CONSTANT(bool, value = 
      (::boost::type_traits::ice_and<
         (1 == sizeof(detail::is_array_helper(&t, t))),
         ::boost::type_traits::ice_not<
            ::boost::is_reference<T>::value>::value,
         ::boost::type_traits::ice_not<
            (1 == sizeof(detail::is_function_tester(t)))>::value
      >::value));
};
template <> 
struct is_array<void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> 
struct is_array<const void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <> 
struct is_array<volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <> 
struct is_array<const volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

/**********************************************
 *
 * is_pointer
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail{
template <typename T> struct is_pointer_helper
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_pointer_helper<T*>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T> struct is_pointer_helper<T*const>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T> struct is_pointer_helper<T*volatile>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T> struct is_pointer_helper<T*const volatile>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
} // namespace detail
template <typename T> struct is_pointer
{ BOOST_STATIC_CONSTANT(bool, value = (::boost::type_traits::ice_and< ::boost::detail::is_pointer_helper<T>::value, ::boost::type_traits::ice_not< ::boost::is_member_pointer<T>::value >::value >::value)); };
#else
template <typename T>
struct is_pointer 
{ 
private:
   static T t;
public:
   BOOST_STATIC_CONSTANT(bool, value =
                (::boost::type_traits::ice_and<
                  ::boost::type_traits::ice_not<
                     ::boost::is_reference<T>::value
                  >::value,
                  ::boost::type_traits::ice_not<
                     ::boost::is_array<T>::value
                  >::value,
                  (::boost::type_traits::ice_or<
                       (1 == sizeof(detail::is_pointer_helper(t))),
                       (1 == sizeof(detail::is_function_tester(t)))
                  >::value)
                >::value ) );
};
template <>
struct is_pointer <void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct is_pointer <const void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <>
struct is_pointer <volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <>
struct is_pointer <const volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#endif
#endif

/**********************************************
 *
 * is_reference
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T> struct is_reference 
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_reference<T&> 
{ BOOST_STATIC_CONSTANT(bool, value = true); };
#if defined(__BORLANDC__)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct is_reference<T&const> 
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T> struct is_reference<T&volatile> 
{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <typename T> struct is_reference<T&const volatile> 
{ BOOST_STATIC_CONSTANT(bool, value = true); };
#endif
#else
# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
#endif // BOOST_MSVC
template <typename T> struct is_reference
{ 
private:
   typedef T const volatile cv_t;
public:
   BOOST_STATIC_CONSTANT(bool, value = 
      (::boost::type_traits::ice_or<
      ::boost::type_traits::ice_not<
         ::boost::is_const<cv_t>::value
      >::value, 
      ::boost::type_traits::ice_not<
         ::boost::is_volatile<cv_t>::value>::value
      >::value));
};
template <> struct is_reference<void>
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct is_reference<const void>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <> struct is_reference<volatile void>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <> struct is_reference<const volatile void>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
#endif

# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif // BOOST_MSVC
#endif

/**********************************************
 *
 * is_union
 *
 **********************************************/
template <typename T> struct is_union
{
private:
   typedef typename remove_cv<T>::type cvt;
public:
   BOOST_STATIC_CONSTANT(bool, value = BOOST_IS_UNION(cvt));
};

/**********************************************
 *
 * is_enum
 *
 **********************************************/
namespace detail{
struct int_convertible
{
   int_convertible(int);
};
} // namespace detail
#ifndef __BORLANDC__
template <typename T> struct is_enum
{
private:
   typedef typename ::boost::add_reference<T>::type r_type;
public:
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::type_traits::ice_not< ::boost::is_arithmetic<T>::value>::value,
         ::boost::type_traits::ice_not< ::boost::is_reference<T>::value>::value,
         ::boost::is_convertible<r_type, detail::int_convertible>::value
      >::value));
};
#else // __BORLANDC__
//
// buggy is_convertible prevents working 
// implementation of is_enum:
template <typename T> struct is_enum
{
public:
   BOOST_STATIC_CONSTANT(bool, value = BOOST_IS_ENUM(T));
};
#endif

/**********************************************
 *
 * is_member_pointer
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T> struct is_member_pointer
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T, typename U> struct is_member_pointer<U T::*>
{ BOOST_STATIC_CONSTANT(bool, value = true); };
#ifdef __GNUC__
// gcc workaround (JM 02 Oct 2000)
template <class R, class T>
struct is_member_pointer<R (T::*)(void)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0>
struct is_member_pointer<R (T::*)(A0)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1>
struct is_member_pointer<R (T::*)(A0, A1)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2>
struct is_member_pointer<R (T::*)(A0, A1, A2)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27, class A28>
struct is_member_pointer<R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28)>{ BOOST_STATIC_CONSTANT(bool, value = true); };
#endif
#else
namespace detail{
template <class R, class T>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(void));
template <class R, class T, class A0>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0));
template <class R, class T, class A0, class A1>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1));
template <class R, class T, class A0, class A1, class A2>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2));
template <class R, class T, class A0, class A1, class A2, class A3>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3));
template <class R, class T, class A0, class A1, class A2, class A3, class A4>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27, class A28>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28));
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11, class A12, class A13, class A14, class A15, class A16, class A17, class A18, class A19, class A20, class A21, class A22, class A23, class A24, class A25, class A26, class A27, class A28, class A29>
::boost::type_traits::yes_type is_member_pointer_helper(R (T::*)(A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, A16, A17, A18, A19, A20, A21, A22, A23, A24, A25, A26, A27, A28, A29));
   no_type is_member_pointer_helper(...);
}
template <typename T> 
struct is_member_pointer
{ 
private:
   static T t;
public:
   BOOST_STATIC_CONSTANT(bool, value = (1 == sizeof(detail::is_member_pointer_helper(t))) );
};
template <> 
struct is_member_pointer<void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> 
struct is_member_pointer<const void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <> 
struct is_member_pointer<volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <> 
struct is_member_pointer<const volatile void>
{ 
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#endif

#endif


} // namespace boost

#endif // BOOST_COMPOSITE_TYPE_TRAITS_HPP
 




