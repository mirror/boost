//-----------------------------------------------------------------------------
// boost mpl/size_t_c.hpp header file
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

#ifndef BOOST_MPL_SIZE_T_C_HPP_INCLUDED
#define BOOST_MPL_SIZE_T_C_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/config.hpp"
#include <cstddef> // for std::size_t

namespace boost {
namespace mpl {

template< std::size_t N > struct size_t_c
#if !defined(__BORLANDC__)
    : integral_c< std::size_t,N >
{
    typedef size_t_c type;
};
#else
{
    BOOST_STATIC_CONSTANT(std::size_t, value = N);
    typedef size_t_c type;
    typedef std::size_t value_type;

    typedef size_t_c<N + 1> next;
    typedef size_t_c<N - 1> prior;

    operator std::size_t() const { return this->value; }
};
#endif

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_SIZE_T_C_HPP_INCLUDED
