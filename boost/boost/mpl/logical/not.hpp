//-----------------------------------------------------------------------------
// boost mpl/logical/not.hpp header file
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

#ifndef BOOST_MPL_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_MPL_LOGICAL_NOT_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/aux_/nested_type_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< long C > // |long| is intentional here
struct logical_not_impl
    : bool_c<!C>
{
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct logical_not
    : aux::logical_not_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,logical_not,(T))
};

BOOST_MPL_AUX_VOID_SPEC(1,logical_not)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LOGICAL_NOT_HPP_INCLUDED
