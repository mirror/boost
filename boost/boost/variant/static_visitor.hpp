//-----------------------------------------------------------------------------
// boost visitor/static_visitor.hpp header file
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

#ifndef BOOST_STATIC_VISITOR_HPP
#define BOOST_STATIC_VISITOR_HPP

#include "boost/config.hpp"
#include "boost/type_traits/is_base_and_derived.hpp"

#include "boost/mpl/aux_/lambda_support.hpp" // used by is_static_visitor

namespace boost {

//////////////////////////////////////////////////////////////////////////
// class template static_visitor
//
// An empty base class that typedefs the return type of a deriving static
// visitor. The class is analogous to std::unary_function in this role.
//

namespace detail {

    struct is_static_visitor_tag { };

} // namespace detail

template <typename R = void>
struct static_visitor
    : public detail::is_static_visitor_tag
{
    typedef R result_type;

protected:
    ~static_visitor() { }
};

//////////////////////////////////////////////////////////////////////////
// metafunction is_static_visitor
//
// Value metafunction indicates whether the specified type is a static
// visitor of any types.
// 
// NOTE: This template never needs to be specialized!
//
template <typename T>
struct is_static_visitor
{
    typedef typename is_base_and_derived<
          detail::is_static_visitor_tag
        , T
        >::type type;

    BOOST_STATIC_CONSTANT(bool, value = type::value);

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_static_visitor,(T))
};

} // namespace boost

#endif // BOOST_STATIC_VISITOR_HPP
