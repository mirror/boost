//-----------------------------------------------------------------------------
// boost mpl/aux_/find_if_pred.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy, Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

#include "boost/mpl/aux_/iter_apply.hpp"
#include "boost/mpl/not.hpp"

namespace boost {
namespace mpl {
namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
