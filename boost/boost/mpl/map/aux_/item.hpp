
#ifndef BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED

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

#include <boost/mpl/void.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/map/aux_/map0.hpp>
#include <boost/mpl/aux_/order_impl.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/operators.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

aux::type_wrapper<void_>    BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY( map0<> const&, void const volatile* );
aux::type_wrapper<void_>    BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER( map0<> const&, long_<1>* );
aux::no_tag                 BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( map0<> const&, void const volatile* );

#   if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)

template< typename Key, typename T, typename Base > struct m_item;
template< typename Key, typename Base > struct m_mask;

template< typename Key, typename T, typename Base >
aux::type_wrapper<T>
BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY( m_item<Key,T,Base> const&, aux::type_wrapper<Key>* );

template< typename Key, typename T, typename Base >
aux::type_wrapper< typename m_item<Key,T,Base>::item >
BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER( m_item<Key,T,Base> const&, typename m_item<Key,T,Base>::order* );

template< typename Key, typename Base >
aux::type_wrapper<void_>
BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY( m_mask<Key,Base> const&, aux::type_wrapper<Key>* );

template< typename Key, typename Base >
aux::type_wrapper<void_>
BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER( m_mask<Key,Base> const&, typename m_mask<Key,Base>::key_order_* );

template< typename Key, typename T, typename Base >
typename m_item<Key,T,Base>::order_tag_
BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( m_item<Key,T,Base> const&, aux::type_wrapper<Key>* );

#       define AUX778076_MAP_OVERLOAD(f) BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)<>

#   else
#       define AUX778076_MAP_OVERLOAD(f) BOOST_PP_CAT(BOOST_MPL_AUX_OVERLOAD_,f)
#   endif


template< typename Key, typename T, typename Base >
struct m_item
    : Base
{
    typedef Key         key_;
    typedef pair<Key,T> item;
    typedef Base        base;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    friend aux::type_wrapper<T>     AUX778076_MAP_OVERLOAD(VALUE_BY_KEY)( m_item const&, aux::type_wrapper<Key>* );
    friend aux::type_wrapper<item>  AUX778076_MAP_OVERLOAD(ITEM_BY_ORDER)( m_item const&, order* );
    friend order_tag_               AUX778076_MAP_OVERLOAD(ORDER_BY_KEY)( m_item const&, aux::type_wrapper<Key>* );
};


template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    friend aux::type_wrapper<void_> AUX778076_MAP_OVERLOAD(VALUE_BY_KEY)( m_mask const&, aux::type_wrapper<Key>* );
    friend aux::type_wrapper<void_> AUX778076_MAP_OVERLOAD(ITEM_BY_ORDER)( m_mask const&, key_order_* );
};

#   undef AUX778076_MAP_OVERLOAD

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

aux::no_tag BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( map0<> const&, void const volatile* );
aux::no_tag BOOST_MPL_AUX_OVERLOAD_IS_MASKED( map0<> const&, void const volatile* );

template< long n, typename Key, typename T, typename Base >
struct m_item;

template< typename Key, typename T, typename Base >
struct m_item_
    : Base
{
    typedef Key     key_;
    typedef Base    base;
    typedef m_item_ type;
    
    typedef typename next< typename Base::size >::type  size;
    typedef typename next< typename Base::order >::type order;

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value>::type order_tag_;
#else
    typedef char (&order_tag_)[BOOST_MPL_AUX_MSVC_VALUE_WKND(order)::value];
#endif

    friend order_tag_   BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( m_item_ const&, aux::type_wrapper<Key>* );
};

template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;

    typedef typename prior< typename Base::size >::type  size;
    typedef typename x_order_impl<Base,Key>::type key_order_;
    
    friend aux::no_tag  BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY( m_mask const&, aux::type_wrapper<Key>* );
    friend aux::yes_tag BOOST_MPL_AUX_OVERLOAD_IS_MASKED( m_mask const&, key_order_* );
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
