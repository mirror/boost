//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

// call_traits: defines typedefs for function usage
// (see libs/utility/call_traits.htm)

/* Release notes:
   23rd July 2000:
      Fixed array specialization. (JM)
      Added Borland specific fixes for reference types
      (issue raised by Steve Cleary).
*/

#ifndef BOOST_DETAIL_CALL_TRAITS_HPP
#define BOOST_DETAIL_CALL_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifndef BOOST_TYPE_TRAITS_HPP
#include <boost/type_traits.hpp>
#endif

namespace boost{

namespace detail{

template <typename T, bool isp, bool b1, bool b2>
struct ct_imp
{
   typedef const T& param_type;
};

template <typename T, bool isp>
struct ct_imp<T, isp, true, true>
{
   typedef T const param_type;
};

template <typename T, bool b1, bool b2>
struct ct_imp<T, true, b1, b2>
{
   typedef T const param_type;
};

}

template <typename T>
struct call_traits
{
public:
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   //
   // C++ Builder workaround: we should be able to define a compile time
   // constant and pass that as a single template parameter to ct_imp<T,bool>,
   // however compiler bugs prevent this - instead pass three bool's to
   // ct_imp<T,bool,bool,bool> and add an extra partial specialisation
   // of ct_imp to handle the logic. (JM)
   typedef typename detail::ct_imp<T, ::boost::is_pointer<typename remove_const<T>::type>::value, ::boost::is_arithmetic<typename remove_const<T>::type>::value, sizeof(T) <= sizeof(void*)>::param_type param_type;
};

template <typename T>
struct call_traits<T&>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x551)
// these are illegal specialisations; cv-qualifies applied to
// references have no effect according to [8.3.2p1],
// C++ Builder requires them though as it treats cv-qualified
// references as distinct types...
template <typename T>
struct call_traits<T&const>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
template <typename T>
struct call_traits<T&const volatile>
{
   typedef T& value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef T& param_type;  // hh removed const
};
#endif

template <typename T, std::size_t N>
struct call_traits<T [N]>
{
private:
   typedef T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};

template <typename T, std::size_t N>
struct call_traits<const T [N]>
{
private:
   typedef const T array_type[N];
public:
   // degrades array to pointer:
   typedef const T* value_type;
   typedef array_type& reference;
   typedef const array_type& const_reference;
   typedef const T* const param_type;
};

}

#endif // BOOST_DETAIL_CALL_TRAITS_HPP
