#ifndef BOOST_FSM_EVENT_HPP_INCLUDED
#define BOOST_FSM_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp>
#include <boost/fsm/detail/event_base.hpp>
#include <boost/fsm/detail/event_handler.hpp>

#include <boost/cast.hpp>


#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{



template< class Derived >
class event : public detail::event_base
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual bool send_to( detail::state_base & toState ) const
    {
      bool wasConsumed( false );
      detail::state_base * pCurrentState( &toState );

      while ( !wasConsumed && ( pCurrentState != 0 ) )
      {
        detail::event_handler< Derived > * const pReceiver =
          dynamic_cast< detail::event_handler< Derived > * >( pCurrentState );

        if ( pReceiver != 0 )
        {
          wasConsumed = pReceiver->handle_event(
            *polymorphic_downcast< const Derived * >( this ) );
        }

        if ( !wasConsumed )
        {
          pCurrentState = pCurrentState->outer_state_ptr();
        }
      }

      return wasConsumed;
    }
};



} // namespace fsm
} // namespace boost



#endif
