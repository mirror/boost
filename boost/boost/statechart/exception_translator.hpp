#ifndef BOOST_FSM_EXCEPTION_TRANSLATOR_HPP_INCLUDED
#define BOOST_FSM_EXCEPTION_TRANSLATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
