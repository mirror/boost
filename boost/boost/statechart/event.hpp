#ifndef BOOST_FSM_EVENT_HPP_INCLUDED
#define BOOST_FSM_EVENT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/counted_base.hpp>
#include <boost/fsm/rtti_policy.hpp>

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class RttiPolicy >
class event_base :
  public RttiPolicy::base_type< detail::counted_base< unsigned int > >
{
  typedef typename RttiPolicy::base_type<
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
    event_base( typename RttiPolicy::id_type id ) : base_type( id ) {}
};


//////////////////////////////////////////////////////////////////////////////
template< class MostDerived, class RttiPolicy = rtti_policy >
class event : public RttiPolicy::derived_type<
  MostDerived, event_base< RttiPolicy > >
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}
};



} // namespace fsm
} // namespace boost



#endif
