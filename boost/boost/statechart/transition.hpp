#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
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
        return impl< State, EventBase >::react< TransitionContext >(
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
