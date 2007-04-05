///////////////////////////////////////////////////////////////////////////////
// as_quantifier.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_QUANTIFIER_HPP_EAN_04_01_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_QUANTIFIER_HPP_EAN_04_01_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/detail/static/transforms/fold_to_xxx.hpp>
#include <boost/xpressive/detail/core/matcher/alternate_matcher.hpp>
#include <boost/xpressive/detail/utility/cons.hpp>
#include <boost/xpressive/proto/transform/branch.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>
#include <boost/xpressive/proto/transform/compose.hpp>
#include <boost/xpressive/proto/transform/conditional.hpp>

// BUGBUG move quant traits here
#include <boost/xpressive/detail/static/productions/quant_traits.hpp>
#include <boost/xpressive/detail/static/productions/quant_transforms.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // as_simple_quantifier
    template<typename Grammar, bool Greedy>
    struct as_simple_quantifier
      : Grammar
    {
        as_simple_quantifier();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef simple_repeat_matcher<
                typename Grammar::template apply<Expr, true_xpression, Visitor>::type
              , Greedy
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typename Grammar::template apply<Expr, true_xpression, Visitor>::type const &xpr =
                Grammar::call(expr, true_xpression(), visitor);
            return typename apply<Expr, State, Visitor>::type(
                xpr
              , min_type<typename Expr::tag_type>::value
              , max_type<typename Expr::tag_type>::value
              , xpr.get_width().value()
            );
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // add_hidden_mark
    template<typename Grammar>
    struct add_hidden_mark
      : Grammar
    {
        add_hidden_mark();

        template<typename Expr, typename, typename>
        struct apply
          : proto::right_shift<
                proto::terminal<mark_begin_matcher>::type
              , typename proto::right_shift<
                    Expr
                  , proto::terminal<mark_end_matcher>::type
                >::type
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &visitor)
        {
            // we're inserting a hidden mark ... so grab the next hidden mark number.
            int mark_nbr = visitor.get_hidden_mark();
            mark_begin_matcher begin(mark_nbr);
            mark_end_matcher end(mark_nbr);

            typename apply<Expr, State, Visitor>::type that = {{begin}, {expr, {end}}};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // InsertMark
    struct InsertMark
      : proto::or_<
            proto::assign<basic_mark_tag, proto::_>
          , add_hidden_mark<proto::_>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // as_default_quantifier_impl
    template<bool Greedy, uint_t Min, uint_t Max>
    struct as_default_quantifier_impl
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::right_shift<
                proto::terminal<repeat_begin_matcher>::type
              , typename proto::right_shift<
                    typename InsertMark::apply<typename proto::result_of::arg<Expr>::type, State, Visitor>::type
                  , typename proto::terminal<repeat_end_matcher<Greedy> >::type
                >::type
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            // Ensure this sub-expression is book-ended with mark matchers
            typedef typename proto::result_of::arg<Expr>::type arg_type;
            typename InsertMark::apply<arg_type, State, Visitor>::type const &
                marked_sub = InsertMark::call(proto::arg(expr), state, visitor);
            
            // Get the mark_number from the begin_mark_matcher
            int mark_number = proto::arg(proto::left(marked_sub)).mark_number_;
            BOOST_ASSERT(0 != mark_number);

            unsigned min_ = min_type<typename Expr::tag_type>::value;
            unsigned max_ = max_type<typename Expr::tag_type>::value;

            repeat_begin_matcher begin(mark_number);
            repeat_end_matcher<Greedy> end(mark_number, min_, max_);

            typename apply<Expr, State, Visitor>::type that = {{begin}, {marked_sub, {end}}};
            return that;
        }
    };

    // TODO use optional_matcher and optional_mark_matcher
    template<bool Greedy>
    struct make_optional_
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::bitwise_or<
                Expr
              , proto::terminal<epsilon_matcher>::type
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typename apply<Expr, State, Visitor>::type that = {expr, {epsilon_matcher()}};
            return that;
        }
    };

    template<>
    struct make_optional_<false>
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::bitwise_or<
                proto::terminal<epsilon_matcher>::type
              , Expr
            >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typename apply<Expr, State, Visitor>::type that = {{epsilon_matcher()}, expr};
            return that;
        }
    };


    ///////////////////////////////////////////////////////////////////////////////
    // as_default_quantifier_impl
    template<bool Greedy, uint_t Max>
    struct as_default_quantifier_impl<Greedy, 0, Max>
      : proto::trans::compose<
            as_default_quantifier_impl<Greedy, 1, Max>
          , make_optional_<Greedy>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // as_default_quantifier_impl
    template<bool Greedy>
    struct as_default_quantifier_impl<Greedy, 0, 1>
      : proto::trans::compose<
            proto::trans::arg<proto::_>
          , make_optional_<Greedy>
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // as_default_quantifier
    template<typename Grammar, bool Greedy>
    struct as_default_quantifier
      : Grammar
    {
        as_default_quantifier();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : as_default_quantifier_impl<
                Greedy
              , min_type<typename Expr::tag_type>::value
              , max_type<typename Expr::tag_type>::value
            >::template apply<Expr, State, Visitor>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return as_default_quantifier_impl<
                Greedy
              , min_type<typename Expr::tag_type>::value
              , max_type<typename Expr::tag_type>::value
            >::call(expr, state, visitor);
        }
    };

}}}

#endif
