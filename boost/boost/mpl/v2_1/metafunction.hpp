//-----------------------------------------------------------------------------
// boost mpl/v2_1/metafunction.hpp header file
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

#ifndef BOOST_MPL_V2_1_METAFUNCTION_HPP_INCLUDED
#define BOOST_MPL_V2_1_METAFUNCTION_HPP_INCLUDED

#include "boost/mpl/v2_1/expr.hpp"
#include "boost/mpl/v2_1/metafunction_base.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/identity.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"

#define BOOST_MPL_AUX_METAFUNCTION_PARAM(unused, prefix, n, param) \
    BOOST_PP_COMMA_IF(n) prefix() param \
/**/

#define METAFUNCTION(name, params, body) \
struct name : metafunction_base \
{ \
    template< \
          BOOST_PP_SEQ_FOR_EACH_I( \
              BOOST_MPL_AUX_METAFUNCTION_PARAM \
            , BOOST_PP_IDENTITY(typename) \
            , params \
            ) \
        > \
    struct apply \
        : boost::mpl::v2_1::expr< body > \
    { \
    }; \
}; \
/**/

#endif // BOOST_MPL_V2_1_METAFUNCTION_HPP_INCLUDED
