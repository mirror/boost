#ifndef BOOST_FSM_CUSTOM_HANDLER_HPP_INCLUDED
#define BOOST_FSM_CUSTOM_HANDLER_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/event_handler.hpp>



namespace boost
{
namespace fsm
{



template< class Event >
struct custom_handler
{
    template< class Derived >
    struct apply
    {
      typedef detail::event_handler< Event > type;
    };
};



} // namespace fsm
} // namespace boost



#endif
