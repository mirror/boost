//-----------------------------------------------------------------------------
// boost mpl/replace_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy and John R. Bandela
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

#include "boost/mpl/transform.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/aux_/common_name_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(replace_if)

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct replace_if
{
 private:
    typedef typename lambda<Predicate>::type pred_;

 public:
    typedef typename transform<
          Sequence
        , protect< aux::replace_if_op<pred_,T> >
        >::type type;
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(3, replace_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED
