#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP
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



//////////////////////////////////////////////////////////////////////////////
template< class Event >
class event_receiver
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event_receiver() {}
    ~event_receiver() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual const bool receive( const Event & theEvent ) = 0;

    friend class event< Event >;
};



} // namespace fsm
} // namespace boost



#endif
