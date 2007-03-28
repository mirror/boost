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

#include <boost/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/core/quant_style.hpp>
#include <boost/xpressive/detail/core/action.hpp>
#include <boost/xpressive/detail/core/state.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/context.hpp>
#include <boost/xpressive/proto/fusion.hpp>
#include <boost/fusion/sequence/view/transform_view.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // action_context
    //
    struct action_context
    {
        template<typename Expr, typename Tag = typename Expr::tag_type>
        struct eval
          : proto::default_eval<Expr, action_context>
        {};

        template<typename Expr>
        struct eval<Expr, proto::tag::mem_ptr>
        {
            typedef typename proto::result_of::right<Expr>::type right_type;
            
            typedef
                typename proto::result_of::arg<
                    typename proto::result_of::arg_c<right_type, 0>::type
                >::type
            function_type;

            typedef 
                fusion::transform_view<
                    typename fusion::result_of::push_front<
                        typename fusion::result_of::pop_front<proto::children<right_type const> >::type const
                      , typename proto::result_of::left<Expr>::type
                    >::type const
                  , proto::eval_fun<action_context>
                >
            evaluated_args;

            typedef
                typename fusion::result_of::invoke<function_type, evaluated_args>::type
            result_type;

            result_type operator()(Expr const &expr, action_context &ctx) const
            {
                return fusion::invoke<function_type>(
                    proto::arg(proto::arg_c<0>(proto::right(expr)))
                  , evaluated_args(
                        fusion::push_front(fusion::pop_front(proto::children_of(proto::right(expr))), proto::left(expr))
                      , proto::eval_fun<action_context>(ctx)
                    )
                );
            }
        };
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

        virtual void execute() const
        {
            action_context ctx;
            this->actor_.eval(ctx);
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
    // action_arg_transform
    //
    template<typename Grammar>
    struct action_arg_transform
      : Grammar
    {
        action_arg_transform();

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::result_of::arg<Expr>::type action_arg_type;
            typedef typename action_arg_type::reference arg_type;
            typedef typename proto::terminal<arg_type>::type type;
        };
        
        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &)
        {
            detail::action_args_type::iterator where = state.action_args_->find(&typeid(proto::arg(expr)));
            if(where == state.action_args_->end())
            {
                throw regex_error(regex_constants::error_badarg, "An argument to an action was unspecified");
            }
            return proto::as_arg(proto::arg(expr).cast(where->second));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // BindActionArgs
    //
    struct BindActionArgs
      : proto::or_<
            subreg_transform<proto::terminal<detail::any_matcher> >
          , mark_transform<proto::terminal<detail::mark_placeholder> >
          , action_arg_transform<proto::terminal<action_arg<proto::_, proto::_> > >
          , proto::terminal<proto::_>
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
        bool match(state_type<BidiIter> &state, Next const &next) const
        {
            // Bind the arguments
            typedef typename BindActionArgs::apply<Actor, state_type<BidiIter>, int>::type action_type;
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
