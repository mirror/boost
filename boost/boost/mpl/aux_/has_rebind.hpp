//-----------------------------------------------------------------------------
// boost mpl/aux_/has_rebind.hpp header file
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

#ifndef BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/config/msvc_typename.hpp"
#include "boost/mpl/aux_/config/overload_resolution.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {
namespace aux {

#if !defined(BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION)
#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300

// the implementation below is based on a USENET newsgroup's posting by  
// Rani Sharoni (comp.lang.c++.moderated, 2002-03-17 07:45:09 PST)

template< typename T >
yes_tag
has_rebind_helper(type_wrapper<T>*, BOOST_MSVC_TYPENAME T::rebind*);

template< typename T >
no_tag
has_rebind_helper(type_wrapper<T>*, ...);

template< typename T >
struct has_rebind
{
     BOOST_STATIC_CONSTANT(bool, value = 
        sizeof(has_rebind_helper((type_wrapper<T>*)0, 0))
            == sizeof(yes_tag)
        );
};

#else

// agurt, 11/sep/02: MSVC version, based on a USENET newsgroup's posting by 
// John Madsen (comp.lang.c++.moderated, 1999-11-12 19:17:06 GMT);
// note that the code is _not_ standard-conforming, but it works, 
// and it resolves some nasty ICE cases with the above implementation

template< typename T, typename rebind = int >
struct has_rebind : T
{
 private:
    static no_tag test(int*);
    static yes_tag test(...);

 public:
    BOOST_STATIC_CONSTANT(bool, value = 
        sizeof(test(static_cast<rebind*>(0))) != sizeof(no_tag)
        );
};

#   define AUX_HAS_REBIND_SPEC(T) \
    template<> struct has_rebind<T,int> \
    { \
        enum { value = false }; \
    }; \
    /**/

AUX_HAS_REBIND_SPEC(void)
AUX_HAS_REBIND_SPEC(bool)
AUX_HAS_REBIND_SPEC(char)
AUX_HAS_REBIND_SPEC(signed char)
AUX_HAS_REBIND_SPEC(unsigned char)
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
AUX_HAS_REBIND_SPEC(wchar_t)
#endif
AUX_HAS_REBIND_SPEC(signed short)
AUX_HAS_REBIND_SPEC(unsigned short)
AUX_HAS_REBIND_SPEC(signed int)
AUX_HAS_REBIND_SPEC(unsigned int)
AUX_HAS_REBIND_SPEC(signed long)
AUX_HAS_REBIND_SPEC(unsigned long)
AUX_HAS_REBIND_SPEC(float)
AUX_HAS_REBIND_SPEC(double)
AUX_HAS_REBIND_SPEC(long double)

#   undef AUX_HAS_REBIND_SPEC

#endif // BOOST_MSVC > 1300
#else 

template< typename T >
struct has_rebind
{
     BOOST_STATIC_CONSTANT(bool, value = false);
};

#endif

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
