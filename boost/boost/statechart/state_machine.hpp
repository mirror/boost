#ifndef BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
#define BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp>

#include <boost/fsm/event_base.hpp>
#include <boost/fsm/exception_translator.hpp>
#include <boost/fsm/result.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/clear.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/cast.hpp>    // boost::polymorphic_downcast
#include <boost/utility.hpp> // boost::noncopyable
#include <boost/assert.hpp>  // BOOST_ASSERT
#include <boost/config.hpp>  // BOOST_STATIC_CONSTANT

#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable: 4702 ) // unreachable code (in release mode only)
#endif

#include <list>

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#include <memory>   // std::allocator
#include <typeinfo> // std::bad_cast



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

  
  
template< class StateList >
class universal_state;
template< orthogonal_position_type noOfOrthogonalRegions, class StateList >
class node_state;
template< class StateList >
class leaf_state;

class send_function
{
  public:
    //////////////////////////////////////////////////////////////////////////
    send_function(
      const event_base & evt, state_base & toState
    ) :
      evt_( evt ), toState_( toState )
    {
    }

    result operator()()
    {
      return evt_.send( toState_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    const event_base & evt_;
    state_base & toState_;
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
// Base class for all state machines
// Some function names were derived from a state machine by Aleksey Gurtovoy.
template< class Derived,
          class InitialState,
          class ExceptionTranslator = exception_translator, 
          class Allocator = std::allocator< void > >
class state_machine : private noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    typedef intrusive_ptr< event_base > event_ptr_type;

    void initiate()
    {
      terminate();
      translator_(
        initial_construct_function( *this ),
        exception_event_handler( *this ),
        do_discard_event );
      process_queued_events();
    }

    void terminate()
    {
      terminate( *this );
    }


    void process_event( const event_base & evt )
    {
      send_event( evt );
      process_queued_events();
    }

    // Polymorphic state query. Returns a pointer to the state identified by
    // the template parameter _if_ the machine is currently in this state.
    // Throws std::bad_cast otherwise.
    template< class State >
    const State & current_state() const
    {
      const State * const pCurrentState( current_state_ptr< State >() );

      if ( pCurrentState != 0 )
      {
        return *pCurrentState;
      }

      throw std::bad_cast();
    }

    // Polymorphic state query. Returns a pointer to the state identified by
    // the template parameter _if_ the machine is currently in this state.
    // Returns 0 otherwise.
    template< class State >
    const State * current_state_ptr() const
    {
      const State * pResult = 0;

      for ( state_list_type::const_iterator pCurrentLeafState =
              currentStates_.begin();
            ( pCurrentLeafState != currentStates_.end() ) && ( pResult == 0 );
            ++pCurrentLeafState )
      {
        const detail::state_base * pCurrentState(
          get_pointer( *pCurrentLeafState ) );

        while ( ( pCurrentState != 0 ) && ( ( pResult =
                    dynamic_cast< const State * >( pCurrentState ) ) == 0 ) )
        {
          pCurrentState = pCurrentState->outer_state_ptr();
        }
      }

      return pResult;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    state_machine() :
      pUnstableState_( currentStates_.end() )
    {
    }

    // This destructor was only made virtual, so that that
    // polymorphic_downcast can be used to cast to Derived.
    virtual ~state_machine() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef Derived inner_context_type;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      inner_orthogonal_position = 0 );

    typedef Derived top_context_type;
    typedef Derived * inner_context_ptr_type;
    typedef intrusive_ptr< detail::state_base > state_ptr_type;
    typedef std::list<
      state_ptr_type,
      typename Allocator::rebind< state_ptr_type >::other > state_list_type;

    typedef mpl::clear< mpl::list<> >::type context_type_list;


    // Returns a reference to the context identified by the template
    // parameter. This can either be _this_ object or one of its direct or
    // indirect contexts.
    template< class Context >
    Context & context()
    {
      // As we are in the top context here, only this object can be returned.
      return *polymorphic_downcast< Derived * >( this );
    }

    template< class Context >
    const Context & context() const
    {
      // As we are in the top context here, only this object can be returned.
      return *polymorphic_downcast< const Derived * >( this );
    }


    top_context_type & top_context()
    {
      return *polymorphic_downcast< Derived * >( this );
    }


    void terminate( state_machine & )
    {
      pUnstableState_ = currentStates_.end();
      currentStates_.clear();
      // there is no longer any use for possibly remaining events
      eventQueue_.clear();
    }

    void terminate( detail::universal_state< state_list_type > & theState )
    {
		  if ( currentStates_.size() == 1 )
		  {
			  // The following optimization is only correct when there are no
			  // orthogonal states.
			  currentStates_.clear();
		  }
		  else
		  {
			  // This would work for all cases, but is unnecessarily inefficient
			  // when there are no orthogonal states.
			  theState.remove_from_state_list( currentStates_, pUnstableState_ );
		  }
    }

    void post_event( const event_ptr_type & pEvent )
    {
      BOOST_ASSERT( get_pointer( pEvent ) != 0 );
      eventQueue_.push_back( pEvent );
    }

    template< class State >
    void add( const intrusive_ptr< State > & pState )
    { 
      if ( machine_status() == unstable )
      {
        *pUnstableState_ = pState;
      }
      else
      {
        pUnstableState_ =
          currentStates_.insert( currentStates_.end(), pState );
      }

      add_impl( *pState );
    }

    void add( state_machine * )
    {
      BOOST_ASSERT( machine_status() == no_state );
    }


    void add_inner_state( detail::orthogonal_position_type position,
                          detail::universal_state< state_list_type > * )
    {
      BOOST_ASSERT( position == 0 );
      position;
    }

    void remove_inner_state( detail::orthogonal_position_type position )
    {
      BOOST_ASSERT( position == 0 );
      position;
    }

  private: // implementation
    //////////////////////////////////////////////////////////////////////////
    typedef std::list<
      event_ptr_type,
      typename Allocator::rebind< event_ptr_type >::other > event_queue_type;

    void initial_construct()
    {
      InitialState::deep_construct(
        *polymorphic_downcast< Derived * >( this ) );
    }

    class initial_construct_function
    {
      public:
        //////////////////////////////////////////////////////////////////////
        initial_construct_function(
          state_machine & machine
        ) :
          machine_( machine )
        {
        }

        result operator()()
        {
          machine_.initial_construct();
          return do_discard_event; // there is nothing to be consumed
        }

      private:
        //////////////////////////////////////////////////////////////////////
        state_machine & machine_;
    };

    friend initial_construct_function;

    template< class ExceptionEvent >
    bool handle_exception_event(
      const ExceptionEvent & exceptionEvent,
      detail::state_base * pCurrentState )
    {
      const machine_status_enum status = machine_status();

      if ( status == no_state )
      {
        // there is not state that could handle the exception -> bail out
        return false;
      }

      // If we are stable, an event handler has thrown.
      // Otherwise, either a state constructor or a transition action
      // has thrown and the state machine is now in an invalid state.
      // This situation can be resolved by the exception event handler
      // function by orderly transiting to another state or terminating.
      // As a result of this, the machine must not be unstable when this
      // function is left.
      detail::state_base * const pHandlingState =
        status == stable ? pCurrentState : &unstable_state();

      BOOST_ASSERT( pHandlingState != 0 );

      const result reaction_result = translator_( 
        detail::send_function( exceptionEvent, *pHandlingState ),
        exception_event_handler( *this, pCurrentState ),
        do_discard_event );

      // TODO: defer event here

      return ( reaction_result != do_forward_event ) &&
        ( machine_status() != unstable );
    }

    class exception_event_handler
    {
      public:
        //////////////////////////////////////////////////////////////////////
        exception_event_handler(
          state_machine & machine,
          detail::state_base * pCurrentState = 0
        ) :
          machine_( machine ),
          pCurrentState_( pCurrentState )
        {
        }

        template< class ExceptionEvent >
        bool operator()( const ExceptionEvent & exceptionEvent )
        {
          return machine_.handle_exception_event( exceptionEvent, pCurrentState_ );
        }

      private:
        //////////////////////////////////////////////////////////////////////
        state_machine & machine_;
        detail::state_base * pCurrentState_;
    };

    friend exception_event_handler;

    void send_event( const event_base & evt )
    {
      BOOST_ASSERT( machine_status() != unstable );

      result reaction_result = do_forward_event;
      state_list_type::iterator pState = currentStates_.begin();

      while ( ( reaction_result == do_forward_event ) &&
        ( pState != currentStates_.end() ) )
      {
        try
        {
          // CAUTION: The following statement could modify our state list!
          // We must not continue iterating, if the event was consumed
          reaction_result = translator_(
            detail::send_function( evt, **pState ),
            exception_event_handler( *this, get_pointer( *pState ) ),
            do_discard_event );
        }
        catch ( ... )
        {
          terminate();
          throw;
        }

        // TODO: defer event here

        if ( reaction_result == do_forward_event )
        {
          // we can only safely advance the iterator if currentStates has
          // not been modified!
          ++pState;
        }
      }
    }

    void process_queued_events()
    {
      while ( !eventQueue_.empty() )
      {
        const event_ptr_type pCurrentEvent( eventQueue_.front() );
        eventQueue_.pop_front();
        send_event( *pCurrentEvent );
      }
    }


    enum machine_status_enum
    {
      no_state,
      unstable,
      stable
    };

    machine_status_enum machine_status() const
    {
      if ( currentStates_.empty() )
      {
        return no_state;
      }
      else if ( pUnstableState_ != currentStates_.end() )
      {
        return unstable;
      }
      else
      {
        return stable;
      }
    }

    detail::state_base & unstable_state()
    {
      BOOST_ASSERT( machine_status() == unstable );
      return **pUnstableState_;
    }

    template< detail::orthogonal_position_type noOfOrthogonalRegions, class StateList >
    void add_impl(
      const detail::node_state< noOfOrthogonalRegions, StateList > & ) {}

    template< class StateList >
    void add_impl( detail::leaf_state< StateList > & theState )
    {
      theState.set_list_position( pUnstableState_ );
      pUnstableState_ = currentStates_.end();
    }

    event_queue_type eventQueue_;
    state_list_type currentStates_;
    typename state_list_type::iterator pUnstableState_;
    ExceptionTranslator translator_;
};



} // namespace fsm
} // namespace boost



#endif
