//-----------------------------------------------------------------------------
// boost mpl/list/aux_/node.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_VECTOR_AUX_NODE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_NODE_HPP_INCLUDED

#include "boost/mpl/aux_/config/vector.hpp"

#if defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL)

#   include "boost/mpl/aux_/next.hpp"
#   include "boost/mpl/aux_/type_wrapper.hpp"
#   include "boost/mpl/vector/aux_/tag.hpp"

namespace boost {
namespace mpl {

template<
      long Size
    , typename T
    , typename Base
    >
struct vector_node
    : Base
{
    using Base::item;
    static aux::type_wrapper<T> item(typename Base::size);

    typedef aux::vector_tag tag;
    typedef integral_c<long,Size> size;
    typedef vector_node type;
    typedef Base base;
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL

#endif // BOOST_MPL_VECTOR_AUX_NODE_HPP_INCLUDED
