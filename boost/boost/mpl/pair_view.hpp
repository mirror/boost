
#ifndef BOOST_MPL_PAIR_VIEW_HPP_INCLUDED
#define BOOST_MPL_PAIR_VIEW_HPP_INCLUDED

// Copyright David Abrahams 2003-2004
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_category.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/iterator_names.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename I1, typename I2, typename Category >
struct pair_iter;

template< typename Category >
struct pair_iter_ops
{
    template< typename I1, typename I2 > struct result_
    {
        typedef typename mpl::next<I1>::type i1_;
        typedef typename mpl::next<I2>::type i2_;
        typedef pair_iter<i1_,i2_,Category> next;
    };
};

template<>
struct pair_iter_ops<bidirectional_iterator_tag>
{
    template< typename I1, typename I2 > struct result_
    {
        typedef bidirectional_iterator_tag category;

        typedef typename mpl::next<I1>::type i1_;
        typedef typename mpl::next<I2>::type i2_;
        typedef pair_iter<i1_,i2_,category> next;

        typedef typename mpl::prior<I1>::type k1_;
        typedef typename mpl::prior<I2>::type k2_;
        typedef pair_iter<k1_,k2_,category> prior;
    };
};

template<>
struct pair_iter_ops<random_access_iterator_tag>
{
    template< typename I1, typename I2 > struct result_
    {
        typedef random_access_iterator_tag category;

        typedef typename mpl::next<I1>::type i1_;
        typedef typename mpl::next<I2>::type i2_;
        typedef pair_iter<i1_,i2_,category> next;

        typedef typename mpl::prior<I1>::type k1_;
        typedef typename mpl::prior<I2>::type k2_;
        typedef pair_iter<k1_,k2_,category> prior;

        template< typename Distance > struct BOOST_MPL_AUX_ITERATOR_ADVANCE
        {
            typedef typename advance<I1,Distance>::type iter1_;
            typedef typename advance<I2,Distance>::type iter2_;
            typedef pair_iter<iter1_,iter2_,category> type;
        };

        template< typename U > struct BOOST_MPL_AUX_ITERATOR_DISTANCE
            : distance<typename U::first,I1>
        {
        };
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


template< typename I1, typename I2, typename Category >
struct pair_iter
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    : aux::msvc_eti_base< pair_iter_ops<Category>
        ::template result_<I1,I2> >::type
#endif
{
    typedef Category category;
    typedef pair<typename I1::type, typename I2::type> type;
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< typename I1, typename I2, typename C >
struct next< pair_iter<I1,I2,C> >
{
    typedef typename mpl::next<I1>::type i1_;
    typedef typename mpl::next<I2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

template< typename I1, typename I2, typename C >
struct prior< pair_iter<I1,I2,C> >
{
    typedef typename mpl::prior<I1>::type i1_;
    typedef typename mpl::prior<I2>::type i2_;
    typedef pair_iter<i1_,i2_,C> type;
};

template< typename I1, typename I2, typename C, typename Distance >
struct advance< pair_iter<I1,I2,C>,Distance>
{
    typedef typename mpl::advance<I1,Distance>::type iter1_;
    typedef typename mpl::advance<I2,Distance>::type iter2_;
    typedef pair_iter<iter1_,iter2_,C> type;
};

template< typename I1, typename I2, typename K1, typename K2, typename C >
struct distance< pair_iter<I1,I2,C>, pair_iter<K1,K2,C> >
    : mpl::distance<K1,I1>
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2)
    >
struct pair_view
{
    typedef nested_begin_end_tag tag;

    typedef typename begin<Sequence1>::type iter1_;
    typedef typename begin<Sequence2>::type iter2_;
    typedef typename min<
          typename iterator_category<iter1_>::type
        , typename iterator_category<iter2_>::type
        >::type category_;
    
    typedef pair_iter<iter1_,iter2_,category_> begin;
    
    typedef pair_iter<
          typename end<Sequence1>::type
        , typename end<Sequence2>::type
        , category_
        > end;
};

BOOST_MPL_AUX_NA_SPEC(2, pair_view)

}}

#endif // BOOST_MPL_PAIR_VIEW_HPP_INCLUDED
