#ifndef BOOST_FSM_RESULT_HPP_INCLUDED
#define BOOST_FSM_RESULT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
enum result
{
  no_reaction,
  do_forward_event,
  do_discard_event,
  do_defer_event
};



} // namespace fsm
} // namespace boost



#endif
