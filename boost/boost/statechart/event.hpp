#ifndef EVENT_HPP
#define EVENT_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_base.hpp>
#include <boost/fsm/event_base.hpp>
#include <boost/fsm/event_receiver.hpp>



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
class event : public event_base
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual const bool send_to( state_base & toState ) const
    {
      bool wasConsumed( false );
      state_base * pCurrentState( &toState );

      while ( !wasConsumed && ( pCurrentState != 0 ) )
      {
        event_receiver< Derived > * const pReceiver(
          dynamic_cast< event_receiver< Derived > * >( pCurrentState ) );

        if ( pReceiver != 0 )
        {
          wasConsumed =
            pReceiver->receive( static_cast< const Derived & >( *this ) );
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
