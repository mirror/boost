//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/deep_history.hpp>



namespace fsm = boost::fsm;



struct EvX : fsm::event< EvX > {};

struct Active;
struct InvalidTransitionTest : fsm::state_machine<
  InvalidTransitionTest, Active > {};

struct Idle0;
struct Active : fsm::simple_state< Active, InvalidTransitionTest,
  fsm::no_reactions, Idle0, fsm::has_deep_history >
{
};

  struct Running0 : fsm::simple_state< Running0, Active > {};

  struct Idle0 : fsm::simple_state< Idle0, Active,
    fsm::transition< EvX, fsm::deep_history< Running0 > > >
  {
  };

int main()
{
  InvalidTransitionTest machine;
  machine.initiate();
  return 0;
}
