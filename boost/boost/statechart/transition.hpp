#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/event_handler.hpp>

#include <boost/cast.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



struct no_context
{
  template< class Event >
  void no_function( const Event & );
};



template< class Derived, class Event, class Destination,
          class TransitionContext,
          void ( TransitionContext::*pTransitionAction )( const Event & ) >
class transition_handler : public event_handler< Event >
{
  private:
    virtual bool handle_event( const Event & evt )
    {
      return handle_event_impl< TransitionContext >( evt );
    }

    template< class TransitionContext >
    bool handle_event_impl( const Event & evt )
    {
      return polymorphic_downcast< Derived * >( this )->
        transit_to< Destination >( pTransitionAction, evt );
    }

    template<>
    bool handle_event_impl< no_context >( const Event & )
    {
      return polymorphic_downcast< Derived * >( this )->
        transit_to< Destination >();
    }
};



} // namespace detail



template< class Event, class Destination,
          class TransitionContext = detail::no_context,
          void ( TransitionContext::*pTransitionAction )( const Event & ) =
            &detail::no_context::no_function< Event > >
struct transition
{
  template< class Derived >
  struct apply
  {
    typedef detail::transition_handler<
      Derived, Event, Destination,
      TransitionContext, pTransitionAction > type;
  };
};



} // namespace fsm
} // namespace boost



#endif
