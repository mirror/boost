
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
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/operators.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

aux::type_wrapper<void_> operator|(map0<> const&, void const volatile*);
aux::type_wrapper<void_> operator||(map0<> const&, long_<1>);
aux::no_tag operator/(map0<> const&, void const volatile*);

#   if defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION)

template< typename Key, typename T, typename Base > struct m_item;
template< typename Key, typename Base > struct m_mask;

template< typename Key, typename T, typename Base >
aux::type_wrapper<T>
operator|(m_item<Key,T,Base> const&, aux::type_wrapper<Key>*);

template< typename Key, typename T, typename Base >
aux::type_wrapper<typename m_item<Key,T,Base>::type>
operator||(m_item<Key,T,Base> const&, long_<m_item<Key,T,Base>::order>);

template< typename Key, typename Base >
aux::type_wrapper<void_>
operator|(m_mask<Key,Base> const&, aux::type_wrapper<Key>*);

template< typename Key, typename Base >
aux::type_wrapper<void_>
operator||(m_mask<Key,Base> const&, long_<m_mask<Key,Base>::old_order_::value>);

template< typename Key, typename T, typename Base >
typename m_item<Key,T,Base>::order_tag_
operator/(m_item<Key,T,Base> const&, aux::type_wrapper<Key>*);

#       define MPL_AUX_MAP_OPERATOR(x) operator x <>

#   else
#       define MPL_AUX_MAP_OPERATOR(x) operator x
#   endif


template< typename Key, typename T, typename Base >
struct m_item
    : Base
{
    typedef Key         key_;
    typedef pair<Key,T> type;
    typedef Base        base;
    
    typedef typename next< typename Base::size >::type  size;

    BOOST_STATIC_CONSTANT(long, order = Base::order + 1);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
    typedef typename aux::weighted_tag<(Base::order + 1)>::type order_tag_;
#else
    typedef char (&order_tag_)[order];
#endif

    friend aux::type_wrapper<T>     MPL_AUX_MAP_OPERATOR(|)(m_item const&, aux::type_wrapper<Key>*);
    friend aux::type_wrapper<type>  MPL_AUX_MAP_OPERATOR(||)(m_item const&, long_<order>);
    friend order_tag_               MPL_AUX_MAP_OPERATOR(/)(m_item const&, aux::type_wrapper<Key>*);
};


template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;

    typedef typename prior< typename Base::size >::type  size;

    typedef typename x_order_impl<Base,Key>::type old_order_;
    
    friend aux::type_wrapper<void_> MPL_AUX_MAP_OPERATOR(|)(m_mask const&, aux::type_wrapper<Key>*);
    friend aux::type_wrapper<void_> MPL_AUX_MAP_OPERATOR(||)(m_mask const&, long_<old_order_::value>);
//    friend order_tag_           MPL_AUX_MAP_OPERATOR(/)(m_mask const&, aux::type_wrapper<T>*);
};

#   undef MPL_AUX_MAP_OPERATOR

#else // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

aux::no_tag operator/(map0<> const&, void*);
aux::no_tag operator%(map0<> const&, void*);

template< typename Key, typename T, typename Base >
struct m_item_
    : Base
{
    typedef Key         key_;
    typedef Base        base;
    
    typedef typename next< typename Base::size >::type  size;

    BOOST_STATIC_CONSTANT(long, order = Base::order + 1);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
    typedef typename aux::weighted_tag<(Base::order + 1)>::type order_tag_;
#else
    typedef char (&order_tag_)[order];
#endif

    friend order_tag_           operator/(m_item_ const&, aux::type_wrapper<Key>*);
};

template< typename Key, typename T, typename Base >
struct m_item1
    : m_item_<Key,T,Base>
{
    typedef pair<Key,T> type1;
};

template< typename Key, typename T, typename Base >
struct m_item2
    : m_item_<Key,T,Base>
{
    typedef pair<Key,T> type2;
};

template< typename Key, typename T, typename Base >
struct m_item3
    : m_item_<Key,T,Base>
{
    typedef pair<Key,T> type3;
};

template< typename Key, typename Base >
struct m_mask
    : Base
{
    typedef void_   key_;
    typedef Base    base;

    typedef typename prior< typename Base::size >::type  size;

    typedef typename x_order_impl<Base,Key>::type old_order_;
    
    friend aux::no_tag operator/(m_mask const&, aux::type_wrapper<Key>*);
    friend aux::yes_tag operator%(m_mask const&, long_<old_order_::value>*);
};


#endif

}}

#endif // BOOST_MPL_MAP_AUX_ITEM_HPP_INCLUDED
