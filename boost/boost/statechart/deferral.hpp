#ifndef BOOST_FSM_DEFERRAL_HPP_INCLUDED
#define BOOST_FSM_DEFERRAL_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class Event >
struct deferral
{
  template< class State, class EventBase, class IdType >
  static result react(
    State & stt, const EventBase &, const IdType & eventType )
  {
    if ( eventType == Event::static_type() )
    {
      return stt.defer_event();
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
