#ifndef BOOST_FSM_EVENT_HPP_INCLUDED
#define BOOST_FSM_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/reaction.hpp>
#include <boost/fsm/event_base.hpp>
#include <boost/fsm/result.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast



namespace boost
{
namespace fsm
{



class state_base;



template< class Derived >
class event : public event_base
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual result send( detail::state_base & toState ) const
    {
      result reactionResult = do_forward_event;
      detail::state_base * pCurrentState( &toState );

      while ( ( reactionResult == do_forward_event ) &&
              ( pCurrentState != 0 ) )
      {
        detail::reaction< Derived > * const pReceiver =
          dynamic_cast< detail::reaction< Derived > * >( pCurrentState );

        if ( pReceiver != 0 )
        {
          enable_reaction( *pCurrentState );
          // the following statement could delete pCurrentState!
          reactionResult = pReceiver->react(
            *polymorphic_downcast< const Derived * >( this ) );
        }

        if ( reactionResult == do_forward_event )
        {
          // we can only safely access pCurrentState if the handler did not
          // return do_discard_event!
          pCurrentState = pCurrentState->outer_state_ptr();
        }
      }

      return reactionResult;
    }
};



} // namespace fsm
} // namespace boost



#endif
