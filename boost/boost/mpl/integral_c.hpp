//-----------------------------------------------------------------------------
// boost/mpl/intergal_c.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
#define BOOST_MPL_INTEGRAL_C_HPP_INCLUDED

#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< typename T, T N >
struct integral_c
{
    BOOST_STATIC_CONSTANT(T, value = N);
    typedef integral_c type;
    typedef T value_type;

    // have to #ifdef here: some compilers don't like the 'N + 1' form (MSVC),
    // while some other don't like 'value + 1' (Borland)
#if defined(__BORLANDC__) || defined(__IBMCPP__) || defined(__EDG_VERSION__) && __EDG_VERSION__ <= 241
    BOOST_STATIC_CONSTANT(T, next_value = (N + 1));
    BOOST_STATIC_CONSTANT(T, prior_value = (N - 1));
    typedef integral_c<T, next_value> next;
    typedef integral_c<T, prior_value> prior;
#else
    BOOST_STATIC_CONSTANT(T, next_value = (value + 1));
    BOOST_STATIC_CONSTANT(T, prior_value = (value - 1));
    typedef integral_c<T, next_value> next;
    typedef integral_c<T, prior_value> prior;
#endif

    // enables uniform function call syntax for families of overloaded 
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and 'integral_c<..>' types (for an example, see 
    // "mpl/example/power.cpp")
    operator T() const { return this->value; } 
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && (!defined(BOOST_MSVC) || BOOST_MSVC != 1301) \
 && !defined(__BORLANDC__)
// 'bool' constant doesn't have 'next'/'prior' members
template< bool C >
struct integral_c<bool, C>
{
    BOOST_STATIC_CONSTANT(bool, value = C);
    typedef integral_c type;
    operator bool() const { return this->value; }
};
#endif

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_INTEGRAL_C_HPP_INCLUDED
