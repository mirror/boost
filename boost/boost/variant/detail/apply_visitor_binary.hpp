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

#include "boost/variant/detail/generic_result_type.hpp"
#include "boost/variant/detail/define_forwarding_func.hpp"

#include "boost/variant/detail/apply_visitor_unary.hpp"

#include "boost/variant/variant_fwd.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// function template apply_visitor(visitor, visitable1, visitable2)
//
// Visits visitable1 and visitable2 such that their values (which we
// shall call x and y, respectively) are used as arguments in the
// expression visitor(x, y).
//

namespace detail { namespace variant {

template <typename Visitor, typename Value1>
class apply_visitor_binary_invoke
{
public: // visitor typedefs

    typedef typename Visitor::result_type
        result_type;

private: // representation

    Visitor& visitor_;
    Value1& value1_;

public: // structors

    apply_visitor_binary_invoke(Visitor& visitor, Value1& value1)
        : visitor_(visitor)
        , value1_(value1)
    {
    }

public: // visitor interfaces

    template <typename Value2>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(Value2& value2)
    {
        return visitor_(value1_, value2);
    }

};

template <typename Visitor, typename Visitable2>
class apply_visitor_binary_unwrap
{
public: // visitor typedefs

    typedef typename Visitor::result_type
        result_type;

private: // representation

    Visitor& visitor_;
    Visitable2& visitable2_;

public: // structors

    apply_visitor_binary_unwrap(Visitor& visitor, Visitable2& visitable2)
        : visitor_(visitor)
        , visitable2_(visitable2)
    {
    }

public: // visitor interfaces

    template <typename Value1>
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(result_type)
    operator()(Value1& value1)
    {
        apply_visitor_binary_invoke<
              Visitor
            , Value1
            > invoker(visitor_, value1);

        return boost::apply_visitor(invoker, visitable2_);
    }

};

}} // namespace detail::variant

#define BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(CV1_, CV2_, CV3_) \
    template <                                          \
          typename Visitor                              \
        , BOOST_VARIANT_ENUM_PARAMS(typename T)         \
        , BOOST_VARIANT_ENUM_PARAMS(typename U)         \
        >                                               \
    inline                                              \
        BOOST_VARIANT_AUX_GENERIC_RESULT_TYPE(          \
              typename Visitor::result_type             \
            )                                           \
    apply_visitor(                                      \
          CV1_ Visitor& visitor                         \
        , CV2_ boost::variant<                          \
              BOOST_VARIANT_ENUM_PARAMS(T)              \
            >& var1                                     \
        , CV3_ boost::variant<                          \
              BOOST_VARIANT_ENUM_PARAMS(U)              \
            >& var2                                     \
        )                                               \
    {                                                   \
        detail::variant::apply_visitor_binary_unwrap<   \
              CV1_ Visitor                              \
            , CV2_ boost::variant<                      \
                  BOOST_VARIANT_ENUM_PARAMS(U)          \
                >                                       \
            > unwrapper(visitor, var2);                 \
                                                        \
        return boost::apply_visitor(unwrapper, var1);   \
    }                                                   \
    /**/

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC(BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY, 3)
#else
    BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)
    BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING,const)
    BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(BOOST_VARIANT_AUX_NOTHING,const,BOOST_VARIANT_AUX_NOTHING)
    BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY(BOOST_VARIANT_AUX_NOTHING,const,const)
#endif

#undef BOOST_VARIANT_AUX_APPLY_VISITOR_BINARY

} // namespace boost

#endif // BOOST_VARIANT_DETAIL_APPLY_VISITOR_BINARY_HPP
