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
#include "boost/detail/workaround.hpp"
#include "boost/variant/detail/generic_result_type.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor, visitable)
//
// Visits visitable with visitor.
//

template <typename Visitor, typename Visitable>
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
apply_visitor(Visitor& visitor, Visitable& visitable)
{
    return visitable.apply_visitor(visitor);
}

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1200)

template <typename Visitor, typename Visitable>
inline
    BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(typename Visitor::result_type)
apply_visitor(const Visitor& visitor, Visitable& visitable)
{
    return visitable.apply_visitor(visitor);
}

#endif // MSVC6 exclusion

} // namespace boost

#endif // BOOST_VARIANT_DETAIL_APPLY_VISITOR_UNARY_HPP
