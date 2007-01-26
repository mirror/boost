///////////////////////////////////////////////////////////////////////////////
// quant_transforms.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005

#include <boost/mpl/or.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/static/productions/quant_traits.hpp>
#include <boost/xpressive/detail/static/productions/marker_transform.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // RepeaterPattern
    struct RepeaterPattern
      : proto::meta::right_shift<proto::meta::terminal<repeat_begin_matcher>, proto::_>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_marker_or_repeater_predicate
    struct is_marker_or_repeater_predicate
    {
        template<typename Expr, typename, typename>
        struct apply
          : proto::matches<typename Expr::arg0_type, proto::or_<MarkerPattern, RepeaterPattern> >
        {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    // simple_repeat_branch
    template<bool Greedy, uint_t Min, uint_t Max>
    struct simple_repeat_branch
    {
        typedef true_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<simple_repeat_matcher<Expr, Greedy>, State> type;
        };

        template<typename Expr, typename State>
        static static_xpression<simple_repeat_matcher<Expr, Greedy>, State>
        call(Expr const &expr, State const &state, dont_care)
        {
            std::size_t width = expr.get_width().value();
            return make_static(simple_repeat_matcher<Expr, Greedy>(expr, Min, Max, width), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // optional_branch
    template<bool Greedy>
    struct optional_branch
    {
        typedef alternate_end_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<optional_matcher<Expr, Greedy>, State> type;
        };

        template<typename Expr, typename State>
        static static_xpression<optional_matcher<Expr, Greedy>, State>
        call(Expr const &expr, State const &state, dont_care)
        {
            return make_static(optional_matcher<Expr, Greedy>(expr), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // optional_mark_branch
    template<bool Greedy>
    struct optional_mark_branch
    {
        typedef alternate_end_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<optional_mark_matcher<Expr, Greedy>, State> type;
        };

        template<typename Expr, typename State>
        static static_xpression<optional_mark_matcher<Expr, Greedy>, State>
        call(Expr const &expr, State const &state, dont_care)
        {
            return make_static(optional_mark_matcher<Expr, Greedy>(expr, expr.mark_number_), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // repeater_insert_transform
    template<bool Greedy, uint_t Min, uint_t Max>
    struct repeater_insert_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename proto::meta::right_shift
            <
                proto::meta::terminal<repeat_begin_matcher>::type
              , typename proto::meta::right_shift
                <
                    Expr
                  , typename proto::meta::terminal<repeat_end_matcher<Greedy> >::type
                >::type
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            // Get the mark_number from the begin_mark_matcher
            int mark_number = proto::arg(proto::left(expr)).mark_number_;
            BOOST_ASSERT(0 != mark_number);

            typename apply<Expr, State, Visitor>::type that =
                {
                    {repeat_begin_matcher(mark_number)}
                  , {
                        expr
                      , {repeat_end_matcher<Greedy>(mark_number, Min, Max)}
                    }
                };
            return that;
        }
    };

    template<bool Greedy>
    struct optional_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename proto::meta::logical_not<Expr>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            typename apply<Expr, State, Visitor>::type that = {expr};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // repeater_transform
    //   Insert repeat and marker matcher before and after the expression
    template<bool Greedy, uint_t Min, uint_t Max>
    struct repeater_transform
      : proto::compose_transforms
        <
            proto::conditional_transform
            <
                is_marker_predicate
              , marker_replace_transform
              , marker_insert_transform
            >
          , repeater_insert_transform<Greedy, Min, Max>
        >
    {
    };

    // transform *foo to !+foo
    template<bool Greedy, uint_t Max>
    struct repeater_transform<Greedy, 0, Max>
      : proto::compose_transforms
        <
            repeater_transform<Greedy, 1, Max>
          , optional_transform<Greedy>
        >
    {
        BOOST_MPL_ASSERT_RELATION(1, <, Max);
    };

}}}

#endif
