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
#include "boost/mpl/aux_/iter_fold_if_impl.hpp"
#include "boost/mpl/aux_/iter_apply.hpp"
#include "boost/mpl/always.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/int.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/or.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

namespace aux {

// slight modification of Aleksey Gurtovoy's find_if_pred
//   (could replace find_if_pred)
template< typename Predicate, typename LastIterator >
struct index_if_pred
{
    template< typename State, typename Iterator >
    struct apply
    {
        typedef not_< or_<
              is_same<Iterator,LastIterator>
            , aux::iter_apply1<Predicate,Iterator>
            > > type;
    };
};

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

// cwpro8 doesn't like 'cut-off' type here (use typedef instead)
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
    struct result_ :
#else
    typedef
#endif
        aux::iter_fold_if_impl<
          first_
        , int_<0>
        , aux::index_if_op
        , aux::index_if_pred<pred_,last_>
        , void
        , always<false_>
        >
#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
    { };
#else
    result_;
#endif

    typedef typename result_::state result_index_;
    typedef typename result_::iterator result_iterator_;

 public:
    typedef typename if_<
          is_same< result_iterator_,last_ >
        , int_<-1>
        , result_index_
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, index_if)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INDEX_IF_HPP_INCLUDED
