#ifndef BOOST_FSM_HISTORY_HPP_INCLUDED
#define BOOST_FSM_HISTORY_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp> // orthogonal_position_type

#include <boost/static_assert.hpp>



namespace boost
{
namespace fsm
{

  
  
template< class DefaultState >
class shallow_history
{
  public:
    // If you receive a 
    // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or similar
    // compiler error here then you forgot to pass either
    // fsm::has_shallow_history or fsm::has_full_history as the last parameter
    // of DefaultState's context.
    BOOST_STATIC_ASSERT( DefaultState::context_type::shallow_history );

    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef typename DefaultState::outermost_context_type
      outermost_context_type;
    typedef typename DefaultState::context_type context_type;
    typedef typename DefaultState::context_ptr_type context_ptr_type;
    typedef typename DefaultState::context_type_list context_type_list;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      orthogonal_position = DefaultState::orthogonal_position );

    BOOST_STATIC_CONSTANT( bool, history_destination = true );

    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_type & outermostContext )
    {
      outermostContext.construct_with_shallow_history< DefaultState >(
        pContext );
    }

    static void reserve_history_slot(
      outermost_context_type & outermostContext )
    {
      DefaultState::reserve_history_slot( outermostContext );
    }
};



template< class DefaultState >
class deep_history
{
  public:
    // If you receive a 
    // "use of undefined type 'boost::STATIC_ASSERTION_FAILURE<x>'" or similar
    // compiler error here then you forgot to pass either
    // fsm::has_deep_history or fsm::has_full_history as the last parameter of
    // DefaultState's context.
    BOOST_STATIC_ASSERT( DefaultState::context_type::deep_history );

    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    typedef typename DefaultState::outermost_context_type
      outermost_context_type;
    typedef typename DefaultState::context_type context_type;
    typedef typename DefaultState::context_ptr_type context_ptr_type;
    typedef typename DefaultState::context_type_list context_type_list;
    BOOST_STATIC_CONSTANT(
      detail::orthogonal_position_type,
      orthogonal_position = DefaultState::orthogonal_position );

    BOOST_STATIC_CONSTANT( bool, history_destination = true );

    static void deep_construct(
      const context_ptr_type & pContext,
      outermost_context_type & outermostContext )
    {
      outermostContext.construct_with_deep_history< DefaultState >(
        pContext );
    }

    static void reserve_history_slot(
      outermost_context_type & outermostContext )
    {
      DefaultState::reserve_history_slot( outermostContext );
    }
};



} // namespace fsm
} // namespace boost



#endif
