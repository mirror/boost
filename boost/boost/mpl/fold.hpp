//-----------------------------------------------------------------------------
// boost mpl/fold.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy, David Abrahams
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_FOLD_HPP_INCLUDED
#define BOOST_MPL_FOLD_HPP_INCLUDED

#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/O1_size.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/aux_/fold_impl.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(State)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(ForwardOp)
    >
struct fold
{
    typedef typename aux::fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , typename lambda<ForwardOp>::type
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_VOID_SPEC(3, fold)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_FOLD_HPP_INCLUDED
