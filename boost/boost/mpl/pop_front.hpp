//-----------------------------------------------------------------------------
// boost mpl/pop_front.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_POP_FRONT_HPP_INCLUDED

#include "boost/mpl/pop_front_fwd.hpp"
#include "boost/mpl/aux_/pop_front_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct pop_front
    : pop_front_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,pop_front,(Sequence))
};

BOOST_MPL_AUX_VOID_SPEC(1, pop_front)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_POP_FRONT_HPP_INCLUDED
