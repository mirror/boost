//-----------------------------------------------------------------------------
// boost/mpl/apply_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_APPLY_IF_HPP_INCLUDED
#define BOOST_MPL_APPLY_IF_HPP_INCLUDED

#include "boost/mpl/if.hpp"
#include "boost/mpl/aux_/apply.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(C)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(F1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(F2)
    >
struct apply_if
{
 private:
    typedef typename if_<C,F1,F2>::type nullary_func_;

 public:
    typedef typename BOOST_MPL_AUX_APPLY0(nullary_func_)::type type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,apply_if,(C,F1,F2))
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      bool C
    , typename F1
    , typename F2
    >
struct apply_if_c
{
 private:
    typedef typename if_c<C,F1,F2>::type nullary_func_;

 public:
    typedef typename BOOST_MPL_AUX_APPLY0(nullary_func_)::type type;
};

BOOST_MPL_AUX_VOID_SPEC(3, apply_if)
 
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_APPLY_IF_HPP_INCLUDED
