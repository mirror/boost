//-----------------------------------------------------------------------------
// boost mpl/iter_fold_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED
#define BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED

#include "boost/mpl/aux_/iter_fold_if_impl.hpp"
#include "boost/mpl/always.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/pair.hpp"
#include "boost/mpl/void.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Iterator)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(State)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(ForwardOp)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(ForwardPredicate)
    , typename BackwardOp = void_
    , typename BackwardPredicate = always<false_>
    >
struct iter_fold_if
{
private:

// cwpro8 doesn't like 'cut-off' type here (use typedef instead)
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
    struct result_ :
#else
    typedef
#endif
        aux::iter_fold_if_impl<
          Iterator
        , State
        , typename lambda<ForwardOp>::type
        , typename lambda<ForwardPredicate>::type
        , typename lambda<BackwardOp>::type
        , typename lambda<BackwardPredicate>::type
        >
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
    { };
#else
    result_;
#endif

public:

    typedef pair<
          typename result_::state
        , typename result_::iterator
        > type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , iter_fold_if
        , (Iterator,State,ForwardOp,ForwardPredicate,BackwardOp,BackwardPredicate)
        )
};

BOOST_MPL_AUX_VOID_SPEC(4, iter_fold_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITER_FOLD_IF_HPP_INCLUDED
