#ifndef BOOST_FSM_DETAIL_STATE_BASE_HPP_INCLUDED
#define BOOST_FSM_DETAIL_STATE_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/result.hpp>
#include <boost/fsm/event.hpp>

#include <boost/fsm/detail/counted_base.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable: 4702 ) // unreachable code (in release mode only)
#endif

#include <list>

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif



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
namespace detail
{



typedef unsigned char orthogonal_position_type;



//////////////////////////////////////////////////////////////////////////////
template< class Allocator, class RttiPolicy >
class state_base : private noncopyable, public RttiPolicy::base_type<
  // Derived class objects will be created, handled and destroyed by one and
  // the same thread --> locking is not necessary
  counted_base< orthogonal_position_type, false > >
{
  typedef typename RttiPolicy::base_type<
    counted_base< orthogonal_position_type, false > > base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only protected because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    state_base( typename RttiPolicy::id_type id ) :
      base_type( id ),
      reactionEnabled_( false ),
      deferredEvents_( false ),
      terminationState_( false )
    {
    }

    void enable_reaction()
    {
      reactionEnabled_ = true;
    }

    void reaction_initiated()
    {
      // This assert fails when you try to call a reaction function outside
      // an event handler or when you try to call two reaction functions
      // inside an event handler.
      // Every event handler must return the result of exactly one reaction
      // function call (forward_event, discard_event, defer_event, transit,
      // terminate)
      BOOST_ASSERT( reactionEnabled_ );
      reactionEnabled_ = false;
    }

    void defer_event()
    {
      deferredEvents_ = true;
    }

    bool deferred_events() const
    {
      return deferredEvents_;
    }

    template< class Context >
    void set_context( orthogonal_position_type position, Context * pContext )
    {
      pContext->add_inner_state( position, this );
    }

    bool termination_state() const
    {
      return terminationState_;
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void set_termination_state()
    {
      terminationState_ = true;
    }

    virtual result react_impl(
      const event_base & evt,
      typename RttiPolicy::id_type eventType ) = 0;

    // returns a pointer to the immediate outer state _if_ there is one,
    // returns 0 otherwise (this is the outermost state then)
    virtual state_base * outer_state_ptr() const = 0;

    typedef intrusive_ptr< state_base > state_base_ptr_type;
    typedef std::list<
      state_base_ptr_type,
      typename Allocator::rebind< state_base_ptr_type >::other
    > state_list_type;

    virtual void remove_from_state_list(
      state_list_type & states,
      typename state_list_type::iterator & pUnstableState ) = 0;

  private:
    //////////////////////////////////////////////////////////////////////////
    bool reactionEnabled_;
    bool deferredEvents_;
    bool terminationState_;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
