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

#include "boost/mpl/aux_/config/static_constant.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"

namespace boost {
namespace mpl {

template< typename T,
// the type of non-type template arguments may not depend on template arguments
#if BOOST_WORKAROUND(__HP_aCC, BOOST_TESTED_AT(53800))
        long
#else 
        T
#endif 
          N >
struct integral_c
{
    BOOST_STATIC_CONSTANT(T, value = N);
    typedef integral_c type;
    typedef T value_type;

    // Note that the static_casts below are there to handle the case
    // where T is an enum type.
    
    // have to #ifdef here: some compilers don't like the 'N + 1' form (MSVC),
    // while some other don't like 'value + 1' (Borland), and some don't like
    // either
#if defined(__EDG_VERSION__) && __EDG_VERSION__ <= 243
 private:
    BOOST_STATIC_CONSTANT(T, next_value = static_cast<T>(N + 1));
    BOOST_STATIC_CONSTANT(T, prior_value = static_cast<T>(N - 1));
 public:
    typedef integral_c<T, next_value> next;
    typedef integral_c<T, prior_value> prior;
#elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__HP_aCC, BOOST_TESTED_AT(53800))
    // Borland can't handle the casts, and HP doesn't need them
    // because the 2nd template parameter is not T but long
    typedef integral_c<T, N + 1> next;
    typedef integral_c<T, N - 1> prior;
#elif BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502))
    typedef integral_c<T, static_cast<T>(N + 1)> next;
    typedef integral_c<T, static_cast<T>(N - 1)> prior;
#else
    typedef integral_c<T, static_cast<T>(value + 1)> next;
    typedef integral_c<T, static_cast<T>(value - 1)> prior;
#endif

    // enables uniform function call syntax for families of overloaded 
    // functions that return objects of both arithmetic ('int', 'long',
    // 'double', etc.) and 'integral_c<..>' types (for an example, see 
    // "mpl/example/power.cpp")
    operator T() const { return this->value; } 
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !BOOST_WORKAROUND(__BORLANDC__, <= 0x551)
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
