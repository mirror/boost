#ifndef BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
#define BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
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



//////////////////////////////////////////////////////////////////////////////
template< class Event >
struct custom_reaction
{
  template< class State >
  static result react(
    State & stt, const event & evt, const std::type_info & eventType )
  {
    if ( eventType == typeid( const Event ) )
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
