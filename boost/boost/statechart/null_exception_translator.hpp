#ifndef BOOST_FSM_NULL_EXCEPTION_TRANSLATOR_HPP_INCLUDED
#define BOOST_FSM_NULL_EXCEPTION_TRANSLATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
struct null_exception_translator
{
  template< class Action, class ExceptionEventHandler >
  result operator()( Action action, ExceptionEventHandler, result )
  {
    return action();
  }
};



} // namespace fsm
} // namespace boost



#endif
