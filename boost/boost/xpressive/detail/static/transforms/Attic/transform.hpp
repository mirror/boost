///////////////////////////////////////////////////////////////////////////////
// transform.hpp
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_TRANSFORM_HPP_EAN_04_01_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_TRANSFORM_HPP_EAN_04_01_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/not.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/detail/static/transforms/as_matcher.hpp>
#include <boost/xpressive/detail/static/transforms/as_alternate.hpp>
#include <boost/xpressive/detail/static/transforms/as_sequence.hpp>
#include <boost/xpressive/detail/static/transforms/as_quantifier.hpp>
#include <boost/xpressive/detail/static/transforms/as_marker.hpp>
#include <boost/xpressive/detail/static/transforms/as_set.hpp>
#include <boost/xpressive/detail/static/transforms/as_independent.hpp>
#include <boost/xpressive/detail/static/transforms/as_modifier.hpp>
#include <boost/xpressive/detail/static/transforms/as_inverse.hpp>
#include <boost/xpressive/detail/static/transforms/as_action.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/compose.hpp>

namespace boost { namespace xpressive { namespace detail
{
    struct Grammar;

    ///////////////////////////////////////////////////////////////////////////
    // ListSet
    struct ListSet
      : proto::or_<
            proto::comma<ListSet, proto::terminal<char> >
          , proto::assign<set_initializer_type, proto::terminal<char> >
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // as_repeat
    template<typename Tag, bool Greedy>
    struct as_repeat
      : proto::trans::conditional<
            use_simple_repeat<proto::result_of::arg<mpl::_> >
          , as_simple_quantifier<proto::unary_expr<Tag, Grammar>, Greedy>
          , as_default_quantifier<proto::unary_expr<Tag, Grammar>, Greedy>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // NonGreedyRepeatCases
    struct NonGreedyRepeatCases
    {
        template<typename Tag>
        struct case_
          : proto::not_<proto::_>
        {};
    };

    template<>
    struct NonGreedyRepeatCases::case_<proto::tag::unary_star>
      : as_repeat<proto::tag::unary_star, false>
    {};

    template<>
    struct NonGreedyRepeatCases::case_<proto::tag::unary_plus>
      : as_repeat<proto::tag::unary_plus, false>
    {};

    template<>
    struct NonGreedyRepeatCases::case_<proto::tag::logical_not>
      : as_repeat<proto::tag::logical_not, false>
    {};

    template<uint_t Min, uint_t Max>
    struct NonGreedyRepeatCases::case_<generic_quant_tag<Min, Max> >
      : as_repeat<generic_quant_tag<Min, Max>, false>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // InvertibleCases
    struct InvertibleCases
    {
        template<typename Tag>
        struct case_
          : proto::not_<proto::_>
        {};
    };

    template<>
    struct InvertibleCases::case_<proto::tag::comma>
      : as_list_set<ListSet>
    {};

    template<>
    struct InvertibleCases::case_<proto::tag::assign>
      : as_list_set<ListSet>
    {};

    template<>
    struct InvertibleCases::case_<proto::tag::subscript>
      : proto::trans::right<proto::subscript<set_initializer_type, as_set<Grammar> > >
    {};

    template<>
    struct InvertibleCases::case_<lookahead_tag<true> >
      : proto::trans::arg<proto::unary_expr<lookahead_tag<true>, as_lookahead<Grammar> > >
    {};

    template<>
    struct InvertibleCases::case_<lookbehind_tag<true> >
      : proto::trans::arg<proto::unary_expr<lookbehind_tag<true>, as_lookbehind<Grammar> > >
    {};

    template<>
    struct InvertibleCases::case_<proto::tag::terminal>
      : proto::or_<
            as_matcher<proto::terminal<posix_charset_placeholder> >
          , as_matcher<proto::terminal<range_placeholder<proto::_> > >
          , as_matcher<proto::terminal<char> >
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Cases
    struct Cases
    {
        template<typename Tag>
        struct case_
          : proto::not_<proto::_>
        {};
    };

