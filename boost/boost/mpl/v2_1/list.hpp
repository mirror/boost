//-----------------------------------------------------------------------------
// boost mpl/v2_1/list.hpp header file
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

#ifndef BOOST_MPL_V2_1_LIST_HPP_INCLUDED
#define BOOST_MPL_V2_1_LIST_HPP_INCLUDED

#include "boost/mpl/list.hpp"
#include "boost/mpl/limits/list.hpp"
#include "boost/preprocessor/enum_params_with_a_default.hpp"
#include "boost/preprocessor/enum_params.hpp"

namespace boost { namespace mpl { namespace v2_1 {

#   define AUX_LIST_PARAMS(param) \
    BOOST_PP_ENUM_PARAMS( \
          BOOST_MPL_LIMIT_LIST_SIZE \
        , param \
        ) \
    /**/

#   define AUX_LIST_DEFAULT_PARAMS(param, value) \
     BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          BOOST_MPL_LIMIT_LIST_SIZE \
        , param \
        , value \
        ) \
    /**/

struct list
{
    template<
          AUX_LIST_DEFAULT_PARAMS(typename T, void_)
        >
    struct apply
        : mpl::list< AUX_LIST_PARAMS(T) >
    {
    };
};

#   undef AUX_LIST_DEFAULT_PARAMS
#   undef AUX_LIST_PARAMS

}}} // namespace boost::mpl::v2_1

#endif // BOOST_MPL_V2_1_LIST_HPP_INCLUDED
