#ifndef BOOST_FSM_EVENT_BASE_HPP_INCLUDED
#define BOOST_FSM_EVENT_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/utility.hpp>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{
namespace detail
{



class state_base;



//////////////////////////////////////////////////////////////////////////////
class event_base : noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~event_base() {}

  protected:
    //////////////////////////////////////////////////////////////////////////
    event_base() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    virtual bool send_to( state_base & toState ) const = 0;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
