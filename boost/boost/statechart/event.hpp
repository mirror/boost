#ifndef BOOST_STATECHART_EVENT_HPP_INCLUDED
#define BOOST_STATECHART_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/statechart/event_base.hpp>
#include <boost/statechart/detail/rtti_policy.hpp>



namespace boost
{
namespace statechart
{



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived >
class event : public detail::rtti_policy::rtti_derived_type<
  MostDerived, event_base >
{
  // Events need to be copyable so that they can be reposted in a transition
  // action (happens very rarely). This is because a transition action is only
  // passed a reference to the (possibly stack-allocated) event but the
  // post_event function requests an event allocated with new (and pointed to
  // by an intrusive_ptr).
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}
    virtual ~event() {}
};



} // namespace statechart
} // namespace boost



#endif
