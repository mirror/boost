///////////////////////////////////////////////////////////////////////////////
// as_independent.hpp
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_INDEPENDENT_HPP_EAN_04_05_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_INDEPENDENT_HPP_EAN_04_05_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/sizeof.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform.hpp>

namespace boost { namespace xpressive { namespace detail
{
    struct keeper_tag
    {};

    struct lookahead_tag
    {};

    struct lookbehind_tag
    {};
}}}

namespace boost { namespace xpressive { namespace grammar_detail
{

    template<typename Grammar>
    struct as_lookahead : proto::callable
    {
        template<typename Sig> struct result {};

        template<typename This, typename Expr, typename State, typename Visitor>
        struct result<This(Expr, State, Visitor)>
        {
            typedef typename proto::result_of::arg<Expr>::type arg_type;
            typedef detail::lookahead_matcher<
                typename Grammar::template result<void(arg_type, detail::true_xpression, Visitor)>::type
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        typename result<void(Expr, State, Visitor)>::type
        operator ()(Expr const &expr, State const &, Visitor &visitor) const
        {
            return typename result<void(Expr, State, Visitor)>::type(
                Grammar()(proto::arg(expr), detail::true_xpression(), visitor)
              , false
            );
        }
    };

    template<typename Grammar>
    struct as_lookbehind : proto::callable
    {
        template<typename Sig> struct result {};

        template<typename This, typename Expr, typename State, typename Visitor>
        struct result<This(Expr, State, Visitor)>
        {
            typedef typename proto::result_of::arg<Expr>::type arg_type;
            typedef typename Grammar::template result<void(arg_type, detail::true_xpression, Visitor)>::type xpr_type;
            typedef detail::lookbehind_matcher<xpr_type> type;
        };

        template<typename Expr, typename State, typename Visitor>
        typename result<void(Expr, State, Visitor)>::type
        operator ()(Expr const &expr, State const &, Visitor &visitor) const
        {
            typedef typename result<void(Expr, State, Visitor)>::xpr_type xpr_type;
            xpr_type const &expr2 = Grammar()(proto::arg(expr), detail::true_xpression(), visitor);
            std::size_t width = expr2.get_width().value();
            return detail::lookbehind_matcher<xpr_type>(expr2, width, false);
        }
    };

    template<typename Grammar>
    struct as_keeper : proto::callable
    {
        template<typename Sig> struct result {};

        template<typename This, typename Expr, typename State, typename Visitor>
        struct result<This(Expr, State, Visitor)>
        {
            typedef typename proto::result_of::arg<Expr>::type arg_type;
            typedef detail::keeper_matcher<
                typename Grammar::template result<void(arg_type, detail::true_xpression, Visitor)>::type
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        typename result<void(Expr, State, Visitor)>::type
        operator ()(Expr const &expr, State const &, Visitor &visitor) const
        {
            return typename result<void(Expr, State, Visitor)>::type(
                Grammar()(proto::arg(expr), detail::true_xpression(), visitor)
            );
        }
    };

}}}

#endif
