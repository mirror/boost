//-----------------------------------------------------------------------------
// boost mpl/aux_/has_xxx.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_HAS_XXX_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_XXX_HPP_INCLUDED

#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/config/msvc_typename.hpp"
#include "boost/mpl/aux_/config/overload_resolution.hpp"
#include "boost/config.hpp"

#if !defined(BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION)

#   if !defined(BOOST_MSVC) || BOOST_MSVC > 1300

// the implementation below is based on a USENET newsgroup's posting by  
// Rani Sharoni (comp.lang.c++.moderated, 2002-03-17 07:45:09 PST)

#   define BOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
template< typename T > \
boost::mpl::aux::yes_tag \
has_##name##_helper( \
      boost::mpl::aux::type_wrapper<T>* \
    , BOOST_MSVC_TYPENAME T::name* \
    ); \
\
template< typename T > \
no_tag has_##name##_helper( \
      boost::mpl::aux::type_wrapper<T>* \
    , ... \
    ); \
\
template< typename T > \
struct has_##name \
{ \
     BOOST_STATIC_CONSTANT(bool, value =  \
        sizeof(has_##name##_helper((boost::mpl::aux::type_wrapper<T>*)0, 0)) \
            == sizeof(boost::mpl::aux::yes_tag) \
        ); \
}; \
/**/

#   else

// agurt, 11/sep/02: MSVC version, based on a USENET newsgroup's posting by 
// John Madsen (comp.lang.c++.moderated, 1999-11-12 19:17:06 GMT);
// note that the code is _not_ standard-conforming, but it works, 
// and it resolves some nasty ICE cases with the above implementation

#   define BOOST_MPL_HAS_XXX_TRAIT_DEF_(name) \
template< typename T, typename name = int > \
struct has_##name : T \
{ \
 private: \
    static boost::mpl::aux::no_tag test(int*); \
    static boost::mpl::aux::yes_tag test(...); \
\
 public: \
    BOOST_STATIC_CONSTANT(bool, value =  \
        sizeof(test(static_cast<name*>(0))) != sizeof(boost::mpl::aux::no_tag) \
        ); \
}; \
\
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, void) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, bool) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, signed char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, unsigned char) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, signed short) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, unsigned short) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, signed int) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, unsigned int) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, signed long) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, unsigned long) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, float) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, double) \
BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, long double) \
/**/

#   define BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, T) \
template<> struct has_##name<T,int> \
{ \
    enum { value = false }; \
}; \
/**/

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
#   define BOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
    BOOST_MPL_HAS_XXX_TRAIT_DEF_(name) \
    BOOST_MPL_AUX_HAS_XXX_TRAIT_SPEC(name, wchar_t) \
    /**/
#else
#   define BOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
    BOOST_MPL_HAS_XXX_TRAIT_DEF_(name) \
    /**/
#endif

#   endif // BOOST_MSVC > 1300

#else 

#   define BOOST_MPL_HAS_XXX_TRAIT_DEF(name) \
template< typename T > \
struct has_##name \
{ \
     BOOST_STATIC_CONSTANT(bool, value = false); \
}; \
/**/

#endif // BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION

#endif // BOOST_MPL_AUX_HAS_XXX_HPP_INCLUDED
