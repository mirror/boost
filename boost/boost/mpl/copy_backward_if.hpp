//-----------------------------------------------------------------------------
// boost mpl/copy_backward_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_COPY_BACKWARD_IF_HPP_INCLUDED
#define BOOST_MPL_COPY_BACKWARD_IF_HPP_INCLUDED

#include "boost/mpl/fold_backward.hpp"
#include "boost/mpl/aux_/copy_if_op.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(State)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(BinaryOp)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct copy_backward_if
{
 private:
    typedef typename lambda<BinaryOp>::type op_;
    typedef typename lambda<Predicate>::type pred_;

 public:
    typedef typename fold_backward<
          Sequence
        , State
        , protect< aux::copy_if_op<op_,pred_> >
        >::type type;
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(4, copy_backward_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_COPY_BACKWARD_IF_HPP_INCLUDED
