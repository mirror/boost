#ifndef BOOST_FSM_EXCEPTION_TRANSLATOR_HPP_INCLUDED
#define BOOST_FSM_EXCEPTION_TRANSLATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/result.hpp>

#include <boost/config.hpp> // BOOST_NO_EXCEPTIONS



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class exception_thrown : public event< exception_thrown > {};



//////////////////////////////////////////////////////////////////////////////
template< class ExceptionEvent = exception_thrown >
struct exception_translator
{
  template< class Action, class ExceptionEventHandler >
  result operator()(
    Action action,
    ExceptionEventHandler eventHandler,
    result handlerSuccessResult )
  {
    #ifdef BOOST_NO_EXCEPTIONS
    eventHandler;
    handlerSuccessResult;
    return action();
    #else
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

      return handlerSuccessResult;
    }
    #endif
  }
};



} // namespace fsm
} // namespace boost



#endif