    template<>
    struct Cases::case_<proto::tag::right_shift>
      : proto::trans::reverse_fold<proto::right_shift<Grammar, Grammar> >
    {};

    template<>
    struct Cases::case_<proto::tag::terminal>
      : in_sequence<as_matcher<proto::terminal<proto::_> > >
    {};

    template<>
    struct Cases::case_<proto::tag::bitwise_or>
      : in_sequence<as_alternate<proto::bitwise_or<Grammar, Grammar> > >
    {};

    template<bool Greedy>
    struct Cases::case_<optional_tag<Greedy> >
      : in_sequence<proto::trans::arg<proto::unary_expr<optional_tag<Greedy>, as_optional<Grammar, Greedy> > > >
    {};

    template<>
    struct Cases::case_<proto::tag::unary_star>
      : proto::trans::compose<as_repeat<proto::tag::unary_star, true>, Grammar>
    {};

    template<>
    struct Cases::case_<proto::tag::unary_plus>
      : proto::trans::compose<as_repeat<proto::tag::unary_plus, true>, Grammar>
    {};

    template<>
    struct Cases::case_<proto::tag::logical_not>
      : proto::trans::compose<as_repeat<proto::tag::logical_not, true>, Grammar>
    {};

    template<uint_t Min, uint_t Max>
    struct Cases::case_<generic_quant_tag<Min, Max> >
      : proto::trans::compose<as_repeat<generic_quant_tag<Min, Max>, true>, Grammar>
    {};

    template<>
    struct Cases::case_<proto::tag::unary_minus>
      : proto::trans::compose<
            proto::trans::arg<proto::unary_minus<proto::switch_<NonGreedyRepeatCases> > >
          , Grammar
        >
    {};

    template<>
    struct Cases::case_<proto::tag::complement>
      : in_sequence<as_inverse<proto::trans::arg<proto::complement<proto::switch_<InvertibleCases> > > > >
    {};

    template<>
    struct Cases::case_<modifier_tag>
      : as_modifier<proto::binary_expr<modifier_tag, proto::_, Grammar> >
    {};

    template<>
    struct Cases::case_<lookahead_tag<true> >
      : in_sequence<proto::trans::arg<proto::unary_expr<lookahead_tag<true>, as_lookahead<Grammar> > > >
    {};

    template<>
    struct Cases::case_<lookbehind_tag<true> >
      : in_sequence<proto::trans::arg<proto::unary_expr<lookbehind_tag<true>, as_lookbehind<Grammar> > > >
    {};

    template<>
    struct Cases::case_<keeper_tag>
      : in_sequence<proto::trans::arg<proto::unary_expr<keeper_tag, as_keeper<Grammar> > > >
    {};

    template<>
    struct Cases::case_<proto::tag::comma>
      : in_sequence<as_list_set<ListSet> >
    {};

    template<>
    struct Cases::case_<proto::tag::assign>
      : proto::or_<
            proto::trans::compose<as_marker<proto::assign<basic_mark_tag, Grammar> >, Grammar>
          , in_sequence<as_list_set<ListSet> >
        >
    {};

    template<>
    struct Cases::case_<proto::tag::subscript>
      : proto::or_<
            in_sequence<proto::trans::right<proto::subscript<set_initializer_type, as_set<Grammar> > > >
          , proto::trans::compose<as_action<proto::subscript<Grammar, proto::_> >, Grammar>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Grammar
    struct Grammar
      : proto::switch_<Cases>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // transform()
    template<typename Expr, typename Visitor>
    typename Grammar::apply<Expr, end_xpression, Visitor>::type
    transform(Expr const &expr, Visitor &visitor)
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, Grammar>));
        return Grammar::call(expr, end_xpression(), visitor);
    }

}}}

#endif
