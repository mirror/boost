#ifndef STATE_HPP
#define STATE_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_base.hpp>
#include <boost/fsm/event_base.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/assert.hpp>

#include <utility>



namespace boost
{
namespace fsm
{

template< class Context > class no_inner;



// Base class for all states
template< class Derived,
          class Context, // either an outer state or a state_machine
          class InnerInitial = no_inner< Derived > > // initial inner state
class state : public state_base
{
  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be protected.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef Context context_type;

    // Returns a reference to the context identified by the template
    // parameter. This can either be _this_ object or one of its
    // direct or indirect contexts
    template< class Context >
    Context & context()
    {
      return context_impl( static_cast< Context * >( 0 ) );
    }

    template< class Context >
    const Context & context() const
    {
      return context_impl( static_cast< Context * >( 0 ) );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    typedef state base_type;
    typedef typename context_type::inner_context_ptr_type context_ptr_type;

    state( context_ptr_type pContext ) :
      state_base( boost::get_pointer( pContext ) ),
      pContext_( pContext )
    {
      // pContext can either be a plain old pointer or a shared pointer
      BOOST_ASSERT( boost::get_pointer( pContext_ ) != 0 );
    }


    // Initiates a transition to next_state (without transition action).
    template< class NextState >
    const bool transit_to()
    {
      typedef common_context< NextState >::result common_context_type;
      const common_context_type::inner_context_ptr_type pCommonContext(
        context_ptr< common_context_type >() );
      top_context_type & topContext( pCommonContext->top_context() );
      topContext.current_context( pCommonContext, false );
      NextState::construct( pCommonContext, topContext );

      return true;
    }

    // Initiates a transition to next_state with a transition action. The
    // transition action must be a member of the innermost common context
    // or of one of its contexts.
    template< class NextState, class TransitionContext, class Event >
    const bool transit_to(
      void ( TransitionContext::*pTransitionAction )( const Event & ),
      const Event & theEvent )
    {
      typedef common_context< NextState >::result common_context_type;
      const common_context_type::inner_context_ptr_type pCommonContext(
        context_ptr< common_context_type >() );
      top_context_type & topContext( pCommonContext->top_context() );
      topContext.current_context( pCommonContext, false );
      ( pCommonContext->context< TransitionContext >()
        .*pTransitionAction )( theEvent );
      NextState::construct( pCommonContext, topContext );

      return true;
    }

    // Terminates the state machine, all future events will be ignored
    const bool terminate()
    {
      top_context().terminate();
      return true;
    }


    void post_event( std::auto_ptr< const event_base > pEvent )
    {
      top_context().post_event( pEvent );
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef typename context_type::top_context_type top_context_type;
    typedef context_type::state_base_ptr_type state_base_ptr_type;
    // TODO: replace shared_ptr with intrusive_ptr
    typedef boost::shared_ptr< Derived > inner_context_ptr_type;

    // result is either equal to:
    // - TestContext (TestContext is indeed our direct or one of our indirect
    //   contexts).
    // - void (TestContext is not one of our contexts).
    template< class TestContext >
    struct is_context
    {
      typedef context_type::is_context< TestContext >::result result;
    };

    template<>
    struct is_context< context_type >
    {
      typedef context_type result;
    };


    // result is the innermost common context of this state and other_state.
    template< class OtherState >
    struct common_context
    {
      private:
        template< class FoundCommonContext >
        struct impl_holder
        {
          template< class OtherState2 >
          struct impl
          {
            typedef FoundCommonContext result;
          };
        };

        template<>
        struct impl_holder< void >
        {
          template< class OtherState2 >
          struct impl
          {
            typedef context_type::template common_context< OtherState2 >::result result;
          };
        };

      public:
        typedef impl_holder< OtherState::is_context< context_type >::result >::
          impl< OtherState >::result result;
    };


    top_context_type & top_context()
    {
      return pContext_->top_context();
    }


    // Returns a pointer to the direct or indirect context identified by the
    // template parameter. In contrast to context(), this function cannot
    // return a pointer to this object.
    template< class Context >
    const typename Context::inner_context_ptr_type & context_ptr() const
    {
      return context_ptr_impl( Context::inner_context_ptr_type() );
    }


    // Given a top context (i.e. a state machine), constructs this state with
    // all its outer and inner initial states. Used for initial construction
    // only.
    // After each successful (non-throwing) construction the current state is
    // reported back to the state machine.
    static void construct( top_context_type & topContext )
    {
      return construct( &topContext, topContext );
    }

    // Given an existing arbitrary context (may be a state machine or a
    // direct or indirect outer state), constructs this state with all its
    // remaining outer and inner initial states.
    // After each successful (non-throwing) construction the current state is
    // reported back to the state machine.
    template< class ContextPtr >
    static void construct(
      const ContextPtr & pContext,
      top_context_type & topContext )
    {
      return context_type::construct( pContext, topContext );
    }

    template<>
    static void construct(
      const context_ptr_type & pContext,
      top_context_type & topContext )
    {
      topContext.current_context( pContext, false );
      return InnerInitial::construct( 
        inner_context_ptr_type( new Derived( pContext ) ), topContext );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    template< class ContextPtr >
    const ContextPtr & context_ptr_impl(
      const ContextPtr & ) const
    {
      return pContext_->context_ptr< ContextPtr >();
    }

    template<>
    const context_ptr_type & context_ptr_impl(
      const context_ptr_type & ) const
    {
      return pContext_;
    }

    template< class Context >
    Context & context_impl( Context * )
    {
      return pContext_->context< Context >();
    }

    template<>
    Derived & context_impl( Derived * )
    {
      return static_cast< Derived & >( *this );
    }

    template< class Context >
    const Context & context_impl( Context * ) const
    {
      const Context & constContext( *pContext_ );
      return constContext.context< Context >();
    }

    template<>
    const Derived & context_impl( Derived * ) const
    {
      return static_cast< const Derived & >( *this );
    }

    const context_ptr_type pContext_;
};



// Helper class for innermost states. Not to be used by users
template< class Context >
class no_inner
{
  public:
    //////////////////////////////////////////////////////////////////////////
    typedef Context context_type;
    typedef typename context_type::state_base_ptr_type state_base_ptr_type;
    typedef typename context_type::inner_context_ptr_type context_ptr_type;
    typedef typename context_type::top_context_type top_context_type;

    static void construct(
      const context_ptr_type & pContext,
      top_context_type & topContext )
    {
      topContext.current_context( pContext, true );
    }
};



} // namespace fsm
} // namespace boost



#endif
