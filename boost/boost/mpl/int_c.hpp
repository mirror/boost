//-----------------------------------------------------------------------------
// boost mpl/int_c.hpp header file
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

#ifndef BOOST_MPL_INT_C_HPP_INCLUDED
#define BOOST_MPL_INT_C_HPP_INCLUDED

#include "boost/config.hpp"

namespace boost {
namespace mpl {

template< int N >
struct int_c
{
    BOOST_STATIC_CONSTANT(int, value = N);
    typedef int_c type;
    typedef int value_type;

    // have to #ifdef here: some compilers don't like the 'N + 1' form (MSVC),
    // while some other don't like 'value + 1' (Borland)
#if !defined(__BORLANDC__)
    typedef int_c<value + 1> next;
    typedef int_c<value - 1> prior;
#else
    typedef int_c<N + 1> next;
    typedef int_c<N - 1> prior;
#endif

    operator int() const { return this->value; } 
};

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_INT_C_HPP_INCLUDED
