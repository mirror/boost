
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  (C) Copyright Eric Friedman 2002-2003.
//  (C) Copyright Antony Polukhin 2013.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED
#define BOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/type_traits/has_trivial_move_constructor.hpp>
#include <boost/type_traits/has_nothrow_copy.hpp>
#include <boost/type_traits/detail/ice_or.hpp>
#include <boost/utility/declval.hpp>

// should be the last #include
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {

namespace detail{

template <class T>
struct is_nothrow_move_constructible_imp{
#if 0
   //#ifndef BOOST_NO_CXX11_NOEXCEPT
   BOOST_STATIC_CONSTANT(bool, value = 
        (::boost::type_traits::ice_or<
            ::boost::has_trivial_move_constructor<T>::value,
            BOOST_NOEXCEPT_EXPR(T(::boost::declval<T>()))
        >::value));
#else
   BOOST_STATIC_CONSTANT(bool, value = 
        (::boost::type_traits::ice_or<
            ::boost::has_trivial_move_constructor<T>::value,
            ::boost::has_nothrow_copy<T>::value
        >::value));
#endif
};

}

BOOST_TT_AUX_BOOL_TRAIT_DEF1(is_nothrow_move_constructible,T,::boost::detail::is_nothrow_move_constructible_imp<T>::value)

BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_constructible,void,false)
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_constructible,void const,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_constructible,void const volatile,false)
BOOST_TT_AUX_BOOL_TRAIT_SPEC1(is_nothrow_move_constructible,void volatile,false)
#endif

} // namespace boost

#include <boost/type_traits/detail/bool_trait_undef.hpp>

#endif // BOOST_TT_IS_NOTHROW_MOVE_CONSTRUCTIBLE_HPP_INCLUDED
