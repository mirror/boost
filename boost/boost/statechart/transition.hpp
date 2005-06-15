#ifndef BOOST_STATECHART_TRANSITION_HPP_INCLUDED
#define BOOST_STATECHART_TRANSITION_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/statechart/result.hpp>

#include <boost/mpl/if.hpp>

#include <boost/cast.hpp> // boost::polymorphic_downcast
#include <boost/type_traits/is_same.hpp>



namespace boost
{
namespace statechart
{
namespace detail
{



//////////////////////////////////////////////////////////////////////////////
struct no_context
{
  template< class Event >
  void no_function( const Event & );
};



} // namespace detail



//////////////////////////////////////////////////////////////////////////////
template< class Event, class Destination,
          class TransitionContext = detail::no_context,
          void ( TransitionContext::*pTransitionAction )( const Event & ) =
            &detail::no_context::no_function< Event > >
class transition
{
  private:
    //////////////////////////////////////////////////////////////////////////
    struct react_with_transition_action_impl
    {
      template< class State, class EventBase >
      static detail::reaction_result react( State & stt, const EventBase & toEvent )
      {
        return detail::result_utility::get_result(
          stt.template transit< Destination >(
            pTransitionAction,
            *polymorphic_downcast< const Event * >( &toEvent ) ) );
      }
    };

    struct react_without_transition_action_impl
    {
      template< class State, class EventBase >
      static detail::reaction_result react( State & stt, const EventBase & )
      {
        return detail::result_utility::get_result(
          stt.template transit< Destination >() );
      }
    };

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    template< class State, class EventBase, class IdType >
    static detail::reaction_result react(
      State & stt, const EventBase & evt, const IdType & eventType )
    {
      if ( eventType == Event::static_type() )
      {
        typedef typename mpl::if_<
          is_same< TransitionContext, detail::no_context >,
          react_without_transition_action_impl,
          react_with_transition_action_impl
        >::type impl;
        return impl::react( stt, evt );
      }
      else
      {
        return detail::no_reaction;
      }
    }
};



} // namespace statechart
} // namespace boost



#endif
