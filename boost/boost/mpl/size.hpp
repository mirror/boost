//-----------------------------------------------------------------------------
// boost mpl/size.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

#include "boost/mpl/size_fwd.hpp"
#include "boost/mpl/aux_/size_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/msvc_eti_base.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
            ::template algorithm< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,size,(Sequence))
};

BOOST_MPL_AUX_VOID_SPEC(1, size)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SIZE_HPP_INCLUDED
