
//  (C) Copyright John Maddock 2005.  
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef BOOST_TT_IS_SIGNED_HPP_INCLUDED
#define BOOST_TT_IS_SIGNED_HPP_INCLUDED

#include "boost/type_traits/is_integral.hpp"
#include "boost/type_traits/is_enum.hpp"
#include "boost/type_traits/detail/ice_or.hpp"

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail{

template <class T>
struct is_signed_helper
{
   BOOST_STATIC_CONSTANT(bool, value = (static_cast<T>(-1) < 0));
};

template <bool integral_type>
struct is_signed_select_helper
{
   template <class T>
   struct rebind
   {
      typedef is_signed_helper<T> type;
   };
};

template <>
struct is_signed_select_helper<false>
{
   template <class T>
   struct rebind
   {
      typedef false_type type;
   };
};

template <class T>
struct is_signed_imp
{
   typedef is_signed_select_helper< 
      ::boost::type_traits::ice_or<
         ::boost::is_integral<T>::value,
         ::boost::is_enum<T>::value>::value 
   > selector;
   typedef typename selector::template rebind<T> binder;
   typedef typename binder::type type;
#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)
   BOOST_STATIC_CONSTANT(bool, value = is_signed_imp<T>::type::value);
#else
   BOOST_STATIC_CONSTANT(bool, value = type::value);
#endif
};

}

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_signed,T,::boost::detail::is_signed_imp<T>::value)

} // namespace boost

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
