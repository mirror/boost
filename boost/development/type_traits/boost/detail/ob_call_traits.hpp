//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  Crippled version for crippled compilers:
//  see libs/utility/call_traits.htm
//

/* Release notes:
   01st October 2000:
      Fixed call_traits on VC6, using "poor man's partial specialisation",
      using ideas taken from "Generative programming" by Krzysztof Czarnecki 
      & Ulrich Eisenecker.
*/

#ifndef BOOST_OB_CALL_TRAITS_HPP
#define BOOST_OB_CALL_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifndef BOOST_TYPE_TRAITS_HPP
#include <boost/type_traits.hpp>
#endif

namespace boost{

#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)
//
// use member templates to emulate
// partial specialisation:
//
namespace detail{

template <class T>
struct standard_call_traits
{
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef const T& param_type;
};
template <class T>
struct simple_call_traits
{
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef const T param_type;
};
template <class T>
struct reference_call_traits
{
   typedef T value_type;
   typedef T reference;
   typedef T const_reference;
   typedef T param_type;
};
template <bool simple, bool reference>
struct call_traits_chooser
{
   template <class T>
   struct rebind
   {
      typedef standard_call_traits<T> type;
   };
};
template <>
struct call_traits_chooser<true, false>
{
   template <class T>
   struct rebind
   {
      typedef simple_call_traits<T> type;
   };
};
template <>
struct call_traits_chooser<false, true>
{
   template <class T>
   struct rebind
   {
      typedef reference_call_traits<T> type;
   };
};
} // namespace detail
template <typename T>
struct call_traits
{
private:
   typedef detail::call_traits_chooser<(is_pointer<T>::value || is_arithmetic<T>::value) && sizeof(T) <= sizeof(void*), is_reference<T>::value> chooser;
   typedef typename chooser::template rebind<T> bound_type;
   typedef typename bound_type::type call_traits_type;
public:
   typedef typename call_traits_type::value_type       value_type;
   typedef typename call_traits_type::reference        reference;
   typedef typename call_traits_type::const_reference  const_reference;
   typedef typename call_traits_type::param_type       param_type;
};

#else
//
// sorry call_traits is completely non-functional
// blame your broken compiler:
//

template <typename T>
struct call_traits
{
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef const T& param_type;
};

#endif // member templates

}

#endif // BOOST_OB_CALL_TRAITS_HPP
