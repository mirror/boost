#ifndef BOOST_FSM_EVENT_HANDLER_HPP_INCLUDED
#define BOOST_FSM_EVENT_HANDLER_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



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
class event_handler
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event_handler() {}
    ~event_handler() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual bool handle_event( const Event & evt ) = 0;

    friend class event< Event >;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
