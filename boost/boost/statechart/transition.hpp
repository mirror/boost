#ifndef BOOST_FSM_TRANSITION_HPP_INCLUDED
#define BOOST_FSM_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/reaction.hpp>

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
class transition_reaction : public reaction< Event >
{
  private:
    virtual result react( const Event & toEvent )
    {
      return react_impl< TransitionContext >( toEvent );
    }

    template< class TransitionContext >
    result react_impl( const Event & toEvent )
    {
      return polymorphic_downcast< Derived * >( this )->
        transit< Destination >( pTransitionAction, toEvent );
    }

    template<>
    result react_impl< no_context >( const Event & )
    {
      return polymorphic_downcast< Derived * >( this )->
        transit< Destination >();
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
    typedef detail::transition_reaction<
      Derived, Event, Destination,
      TransitionContext, pTransitionAction > type;
  };
};



} // namespace fsm
} // namespace boost



#endif
