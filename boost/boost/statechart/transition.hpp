#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/result.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast

#include <typeinfo> // std::type_info



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
    template< class State >
    struct impl
    {
      template< class TransitionContext2 >
      static result react( State & stt, const event & toEvent )
      {
        return stt.transit< Destination >( pTransitionAction,
          *polymorphic_downcast< const Event * >( &toEvent ) );
      }

      template<>
      static result react< detail::no_context >(
        State & stt, const event & )
      {
        return stt.transit< Destination >();
      }
    };

  public:
    //////////////////////////////////////////////////////////////////////////
    template< class State >
    static result react(
      State & stt, const event & evt, const std::type_info & eventType )
    {
      if ( eventType == typeid( const Event ) )
      {
        return impl< State >::react< TransitionContext >( stt, evt );
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
