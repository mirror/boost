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
//    Some workarounds in here use ideas suggested from "Generic<Programming>: 
//    Mappings between Types and Values" 
//    by Andrei Alexandrescu (see http://www.cuj.com/experts/1810/alexandr.html).
//    Mat Marcus and Jesse Jones posted a version of is_pointer very similar to this one
//    on the boost list (Copyright 2000 Adobe Systems Incorporated and others. 
//    All rights reserved.).
//    Fixes for is_array are based on a newgroup posting by Jonathan Lundquist.

#ifndef COMPOSITE_TYPE_TRAITS_HPP
#define COMPOSITE_TYPE_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif
#ifndef BOOST_CONVERSION_TYPE_TRAITS_HPP
#include <boost/type_traits/conversion_traits.hpp>
#endif
#ifndef CV_TYPE_TRAITS_HPP
#include <boost/type_traits/cv_traits.hpp>
#endif
#ifndef ARITHMETIC_TYPE_TRAITS_HPP
#include <boost/type_traits/arithmetic_traits.hpp>
#endif

namespace boost{

/**********************************************
 *
 * is_array
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T> struct is_array
{ BOOST_DECL_MC(bool, value, false); };
template <typename T, std::size_t N> struct is_array<T[N]>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, std::size_t N> struct is_array<const T[N]>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, std::size_t N> struct is_array<volatile T[N]>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, std::size_t N> struct is_array<const volatile T[N]>
{ BOOST_DECL_MC(bool, value, true); };
#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail{
   struct pointer_helper
   {
      pointer_helper(const volatile void*);
   };
   yes_type is_pointer_helper(pointer_helper);
   no_type is_pointer_helper(...);
   template <class T>
   yes_type is_pointer_helper3(T (*)(void));
   template <class T, class A1>
   yes_type is_pointer_helper3(T (*)(A1));
   template <class T, class A1, class A2>
   yes_type is_pointer_helper3(T (*)(A1, A2));
   template <class T, class A1, class A2, class A3>
   yes_type is_pointer_helper3(T (*)(A1, A2, A3));
   no_type is_pointer_helper3(...);

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
   BOOST_DECL_MC(bool, value, (1 == sizeof(detail::is_array_helper(&t, t)))
                 & !is_reference<T>::value
                 & !(1 == sizeof(detail::is_pointer_helper3(t))) );
};
template <> 
struct is_array<void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> 
struct is_array<const void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <> 
struct is_array<volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <> 
struct is_array<const volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
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
{ BOOST_DECL_MC(bool, value, false); };
template <typename T> struct is_pointer_helper<T*>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T> struct is_pointer_helper<T*const>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T> struct is_pointer_helper<T*volatile>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T> struct is_pointer_helper<T*const volatile>
{ BOOST_DECL_MC(bool, value, true); };
} // namespace detail
template <typename T> struct is_pointer
{ BOOST_DECL_MC(bool, value, (::boost::type_traits::ice_and< ::boost::detail::is_pointer_helper<T>::value, !::boost::is_member_pointer<T>::value>::value)); };
#else
template <typename T>
struct is_pointer 
{ 
private:
   static T t;
public:
   BOOST_DECL_MC(bool, value,
                (::boost::type_traits::ice_and<
                    !::boost::is_reference<T>::value,
                    !::boost::is_array<T>::value,
                    (::boost::type_traits::ice_or<
                       (1 == sizeof(detail::is_pointer_helper(t))),
                       (1 == sizeof(detail::is_pointer_helper3(t)))
                    >::value)
                >::value ) );
};
template <>
struct is_pointer <void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct is_pointer <const void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <>
struct is_pointer <volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <>
struct is_pointer <const volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
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
{ BOOST_DECL_MC(bool, value, false); };
template <typename T> struct is_reference<T&> 
{ BOOST_DECL_MC(bool, value, true); };
#if defined(__BORLANDC__)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct is_reference<T&const> 
{ BOOST_DECL_MC(bool, value, true); };
template <typename T> struct is_reference<T&volatile> 
{ BOOST_DECL_MC(bool, value, true); };
template <typename T> struct is_reference<T&const volatile> 
{ BOOST_DECL_MC(bool, value, true); };
#endif
#else
# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable: 4181)
# endif // BOOST_MSVC
template <typename T> struct is_reference
{ 
private:
   typedef T const volatile cv_t;
public:
   BOOST_DECL_MC(bool, value, (::boost::type_traits::ice_or<!::boost::is_const<cv_t>::value, !::boost::is_volatile<cv_t>::value>::value));
};
template <> struct is_reference<void>
{
   BOOST_DECL_MC(bool, value, false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> struct is_reference<const void>
{ BOOST_DECL_MC(bool, value, false); };
template <> struct is_reference<volatile void>
{ BOOST_DECL_MC(bool, value, false); };
template <> struct is_reference<const volatile void>
{ BOOST_DECL_MC(bool, value, false); };
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
   BOOST_DECL_MC(bool, value, BOOST_IS_UNION(cvt));
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
   BOOST_DECL_MC(bool, value,
      (::boost::type_traits::ice_and<
         !::boost::is_arithmetic<T>::value,
         !::boost::is_reference<T>::value,
         ::boost::is_convertible<T, detail::int_convertible>::value
      >::value));
};
#else // __BORLANDC__
//
// buggy is_convertible prevents working 
// implementation of is_enum:
template <typename T> struct is_enum
{
public:
   BOOST_DECL_MC(bool, value, BOOST_IS_ENUM(T));
};
#endif

/**********************************************
 *
 * is_member_pointer
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T> struct is_member_pointer
{ BOOST_DECL_MC(bool, value, false); };
template <typename T, typename U> struct is_member_pointer<U T::*>
{ BOOST_DECL_MC(bool, value, true); };
#ifdef __GNUC__
// gcc workaround (JM 02 Oct 2000)
template <typename T, typename U> struct is_member_pointer<U (T::*)(void)>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, typename U, typename A1> struct is_member_pointer<U (T::*)(A1)>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, typename U, typename A1, typename A2> struct is_member_pointer<U (T::*)(A1, A2)>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, typename U, typename A1, typename A2, typename A3> struct is_member_pointer<U (T::*)(A1, A2, A3)>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, typename U, typename A1, typename A2, typename A3, typename A4> struct is_member_pointer<U (T::*)(A1, A2, A3, A4)>
{ BOOST_DECL_MC(bool, value, true); };
template <typename T, typename U, typename A1, typename A2, typename A3, typename A4, typename A5> struct is_member_pointer<U (T::*)(A1, A2, A3, A4, A5)>
{ BOOST_DECL_MC(bool, value, true); };
#endif
#else
namespace detail{
   template <class T, class U>
   yes_type is_member_pointer_helper(T (U::*));
   template <class T, class U>
   yes_type is_member_pointer_helper(T (U::*)(void));
   template <class T, class U, class A1>
   yes_type is_member_pointer_helper(T (U::*)(A1));
   template <class T, class U, class A1, class A2>
   yes_type is_member_pointer_helper(T (U::*)(A1, A2));
   template <class T, class U, class A1, class A2, class A3>
   yes_type is_member_pointer_helper(T (U::*)(A1, A2, A3));
   template <class T, class U, class A1, class A2, class A3, class A4>
   yes_type is_member_pointer_helper(T (U::*)(A1, A2, A3, A4));
   template <class T, class U, class A1, class A2, class A3, class A4, class A5>
   yes_type is_member_pointer_helper(T (U::*)(A1, A2, A3, A4, A5));
   no_type is_member_pointer_helper(...);
}
template <typename T> 
struct is_member_pointer
{ 
private:
   static T t;
public:
   BOOST_DECL_MC(bool, value, (1 == sizeof(detail::is_member_pointer_helper(t))) );
};
template <> 
struct is_member_pointer<void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <> 
struct is_member_pointer<const void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <> 
struct is_member_pointer<volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
template <> 
struct is_member_pointer<const volatile void>
{ 
   BOOST_DECL_MC(bool, value, false);
};
#endif

#endif


} // namespace boost

#endif // COMPOSITE_TYPE_TRAITS_HPP
 




