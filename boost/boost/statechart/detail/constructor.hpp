#ifndef BOOST_FSM_DETAIL_CONSTRUCTOR_HPP_INCLUDED
#define BOOST_FSM_DETAIL_CONSTRUCTOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/mpl/apply_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/size.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



template< class ContextList, class OutermostContext >
struct constructor;

//////////////////////////////////////////////////////////////////////////////
template< class ContextList, class OutermostContext >
struct outer_constructor
{
  typedef typename mpl::front< ContextList >::type to_construct;
  typedef typename to_construct::context_ptr_type context_ptr_type;
  typedef typename to_construct::inner_context_ptr_type
    inner_context_ptr_type;

  typedef typename to_construct::inner_initial_list inner_initial_list;
  typedef typename mpl::pop_front< ContextList >::type inner_context_list;
  typedef mpl::integral_c< long,
    mpl::front< inner_context_list >::type::orthogonal_position
  > inner_orthogonal_position;

  typedef typename mpl::erase< 
    inner_initial_list,
    typename mpl::advance<
      typename mpl::begin< inner_initial_list >::type,
      inner_orthogonal_position >::type >::type remaining_inner_initial_list;

  static void construct(
    const context_ptr_type & pContext, OutermostContext & outermostContext )
  {
    outermostContext.add( pContext );
    const inner_context_ptr_type pInnerContext =
      to_construct::shallow_construct( pContext );
    to_construct::template deep_construct_inner<
      remaining_inner_initial_list >( pInnerContext, outermostContext );
    mpl::front< inner_context_list >::type::reserve_history_slot(
      outermostContext );
    constructor< inner_context_list, OutermostContext >::construct(
      pInnerContext, outermostContext );
  }
};

//////////////////////////////////////////////////////////////////////////////
template< class ContextList, class OutermostContext >
struct inner_constructor
{
  typedef typename mpl::front< ContextList >::type to_construct;
  typedef typename to_construct::context_ptr_type context_ptr_type;

  static void construct(
    const context_ptr_type & pContext, OutermostContext & outermostContext )
  {
    to_construct::deep_construct( pContext, outermostContext );
  }
};

//////////////////////////////////////////////////////////////////////////////
template< class ContextList, class OutermostContext >
struct constructor_impl : public mpl::apply_if< 
  mpl::equal_to< mpl::size< ContextList >, mpl::integral_c< long, 1 > >,
  mpl::identity< inner_constructor< ContextList, OutermostContext > >,
  mpl::identity< outer_constructor< ContextList, OutermostContext > > > {};


//////////////////////////////////////////////////////////////////////////////
template< class ContextList, class OutermostContext >
struct constructor :
  constructor_impl< ContextList, OutermostContext >::type {};

//////////////////////////////////////////////////////////////////////////////
template< class CommonContext, class DestinationState >
struct make_context_list
{
  typedef typename mpl::reverse< typename mpl::push_front<
    typename mpl::erase<
      typename DestinationState::context_type_list,
      typename mpl::find<
        typename DestinationState::context_type_list, 
        CommonContext
      >::type,
      typename mpl::end<
        typename DestinationState::context_type_list
      >::type
    >::type,
    DestinationState
  >::type >::type type;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
