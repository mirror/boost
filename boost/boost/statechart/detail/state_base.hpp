#ifndef BOOST_FSM_STATE_BASE_HPP_INCLUDED
#define BOOST_FSM_STATE_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/counted_base.hpp>

#include <boost/utility.hpp> // boost::noncopyable
#include <boost/assert.hpp>  // BOOST_ASSERT



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



class event_base;



namespace detail
{



typedef unsigned char orthogonal_position_type;



//////////////////////////////////////////////////////////////////////////////
class state_base : private noncopyable,
  // Derived class objects will be created, handled and destroyed by one and
  // the same thread --> locking is not necessary
  public counted_base< orthogonal_position_type, false >
{
  public:
    //////////////////////////////////////////////////////////////////////////
    // returns a pointer to the immediate outer state _if_ there is one,
    // returns 0 otherwise (this is the outermost state then)
    state_base * outer_state_ptr() const
    {
      return pOuterState_;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    state_base() :
      reactionEnabled_( false ),
      deferredEvents_( false ),
      pOuterState_( 0 )
    {
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

    void set_context( state_base * pOuterState )
    {
      // Context must only be set once
      BOOST_ASSERT( ( pOuterState != 0 ) && ( pOuterState_ == 0 ) );
      pOuterState_ = pOuterState;
    }

    void set_context( void * pMachine )
    {
      // Context must only be set once
      BOOST_ASSERT( ( pMachine != 0 ) && ( pOuterState_ == 0 ) );
      pMachine;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    friend class ::boost::fsm::event_base;

    void enable_reaction()
    {
      reactionEnabled_ = true;
    }

    bool reactionEnabled_;
    bool deferredEvents_;
    // Storing another pointer to our outer state looks like a bit of a waste
    // but the alternatives are not really appealing either. To begin with,
    // there is a tiny difference between the two pointers: The subclass
    // pointer references the context of a state which can be another state
    // or the state machine. This pointer however only points to our outer
    // state _if_ there is one. It is 0 if the outer context of this state
    // is the state machine itself.
    state_base * pOuterState_;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
