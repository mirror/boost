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

namespace boost { namespace xpressive { namespace detail
{

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
            proto::context<> ctx;
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
    // BindActionArgs
    //
    struct BindActionArgs
      : proto::or_<
            subreg_transform< proto::terminal<detail::any_matcher> >
          , mark_transform< detail::mark_tag >
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
