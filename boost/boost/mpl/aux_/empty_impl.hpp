//-----------------------------------------------------------------------------
// boost mpl/aux_/empty_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

#include "boost/mpl/empty_fwd.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the |empty_traits| or the primary |empty| template

template< typename Tag >
struct empty_traits
{
    template< typename Sequence > struct algorithm
        : is_same<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,empty_traits)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
