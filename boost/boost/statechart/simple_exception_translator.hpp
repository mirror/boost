#ifndef BOOST_FSM_SIMPLE_EXCEPTION_TRANSLATOR_HPP_INCLUDED
#define BOOST_FSM_SIMPLE_EXCEPTION_TRANSLATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/event_base.hpp>
#include <boost/fsm/event.hpp>
#include <boost/shared_ptr.hpp>



namespace boost
{
namespace fsm
{



class simple_exception_event : public event< simple_exception_event > {};



template< class ExceptionEvent = simple_exception_event >
struct simple_exception_translator
{
  template< class Action, class ExceptionEventHandler >
  bool operator()( Action action, ExceptionEventHandler eventHandler )
  {
    try
    {
      return action();
    }
    catch ( ... )
    {
      if ( !eventHandler( ExceptionEvent() ) )
      {
        throw;
      }

      return true;
    }
  }
};



} // namespace fsm
} // namespace boost



#endif
