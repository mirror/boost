#ifndef BOOST_FSM_EVENT_BASE_HPP_INCLUDED
#define BOOST_FSM_EVENT_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/rtti_policy.hpp>
#include <boost/fsm/detail/counted_base.hpp>

#include <boost/assert.hpp>
#include <boost/intrusive_ptr.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class event_base : public detail::rtti_policy::rtti_base_type<
  detail::counted_base< unsigned int > >
{
  typedef detail::rtti_policy::rtti_base_type<
    detail::counted_base< unsigned int > > base_type;
  public:
    //////////////////////////////////////////////////////////////////////////
    intrusive_ptr< const event_base > clone() const
    {
      BOOST_ASSERT( base_type::ref_counted() );
      return intrusive_ptr< const event_base >( this );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    event_base( detail::rtti_policy::id_provider_type idProvider ) :
      base_type( idProvider )
    {
    }

    virtual ~event_base() {}
};



} // namespace fsm
} // namespace boost



#endif
