///////////////////////////////////////////////////////////////////////////////
// action_matcher.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ACTION_MATCHER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_CORE_MATCHER_ACTION_MATCHER_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/version.hpp>
#include <boost/ref.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/action.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#if BOOST_VERSION >= 103500
# include <boost/xpressive/proto/fusion.hpp>
# include <boost/fusion/sequence/view/transform_view.hpp>
# include <boost/fusion/functional/invocation/invoke.hpp>
# include <boost/fusion/algorithm/transformation/push_front.hpp>
# include <boost/fusion/algorithm/transformation/pop_front.hpp>
#endif

namespace boost { namespace xpressive { namespace detail
{

    #if BOOST_VERSION >= 103500
    ///////////////////////////////////////////////////////////////////////////////
    // mem_ptr_eval
    //  Rewrites expressions of the form x->*foo(a) into foo(x, a) and then
    //  evaluates them.
    template<typename Expr, typename Context>
    struct mem_ptr_eval
    {
        typedef typename remove_reference<typename mpl::if_<
            is_const<Expr>
          , typename proto::result_of::right<Expr>::const_reference
          , typename proto::result_of::right<Expr>::reference
        >::type>::type right_type;

        typedef typename remove_reference<typename mpl::if_<
            is_const<Expr>
          , typename proto::result_of::left<Expr>::const_reference
          , typename proto::result_of::left<Expr>::reference
        >::type>::type left_type;

        typedef
            typename proto::result_of::arg<
                typename proto::result_of::arg_c<right_type, 0>::type
            >::type
        function_type;

        typedef
            fusion::transform_view<
                typename fusion::result_of::push_front<
                    typename fusion::result_of::pop_front<proto::children<right_type> >::type const
                  , reference_wrapper<left_type>
                >::type const
              , proto::eval_fun<Context>
            >
        evaluated_args;

        typedef
            typename fusion::result_of::invoke<function_type, evaluated_args>::type
        result_type;

        result_type operator()(Expr &expr, Context &ctx) const
        {
            return fusion::invoke<function_type>(
                proto::arg(proto::arg_c<0>(proto::right(expr)))
              , evaluated_args(
                    fusion::push_front(fusion::pop_front(proto::children_of(proto::right(expr))), boost::ref(proto::left(expr)))
                  , proto::eval_fun<Context>(ctx)
                )
            );
        }
    };
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // action_context
    //
    struct action_context
    {
        explicit action_context(action_args_type *action_args)
          : action_args_(action_args)
        {}

        action_args_type const &args() const
        {
            return *this->action_args_;
        }

        // eval_terminal
        template<typename Expr, typename Arg = typename proto::result_of::arg<Expr>::type>
        struct eval_terminal
          : proto::default_eval<Expr, action_context const>
        {};

        template<typename Expr, typename Arg>
        struct eval_terminal<Expr, reference_wrapper<Arg> >
        {
            typedef Arg &result_type;
            result_type operator()(Expr &expr, action_context const &) const
            {
                return proto::arg(expr).get();
            }
        };

        template<typename Expr, typename Type, typename Int>
        struct eval_terminal<Expr, action_arg<Type, Int> >
        {
            typedef typename action_arg<Type, Int>::reference result_type;
            result_type operator()(Expr &expr, action_context const &ctx) const
            {
                action_args_type::const_iterator where_ = ctx.args().find(&typeid(proto::arg(expr)));
                if(where_ == ctx.args().end())
                {
                    throw regex_error(regex_constants::error_badarg, "An argument to an action was unspecified");
                }
                return proto::arg(expr).cast(where_->second);
            }
        };

        // eval
        template<typename Expr, typename Tag = typename Expr::tag_type>
        struct eval
          : proto::default_eval<Expr, action_context const>
        {};

        template<typename Expr>
        struct eval<Expr, proto::tag::terminal>
          : eval_terminal<Expr>
        {};

        #if BOOST_VERSION >= 103500
        template<typename Expr>
        struct eval<Expr, proto::tag::mem_ptr>
          : mem_ptr_eval<Expr, action_context const>
        {};
        #endif

    private:
        action_args_type *action_args_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // action
    //
    template<typename BidiIter, typename Actor>
    struct action
      : actionable<BidiIter>
    {
        action(Actor const &actor)
          : actionable<BidiIter>()
          , actor_(actor)
        {
        }

        virtual void execute(action_args_type *action_args) const
        {
            action_context const ctx(action_args);
            proto::eval(this->actor_, ctx);
        }

    private:
        Actor actor_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // subreg_transform
    //
    template<typename Grammar>
    struct subreg_transform
      : Grammar
    {
        subreg_transform();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::terminal<sub_match<typename State::iterator> >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            sub_match<typename State::iterator> const &sub = state.sub_matches_[ visitor ];
            return proto::as_expr(sub);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // mark_transform
    //
    template<typename Grammar>
    struct mark_transform
      : Grammar
    {
        mark_transform();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::terminal<sub_match<typename State::iterator> >
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &)
        {
            sub_match<typename State::iterator> const &sub = state.sub_matches_[ proto::arg(expr).mark_number_ ];
            return proto::as_expr(sub);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // by_ref_transform
    //
    template<typename Grammar>
    struct by_ref_transform
      : Grammar
    {
        by_ref_transform();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::terminal<typename proto::result_of::arg<Expr>::const_reference>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &)
        {
            return apply<Expr, State, Visitor>::type::make(proto::arg(expr));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // BindActionArgs
    //
    struct BindActionArgs
      : proto::or_<
            subreg_transform<proto::terminal<any_matcher> >
          , mark_transform<proto::terminal<mark_placeholder> >
          , by_ref_transform<proto::terminal<proto::_> >
          , proto::nary_expr<proto::_, proto::vararg<BindActionArgs> >
        >
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // action_matcher
    //
    template<typename Actor>
    struct action_matcher
      : quant_style<quant_none, 0, false>
    {
        int sub_;
        Actor actor_;

        action_matcher(Actor const &actor, int sub)
          : sub_(sub)
          , actor_(actor)
        {
        }

        template<typename BidiIter, typename Next>
        bool match(match_state<BidiIter> &state, Next const &next) const
        {
            // Bind the arguments
            typedef typename BindActionArgs::apply<Actor, match_state<BidiIter>, int>::type action_type;
            action<BidiIter, action_type> actor(BindActionArgs::call(this->actor_, state, this->sub_));

            // Put the action in the action list
            actionable<BidiIter> const **action_list_tail = state.action_list_tail_;
            *state.action_list_tail_ = &actor;
            state.action_list_tail_ = &actor.next;

            // Match the rest of the pattern
            if(next.match(state))
            {
                return true;
            }

            BOOST_ASSERT(0 == actor.next);
            // remove action from list
            *action_list_tail = 0;
            state.action_list_tail_ = action_list_tail;
            return false;
        }
    };

}}}

#endif
