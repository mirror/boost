#ifndef BOOST_FSM_EVENT_HPP_INCLUDED
#define BOOST_FSM_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/rtti_policy.hpp>
#include <boost/fsm/detail/counted_base.hpp>

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class event_base : public detail::rtti_policy::base_type<
  detail::counted_base< unsigned int > >
{
  typedef detail::rtti_policy::base_type<
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
    event_base( detail::rtti_policy::id_type id ) :
      base_type( id )
    {
    }
};


//////////////////////////////////////////////////////////////////////////////
template< class MostDerived >
class event : public detail::rtti_policy::derived_type<
  MostDerived, event_base >
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}
};



} // namespace fsm
} // namespace boost



#endif
