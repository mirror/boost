//-----------------------------------------------------------------------------
// boost mpl/insert.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_INSERT_HPP_INCLUDED
#define BOOST_MPL_INSERT_HPP_INCLUDED

#include "boost/mpl/insert_fwd.hpp"
#include "boost/mpl/aux_/insert_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Pos_or_T)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct insert
    : insert_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence,Pos_or_T,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert,(Sequence,Pos_or_T,T))
};

BOOST_MPL_AUX_VOID_SPEC(3, insert)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INSERT_HPP_INCLUDED
