//-----------------------------------------------------------------------------
// boost mpl/equal.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_EQUAL_HPP_INCLUDED
#define BOOST_MPL_EQUAL_HPP_INCLUDED

#include "boost/mpl/aux_/iter_fold_if_impl.hpp"
#include "boost/mpl/aux_/iter_apply.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/begin_end.hpp"
#include "boost/mpl/next.hpp"
#include "boost/mpl/always.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/bind.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/void.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/type_traits/is_same.hpp"

namespace boost {
namespace mpl {

namespace aux {

template<
      typename Predicate
    , typename LastIterator1
    , typename LastIterator2
    >
struct equal_pred
{
    template<
          typename Iterator2
        , typename Iterator1
        >
    struct apply
    {
        typedef typename and_< 
              not_< is_same<Iterator1,LastIterator1> >
            , not_< is_same<Iterator2,LastIterator2> >
            , aux::iter_apply2<Predicate,Iterator1,Iterator2>
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence2)
    , typename Predicate = is_same<_,_>
    >
struct equal
{
 private:
    typedef typename begin<Sequence1>::type first1_;
    typedef typename begin<Sequence2>::type first2_;
    typedef typename end<Sequence1>::type last1_;
    typedef typename end<Sequence2>::type last2_;
    typedef typename lambda<Predicate>::type pred_;

    typedef aux::iter_fold_if_impl<
          first1_
        , first2_
        , next<>
        , aux::equal_pred<pred_,last1_,last2_>
        , void_
        , always<false_>
        > fold_;

    typedef typename fold_::iterator iter1_;
    typedef typename fold_::state iter2_;
    typedef and_<
          is_same<iter1_,last1_>
        , is_same<iter2_,last2_>
        > result_;

 public:
    typedef typename result_::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,equal,(Sequence1,Sequence2))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, equal)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_EQUAL_HPP_INCLUDED
