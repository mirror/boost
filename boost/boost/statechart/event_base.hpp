#ifndef BOOST_FSM_EVENT_BASE_HPP_INCLUDED
#define BOOST_FSM_EVENT_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/counted_base.hpp>
#include <boost/fsm/detail/state_base.hpp>

#include <boost/fsm/result.hpp>

#include <boost/utility.hpp>



#ifdef BOOST_MSVC
// We permanently turn off the following level 4 warnings because users will
// have to do so themselves anyway if we turn them back on
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class event_base : private noncopyable, public detail::counted_base< unsigned int >  
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~event_base() {}

  protected:
    //////////////////////////////////////////////////////////////////////////
    event_base() {}

    static void enable_reaction( detail::state_base & fromState )
    {
      fromState.enable_reaction();
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    virtual result send( detail::state_base & toState ) const = 0;
};



} // namespace fsm
} // namespace boost



#endif
