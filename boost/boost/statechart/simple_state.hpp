#ifndef BOOST_FSM_SIMPLE_STATE_HPP_INCLUDED
#define BOOST_FSM_SIMPLE_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/leaf_state.hpp>
#include <boost/fsm/detail/node_state.hpp>

#include <boost/fsm/event.hpp>

#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/get_pointer.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/cast.hpp>   // boost::polymorphic_downcast
#include <boost/config.hpp> // BOOST_STATIC_CONSTANT



namespace boost
{
namespace fsm
{
namespace detail
{

  
  
typedef mpl::clear< mpl::list<> >::type empty_list;

//////////////////////////////////////////////////////////////////////////////
template< class T >
struct make_list : public mpl::apply_if<
  mpl::is_sequence< T >,
  mpl::identity< T >,
  mpl::identity< mpl::list< T > > > {};

using namespace mpl::placeholders;

//////////////////////////////////////////////////////////////////////////////
template< class MostDerived, class Context, class InnerInitial >
struct simple_state_base_type
{
  private:
    typedef typename Context::top_context_type::allocator_type allocator_type;
    typedef typename Context::top_context_type::rtti_policy_type
      rtti_policy_type;
    // TODO: Check that position in inner initial list corresponds to
    // orthogonal_position
    typedef typename detail::make_list< InnerInitial >::type
      inner_initial_list;

  public:
    typedef typename mpl::apply_if<
      mpl::empty< inner_initial_list >,
      mpl::identity< typename rtti_policy_type::
        template derived_type< MostDerived, leaf_state<
          allocator_type,
          rtti_policy_type > > >,
      mpl::identity< typename rtti_policy_type::
        template derived_type< MostDerived, node_state<
          mpl::size< inner_initial_list >::type::value,
          allocator_type,
          rtti_policy_type > > > >::type type;
};


//////////////////////////////////////////////////////////////////////////////
struct no_transition_function
{
  template< class CommonContext >
  void operator()( CommonContext & ) const {}
};

template< class TransitionContext, class Event >
class transition_function
{
  public:
    transition_function(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & evt
    ) :
      pTransitionAction_( pTransitionAction ),
      evt_( evt )
    {
    }

    template< class CommonContext >
    void operator()( CommonContext & commonContext ) const
    {
      ( commonContext.context< TransitionContext >().*pTransitionAction_ )( evt_ );
    }

  private:
    void ( TransitionContext::*pTransitionAction_ )( const Event & );
    const Event & evt_;
};


template< class State >
struct get_context_ptr_type
{
  typedef typename State::context_ptr_type type;
};

template<>
struct get_context_ptr_type< int >
{
  typedef int type;
};

template< class State >
struct get_inner_context_ptr_type
{
  typedef typename State::inner_context_ptr_type type;
};

template<>
struct get_inner_context_ptr_type< int >
{
  typedef int type;
};

template< class State >
struct get_inner_initial_list
{
  typedef typename State::inner_initial_list type;
};

template<>
struct get_inner_initial_list< int >
{
  typedef int type;
};

template< class State >
struct get_orthogonal_position
{
  typedef mpl::integral_c< long, State::orthogonal_position > type;
};

template<>
struct get_orthogonal_position< int >
{
  typedef int type;
};


//////////////////////////////////////////////////////////////////////////////
template< class ContextList, class TopContext >
struct outer_constructor
{
  typedef typename mpl::front< ContextList >::type to_construct;
  typedef typename get_context_ptr_type< to_construct >::type
    context_ptr_type;
  typedef typename get_inner_context_ptr_type< to_construct >::type
    inner_context_ptr_type;

  typedef typename get_inner_initial_list< to_construct >::type
    inner_initial_list;
  typedef typename mpl::pop_front< ContextList >::type inner_context_list;
  typedef typename get_orthogonal_position<
    typename mpl::front< inner_context_list >::type
  >::type inner_orthogonal_position;
  typedef typename mpl::erase< 
    inner_initial_list,
    typename mpl::advance<
      typename mpl::begin< inner_initial_list >::type,
      inner_orthogonal_position >::type >::type remaining_inner_initial_list;

