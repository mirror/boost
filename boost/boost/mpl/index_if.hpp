//-----------------------------------------------------------------------------
// boost mpl/index_if.hpp header file
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

#ifndef BOOST_MPL_INDEX_IF_HPP_INCLUDED
#define BOOST_MPL_INDEX_IF_HPP_INCLUDED

#include "boost/mpl/aux_/config/workaround.hpp"
#include "boost/mpl/aux_/find_if_pred.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/iter_fold_if.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/void.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

namespace aux {

struct index_if_op
{
    template < typename Index, typename Iterator >
    struct apply
        : next< Index >
    {
    };
};

} // namespace aux

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct index_if
{
private:

    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;
    typedef typename lambda<Predicate>::type pred_;

    typedef typename iter_fold_if<
          first_
        , int_<0>
        , protect< aux::index_if_op >
        , protect< aux::find_if_pred<pred_,last_> >
        >::type result_;

    typedef typename result_::first result_index_;
    typedef typename result_::second result_iterator_;

public:

    typedef typename if_<
          is_same< result_iterator_,last_ >
        , void_
        , result_index_
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, index_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INDEX_IF_HPP_INCLUDED
