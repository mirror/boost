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

#include "boost/config.hpp"
#include "boost/variant/detail/define_forwarding_func.hpp"
#include "boost/variant/detail/generic_result_type.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor, variant)
//
// Visits variant with visitor.
//

#define BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(CV1_, CV2_)  \
    template <                                      \
          typename Visitor                          \
        , BOOST_VARIANT_ENUM_PARAMS(typename T)     \
        >                                           \
    inline                                          \
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(      \
              typename Visitor::result_type         \
            )                                       \
    apply_visitor(                                  \
          CV1_ Visitor& visitor                     \
        , CV2_ boost::variant<                      \
              BOOST_VARIANT_ENUM_PARAMS(T)          \
            >& var                                  \
        )                                           \
    {                                               \
        return var.apply_visitor(visitor);          \
    }                                               \
    /**/
#
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC, 2)
#else
    BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)
    BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC(BOOST_VARIANT_AUX_NOTHING,const)
#endif
#
#undef BOOST_VARIANT_AUX_APPLY_VISITOR_FUNC

} // namespace boost

#endif // BOOST_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP
