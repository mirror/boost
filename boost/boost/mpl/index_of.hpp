//-----------------------------------------------------------------------------
// boost mpl/index_of.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

#include "boost/mpl/index_if.hpp"
#include "boost/mpl/same_as.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, index_of)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED
