//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
//  defines traits classes for cv-qualified types:
//  is_const, is_volatile, remove_const, remove_volatile, remove_cv.
//
//  Revision History:
//  24th March 2001:
//    Fixed is_const/is_volatile so that they work with reference types

#ifndef BOOST_CV_TYPE_TRAITS_HPP
#define BOOST_CV_TYPE_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif

namespace boost{

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
namespace detail{
//
// implementation helper:
//
template <class T>
struct cv_traits_imp{};

template <class T>
struct cv_traits_imp<T*>
{
   BOOST_STATIC_CONSTANT(bool, is_const = false);
   BOOST_STATIC_CONSTANT(bool, is_volatile = false);
   typedef T unqualified_type;
};

template <class T>
struct cv_traits_imp<const T*>
{
   BOOST_STATIC_CONSTANT(bool, is_const = true);
   BOOST_STATIC_CONSTANT(bool, is_volatile = false);
   typedef T unqualified_type;
};

template <class T>
struct cv_traits_imp<volatile T*>
{
   BOOST_STATIC_CONSTANT(bool, is_const = false);
   BOOST_STATIC_CONSTANT(bool, is_volatile = true);
   typedef T unqualified_type;
};

template <class T>
struct cv_traits_imp<const volatile T*>
{
   BOOST_STATIC_CONSTANT(bool, is_const = true);
   BOOST_STATIC_CONSTANT(bool, is_volatile = true);
   typedef T unqualified_type;
};

template <class T, bool is_vol>
struct remove_const_helper
{
   typedef T type;
};
template <class T>
struct remove_const_helper<T, true>
{
   typedef volatile T type;
};

template <class T, bool is_vol>
struct remove_volatile_helper
{
   typedef T type;
};
template <class T>
struct remove_volatile_helper<T, true>
{
   typedef const T type;
};

} // namespace detail

// * convert a type T to a non-volatile type - remove_volatile<T>
template <typename T>
struct remove_volatile
{
   typedef typename detail::cv_traits_imp<T*>::unqualified_type uq_type;
   typedef typename detail::remove_volatile_helper<uq_type, ::boost::is_const<T>::value>::type type;
};
template <typename T> struct remove_volatile<T&>{ typedef T& type; };
template <typename T, std::size_t N> struct remove_volatile<volatile T[N]>{ typedef T type[N]; };
template <typename T, std::size_t N> struct remove_volatile<const volatile T[N]>{ typedef const T type[N]; };

// * convert a type T to non-const type - remove_const<T>
template <typename T>
struct remove_const
{
   typedef typename detail::cv_traits_imp<T*>::unqualified_type uq_type;
   typedef typename detail::remove_const_helper<uq_type, ::boost::is_volatile<T>::value>::type type;
};
template <typename T> struct remove_const<T&>{ typedef T& type; };
template <typename T, std::size_t N> struct remove_const<const T[N]>{ typedef T type[N]; };
template <typename T, std::size_t N> struct remove_const<const volatile T[N]>{ typedef volatile T type[N]; };

//  convert a type T to a non-cv-qualified type - remove_cv<T>
template <typename T>
struct remove_cv
{
   typedef typename detail::cv_traits_imp<T*>::unqualified_type type;
};
template <typename T> struct remove_cv<T&>{ typedef T& type; };
template <typename T, std::size_t N> struct remove_cv<const T[N]>{ typedef T type[N]; };
template <typename T, std::size_t N> struct remove_cv<volatile T[N]>{ typedef T type[N]; };
template <typename T, std::size_t N> struct remove_cv<const volatile T[N]>{ typedef T type[N]; };

//* is a type T  declared const - is_const<T>
template <typename T>
struct is_const
{
   BOOST_STATIC_CONSTANT(bool, value = detail::cv_traits_imp<T*>::is_const);
};
template <typename T> struct is_const<T&>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
#if defined(__BORLANDC__)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct is_const<T&const>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_const<T&volatile>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_const<T&const volatile>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
#endif

//* is a type T declared volatile - is_volatile<T>
template <typename T>
struct is_volatile
{
   BOOST_STATIC_CONSTANT(bool, value = detail::cv_traits_imp<T*>::is_volatile);
};
template <typename T> struct is_volatile<T&>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
#if defined(__BORLANDC__)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T> struct is_volatile<T&const>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_volatile<T&volatile>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
template <typename T> struct is_volatile<T&const volatile>
{ BOOST_STATIC_CONSTANT(bool, value = false); };
#endif

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
// The following three don't work:
template <typename T> struct remove_volatile{ typedef T type; };
template <typename T> struct remove_const{ typedef T type; };
template <typename T> struct remove_cv{ typedef T type; };

namespace detail{
   using ::boost::type_traits::yes_type;
   using ::boost::type_traits::no_type;
   yes_type is_const_helper(const volatile void*);
   no_type is_const_helper(volatile void *);
   yes_type is_volatile_helper(const volatile void*);
   no_type is_volatile_helper(const void *);
}

template <typename T>
struct is_const
{ 
private:
   static T t;
public:
   BOOST_STATIC_CONSTANT(bool, value = (sizeof(detail::yes_type) == sizeof(detail::is_const_helper(&t))));
};

template <>
struct is_const<void>
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct is_const<const void>
{
   BOOST_STATIC_CONSTANT(bool, value = true);
};
template <>
struct is_const<volatile void>
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <>
struct is_const<const volatile void>
{
   BOOST_STATIC_CONSTANT(bool, value = true);
};
#endif

template <typename T>
struct is_volatile
{
private:
   static T t;
public:
   BOOST_STATIC_CONSTANT(bool, value = (sizeof(detail::yes_type) == sizeof(detail::is_volatile_helper(&t))));
};

template <>
struct is_volatile<void>
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct is_volatile<const void>
{
   BOOST_STATIC_CONSTANT(bool, value = false);
};
template <>
struct is_volatile<volatile void>
{
   BOOST_STATIC_CONSTANT(bool, value = true);
};
template <>
struct is_volatile<const volatile void>
{
   BOOST_STATIC_CONSTANT(bool, value = true);
};
#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// * convert a type T to const type - add_const<T>
// this is not required since the result is always
// the same as "T const", but it does suppress warnings
// from some compilers:
template <typename T>
struct add_const
{
   typedef T const type;
};
// * convert a type T to volatile type - add_volatile<T>
// this is not required since the result is always
// the same as "T volatile", but it does suppress warnings
// from some compilers:
template <typename T>
struct add_volatile
{
   typedef T volatile type;
};
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T>
struct add_const<T&>{ typedef T& type; };
template <class T>
struct add_volatile<T&>{ typedef T& type; };
#endif

} // namespace boost


#endif // BOOST_CV_TYPE_TRAITS_HPP



