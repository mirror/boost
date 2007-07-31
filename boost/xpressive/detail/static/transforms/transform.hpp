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

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform/fold.hpp>
#include <boost/xpressive/detail/static/transforms/as_matcher.hpp>
#include <boost/xpressive/detail/static/transforms/as_alternate.hpp>
#include <boost/xpressive/detail/static/transforms/as_sequence.hpp>
#include <boost/xpressive/detail/static/transforms/as_quantifier.hpp>
#include <boost/xpressive/detail/static/transforms/as_marker.hpp>
#include <boost/xpressive/proto/transform/compose.hpp>

namespace boost { namespace xpressive { namespace detail
{
    struct Grammar;
    
    struct Alternate
      : proto::bitwise_or< Grammar, Grammar >
    {};

    struct Terminal
      : proto::terminal< proto::_ >
    {};

    struct GreedyQuantifier
      : proto::or_<
            proto::unary_plus<Grammar>
          , proto::unary_star<Grammar>
          , proto::logical_not<Grammar>
        >
    {};

    struct NonGreedyQuantifier
      : proto::unary_minus<GreedyQuantifier>
    {};

    struct SimpleGreedyQuantifier
      : proto::and_<
            GreedyQuantifier
          , proto::if_<use_simple_repeat<proto::result_of::arg<mpl::_>, proto::tag_of<proto::result_of::arg<mpl::_> > > >
          , proto::transform::arg<GreedyQuantifier>
        >
    {};

    struct DefaultGreedyQuantifier
      : proto::and_<
            GreedyQuantifier
          , proto::if_<mpl::not_<use_simple_repeat<proto::result_of::arg<mpl::_>, proto::tag_of<proto::result_of::arg<mpl::_> > > > >
        >
    {};

    struct Mark
      : proto::assign<basic_mark_tag, Grammar>
    {};

    struct Sequence
      : proto::right_shift<Grammar, Grammar>
    {};

    // These sub-expressions generate simple matcher types
    // that must be placed in sequence.
    struct NonSequence
      : proto::or_<
            as_matcher<Terminal>
          , as_alternate<Alternate>
          , as_simple_quantifier<SimpleGreedyQuantifier, false>
          , proto::transform::compose<
                proto::and_<
                    proto::unary_minus<SimpleGreedyQuantifier>
                  , proto::transform::arg<proto::_>
                >
              , as_simple_quantifier<SimpleGreedyQuantifier, true>
            >
        >
    {};

    // These sub-expressions require further processing.
    struct Transforms
      : proto::or_<
            as_default_quantifier<DefaultGreedyQuantifier, false>
          , proto::transform::compose<
                proto::and_<
                    proto::unary_minus<DefaultGreedyQuantifier>         // match -(GreedyQuant) ...
                  , proto::transform::arg<proto::_>                     // and strip off the - ...
                >
              , as_default_quantifier<DefaultGreedyQuantifier, true>    // and process the GreedyQuat
            >
          , as_marker<Mark>
        >
    {};

    struct Grammar
      : proto::or_<
            proto::transform::reverse_fold<Sequence>
          , proto::transform::compose<Transforms, Grammar>
          , in_sequence<NonSequence>
        >
    {};

    template<typename Expr, typename Visitor>
    typename Grammar::apply<Expr, end_xpression, Visitor>::type
    transform(Expr const &expr, Visitor &visitor)
    {
        return Grammar::call(expr, end_xpression(), visitor);
    }

}}}

#endif
