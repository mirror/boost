//-----------------------------------------------------------------------------
// boost mpl/remove.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

#include "boost/mpl/remove_if.hpp"
#include "boost/mpl/same_as.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct remove
    : remove_if< Sequence, same_as<T> >
{
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, remove)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED
