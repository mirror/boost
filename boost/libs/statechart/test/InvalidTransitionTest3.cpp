//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/shallow_history.hpp>



namespace fsm = boost::fsm;



struct EvX : fsm::event< EvX > {};

struct Active;
struct InvalidTransitionTest : fsm::state_machine<
  InvalidTransitionTest, Active > {};

struct Idle;
struct Active : fsm::simple_state< Active, InvalidTransitionTest,
  fsm::no_reactions, Idle, fsm::has_shallow_history >
{
};

  // Invalid transition to shallow history from a state residing on the same
  // level as the history connector.
  struct Idle : fsm::simple_state< Idle, Active,
    fsm::transition< EvX, fsm::shallow_history< Idle > > >
  {
  };

int main()
{
  InvalidTransitionTest machine;
  machine.initiate();
  return 0;
}
