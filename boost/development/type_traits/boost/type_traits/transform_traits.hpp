//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org for most recent version including documentation.
//
//  defines traits classes for transforming one type to another:
//  remove_reference, add_reference, remove_bounds, remove_pointer.
//

#ifndef TRANSFORM_TRAITS_HPP
#define TRANSFORM_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif
#if !defined(COMPOSITE_TYPE_TRAITS_HPP) && defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#include <boost/type_traits/composite_traits.hpp>
#endif

namespace boost{

/**********************************************
 *
 * remove_reference
 *
 **********************************************/
template <typename T>
struct remove_reference
{ typedef T type; };
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T>
struct remove_reference<T&>
{ typedef T type; };
#endif
#if defined(__BORLANDC__) && !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T>
struct remove_reference<T&const>
{ typedef T type; };
template <typename T>
struct remove_reference<T&volatile>
{ typedef T type; };
template <typename T>
struct remove_reference<T&const volatile>
{ typedef T type; };
#endif

/**********************************************
 *
 * add_reference
 *
 **********************************************/
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T>
struct add_reference
{ typedef T& type; };
template <typename T>
struct add_reference<T&>
{ typedef T& type; };
#elif defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)
namespace detail{

template <bool>
struct reference_adder
{
   template <class T>
   struct rebind
   {
      typedef T& type;
   };
};

template <>
struct reference_adder<true>
{
   template <class T>
   struct rebind
   {
      typedef T type;
   };
};

} // namespace detail

template <typename T>
struct add_reference
{
private:
   typedef typename detail::reference_adder< ::boost::is_reference<T>::value>::template rebind<T> binder;
public:
   typedef typename binder::type type;
};

#else
template <typename T>
struct add_reference
{ typedef T& type; };
#endif

/**********************************************
 *
 * remove_bounds
 *
 **********************************************/
template <typename T>
struct remove_bounds
{ typedef T type; };
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T, std::size_t N>
struct remove_bounds<T[N]>
{ typedef T type; };
#endif

/**********************************************
 *
 * remove_pointer
 *
 **********************************************/
template <typename T>
struct remove_pointer
{ typedef T type; };
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <typename T>
struct remove_pointer<T*>
{ typedef T type; };
template <typename T>
struct remove_pointer<T*const>
{ typedef T type; };
template <typename T>
struct remove_pointer<T*volatile>
{ typedef T type; };
template <typename T>
struct remove_pointer<T*const volatile>
{ typedef T type; };
#endif


} // namespace boost

#endif // TRANSFORM_TRAITS_HPP
 


