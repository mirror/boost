//-----------------------------------------------------------------------------
// boost mpl/compose/f_gx_hy.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_COMPOSE_F_GX_HY_HPP_INCLUDED
#define BOOST_MPL_COMPOSE_F_GX_HY_HPP_INCLUDED

#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {

namespace aux {

template<
      typename F
    , typename G
    , typename H
    , typename X
    , typename Y
    >
struct f_gx_hy
{
 private:
    typedef typename apply1<G,X>::type P1;
    typedef typename apply1<H,Y>::type P2;
 
 public:
    typedef apply2<F,P1,P2> type;
};

} // namespace aux

template<
      typename F
    , typename G
    , typename H
    >
struct compose_f_gx_hy
{
    template< typename X, typename Y > struct apply
        : aux::f_gx_hy<F,G,H,X,Y>
    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(3,compose_f_gx_hy)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_COMPOSE_F_GX_HY_HPP_INCLUDED
