
#ifndef BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/partition.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

namespace aux {

template < typename Sequence, typename Predicate > struct quick_sort;

template <typename Predicate, typename Pivot>
struct quick_sort_pred
{
    template <typename T>
    struct apply
    {
        typedef typename apply2< Predicate, T, Pivot >::type
            type;
    };
};

template <typename Sequence, typename Predicate>
struct quick_sort_impl
{
private:

    typedef typename front<Sequence>::type pivot_;
    typedef typename pop_front<Sequence>::type seq_;

    typedef typename partition<
          seq_
        , protect< quick_sort_pred<Predicate,pivot_> >
        >::type partitioned;

    typedef typename quick_sort<
          typename first<partitioned>::type, Predicate
        >::type first_part;
    typedef typename quick_sort<
          typename second<partitioned>::type, Predicate
        >::type second_part;

public:

    typedef typename reverse_fold<
          first_part
        , typename push_front< second_part,pivot_ >::type
        , push_front<_,_>
        >::type type;

};

template <typename Sequence, typename Predicate>
struct quick_sort
    : eval_if<
          empty<Sequence>
        , identity< Sequence >
        , quick_sort_impl< Sequence,Predicate >
        >
{
};

} // namespace aux

template< typename Tag >
struct sort_impl
{
    template< typename Sequence, typename Predicate >
    struct apply
    {
        typedef typename aux::quick_sort<
              Sequence, Predicate
            >::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,sort_impl)

}}

#endif // BOOST_MPL_AUX_SORT_IMPL_HPP_INCLUDED
