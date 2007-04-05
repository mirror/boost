///////////////////////////////////////////////////////////////////////////////
// transform.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
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
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/compose.hpp>

namespace boost { namespace xpressive { namespace detail
{
    template<typename Tag>
    struct is_generic_quant_tag
      : mpl::false_
    {};

    template<unsigned Min, unsigned Max>
    struct is_generic_quant_tag<generic_quant_tag<Min, Max> >
      : mpl::true_
    {};

    struct Grammar;

    struct Sequence
      : proto::right_shift<Grammar, Grammar>
    {};

    struct Alternate
      : proto::bitwise_or< Grammar, Grammar >
    {};

    struct Terminal
      : proto::terminal< proto::_ >
    {};

    struct Mark
      : proto::assign<basic_mark_tag, Grammar>
    {};

    struct GreedyQuantifier
      : proto::or_<
            proto::unary_plus<Grammar>
          , proto::unary_star<Grammar>
          , proto::logical_not<Grammar>
          , proto::and_<
                proto::unary_expr<proto::_, Grammar>
              , proto::if_<is_generic_quant_tag<proto::tag_of<mpl::_> > >
            >
        >
    {};

    typedef
        use_simple_repeat<
            proto::result_of::arg<mpl::_>
          , proto::tag_of<proto::result_of::arg<mpl::_> >
        >
    UseSimpleRepeat;

    struct SimpleGreedyQuantifier
      : proto::and_<
            GreedyQuantifier
          , proto::if_<UseSimpleRepeat>
          , proto::trans::arg<GreedyQuantifier>
        >
    {};

    struct DefaultGreedyQuantifier
      : proto::and_<
            GreedyQuantifier
          , proto::if_<mpl::not_<UseSimpleRepeat> >
        >
    {};

    struct ListSet
      : proto::or_<
            proto::comma<ListSet, proto::terminal<char> >
          , proto::assign<set_initializer_type, proto::terminal<char> >
        >
    {};

    struct InvertibleMatcher
      : proto::or_<
            as_list_set<ListSet>
          , proto::trans::right<proto::subscript<set_initializer_type, as_set<Grammar> > >
          , proto::trans::arg<proto::unary_expr<lookahead_tag<true>, as_lookahead<Grammar> > >
          , proto::trans::arg<proto::unary_expr<lookbehind_tag<true>, as_lookbehind<Grammar> > >
        >
    {};

    // These sub-expressions generate simple matcher types
    // that must be placed in sequence.
    struct Matchers
      : proto::or_<
            as_matcher<Terminal>
          , as_alternate<Alternate>

          , as_simple_quantifier<SimpleGreedyQuantifier, true>
          , proto::trans::arg<proto::unary_minus<as_simple_quantifier<SimpleGreedyQuantifier, false> > >

          , InvertibleMatcher
          , inverse<proto::trans::arg<proto::complement<InvertibleMatcher> > >

          , proto::trans::arg<proto::unary_expr<keeper_tag, as_keeper<Grammar> > >
        >
    {};

    // These sub-expressions require further processing.
    struct Composites
      : proto::or_<
            as_default_quantifier<DefaultGreedyQuantifier, true>
          , proto::trans::arg<proto::unary_minus<as_default_quantifier<DefaultGreedyQuantifier, false> > >

          , as_marker<Mark>
        >
    {};

    struct Grammar
      : proto::or_<
            proto::trans::reverse_fold<Sequence>
          , proto::trans::compose<Composites, Grammar>
          , in_sequence<Matchers>
        >
    {};

    template<typename Expr, typename Visitor>
    typename Grammar::apply<Expr, end_xpression, Visitor>::type
    transform(Expr const &expr, Visitor &visitor)
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, Grammar>));
        return Grammar::call(expr, end_xpression(), visitor);
    }

}}}

#endif
