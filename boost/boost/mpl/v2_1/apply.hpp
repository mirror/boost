//-----------------------------------------------------------------------------
// boost mpl/v2_1/apply.hpp header file
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

#ifndef BOOST_MPL_V2_1_APPLY_HPP_INCLUDED
#define BOOST_MPL_V2_1_APPLY_HPP_INCLUDED

#include "boost/mpl/apply.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"

namespace boost { namespace mpl { namespace v2_1 {

#   define AUX_APPLY_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          BOOST_MPL_METAFUNCTION_MAX_ARITY \
        , param \
        ) \
    /**/

#   define AUX_APPLY_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          BOOST_MPL_METAFUNCTION_MAX_ARITY \
        , param \
        , value \
        ) \
    /**/


struct apply_impl
{
    template<
          typename F
        , AUX_APPLY_DEFAULT_PARAMS(typename T, mpl::void_)
        >
    struct apply
        : mpl::apply<F, AUX_APPLY_PARAMS(T)>
    {
    };
};

struct apply_ : apply_impl {};

#   undef AUX_APPLY_DEFAULT_PARAMS
#   undef AUX_APPLY_PARAMS

}}} // namespace boost::mpl::v2_1

#endif // BOOST_MPL_V2_1_APPLY_HPP_INCLUDED
