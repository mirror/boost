
#ifndef BOOST_MPL_REMOVE_IF_HPP_INCLUDED
#define BOOST_MPL_REMOVE_IF_HPP_INCLUDED

// + file: boost/mpl/remove_if.hpp
// + last modified: 10/mar/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/fold_backward.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template< typename Pred > struct remove_if_helper
{
    template< typename Sequence, typename U > struct apply
    {
        typedef typename apply_if<
              typename apply1<Pred,U>::type
            , identity<Sequence>
            , push_front<Sequence,U>
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct remove_if
{
 private:
    typedef typename lambda<Predicate>::type pred_;
 
 public:
    typedef typename fold_backward<
          Sequence
        , typename clear<Sequence>::type
        , protect< aux::remove_if_helper<pred_> >
        >::type type;
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, remove_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_REMOVE_IF_HPP_INCLUDED
