//-----------------------------------------------------------------------------
// boost mpl/sort_fwd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_SORT_FWD_HPP_INCLUDED
#define BOOST_MPL_SORT_FWD_HPP_INCLUDED

#include "boost/mpl/less.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

template< typename Tag > struct sort_traits;

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template <
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct sort;

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(1, sort)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SORT_FWD_HPP_INCLUDED
