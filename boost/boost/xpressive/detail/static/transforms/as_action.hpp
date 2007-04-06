///////////////////////////////////////////////////////////////////////////////
// as_action.hpp
//
//  Copyright 2007 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_ACTION_HPP_EAN_04_05_2007
#define BOOST_XPRESSIVE_DETAIL_STATIC_TRANSFORMS_AS_ACTION_HPP_EAN_04_05_2007

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/sizeof.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/static.hpp>
#include <boost/xpressive/detail/static/transforms/as_quantifier.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/transform/arg.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // action_transform
    //  turn A[B] into (mark_begin(n) >> A >> mark_end(n) >> action_matcher<B>(n))
    template<typename Grammar>
    struct as_action
      : Grammar
    {
        as_action();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::result_of::left<Expr>::type expr_type;
            typedef typename proto::result_of::right<Expr>::type action_type;
            typedef typename proto::result_of::deep_copy<action_type>::type action_copy_type;

            typedef
                typename InsertMark::apply<expr_type, State, Visitor>::type
            marked_expr_type;

            typedef
                typename mpl::if_<
                    proto::matches<action_type, proto::terminal<predicate_placeholder<proto::_> > >
                  , predicate_matcher<action_copy_type>
                  , action_matcher<action_copy_type>
                >::type
            matcher_type;

            typedef
                typename proto::right_shift<
                    marked_expr_type
                  , typename proto::terminal<matcher_type>::type
                >::type
            type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef apply<Expr, State, Visitor> apply_type;
            typedef typename apply_type::matcher_type matcher_type;

            typename apply_type::marked_expr_type marked_expr =
                marker_transform::call(proto::left(expr), state, visitor);

            typename apply_type::type that =
            {
                marked_expr
              , {
                    matcher_type
                    (
                        proto::deep_copy(proto::right(expr))
                      , proto::arg(proto::left(marked_expr)).mark_number_
                    )
                }
            };
            return that;
        }
    };

}}}

#endif
