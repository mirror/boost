//-----------------------------------------------------------------------------
// boost mpl/aux_/front_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED

#include "boost/mpl/front_fwd.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/aux_/deref_wknd.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the |front_traits| or the primary |front| template

template< typename Tag >
struct front_traits
{
    template< typename Sequence > struct algorithm
    {
        typedef typename begin<Sequence>::type iter_;
        typedef typename BOOST_MPL_AUX_DEREF_WNKD(iter_) type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,front_traits)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_FRONT_IMPL_HPP_INCLUDED
