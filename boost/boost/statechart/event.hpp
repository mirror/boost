#ifndef BOOST_FSM_EVENT_HPP_INCLUDED
#define BOOST_FSM_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event_base.hpp>
#include <boost/fsm/detail/rtti_policy.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived >
class event : public detail::rtti_policy::rtti_derived_type<
  MostDerived, event_base >
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}
    virtual ~event() {}
};



} // namespace fsm
} // namespace boost



#endif
