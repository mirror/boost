#ifndef BOOST_STATECHART_DEFERRAL_HPP_INCLUDED
#define BOOST_STATECHART_DEFERRAL_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/statechart/result.hpp>



namespace boost
{
namespace statechart
{



//////////////////////////////////////////////////////////////////////////////
template< class Event >
class deferral
{
  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    template< class State, class EventBase, class IdType >
    static result react(
      State & stt, const EventBase &, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        return stt.defer_event();
      }
      else
      {
        return no_reaction;
      }
    }
};



} // namespace statechart
} // namespace boost



#endif
