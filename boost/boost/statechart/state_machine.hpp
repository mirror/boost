#ifndef BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
#define BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp>
#include <boost/fsm/detail/event_base.hpp>
#include <boost/fsm/simple_exception_translator.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/clear.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/cast.hpp>
#include <boost/utility.hpp>
#include <boost/assert.hpp>

#include <stdexcept>

#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4702 ) // unreachable code
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif

#include <queue>
#include <list>



namespace boost
{
namespace fsm
{
namespace detail
{

  
  
template< class StateList >
class universal_state;
template< orthogonal_position_type noOfOrthogonalStates, class StateList >
class node_state;
template< class StateList >
class leaf_state;

class event_base;

class send_function
{
  public:
    //////////////////////////////////////////////////////////////////////////
    send_function(
      const detail::event_base & evt, detail::state_base & toState
    ) :
      evt_( evt ), toState_( toState )
    {
    }

    bool operator()()
    {
      return evt_.send_to( toState_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    const detail::event_base & evt_;
    detail::state_base & toState_;
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
// Base class for all state machines
// Some function names were derived from a state machine by Aleksey Gurtovoy.
template< class Derived,
          class InitialState,
          class ExceptionTranslator = simple_exception_translator<>, 
          class EventQueue =
            std::queue< shared_ptr< const detail::event_base > >,
          class StateList = std::list< intrusive_ptr< detail::state_base > > >
class state_machine : noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    typedef EventQueue event_queue_type;

    void initiate()
    {
      terminate();
      translator_(
        initial_construct_function( *this ),
        exception_event_handler( *this ) );
      process_queued_events();
    }

    void terminate()
    {
      terminate( *this );
    }


    void process_event( const detail::event_base & evt )
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

      for ( StateList::const_iterator pCurrentLeafState =
              currentStates_.begin();
            ( pCurrentLeafState != currentStates_.end() ) && ( pResult == 0 );
            ++pCurrentLeafState )
      {
        const detail::state_base * pCurrentState(
          ( *pCurrentLeafState ).get() );

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
      pIncompleteState_( currentStates_.end() )
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
    typedef StateList state_list_type;

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
      // there is no longer any use for possibly remaining events
      eventQueue_ = EventQueue();
      currentStates_.clear();
      pIncompleteState_ = currentStates_.end();
    }

    void terminate( detail::universal_state< StateList > & theState )
    {
      // If we receive a terminate request while the machine is not stable
      // then this can only have happened as a result of an exception and we
      // unconditionally terminate the incomplete state.
      if ( !stable() )
      {
        currentStates_.erase( pIncompleteState_ );
        pIncompleteState_ = currentStates_.end();
      }

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
        theState.remove_from_state_list( currentStates_ );
      }
    }

    template< class State >
    void add( const intrusive_ptr< State > & pState )
    { 
      if ( stable() )
      {
        pIncompleteState_ =
          currentStates_.insert( currentStates_.end(), pState );
      }
      else
      {
        *pIncompleteState_ = pState;
      }

      add_impl( *pState );
    }

    void add( state_machine * )
    {
      BOOST_ASSERT( stable() && ( currentStates_.size() == 0 ) );
    }

    void post_event( const typename event_queue_type::value_type & pEvent )
    {
      BOOST_ASSERT( get_pointer( pEvent ) != 0 );
      eventQueue_.push( pEvent );
    }


    void add_inner_state( detail::orthogonal_position_type position,
                          detail::universal_state< StateList > * )
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

        bool operator()()
        {
          machine_.initial_construct();
          return true; // there is nothing to be consumed
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
      // If we are stable, an event handler has thrown.
      // Otherwise, either a state constructor or a transition action
      // has thrown and the state machine is now in an invalid state.
      // This situation can be resolved by the exception event handler
      // function by orderly transiting to another state or terminating.
      // As a result of this, pCurrentIncompleteState_ must point to
      // currentStates_.end() after processing the exception event.
      detail::state_base * const pHandlingState =
        stable() ? pCurrentState : &incomplete_state();

      BOOST_ASSERT( pHandlingState != 0 );

      // Deliberately ignore whether the event was consumed or not. Important
      // is whether we are stable or not.
      translator_( 
        detail::send_function( exceptionEvent, *pHandlingState ),
        exception_event_handler( *this, pCurrentState ) );

      return stable();
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

    bool send_event( const detail::event_base & evt )
    {
      BOOST_ASSERT( stable() );

      bool wasConsumed = false;
      StateList::iterator pState = currentStates_.begin();

      while ( !wasConsumed && ( pState != currentStates_.end() ) )
      {
        try
        {
          // CAUTION: The following statement could modify our state list!
          // We must not continue iterating, if the event was consumed
          wasConsumed = translator_(
            detail::send_function( evt, **pState ),
            exception_event_handler( *this, get_pointer( *pState ) ) );
        }
        catch ( ... )
        {
          terminate();
          throw;
        }

        if ( !wasConsumed )
        {
          // we can only safely advance the iterator _if_ currentStates has
          // not been modified!
          ++pState;
        }
      }

      return wasConsumed;
    }

    void process_queued_events()
    {
      while ( !eventQueue_.empty() )
      {
        const typename event_queue_type::value_type pCurrentEvent(
          eventQueue_.front() );
        eventQueue_.pop();
        send_event( *pCurrentEvent );
      }
    }


    bool stable() const
    {
      return pIncompleteState_ == currentStates_.end();
    }

    detail::state_base & incomplete_state()
    {
      BOOST_ASSERT( !stable() );
      return **pIncompleteState_;
    }

    template< detail::orthogonal_position_type noOfOrthogonalStates, class StateList >
    void add_impl(
      const detail::node_state< noOfOrthogonalStates, StateList > & ) {}

    template< class StateList >
    void add_impl( detail::leaf_state< StateList > & theState )
    {
      theState.set_list_position( pIncompleteState_ );
      pIncompleteState_ = currentStates_.end();
    }

    event_queue_type eventQueue_;
    state_list_type currentStates_;
    typename state_list_type::iterator pIncompleteState_;
    ExceptionTranslator translator_;
};



} // namespace fsm
} // namespace boost



#endif
