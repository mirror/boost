//-----------------------------------------------------------------------------
// boost type_traits/aux_/size_t_trait.hpp header file
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

#ifndef BOOST_TT_DETAIL_SIZE_T_TRAIT_HPP_INCLUDED
#define BOOST_TT_DETAIL_SIZE_T_TRAIT_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/config.hpp"

#include <cstddef>

namespace boost {
namespace type_traits {

template< std::size_t N >
struct size_t_trait
{
    typedef mpl::integral_c<std::size_t,N> type;
    BOOST_STATIC_CONSTANT(std::size_t, value = N);
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template< std::size_t N >
std::size_t const size_t_trait<N>::value;
#endif

} // namespace type_traits
} // namespace boost 

#endif // BOOST_TT_DETAIL_SIZE_T_TRAIT_HPP_INCLUDED
