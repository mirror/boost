#ifndef BOOST_FSM_EVENT_BASE_HPP_INCLUDED
#define BOOST_FSM_EVENT_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
  detail::counted_base<> >
{
  typedef detail::rtti_policy::rtti_base_type<
    detail::counted_base<> > base_type;
  public:
    //////////////////////////////////////////////////////////////////////////
    intrusive_ptr< const event_base > intrusive_from_this() const
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

    friend void intrusive_ptr_release(
      const ::boost::fsm::event_base * pBase );
};



#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace fsm
#endif



inline void intrusive_ptr_add_ref( const ::boost::fsm::event_base * pBase )
{
  pBase->add_ref();
}

inline void intrusive_ptr_release( const ::boost::fsm::event_base * pBase )
{
  if ( pBase->release() )
  {
    delete pBase;
  }
}



#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace fsm
#endif



} // namespace boost



#endif