  static construct( const context_ptr_type & pContext, TopContext & topContext )
  {
    topContext.add( pContext );
    const inner_context_ptr_type pInnerContext =
      to_construct::shallow_construct( pContext );
    to_construct::deep_construct_inner< remaining_inner_initial_list >(
      pInnerContext, topContext );
    constructor< inner_context_list, TopContext >::construct(
      pInnerContext, topContext );
  }
};

template< class ContextList, class TopContext >
struct inner_constructor
{
  typedef typename mpl::front< ContextList >::type to_construct;
  typedef typename get_context_ptr_type< to_construct >::type context_ptr_type;

  static construct( const context_ptr_type & pContext, TopContext & topContext )
  {
    to_construct::deep_construct( pContext, topContext );
  }
};

template< class ContextList, class TopContext >
struct constructor_impl : public mpl::apply_if< 
  mpl::equal_to< mpl::size< ContextList >, mpl::integral_c< long, 1 > >,
  mpl::identity< inner_constructor< ContextList, TopContext > >,
  mpl::identity< outer_constructor< ContextList, TopContext > > > {};

template< class ContextList, class TopContext >
struct constructor :
  public constructor_impl< ContextList, TopContext >::type {};



} // namespace detail



typedef detail::empty_list no_reactions;



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived,
          class Context, // either an outer state or a state_machine
          class Reactions = no_reactions,
          class InnerInitial = detail::empty_list > // initial inner state
class simple_state : public detail::simple_state_base_type< MostDerived,
  typename Context::inner_context_type, InnerInitial >::type
{
  typedef typename detail::simple_state_base_type<
    MostDerived, typename Context::inner_context_type,
    InnerInitial >::type base_type;

  public:
    //////////////////////////////////////////////////////////////////////////
    typedef typename Context::inner_context_type context_type;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      orthogonal_position = Context::inner_orthogonal_position );
    typedef typename context_type::event_base_ptr_type event_base_ptr_type;


    typedef simple_state my_base;

    template< detail::orthogonal_position_type innerOrthogonalPosition >
    struct orthogonal
    {
      // TODO: check that this state really has such an inner orthogonal state
      BOOST_STATIC_CONSTANT(
        detail::orthogonal_position_type,
        inner_orthogonal_position = innerOrthogonalPosition );
      typedef MostDerived inner_context_type;
    };


    // Returns a reference to the context identified by the template
    // parameter. This can either be _this_ object or one of its
    // direct or indirect contexts
    template< class OtherContext >
    OtherContext & context()
    {
      return context_impl( static_cast< OtherContext * >( 0 ) );
    }

    template< class OtherContext >
    const OtherContext & context() const
    {
      return context_impl( static_cast< OtherContext * >( 0 ) );
    }

    void post_event( const event_base_ptr_type & pEvent )
    {
      top_context().post_event( pEvent );
    }

    // see state_machine class for documentation
    template< class Target >
    Target state_cast() const
    {
      return top_context().state_cast< Target >();
    }

    // see state_machine class for documentation
    template< class Target >
    Target state_downcast() const
    {
      return top_context().state_downcast< Target >();
    }

    
    result discard_event()
    {
      state_base_type::reaction_initiated();
      return do_discard_event;
    }
    
    result forward_event()
    {
      state_base_type::reaction_initiated();
      return do_forward_event;
    }
    
    result defer_event()
    {
      state_base_type::reaction_initiated();
      state_base_type::defer_event();
      return do_defer_event;
    }
    
    // Initiates a transition to DestinationState (without transition action).
    template< class DestinationState >
    result transit()
    {
      return transit_impl< DestinationState >(
        detail::no_transition_function() );
    }

    // Initiates a transition to DestinationState with a transition action.
    // The transition action must be a member of the innermost common context
    // or of one of its contexts.
    template< class DestinationState, class TransitionContext, class Event >
    result transit(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & evt )
    {
      return transit_impl< DestinationState >(
        detail::transition_function< TransitionContext, Event >(
          pTransitionAction, evt ) );
    }

