
#ifndef BOOST_MPL_REPLACE_IF_HPP_INCLUDED
#define BOOST_MPL_REPLACE_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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

#include <boost/mpl/transform.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(replace_if)

namespace aux {

template< typename Predicate, typename T >
struct replace_if_op
{
    template< typename U > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >
    {
#else
    {
        typedef typename if_<
              typename apply1<Predicate,U>::type
            , T
            , U
            >::type type;
#endif
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct replace_if
    : transform1<
          Sequence
        , protect< aux::replace_if_op<Predicate,T> >
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(3, replace_if)

}}

#endif // BOOST_MPL_REPLACE_IF_HPP_INCLUDED
