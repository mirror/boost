//-----------------------------------------------------------------------------
// boost mpl/size_of.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_SIZE_OF_HPP_INCLUDED
#define BOOST_MPL_SIZE_OF_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

#include <cstddef> // for std::size_t

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct size_of
    : mpl::integral_c<std::size_t, sizeof(T)>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,size_of,(T))
};

BOOST_MPL_AUX_VOID_SPEC(1, size_of)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SIZE_OF_HPP_INCLUDED
