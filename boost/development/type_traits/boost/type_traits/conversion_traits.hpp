
// Copyright (C) 2000 John Maddock (john_maddock@compuserve.com)
// Copyright (C) 2000 Jeremy Siek (jsiek@lsc.nd.edu)
// Copyright (C) 1999, 2000 Jaakko J„rvi (jaakko.jarvi@cs.utu.fi)
//
// Permission to copy and use this software is granted, 
// provided this copyright notice appears in all copies. 
// Permission to modify the code and to distribute modified code is granted, 
// provided this copyright notice appears in all copies, and a notice 
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.

#ifndef BOOST_CONVERSION_TYPE_TRAITS_HPP
#define BOOST_CONVERSION_TYPE_TRAITS_HPP

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#include <boost/type_traits/ice.hpp>
#endif
#ifndef BOOST_FWD_TYPE_TRAITS_HPP
#include <boost/type_traits/fwd.hpp>
#endif
#ifndef ARITHMETIC_TYPE_TRAITS_HPP
#include <boost/type_traits/arithmetic_traits.hpp>
#endif
//
// is one type convertable to another?
//
// there are multiple versions of the is_convertible
// template, almost every compiler seems to require its
// own version:

namespace boost{

#ifdef BOOST_MSVC

//
// MS specific version:
//
namespace detail{

   // This workaround is necessary to handle when From is void
   // which is normally taken care of by the partial specialization
   // of the is_convertible class.
   using ::boost::type_traits::yes_type;
   using ::boost::type_traits::no_type;

  struct from_not_void_conversion {
    template <class From, class To>
    struct bind {
      static no_type check(...);
      static yes_type check(To);
    public:
      void foo(); // avoid warning about all members being private
      static From from;
      enum { exists = sizeof( check(from) ) == sizeof(yes_type) };
    };
  };
  struct from_is_void_conversion {
    template <class From, class To>
    struct bind {
       enum { exists = ::boost::is_void<To>::value };
    };
  };

  template <class From>
  struct conversion_helper {
    typedef from_not_void_conversion type;
  };
  template <>
  struct conversion_helper<void> {
    typedef from_is_void_conversion type;
  };
} // namespace detail

template <class From, class To>
struct is_convertible
{
 typedef typename detail::conversion_helper<From>::type Selector;
 typedef Selector::template bind<From,To> Conversion;
public:
 enum { value = Conversion::exists };
};

#elif defined(__BORLANDC__)
//
// special version for Borland compilers
// this version breaks when used for some
// UDT conversions:
//
template <class From, class To>
struct is_convertible_helper
{
private:
   // This workaround for Borland breaks the EDG C++ frontend,
   // so we only use it for Borland.
   template <class T>
   struct checker
   {
      static type_traits::no_type check(...);
      static type_traits::yes_type check(T);
   };
   static From from;
public:
   static const bool value = sizeof( checker<To>::check(from) ) == sizeof(type_traits::yes_type);

   void foo(); // avoid warning about all members being private
};

template <class From, class To>
struct is_convertible
{
private:
   typedef is_convertible_helper<From, To> c_type;
   enum{ v = c_type::value };
   char force_it[v ? 1 : 2];
public:
   static const bool value = is_convertible_helper<From, To>::value;
};

template <class From>
struct is_convertible<From, void>
{
   static const bool value = false;
};
template <class To>
struct is_convertible<void, To>
{
   static const bool value = false;
};
template <>
struct is_convertible<void, void>
{
   static const bool value = true;
};

#elif defined(__GNUC__)
//
// special version for gcc compiler
//
namespace detail{
   struct any_conversion
   {
      template <class T>
      any_conversion(const T&);
   };
   template <class T>
   struct checker
   {
      static boost::type_traits::no_type check(any_conversion ...);
      static boost::type_traits::yes_type check(T, int);
   };
} // namespace detail
template <class From, class To>
struct is_convertible
{
private:
   static From from;
public:
   static const bool value = sizeof( detail::checker<To>::check(from, 0) ) == sizeof(type_traits::yes_type);

   void foo(); // avoid warning about all members being private
};

template <class From>
struct is_convertible<From, void>
{
   static const bool value = false;
};
template <class To>
struct is_convertible<void, To>
{
   static const bool value = false;
};
template <>
struct is_convertible<void, void>
{
   static const bool value = true;
};

#else

template <class From, class To>
struct is_convertible
{
private:
   static type_traits::no_type check(...);
   static type_traits::yes_type check(To);
   static From from;
public:
   BOOST_DECL_MC(bool, value, sizeof( check(from) ) == sizeof(type_traits::yes_type));
   void foo(); // avoid warning about all members being private
};

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class From>
struct is_convertible<From, void>
{
   BOOST_DECL_MC(bool, value, false);
};

template <class To>
struct is_convertible<void, To>
{
   BOOST_DECL_MC(bool, value, false);
};

template <>
struct is_convertible<void, void>
{
   BOOST_DECL_MC(bool, value, true);
};
#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // is_convertible

} // namespace boost

#endif  // include guard
