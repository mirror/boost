#ifndef BOOST_FSM_EVENT_HANDLER_HPP_INCLUDED
#define BOOST_FSM_EVENT_HANDLER_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>



namespace boost
{
namespace fsm
{


  
template< class Derived >
class event;



namespace detail
{



//////////////////////////////////////////////////////////////////////////////
template< class Event >
class reaction
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    reaction() {}
    ~reaction() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual result react( const Event & toEvent ) = 0;

    friend class event< Event >;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
