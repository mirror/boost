//-----------------------------------------------------------------------------
// boost variant/visitor_ptr.hpp header file
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

#ifndef BOOST_VARIANT_VISITOR_PTR_HPP
#define BOOST_VARIANT_VISITOR_PTR_HPP

#include "boost/variant/bad_visit.hpp"
#include "boost/variant/static_visitor.hpp"

#include "boost/type_traits/add_reference.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template visitor_ptr
//
// Adapts a function pointer for use as visitor capable of handling
// values of a single type. Throws bad_visit if inappropriately applied.
//
template <typename T, typename R>
class visitor_ptr_t
    : public static_visitor<R>
{
private: // representation

    typedef R (*visitor_t)(T);

    visitor_t visitor_;

public: // typedefs

    typedef R result_type;

private: // private typedefs

    typedef typename add_reference<T>::type
        argument_fwd_type;

public: // structors

    explicit visitor_ptr_t(visitor_t visitor)
      : visitor_(visitor)
    {
    }

public: // static visitor interfaces

    result_type operator()(argument_fwd_type operand) const
    {
        return visitor_(operand);
    }

    template <typename U>
    result_type operator()(const U& operand) const
    {
        throw bad_visit();
    }

};

template <typename R, typename T>
inline visitor_ptr_t<T,R> visitor_ptr(R (*visitor)(T))
{
    return visitor_ptr_t<T,R>(visitor);
}

} // namespace boost

#endif// BOOST_VISITOR_VISITOR_PTR_HPP
