#ifndef BOOST_FSM_TERMINATION_HPP_INCLUDED
#define BOOST_FSM_TERMINATION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/result.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class Event >
struct termination
{
  template< class State, class EventBase, class IdType >
  static result react(
    State & stt, const EventBase &, const IdType & eventType )
  {
    if ( eventType == Event::static_type() )
    {
      return stt.terminate();
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
