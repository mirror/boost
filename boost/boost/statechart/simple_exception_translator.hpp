#ifndef SIMPLE_EXCEPTION_TRANSLATOR_HPP
#define SIMPLE_EXCEPTION_TRANSLATOR_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>

#include <utility>



namespace boost
{
namespace fsm
{

class simple_exception_event : public event< simple_exception_event > {};



template< class ExceptionEvent = simple_exception_event >
struct simple_exception_translator
{
  template< class Action >
  static std::auto_ptr< const event_base > execute( Action action )
  {
    try
    {
      action();
    }
    catch( ... )
    {
      return std::auto_ptr< const event_base >( new ExceptionEvent );
    }

    return std::auto_ptr< const event_base >( 0 );
  }
};



} // namespace fsm
} // namespace boost



#endif
