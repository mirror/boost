//-----------------------------------------------------------------------------
// boost mpl/at.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

#include "boost/mpl/at_fwd.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/at_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/nttp.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(N)
    >
struct at
    : at_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence,N >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence,integral_c<long,N> >
{
};

BOOST_MPL_AUX_VOID_SPEC(2, at)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AT_HPP_INCLUDED
