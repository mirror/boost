//-----------------------------------------------------------------------------
// boost variant/detail/apply_visitor_binary.hpp header file
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

#ifndef BOOST_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP
#define BOOST_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP

#include "boost/variant/detail/apply_visitor_unary.hpp"
#include "boost/variant/detail/define_forwarding_func.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor, visitable1, visitable2)
//
// Visits visitable1 and visitable2 such that their values (which we
// shall call x and y, respectively) are used as arguments in the
// expression visitor(x, y).
//

namespace detail { namespace visitor {

template <typename Visitor, typename Value1>
class binary_delay0
{
public:
    typedef typename Visitor::result_type
        result_type;

private:
    Visitor& visitor_;
    Value1& value1_;

public:
    binary_delay0(Visitor& visitor, Value1& value1)
        : visitor_(visitor)
        , value1_(value1)
    {
    }

    template <typename Value0>
    result_type operator()(Value0& value0)
    {
        return visitor_(value0, value1_);
    }

    template <typename Value0>
    result_type operator()(const Value0& value0)
    {
        return visitor_(value0, value1_);
    }
};

template <typename Visitor, typename Visitable1>
class binary_delay1
{
public:
    typedef typename Visitor::result_type
        result_type;

private:
    Visitor& visitor_;
    Visitable1& visitable1_;

public:
    binary_delay1(Visitor& visitor, Visitable1& visitable1)
        : visitor_(visitor)
        , visitable1_(visitable1)
    {
    }

#   define BOOST_AUX_BINARY_VISITOR_DELAY1_FUNC_OPERATOR(CV__)  \
    template <typename Visitable2>                              \
    result_type operator()(CV__ Visitable2& visitable2)         \
    {                                                           \
        binary_delay0<                                          \
              Visitor                                           \
            , CV__ Visitable2                                   \
            > delayer(visitor_, visitable2);                    \
        return boost::apply_visitor(delayer, visitable1_);      \
    }                                                           \
    /**/

    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(
          BOOST_AUX_BINARY_VISITOR_DELAY1_FUNC_OPERATOR
        , 1
        )

#   undef BOOST_AUX_BINARY_VISITOR_DELAY1_FUNC_OPERATOR
};

}} // namespace detail::visitor

#define BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(CV1__, CV2__, CV3__)         \
    template <typename Visitor, typename Visitable1, typename Visitable2>   \
    inline                                                                  \
        typename Visitor::result_type                                       \
    apply_visitor(                                                          \
          CV1__ Visitor& visitor                                            \
        , CV2__ Visitable1& visitable1                                      \
        , CV3__ Visitable2& visitable2                                      \
        )                                                                   \
    {                                                                       \
        detail::visitor::binary_delay1<                                     \
              CV1__ Visitor                                                 \
            , CV2__ Visitable1                                              \
            > delayer(visitor, visitable1);                                 \
        return boost::apply_visitor(delayer, visitable2);                   \
    }                                                                       \
    /**/

BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(
      BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY
    , 3
    )

#undef BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY

} // namespace boost

#endif // BOOST_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP
