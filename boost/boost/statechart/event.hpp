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

#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>

#include <typeinfo>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class event : private noncopyable, public detail::counted_base< unsigned int >
{
  public:
    //////////////////////////////////////////////////////////////////////////
    intrusive_ptr< const event > clone() const
    {
      BOOST_ASSERT( ref_counted() );
      return intrusive_ptr< const event >( this );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}
};



} // namespace fsm
} // namespace boost



#endif
