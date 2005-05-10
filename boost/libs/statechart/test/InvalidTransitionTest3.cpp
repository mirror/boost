//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/shallow_history.hpp>



namespace sc = boost::statechart;



struct EvX : sc::event< EvX > {};

struct Active;
struct InvalidTransitionTest : sc::state_machine<
  InvalidTransitionTest, Active > {};

struct Idle;
struct Active : sc::simple_state< Active, InvalidTransitionTest,
  sc::no_reactions, Idle, sc::has_shallow_history >
{
};

  // Invalid transition to shallow history from a state residing on the same
  // level as the history connector.
  struct Idle : sc::simple_state< Idle, Active,
    sc::transition< EvX, sc::shallow_history< Idle > > >
  {
  };


int main()
{
  InvalidTransitionTest machine;
  machine.initiate();
  return 0;
}
