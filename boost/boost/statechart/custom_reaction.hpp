#ifndef BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
#define BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast



namespace boost
{
namespace fsm
{



class event_base;
  
//////////////////////////////////////////////////////////////////////////////
template< class Event >
class custom_reaction
{
  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    template< class State, class EventBase, class IdType >
    static result react(
      State & stt, const EventBase & evt, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        return stt.react( *polymorphic_downcast< const Event * >( &evt ) );
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
