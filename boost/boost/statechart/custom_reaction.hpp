#ifndef BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
#define BOOST_FSM_CUSTOM_REACTION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/reaction.hpp>



namespace boost
{
namespace fsm
{



template< class Event >
struct custom_reaction
{
  template< class Derived >
  struct apply
  {
    typedef detail::reaction< Event > type;
  };
};



} // namespace fsm
} // namespace boost



#endif
