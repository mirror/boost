#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>

#include <boost/mpl/if.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast
#include <boost/type_traits/is_same.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



//////////////////////////////////////////////////////////////////////////////
struct no_context
{
  template< class Event >
  void no_function( const Event & );
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
template< class Event, class Destination,
          class TransitionContext = detail::no_context,
          void ( TransitionContext::*pTransitionAction )( const Event & ) =
            &detail::no_context::no_function< Event > >
struct transition
{
  private:
    //////////////////////////////////////////////////////////////////////////
    struct react_with_transition_action_impl
    {
      template< class State, class EventBase >
      static result react( State & stt, const EventBase & toEvent )
      {
        return stt.template transit< Destination >( pTransitionAction,
          *polymorphic_downcast< const Event * >( &toEvent ) );
      }
    };

    struct react_without_transition_action_impl
    {
      template< class State, class EventBase >
      static result react( State & stt, const EventBase & )
      {
        return stt.template transit< Destination >();
      }
    };

  public:
    //////////////////////////////////////////////////////////////////////////
    template< class State, class EventBase, class IdType >
    static result react(
      State & stt, const EventBase & evt, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        typedef typename mpl::if_<
          is_same< TransitionContext, detail::no_context >,
          react_without_transition_action_impl,
          react_with_transition_action_impl
        >::type impl;
        return impl::react( stt, evt );
      }
      else
      {
        return no_reaction;
      }
    }
};



} // namespace fsm
} // namespace boost



#endif
