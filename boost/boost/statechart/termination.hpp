#ifndef BOOST_FSM_TERMINATION_HPP_INCLUDED
#define BOOST_FSM_TERMINATION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/reaction.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast



namespace boost
{
namespace fsm
{
namespace detail
{



template< class Derived, class Event >
class termination_reaction : public reaction< Event >
{
  private:
    virtual result react( const Event & )
    {
      return polymorphic_downcast< Derived * >( this )->terminate();
    }
};



} // namespace detail



template< class Event >
struct termination
{
  template< class Derived >
  struct apply
  {
    typedef detail::termination_reaction< Derived, Event > type;
  };
};



} // namespace fsm
} // namespace boost



#endif
