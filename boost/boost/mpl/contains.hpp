//-----------------------------------------------------------------------------
// boost mpl/contains.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/find.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct contains
    : not_< is_same<
          typename find<Sequence,T>::type
        , typename end<Sequence>::type
        > >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_VOID_SPEC(2, contains)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED
