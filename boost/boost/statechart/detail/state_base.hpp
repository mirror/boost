#ifndef BOOST_FSM_STATE_BASE_HPP_INCLUDED
#define BOOST_FSM_STATE_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////


#include <boost/fsm/detail/counted_base.hpp>

#include <boost/utility.hpp>
#include <boost/assert.hpp>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{
namespace detail
{



//////////////////////////////////////////////////////////////////////////////
class state_base : public counted_base, noncopyable
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
    state_base() : pOuterState_( 0 )
    {
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
    // Storing another pointer to our outer state looks like a bit of a waste
    // but the alternatives are not really appealing either. To begin with,
    // there is a tiny difference between the two pointers: The subclass
    // pointer references the context of a state which can be another state
    // or the state machine. This pointer however only points to our outer
    // state _if_ there is one. It is 0 if the outer context of this state
    // is the state machine itself.
    // Doing away with the pointer in the subclass would mean the following:
    // - Having a ref-counted smartpointer as a member of this class
    // - The smart pointer would have to point either to a common base class
    //   of state and state_machine or void. The former looks rather
    //   artificial (how would you name the base class?) and the latter 
    //   has a runtime overhead attached to it (deleting the referenced
    //   object of a shared_ptr< void > involves an additional virtual call)
    // - The smart pointer must be given a no-op deleter in case our context
    //   is the state machine
    state_base * pOuterState_;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
