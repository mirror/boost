#ifndef BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
#define BOOST_FSM_STATE_MACHINE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/detail/rtti_policy.hpp>
#include <boost/fsm/exception_translator.hpp>
#include <boost/fsm/result.hpp>

#include <boost/fsm/detail/state_base.hpp>
#include <boost/fsm/detail/constructor.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>
#include <boost/cast.hpp>    // boost::polymorphic_downcast
#include <boost/config.hpp>  // BOOST_STATIC_CONSTANT

#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable: 4702 ) // unreachable code (in release mode only)
#endif

#include <map>

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#include <memory>   // std::allocator
#include <typeinfo> // std::bad_cast
#include <functional> // std::less
#include <iterator>



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



template< orthogonal_position_type noOfOrthogonalRegions,
  class Allocator, class RttiPolicy >
class node_state;
template< class Allocator, class RttiPolicy >
class leaf_state;


//////////////////////////////////////////////////////////////////////////////
template< class StateBaseType, class EventBaseType, class IdType >
class send_function
{
  public:
    //////////////////////////////////////////////////////////////////////////
    send_function(
      StateBaseType & toState,
      const EventBaseType & evt,
      IdType eventType
    ) :
      toState_( toState ), evt_( evt ), eventType_( eventType )
    {
    }

    result operator()()
    {
      return toState_.react_impl( evt_, eventType_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    StateBaseType & toState_;
    const EventBaseType & evt_;
    IdType eventType_;
};


//////////////////////////////////////////////////////////////////////////////
struct state_cast_impl_pointer_target
{
  public:
    //////////////////////////////////////////////////////////////////////////
    template< class StateBaseType >
    static const StateBaseType * deref_if_necessary(
      const StateBaseType * pState )
    {
      return pState;
    }

    template< class Target, class IdType >
    static IdType type_id()
    {
      Target p = 0;
      return type_id_impl< IdType >( p );
    }

    static bool found( const void * pFound )
    {
      return pFound != 0;
    }

    template< class Target >
    static Target not_found()
    {
      return 0;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    template< class IdType, class Type >
    static IdType type_id_impl( const Type * )
    {
      return Type::static_type();
    }
};

struct state_cast_impl_reference_target
{
  template< class StateBaseType >
  static const StateBaseType & deref_if_necessary(
    const StateBaseType * pState )
  {
    return *pState;
  }

  template< class Target, class IdType >
  static IdType type_id()
  {
    return Target::static_type();
  }

  template< class Dummy >
  static bool found( const Dummy & )
  {
    return true;
  }

  template< class Target >
  static Target not_found()
  {
    throw std::bad_cast();
  }
};

template< class Target >
struct state_cast_impl : public mpl::if_<
  is_pointer< Target >,
  state_cast_impl_pointer_target,
  state_cast_impl_reference_target
>::type {};


//////////////////////////////////////////////////////////////////////////////
template< class RttiPolicy >
class history_key
{
  public:
    //////////////////////////////////////////////////////////////////////////
    template< class HistorizedState >
    static history_key make_history_key()
    {
      return history_key(
        HistorizedState::context_type::static_type(),
        HistorizedState::orthogonal_position );
    }

    typename RttiPolicy::id_type history_context_type() const
    {
      return historyContextType_;
    }

    friend bool operator<(
      const history_key & left, const history_key & right )
    {
      return
        std::less< typename RttiPolicy::id_type >()( 
          left.historyContextType_, right.historyContextType_ ) ||
        ( ( left.historyContextType_ == right.historyContextType_ ) &&
          ( left.historizedOrthogonalRegion_ <
            right.historizedOrthogonalRegion_ ) );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    history_key(
      typename RttiPolicy::id_type historyContextType, 
      orthogonal_position_type historizedOrthogonalRegion
    ) :
      historyContextType_( historyContextType ),
      historizedOrthogonalRegion_( historizedOrthogonalRegion )
    {
    }

    const typename RttiPolicy::id_type historyContextType_;
    const orthogonal_position_type historizedOrthogonalRegion_;
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived,
          class InitialState, 
          class Allocator = std::allocator< void >,
          class ExceptionTranslator = exception_translator<> >
class state_machine : noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    typedef Allocator allocator_type;
    typedef detail::rtti_policy rtti_policy_type;
    typedef event_base event_base_type;
    typedef intrusive_ptr< const event_base_type > event_base_ptr_type;

    bool initiate()
    {
      terminate();
      translator_(
        initial_construct_function( *this ),
        exception_event_handler( *this ),
        do_discard_event );
      process_queued_events();

      return terminated();
    }

    void terminate()
    {
      terminate( *this );
    }

    bool terminated() const
    {
      return currentStates_.size() == 0;
    }

    bool process_event( const event_base_type & evt )
    {
      const bool running = !terminated();
      send_event( evt );
      process_queued_events();
      return terminated() && running;
    }

    template< class Target >
    Target state_cast() const
    {
      typedef detail::state_cast_impl< Target > impl;

      for ( typename state_list_type::const_iterator pCurrentLeafState =
              currentStates_.begin();
            pCurrentLeafState != currentStates_.end();
            ++pCurrentLeafState )
      {
        const state_base_type * pCurrentState(
          get_pointer( *pCurrentLeafState ) );

        while ( pCurrentState != 0 )
        {
          // The unnecessary try/catch overhead for pointer targets is
          // typically small compared to the cycles dynamic_cast needs
          try
          {
            Target result = dynamic_cast< Target >(
              impl::deref_if_necessary( pCurrentState ) );

            if ( impl::found( result ) )
            {
              return result;
            }
          }
          catch ( const std::bad_cast & )
          {
          }

          pCurrentState = pCurrentState->outer_state_ptr();
        }
      }

      return impl::template not_found< Target >();
    }

    template< class Target >
    Target state_downcast() const
    {
      typedef detail::state_cast_impl< Target > impl;

      typename rtti_policy_type::id_type targetType =
        impl::template type_id< Target, rtti_policy_type::id_type >();

      for ( typename state_list_type::const_iterator pCurrentLeafState =
              currentStates_.begin();
            pCurrentLeafState != currentStates_.end();
            ++pCurrentLeafState )
      {
        const state_base_type * pCurrentState(
          get_pointer( *pCurrentLeafState ) );

        while ( pCurrentState != 0 )
        {
          if ( pCurrentState->dynamic_type() == targetType )
          {
            return static_cast< Target >(
              impl::deref_if_necessary( pCurrentState ) );
          }

          pCurrentState = pCurrentState->outer_state_ptr();
        }
      }

      return impl::template not_found< Target >();
    }

    typedef detail::state_base< allocator_type, rtti_policy_type >
      state_base_type;

    class state_iterator : public std::iterator<
      std::forward_iterator_tag,
      state_base_type, std::ptrdiff_t, 
      const state_base_type *, const state_base_type & >
    {
      public:
        //////////////////////////////////////////////////////////////////////
        explicit state_iterator(
          typename state_base_type::state_list_type::const_iterator baseIterator
        ) : baseIterator_( baseIterator ) {}

        const state_base_type & operator*() const { return **baseIterator_; }
        const state_base_type * operator->() const
        {
          return &**baseIterator_;
        }

        state_iterator & operator++() { ++baseIterator_; return *this; }
        state_iterator operator++( int )
        {
          return state_iterator( baseIterator_++ );
        }

        bool operator==( const state_iterator & right ) const
        {
          return baseIterator_ == right.baseIterator_;
        }
        bool operator!=( const state_iterator & right ) const
        {
          return !( *this == right );
        }

      private:
        typename state_base_type::state_list_type::const_iterator baseIterator_;
    };

    state_iterator state_begin() const
    {
      return state_iterator( currentStates_.begin() );
    }

    state_iterator state_end() const
    {
      return state_iterator( currentStates_.end() );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    state_machine() :
      pUnstableState_( currentStates_.end() )
    {
    }

    // This destructor was only made virtual so that that
    // polymorphic_downcast can be used to cast to MostDerived.
    virtual ~state_machine() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef MostDerived inner_context_type;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      inner_orthogonal_position = 0 );
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      no_of_orthogonal_regions = 1 );

    typedef MostDerived outermost_context_type;
    typedef MostDerived * inner_context_ptr_type;
    typedef typename state_base_type::state_base_ptr_type state_base_ptr_type;
    typedef typename state_base_type::state_list_type state_list_type;

    typedef mpl::clear< mpl::list<> >::type context_type_list;

    BOOST_STATIC_CONSTANT( bool, shallow_history = false );
    BOOST_STATIC_CONSTANT( bool, deep_history = false );
    BOOST_STATIC_CONSTANT( bool, inherited_deep_history = false );


    result react_impl(
      const event_base_type &,
      typename rtti_policy_type::id_type )
    {
      return do_forward_event;
    }


    // Returns a reference to the context identified by the template
    // parameter. This can either be _this_ object or one of its direct or
    // indirect contexts.
    template< class Context >
    Context & context()
    {
      // As we are in the outermost context here, only this object can be
      // returned.
      return *polymorphic_downcast< MostDerived * >( this );
    }

    template< class Context >
    const Context & context() const
    {
      // As we are in the outermost context here, only this object can be
      // returned.
      return *polymorphic_downcast< const MostDerived * >( this );
    }

    outermost_context_type & outermost_context()
    {
      return *polymorphic_downcast< MostDerived * >( this );
    }

    const outermost_context_type & outermost_context() const
    {
      return *polymorphic_downcast< const MostDerived * >( this );
    }


    void terminate( state_machine & )
    {
      pUnstableState_ = currentStates_.end();
      currentStates_.clear(); // this also empties the deferredMap_
      // there is no longer any use for possibly remaining events
      eventQueue_.clear();
      shallowHistoryMap_.clear();
      deepHistoryMap_.clear();
    }

    void terminate( state_base_type & theState )
    {
      theState.set_termination_state();

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

    void post_event( const event_base_ptr_type & pEvent )
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


    void add_inner_state(
      detail::orthogonal_position_type position, state_base_type * )
    {
      BOOST_ASSERT( position == 0 );
      position;
    }

    void remove_inner_state( detail::orthogonal_position_type position )
    {
      BOOST_ASSERT( position == 0 );
      position;
    }

    void release_events( const state_base_type * pForState )
    {
      const typename deferred_map_type::iterator pFound =
        deferredMap_.find( pForState );

      // We are not guaranteed to find an entry because a state is marked for
      // having deferred events _before_ the event is actually deferred. An
      // exception might be thrown during deferral.
      if ( pFound != deferredMap_.end() )
      {
        eventQueue_.splice( eventQueue_.end(), pFound->second );
        deferredMap_.erase( pFound );
      }
    }


    template< class ForState >
    void reserve_shallow_history_slot()
    {
      reserve_history_slot_impl( 
        shallowHistoryMap_,
        history_key_type::make_history_key< ForState >() );
    }

    template< class HistorizedState >
    void store_shallow_history()
    {
      // 5.2.10.6 declares that reinterpret_casting a function pointer to a
      // different function pointer and back must yield the same value. The
      // following reinterpret_cast is the first half of such a sequence.
      store_history_impl(
        shallowHistoryMap_,
        history_key_type::make_history_key< HistorizedState >(),
        reinterpret_cast< void (*)() >( &HistorizedState::deep_construct ) );
    }

    template<
      class HistoryContext,
      detail::orthogonal_position_type orthogonalPosition >
    void clear_shallow_history()
    {
      // If you receive a
      // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or
      // similar compiler error here then you tried to clear shallow history
      // for a state that does not have shallow history. That is, the state
      // does not pass either fsm::has_shallow_history or
      // fsm::has_full_history to its base class template.
      BOOST_STATIC_ASSERT( HistoryContext::shallow_history );

      typedef typename mpl::at_c<
        typename HistoryContext::inner_initial_list,
        orthogonalPosition >::type historized_state;

      store_history_impl(
        shallowHistoryMap_,
        history_key_type::make_history_key< historized_state >(),
        reinterpret_cast< void (*)() >( 0 ) );
    }

    template< class DefaultState >
    void construct_with_shallow_history(
      const typename DefaultState::context_ptr_type & pContext )
    {
      construct_with_history_impl< DefaultState >(
        shallowHistoryMap_, pContext );
    }


    template< class ForState >
    void reserve_deep_history_slot()
    {
      reserve_history_slot_impl( 
        deepHistoryMap_,
        history_key_type::make_history_key< ForState >() );
    }

    template< class HistorizedState, class LeafState >
    void store_deep_history()
    {
      typedef typename detail::make_context_list<
        typename HistorizedState::context_type,
        LeafState >::type history_context_list;
      typedef detail::constructor< 
        history_context_list, outermost_context_type > constructor_type;
      // 5.2.10.6 declares that reinterpret_casting a function pointer to a
      // different function pointer and back must yield the same value. The
      // following reinterpret_cast is the first half of such a sequence.
      store_history_impl(
        deepHistoryMap_, 
        history_key_type::make_history_key< HistorizedState >(),
        reinterpret_cast< void (*)() >( &constructor_type::construct ) );
    }

    template<
      class HistoryContext,
      detail::orthogonal_position_type orthogonalPosition >
    void clear_deep_history()
    {
      // If you receive a
      // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or
      // similar compiler error here then you tried to clear deep history for
      // a state that does not have deep history. That is, the state does not
      // pass either fsm::has_deep_history or fsm::has_full_history to its
      // base class template
      BOOST_STATIC_ASSERT( HistoryContext::deep_history );

      typedef typename mpl::at_c<
        typename HistoryContext::inner_initial_list,
        orthogonalPosition >::type historized_state;

      store_history_impl(
        deepHistoryMap_,
        history_key_type::make_history_key< historized_state >(),
        reinterpret_cast< void (*)() >( 0 ) );
    }

    template< class DefaultState >
    void construct_with_deep_history(
      const typename DefaultState::context_ptr_type & pContext )
    {
      construct_with_history_impl< DefaultState >(
        deepHistoryMap_, pContext );
    }

  private: // implementation
    //////////////////////////////////////////////////////////////////////////
    void initial_construct()
    {
      InitialState::initial_deep_construct(
        *polymorphic_downcast< MostDerived * >( this ) );
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

    friend class initial_construct_function;

    template< class ExceptionEvent >
    bool handle_exception_event(
      const ExceptionEvent & exceptionEvent,
      state_base_type * pCurrentState )
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
      state_base_type * const pHandlingState =
        status == stable ? pCurrentState : &unstable_state();

      BOOST_ASSERT( pHandlingState != 0 );

      const result reactionResult = pHandlingState->react_impl(
        exceptionEvent, exceptionEvent.dynamic_type() );

      if ( reactionResult == do_defer_event )
      {
        // For clone() to work, the exception event must have been allocated
        // with new. Out of the box this is not the case, so users will have
        // to replace the exception_translator should they ever need to do so.
        // Deferring exception events makes sense only in very rare cases and
        // is dangerous unless operator new never throws.
        defer_event( exceptionEvent, pHandlingState );
      }

      return ( reactionResult != do_forward_event ) &&
        ( machine_status() != unstable );
    }

    class exception_event_handler
    {
      public:
        //////////////////////////////////////////////////////////////////////
        exception_event_handler(
          state_machine & machine,
          state_base_type * pCurrentState = 0
        ) :
          machine_( machine ),
          pCurrentState_( pCurrentState )
        {
        }

        template< class ExceptionEvent >
        bool operator()( const ExceptionEvent & exceptionEvent )
        {
          return machine_.handle_exception_event(
            exceptionEvent, pCurrentState_ );
        }

      private:
        //////////////////////////////////////////////////////////////////////
        state_machine & machine_;
        state_base_type * pCurrentState_;
    };

    friend class exception_event_handler;

    class terminator
    {
      public:
        terminator( state_machine & machine ) :
          machine_( machine ), dismissed_( false ) {}
        ~terminator() { if ( !dismissed_ ) { machine_.terminate(); } }
        void dismiss() { dismissed_ = true; }

      private:
        state_machine & machine_;
        bool dismissed_;
    };


    void send_event( const event_base_type & evt )
    {
      terminator guard( *this );
      BOOST_ASSERT( machine_status() != unstable );

      typename rtti_policy_type::id_type eventType = evt.dynamic_type();

      result reactionResult = do_forward_event;
      typename state_list_type::iterator pState = currentStates_.begin();

      while ( ( reactionResult == do_forward_event ) &&
        ( pState != currentStates_.end() ) )
      {
        // CAUTION: The following statement could modify our state list!
        // We must not continue iterating if the event was consumed
        reactionResult = translator_( detail::send_function<
          state_base_type, event_base_type, rtti_policy_type::id_type >(
            **pState, evt, eventType ),
          exception_event_handler( *this, get_pointer( *pState ) ),
          do_discard_event );

        switch ( reactionResult )
        {
          case do_defer_event:
            defer_event( evt, get_pointer( *pState ) ); break;
          case do_forward_event:
            ++pState; break;
          // intentionally no default case (do nothing)
        }
      }

      guard.dismiss();
    }


    void defer_event(
      const event_base_type & evt,
      const state_base_type * pForState )
    {
      deferredMap_[ pForState ].push_back( evt.clone() );
    }


    void process_queued_events()
    {
      while ( !eventQueue_.empty() )
      {
        const event_base_ptr_type pCurrentEvent( eventQueue_.front() );
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

    state_base_type & unstable_state()
    {
      BOOST_ASSERT( machine_status() == unstable );
      return **pUnstableState_;
    }

    template< detail::orthogonal_position_type noOfOrthogonalRegions >
    void add_impl( const detail::node_state<
      noOfOrthogonalRegions, allocator_type, rtti_policy_type > & ) {}

    void add_impl(
      detail::leaf_state< allocator_type, rtti_policy_type > & theState )
    {
      theState.set_list_position( pUnstableState_ );
      pUnstableState_ = currentStates_.end();
    }


    typedef detail::history_key< rtti_policy_type > history_key_type;

    typedef std::map<
      history_key_type, void (*)(),
      std::less< history_key_type >,
      typename allocator_type::template rebind< 
        std::pair< const history_key_type, void (*)() > >::other
    > history_map_type;

    void reserve_history_slot_impl(
      history_map_type & historyMap, 
      const history_key_type & historyId )
    {
      historyMap.insert(
        std::make_pair( historyId, static_cast< void (*)() >( 0 ) ) );
    }

    void store_history_impl(
      history_map_type & historyMap,
      const history_key_type & historyId,
      void (*pConstructFunction)() )
    {
      // Make sure we don't save history if the most derived class constructor
      // throws (test only necessary with state).
      if ( machine_status() != unstable )
      {
        historyMap[ historyId ] = pConstructFunction;
      }
    }

    template< class DefaultState >
    void construct_with_history_impl(
      history_map_type & historyMap,
      const typename DefaultState::context_ptr_type & pContext )
    {
      typename history_map_type::iterator pFoundSlot = historyMap.find(
        history_key_type::make_history_key< DefaultState >() );
      // The slot is allocated before this state is entered.
      BOOST_ASSERT( pFoundSlot != historyMap.end() );
      
      if ( pFoundSlot->second == 0 )
      {
        // We have never entered this state before.
        DefaultState::deep_construct(
          pContext, *polymorphic_downcast< MostDerived * >( this ) );
      }
      else
      {
        typedef void construct_function(
          const typename DefaultState::context_ptr_type &,
          typename DefaultState::outermost_context_type & );
        // 5.2.10.6 declares that reinterpret_casting a function pointer to a
        // different function pointer and back must yield the same value. The
        // following reinterpret_cast is the second half of such a sequence.
        construct_function * const pConstructFunction =
          reinterpret_cast< construct_function * >( pFoundSlot->second );
        // Delete history, so that transitions to history from inside will
        // go to the default state.
        pFoundSlot->second = 0;
        (*pConstructFunction)(
          pContext, *polymorphic_downcast< MostDerived * >( this ) );
      }
    }

    typedef std::list<
      event_base_ptr_type, 
      typename allocator_type::template rebind< event_base_ptr_type >::other
    > event_queue_type;

    typedef std::map<
      const state_base_type *, event_queue_type,
      std::less< const state_base_type * >,
      typename allocator_type::template rebind<
        std::pair< const state_base_type * const, event_queue_type > >::other
    > deferred_map_type;


    event_queue_type eventQueue_;
    deferred_map_type deferredMap_;
    state_list_type currentStates_;
    typename state_list_type::iterator pUnstableState_;
    history_map_type shallowHistoryMap_;
    history_map_type deepHistoryMap_;
    ExceptionTranslator translator_;
};



} // namespace fsm
} // namespace boost



#endif
