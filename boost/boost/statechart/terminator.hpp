#ifndef BOOST_FSM_TERMINATOR_HPP_INCLUDED
#define BOOST_FSM_TERMINATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/event_handler.hpp>

#include <boost/cast.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



template< class Derived, class Event >
class terminator_handler : public event_handler< Event >
{
  private:
    virtual bool handle_event( const Event & )
    {
      return polymorphic_downcast< Derived * >( this )->terminate();
    }
};



} // namespace detail



template< class Event >
struct terminator
{
    template< class Derived >
    struct apply
    {
      typedef detail::terminator_handler< Derived, Event > type;
    };
};



} // namespace fsm
} // namespace boost



#endif
