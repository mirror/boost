
#ifndef BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/operators.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

aux::no_tag operator/(set0<> const&, void*);
aux::no_tag operator%(set0<> const&, void*);

#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)

template< typename T, typename Base > struct s_item;
template< typename T, typename Base > struct s_mask;
template< typename T, typename Base > struct s_unmask;

template< typename T, typename Base >
typename s_item<T,Base>::order_tag_
operator/(s_item<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::yes_tag operator%(s_item<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::yes_tag operator%(s_unmask<T,Base> const&, aux::type_wrapper<T>*);

template< typename T, typename Base >
aux::no_tag operator%(s_mask<T,Base> const&, aux::type_wrapper<T>*);

#   define MPL_AUX_SET_OPERATOR(x) operator x <>

#else
#   define MPL_AUX_SET_OPERATOR(x) operator x
#endif


template< typename T, typename Base >
struct s_item
    : Base
{
    typedef void_       last_masked_;
    typedef Base        next_;
    typedef T           item_type_;
    typedef item_type_  type;
    typedef Base        base;
    
    typedef typename next< typename Base::size >::type  size;
    
    BOOST_STATIC_CONSTANT(long, order = Base::order + 1);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
    typedef typename aux::weighted_tag<(Base::order + 1)>::type order_tag_;
#else
    typedef char (&order_tag_)[order];
#endif

    friend order_tag_   MPL_AUX_SET_OPERATOR(/)(s_item const&, aux::type_wrapper<T>*);
    friend aux::yes_tag MPL_AUX_SET_OPERATOR(%)(s_item const&, aux::type_wrapper<T>*);
};


template< typename T, typename Base >
struct s_mask
    : Base
{
    typedef T       last_masked_;
    typedef void_   item_type_;
    typedef Base    base;
    typedef typename prior< typename Base::size >::type  size;

    friend aux::no_tag MPL_AUX_SET_OPERATOR(%)(s_mask const&, aux::type_wrapper<T>*);
};


template< typename T, typename Base >
struct s_unmask
    : Base
{
    typedef void_   last_masked_;
    typedef T       item_type_;
    typedef Base    base;
    typedef typename next< typename Base::size >::type  size;

    friend aux::yes_tag MPL_AUX_SET_OPERATOR(%)(s_unmask const&, aux::type_wrapper<T>*);
};

#undef MPL_AUX_SET_OPERATOR

}}

#endif // BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
