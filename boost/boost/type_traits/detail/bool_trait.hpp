//-----------------------------------------------------------------------------
// boost/type_traits/detail/bool_trait.hpp header file
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

#ifndef BOOST_TT_DETAIL_BOOL_TRAIT_HPP_INCLUDED
#define BOOST_TT_DETAIL_BOOL_TRAIT_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/config.hpp"

namespace boost {
namespace type_traits {

template< bool C > struct bool_trait
{
    typedef mpl::bool_c<C> type;
    BOOST_STATIC_CONSTANT(bool, value = C);
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template< bool C >
bool const bool_trait<C>::value;
#endif

} // namespace type_traits
} // namespace boost

#endif // BOOST_TT_DETAIL_BOOL_TRAIT_HPP_INCLUDED
