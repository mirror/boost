//-----------------------------------------------------------------------------
// boost mpl/list/aux_/empty.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

#include "boost/mpl/empty_fwd.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/list/aux_/tag.hpp"

namespace boost {
namespace mpl {

template<>
struct empty_traits< aux::list_tag >
{
    template< typename List > struct algorithm
        : not_<typename List::size>
    {
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
