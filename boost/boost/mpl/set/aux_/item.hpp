
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
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/operators.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

aux::no_tag  BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( set0<> const&, void const volatile* );
aux::yes_tag BOOST_MPL_AUX_OVERLOAD_IS_MASKED( set0<> const&, void const volatile* );

#if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)

template< typename T, typename Base > struct s_item;
template< typename T, typename Base > struct s_mask;
template< typename T, typename Base > struct s_unmask;

template< typename T, typename Base >
typename s_item<T,Base>::order_tag_
BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( s_item<T,Base> const&, aux::type_wrapper<T>* );

template< typename T, typename Base >
aux::no_tag
BOOST_MPL_AUX_OVERLOAD_IS_MASKED( s_item<T,Base> const&, aux::type_wrapper<T>* );

template< typename T, typename Base >
aux::no_tag
BOOST_MPL_AUX_OVERLOAD_IS_MASKED( s_unmask<T,Base> const&, aux::type_wrapper<T>* );

template< typename T, typename Base >
aux::yes_tag
BOOST_MPL_AUX_OVERLOAD_IS_MASKED( s_mask<T,Base> const&, aux::type_wrapper<T>* );

#       define AUX778076_SET_OVERLOAD(f) BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)<>

#   else
#       define AUX778076_SET_OVERLOAD(f) BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)
#   endif


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
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    friend order_tag_   AUX778076_SET_OVERLOAD(ORDER_BY_KEY)( s_item const&, aux::type_wrapper<T>* );
    friend aux::no_tag  AUX778076_SET_OVERLOAD(IS_MASKED)( s_item const&, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_mask
    : Base
{
    typedef T       last_masked_;
    typedef void_   item_type_;
    typedef Base    base;
    typedef typename prior< typename Base::size >::type  size;

    friend aux::yes_tag AUX778076_SET_OVERLOAD(IS_MASKED)( s_mask const&, aux::type_wrapper<T>* );
};


template< typename T, typename Base >
struct s_unmask
    : Base
{
    typedef void_   last_masked_;
    typedef T       item_type_;
    typedef Base    base;
    typedef typename next< typename Base::size >::type  size;

    friend aux::no_tag AUX778076_SET_OVERLOAD(IS_MASKED)( s_unmask const&, aux::type_wrapper<T>* );
};

#undef AUX778076_SET_OVERLOAD

}}

#endif // BOOST_MPL_SET_AUX_ITEM_HPP_INCLUDED
