//-----------------------------------------------------------------------------
// boost mpl/v2_1/int.hpp header file
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

#ifndef BOOST_MPL_V2_1_INT_HPP_INCLUDED
#define BOOST_MPL_V2_1_INT_HPP_INCLUDED

#include "boost/mpl/int_c.hpp"
#include "boost/mpl/aux_/config/nttp.hpp"

namespace boost { namespace mpl { namespace v2_1 {

template< BOOST_MPL_AUX_NTTP_DECL(int, N) > struct int_ : mpl::int_c<N> {};

}}} // namespace boost::mpl::v2_1

#endif // BOOST_MPL_V2_1_INT_HPP_INCLUDED
