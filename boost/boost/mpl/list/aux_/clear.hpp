//-----------------------------------------------------------------------------
// boost mpl/list/aux_/clear.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED

#include "boost/mpl/clear_fwd.hpp"
#include "boost/mpl/list/aux_/node.hpp"
#include "boost/mpl/list/aux_/tag.hpp"

namespace boost {
namespace mpl {

template<>
struct clear_traits< aux::list_tag >
{
    template< typename List > struct algorithm
    {
        typedef null_node type;
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_CLEAR_HPP_INCLUDED