    // Terminates this state. Depending on whether there are other orthogonal
    // states present this may or may not lead to the whole statemachine being
    // terminated.
    result terminate()
    {
      state_base_type::reaction_initiated();
      top_context().terminate( *this );
      return do_discard_event;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    simple_state() {}

    virtual ~simple_state()
    {
      // As a result of a throwing derived class constructor, this destructor
      // can be called before the context is set.
      if ( get_pointer( pContext_ ) != 0 )
      {
        if ( state_base_type::deferred_events() )
        {
          top_context().release_events( this );
        }

        pContext_->remove_inner_state( orthogonal_position );
      }
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    // TODO: check that this state really has such an inner orthogonal state
    typedef MostDerived inner_context_type;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      inner_orthogonal_position = 0 );

    typedef typename context_type::state_base_type state_base_type;
    typedef typename context_type::event_base_type event_base_type;
    typedef typename context_type::rtti_policy_type rtti_policy_type;

    typedef typename context_type::top_context_type top_context_type;
    typedef typename context_type::inner_context_ptr_type context_ptr_type;
    typedef typename context_type::state_list_type state_list_type;
    typedef intrusive_ptr< MostDerived > inner_context_ptr_type;
    typedef typename detail::make_list< InnerInitial >::type
      inner_initial_list;
    typedef typename mpl::push_front<
      typename context_type::context_type_list,
      context_type >::type context_type_list;


    virtual result react_impl(
      const event_base_type & evt,
      typename rtti_policy_type::id_type eventType )
    {
      state_base_type::enable_reaction();
      typedef detail::make_list< Reactions >::type reaction_list;
      result reactionResult =
        local_react_impl< reaction_list >( evt, eventType );

      if ( reactionResult == do_forward_event )
      {
        // we can only safely access pCurrentState if the handler did not
        // return do_discard_event!
        reactionResult = pContext_->Context::react_impl( evt, eventType );
      }

      return reactionResult;
    }

    virtual state_base_type * outer_state_ptr() const
    {
      return outer_state_ptr_impl<
        is_same< top_context_type, Context >::value >();
    }


    top_context_type & top_context()
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->top_context();
    }

    const top_context_type & top_context() const
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->top_context();
    }


    // Returns a pointer to the direct or indirect context identified by the
    // template parameter. In contrast to context(), this function cannot
    // return a pointer to this object.
    template< class OtherContext >
    const typename OtherContext::inner_context_ptr_type & context_ptr() const
    {
      return context_ptr_impl( OtherContext::inner_context_ptr_type() );
    }


    // Given a top context (i.e. a state machine), constructs this state with
    // all its outer and inner initial states. Used for initial construction
    // only.
    // After each successful (non-throwing) construction the current state is
    // reported back to the state machine.
    static void deep_construct( top_context_type & topContext )
    {
      deep_construct( &topContext, topContext );
    }

    // Constructs this state with all its inner initial states.
    // After each successful (non-throwing) construction the current state is
    // reported back to the state machine.
    static void deep_construct(
      const context_ptr_type & pContext,
      top_context_type & topContext )
    {
      topContext.add( pContext );
      const inner_context_ptr_type pInnerContext(
        shallow_construct( pContext ) );
      deep_construct_inner< inner_initial_list >( pInnerContext, topContext );
    }

    static inner_context_ptr_type shallow_construct(
      const context_ptr_type & pContext )
    {
      const inner_context_ptr_type pInnerContext( new MostDerived );
      pInnerContext->set_context( pContext );
      return pInnerContext;
    }

    void set_context( const context_ptr_type & pContext )
    {
      BOOST_ASSERT( get_pointer( pContext ) != 0 );
      pContext_ = pContext;
      base_type::set_context( orthogonal_position, get_pointer( pContext ) );
    }

    template< class InnerList >
    static void deep_construct_inner(
      const inner_context_ptr_type & pInnerContext,
      top_context_type & topContext )
    {
      deep_construct_inner_impl< InnerList >( pInnerContext, topContext );
    }

