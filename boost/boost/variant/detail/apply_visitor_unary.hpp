//-----------------------------------------------------------------------------
// boost variant/detail/apply_visitor_unary.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP
#define BOOST_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP

#include "boost/detail/workaround.hpp"

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include "boost/variant/detail/define_forwarding_func.hpp"
#endif

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor, variant)
//
// Visits visitable with visitor.
//

#define BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(CV1_, CV2_)  \
    template <                                                          \
          typename Visitor                                              \
        , BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, typename T)   \
        >                                                               \
    inline                                                              \
        typename Visitor::result_type                                   \
    apply_visitor(                                                      \
          CV1_ Visitor& visitor                                         \
        , CV2_ boost::variant<                                          \
              BOOST_PP_ENUM_PARAMS(BOOST_VARIANT_LIMIT_TYPES, T)        \
            >& var                                                      \
        )                                                               \
    {                                                                   \
        return var.apply_visitor(visitor);                              \
    }                                                                   \
    /**/
#
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC, 2)
#else
    BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)
    BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(BOOST_VARIANT_AUX_NOTHING,const)
#endif
#
#undef BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC

} // namespace boost

#endif // BOOST_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP
