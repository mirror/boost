//-----------------------------------------------------------------------------
// boost variant/detail/apply_visitor_delayed.hpp header file
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

#ifndef BOOST_VISITOR_APPLY_VISITOR_DELAYED_HPP
#define BOOST_VISITOR_APPLY_VISITOR_DELAYED_HPP

#include "boost/variant/detail/apply_visitor_unary.hpp"
#include "boost/variant/detail/apply_visitor_binary.hpp"

#include "boost/variant/detail/define_forwarding_func.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor)
//
// Returns a function object, overloaded for unary and binary usage, that
// visits its arguments using visitor (or a copy of visitor) via
//  * apply_visitor( visitor, [argument] )
// under unary invocation, or
//  * apply_visitor( visitor, [argument1], [argument2] )
// under binary invocation.
//
// NOTE: Unlike other apply_visitor forms, the visitor object must be
//   non-const; this prevents user from giving temporary, to disastrous
//   effect (i.e., returned function object would have dead reference).
//

template <typename Visitor>
class apply_visitor_delayed_t
{
public: // typedefs

    typedef typename Visitor::result_type
        result_type;

private: // representation

    Visitor& visitor_;

public: // structors

    explicit apply_visitor_delayed_t(Visitor& visitor)
      : visitor_(visitor)
    {
    }

public: // unary function operators

#   define BOOST_AUX_APPLY_VISITOR_DELAYED_T_UNARY_FUNC_OPERATOR(CV__)    \
    template <typename Visitable>                       \
    result_type operator()(                             \
          CV__ Visitable& visitable                     \
        )                                               \
    {                                                   \
        apply_visitor(visitor_, visitable);             \
    }                                                   \
    /**/

    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(
          BOOST_AUX_APPLY_VISITOR_DELAYED_T_UNARY_FUNC_OPERATOR
        , 1
        )

#   undef BOOST_AUX_APPLY_VISITOR_DELAYED_T_UNARY_FUNC_OPERATOR

public: // binary function operators

#   define BOOST_AUX_APPLY_VISITOR_DELAYED_T_BINARY_FUNC_OPERATOR(CV1__, CV2__)   \
    template <typename Visitable1, typename Visitable2>         \
    result_type operator()(                                     \
          CV1__ Visitable1& visitable1                          \
        , CV2__ Visitable2& visitable2                          \
        )                                                       \
    {                                                           \
        apply_visitor(visitor_, visitable1, visitable2);        \
    }                                                           \
    /**/

    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(
          BOOST_AUX_APPLY_VISITOR_DELAYED_T_BINARY_FUNC_OPERATOR
        , 2
        )

#   undef BOOST_AUX_APPLY_VISITOR_DELAYED_T_BINARY_FUNC_OPERATOR

};

template <typename Visitor>
inline apply_visitor_delayed_t<Visitor> apply_visitor(Visitor& visitor)
{
    return apply_visitor_delayed_t<Visitor>(visitor);
}

} // namespace boost

#endif // BOOST_VISITOR_APPLY_VISITOR_DELAYED_HPP
