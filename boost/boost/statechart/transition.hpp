#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast



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
    template< class State, class EventBase >
    struct impl
    {
      template< class TransitionContext2 >
      static result react( State & stt, const EventBase & toEvent )
      {
        return stt.transit< Destination >( pTransitionAction,
          *polymorphic_downcast< const Event * >( &toEvent ) );
      }

      template<>
      static result react< detail::no_context >(
        State & stt, const EventBase & )
      {
        return stt.transit< Destination >();
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
        return impl< State, EventBase >::template react< TransitionContext >(
          stt, evt );
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