    template<>
    static void deep_construct_inner< detail::empty_list >(
      const inner_context_ptr_type & pInnerContext, top_context_type & topContext )
    {
      topContext.add( pInnerContext );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    template< class OtherContextPtr >
    const OtherContextPtr & context_ptr_impl(
      const OtherContextPtr & ) const
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->context_ptr< OtherContextPtr >();
    }

    template<>
    const context_ptr_type & context_ptr_impl(
      const context_ptr_type & ) const
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_;
    }


    template< class OtherContext >
    OtherContext & context_impl( OtherContext * )
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      return pContext_->context< OtherContext >();
    }

    template<>
    MostDerived & context_impl( MostDerived * )
    {
      return *polymorphic_downcast< MostDerived * >( this );
    }

    template< class OtherContext >
    const OtherContext & context_impl( OtherContext * ) const
    {
      BOOST_ASSERT( get_pointer( pContext_ ) != 0 );
      const OtherContext & constContext( *pContext_ );
      return constContext.context< OtherContext >();
    }

    template<>
    const MostDerived & context_impl( MostDerived * ) const
    {
      return *polymorphic_downcast< const MostDerived * >( this );
    }


    template< class DestinationState, class TransitionAction >
    result transit_impl( const TransitionAction & transitionAction )
    {
      base_type::reaction_initiated();
      typedef typename mpl::find_if<
        context_type_list,
        mpl::contains< typename DestinationState::context_type_list, _ >
      >::type common_context_iter;
      typedef typename mpl::deref< common_context_iter >::type
        common_context_type;
      typedef typename mpl::at<
        typename mpl::push_front< context_type_list, MostDerived >::type,
        typename mpl::distance<
          typename mpl::begin< context_type_list >::type,
          common_context_iter >::type >::type termination_state_type;

      termination_state_type & terminationState(
        context< termination_state_type >() );
      const common_context_type::inner_context_ptr_type pCommonContext(
        terminationState.context_ptr< common_context_type >() );
      top_context_type & topContext( pCommonContext->top_context() );

      topContext.terminate( terminationState );
      topContext.add( pCommonContext );
      transitionAction( *pCommonContext );

      // TODO: Check that the termination state and the construction state
      // have the same orthogonal_position

      typedef typename mpl::reverse< mpl::push_front<
        mpl::erase<
          typename DestinationState::context_type_list,
          typedef typename mpl::find<
            typename DestinationState::context_type_list, 
            common_context_type >::type,
          typename mpl::end< typename DestinationState::context_type_list >::type
        >::type,
        DestinationState
      >::type >::type context_list;

      detail::constructor< context_list, top_context_type >::construct(
        pCommonContext, topContext );

      return do_discard_event;
    }

    template< class ReactionList >
    result local_react_impl(
      const event_base_type & evt,
      typename rtti_policy_type::id_type eventType )
    {
      result reactionResult = mpl::front< ReactionList >::type::react(
        *polymorphic_downcast< MostDerived * >( this ), evt, eventType );

      if ( reactionResult == no_reaction )
      {
        reactionResult =
          local_react_impl< mpl::pop_front< ReactionList >::type >(
            evt, eventType );
      }

      return reactionResult;
    }

    template<>
    result local_react_impl< no_reactions >(
      const event_base_type &, typename rtti_policy_type::id_type )
    {
      return do_forward_event;
    }

    template< bool isOutermost >
    state_base_type * outer_state_ptr_impl() const
    {
      return get_pointer( pContext_ );
    }

    template<>
    state_base_type * outer_state_ptr_impl< true >() const
    {
      return 0;
    }


    template< class InnerList >
    static void deep_construct_inner_impl(
      const inner_context_ptr_type & pInnerContext,
      top_context_type & topContext )
    {
      mpl::front< InnerList >::type::deep_construct(
        pInnerContext, topContext );
      deep_construct_inner_impl< mpl::pop_front< InnerList >::type >(
        pInnerContext, topContext );
    }

    template<>
    static void deep_construct_inner_impl< detail::empty_list >(
      const inner_context_ptr_type &, top_context_type & ) {}


    context_ptr_type pContext_;
};



} // namespace fsm
} // namespace boost



#endif
