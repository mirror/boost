#ifndef BOOST_FSM_COUNTED_BASE_HPP_INCLUDED
#define BOOST_FSM_COUNTED_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/assert.hpp>
#include <boost/config.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



typedef unsigned char orthogonal_position_type;



//////////////////////////////////////////////////////////////////////////////
class counted_base
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~counted_base() {}

  protected:
    //////////////////////////////////////////////////////////////////////////
    counted_base() : count_( 0 ) {}

  public:
    //////////////////////////////////////////////////////////////////////////
    mutable orthogonal_position_type count_;
};



#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
} // namespace boost
#endif



inline void intrusive_ptr_add_ref(
  const ::boost::fsm::detail::counted_base * pBase )
{
  ++pBase->count_;
}

inline void intrusive_ptr_release(
  const ::boost::fsm::detail::counted_base * pBase )
{
  BOOST_ASSERT( pBase->count_ > 0 );
  --pBase->count_;

  if ( pBase->count_ == 0 )
  {
    delete pBase;
  }
}



#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
} // namespace boost
#endif



#endif
