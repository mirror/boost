#ifndef BOOST_FSM_STATE_HPP_INCLUDED
#define BOOST_FSM_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/simple_state.hpp>



namespace boost
{
namespace fsm
{



template< class MostDerived,
          class Context,
          class Reactions = no_reactions,
          class InnerInitial = detail::empty_list,
          history_mode historyMode = has_no_history >
class state : public simple_state<
  MostDerived, Context, Reactions, InnerInitial, historyMode >
{
  typedef simple_state<
    MostDerived, Context, Reactions, InnerInitial, historyMode > base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    struct my_context
    {
      my_context( typename base_type::context_ptr_type pContext ) :
        pContext_( pContext )
      {
      }

      typename base_type::context_ptr_type pContext_;
    };

    typedef state my_base;

    state( my_context ctx )
    {
      base_type::set_context( ctx.pContext_ );
    }

    virtual ~state() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    // See base class for documentation
    typedef typename base_type::outermost_context_type outermost_context_type;
    typedef typename base_type::inner_context_ptr_type inner_context_ptr_type;
    typedef typename base_type::context_ptr_type context_ptr_type;
    typedef typename base_type::inner_initial_list inner_initial_list;

    static void initial_deep_construct(
      outermost_context_type & outermostContext )
    {
      deep_construct( &outermostContext, outermostContext );
    }

    // See base class for documentation
    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_type & outermostContext )
    {
      const inner_context_ptr_type pInnerContext(
        shallow_construct( pContext ) );
      base_type::deep_construct_inner< inner_initial_list >(
        pInnerContext, outermostContext );
    }

    static inner_context_ptr_type shallow_construct(
      const context_ptr_type & pContext )
    {
      return inner_context_ptr_type(
        new MostDerived( my_context( pContext ) ) );
    }
};



} // namespace fsm
} // namespace boost



#endif
