#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_base.hpp>
#include <boost/fsm/simple_exception_translator.hpp>

#include <boost/utility.hpp>
#include <boost/bind.hpp>

#include <queue>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{

class event_base;



//////////////////////////////////////////////////////////////////////////////
// Base class for all state machines
// Some function names were derived from a state machine by Aleksey Gurtovoy.
template< class Derived,
          class ExceptionTranslator = simple_exception_translator<>, 
          class EventQueue = std::queue< const event_base * > >
class state_machine : boost::noncopyable
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    typedef state_machine base_type;

    // TODO: Figure out a better way of passing the type of the initial state
    // to the constructor.
    // As our derived object is not yet constructed, we cannot construct the
    // initial state yet (we would have to pass our derived class object to
    // construct).
    template< class InitialState >
    state_machine( const InitialState * ) :
      isStable_( true ),
      pInitialConstructor_( &InitialState::construct )
    {
    }

    ~state_machine()
    {
      while ( !queue_.empty() )
      {
        delete queue_.front();
        queue_.pop();
      }
    }


    void process_event( const event_base & evt )
    {
      if ( pInitialConstructor_ != 0 )
      {
        // HACK: Because there's no way to start the machine in the
        // constructor of this class, we start it before processing the first
        // event. Maybe requiring the derived class to call start() in its
        // constructor is a cleaner and less surprising way to achieve the
        // same.
        BOOST_ASSERT( pCurrentState_.get() == 0 );
        execute( boost::bind(
          pInitialConstructor_, 
          boost::ref( static_cast< Derived & >( *this ) ) ) );
        pInitialConstructor_ = 0;

        while ( !queue_.empty() )
        {
          const std::auto_ptr< const event_base > pCurrentEvent(
            queue_.front() );
          queue_.pop();
          send_event( *pCurrentEvent );
        }
      }

      send_event( evt );

      while ( !queue_.empty() )
      {
        const std::auto_ptr< const event_base > pCurrentEvent(
          queue_.front() );
        queue_.pop();
        send_event( *pCurrentEvent );
      }
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
    const State * const current_state_ptr() const
    {
      const state_base * pCurrentState( pCurrentState_.get() );
      const State * pResult( 0 );

      while ( ( pCurrentState != 0 ) &&
              ( ( pResult = dynamic_cast< const State * >( pCurrentState ) ) == 0 ) )
      {
        pCurrentState = pCurrentState->outer_state_ptr();
      }

      return pResult;
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    // TODO: replace shared_ptr with intrusive_ptr
    typedef boost::shared_ptr< state_base > state_base_ptr_type;
    typedef Derived * inner_context_ptr_type;
    typedef Derived top_context_type;

    template< class Context >
    struct is_context
    {
      typedef void result;
    };


    // Returns a reference to the context identified by the template
    // parameter. This can either be _this_ object or one of its direct or
    // indirect contexts.
    template< class Context >
    Context & context()
    {
      // As we are in the top context here, only this object can be returned.
      return static_cast< Derived & >( *this );
    }

    template< class Context >
    const Context & context() const
    {
      // As we are in the top context here, only this object can be returned.
      return static_cast< const Derived & >( *this );
    }


    top_context_type & top_context()
    {
      return static_cast< Derived & >( *this );
    }


    template< class ContextPtr >
    void current_context(
      const ContextPtr & pCurrentContext,
      bool isStable )
    {
      pCurrentState_ = pCurrentContext;
      isStable_ = isStable;
    }

    template<>
    void current_context( 
      const inner_context_ptr_type & pCurrentContext, 
      bool isStable )
    {
      // The current context is _only_ this state_machine -> delete the
      // current state
      pCurrentContext;
      BOOST_ASSERT( pCurrentContext == this );
      pCurrentState_.reset();
      isStable_ = isStable;
    }


    void terminate()
    {
      pCurrentState_.reset();
      isStable_ = true;
    }

    void post_event( std::auto_ptr< const event_base > pEvent )
    {
      BOOST_ASSERT( pEvent.get() != 0 );
      queue_.push( pEvent.get() );
      pEvent.release(); // only release the event if push did not throw
    }

  private:
    typedef void initial_state_construction_function( top_context_type & );

    void send_event( const event_base & theEvent )
    {
      // The state machine is in terminated state if pCurrentState_ is 0.
      // We simply ignore all events in this case.
      if ( pCurrentState_.get() != 0 )
      {
        execute( boost::bind( &event_base::send_to,
          boost::cref( theEvent ), boost::ref( *pCurrentState_ ) ) );
      }
    }

    template< class Action >
    void execute( Action action )
    {
      const std::auto_ptr< const event_base > pExceptionEvent =
        ExceptionTranslator::execute( action );

      if ( pExceptionEvent.get() != 0 )
      {
        // When either a state constructor or a transition action throws, the
        // state machine is instable when the exception event is processed
        // (pCurrentState_ does not point to an innermost state).
        // This situation can be resolved by the exception event handler
        // function by orderly transiting to another state or terminating.
        // As a result of this, pCurrentState_ must either be 0 or point to an
        // innermost state after processing the exception event.

        // TODO: The following call could lead to an infinite recursion as a
        // result of a bad state machine design. Find a way to bail out or
        // disallow recursive exceptions.
        send_event( *pExceptionEvent );

        if ( !isStable_ )
        {
          terminate();
        }
      }
    }

    EventQueue queue_;
    state_base_ptr_type pCurrentState_;
    bool isStable_;
    initial_state_construction_function * pInitialConstructor_;
};



} // namespace fsm
} // namespace boost



#endif
