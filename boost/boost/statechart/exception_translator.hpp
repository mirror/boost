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



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class exception_thrown : public event {};



//////////////////////////////////////////////////////////////////////////////
struct exception_translator
{
  template< class Action, class ExceptionEventHandler >
  result operator()(
    Action action,
    ExceptionEventHandler eventHandler,
    result handlerSuccessResult )
  {
    try
    {
      return action();
    }
    catch ( ... )
    {
      if ( !eventHandler( exception_thrown() ) )
      {
        throw;
      }

      return handlerSuccessResult;
    }
  }
};



} // namespace fsm
} // namespace boost



#endif
