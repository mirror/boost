//-----------------------------------------------------------------------------
// boost mpl/list/list0_c.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_LIST_LIST0_C_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST0_C_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/list/aux_/push_front.hpp"
#include "boost/mpl/list/aux_/pop_front.hpp"
#include "boost/mpl/list/aux_/front.hpp"
#include "boost/mpl/list/aux_/clear.hpp"
#include "boost/mpl/list/aux_/size.hpp"
#include "boost/mpl/list/aux_/empty.hpp"
#include "boost/mpl/list/aux_/begin_end.hpp"
#include "boost/mpl/list/aux_/node.hpp"

namespace boost {
namespace mpl {

template< typename T > struct list0_c
    : null_node
{
    typedef null_node type;
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_LIST0_C_HPP_INCLUDED
