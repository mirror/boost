//-----------------------------------------------------------------------------
// boost mpl/list/aux_/begin_end.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

#include "boost/mpl/begin_end_fwd.hpp"
#include "boost/mpl/list/aux_/iterator.hpp"
#include "boost/mpl/list/aux_/tag.hpp"
#include "boost/mpl/list/aux_/node.hpp"

namespace boost {
namespace mpl {

template<>
struct begin_traits< aux::list_tag >
{
    template< typename List > struct algorithm
    {
        typedef list_iterator<typename List::type> type;
    };
};

template<>
struct end_traits< aux::list_tag >
{
    template< typename > struct algorithm
    {
        typedef list_iterator<null_node> type;
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
