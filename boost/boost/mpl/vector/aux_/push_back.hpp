//-----------------------------------------------------------------------------
// boost mpl/vector/aux_/push_back.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

#include "boost/mpl/push_back_fwd.hpp"
#include "boost/mpl/aux_/config/vector.hpp"

#if defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL)

#   include "boost/mpl/vector/aux_/node.hpp"
#   include "boost/mpl/list/aux_/tag.hpp"

namespace boost {
namespace mpl {

template<>
struct push_back_traits< aux::vector_tag >
{
    template< typename Vector, typename T > struct algorithm
    {
        typedef vector_node<T,Vector> type;
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
