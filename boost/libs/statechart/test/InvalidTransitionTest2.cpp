//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/transition.hpp>

#include <boost/mpl/list.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvX : fsm::event< EvX > {};

struct Active;
struct InvalidTransitionTest : fsm::state_machine<
  InvalidTransitionTest, Active > {};

struct Idle0;
struct Idle1;
struct Active : fsm::simple_state< Active, InvalidTransitionTest,
  fsm::no_reactions, mpl::list< Idle0, Idle1 > >
{
};

  struct Idle00;
  struct Idle0 : fsm::simple_state< Idle0, Active::orthogonal< 0 >,
    fsm::no_reactions, Idle00 >
  {
  };

    struct Idle00 : fsm::simple_state< Idle00, Idle0 > {};

  struct Idle10;
  struct Idle1 : fsm::simple_state< Idle1, Active::orthogonal< 1 >,
    fsm::no_reactions, Idle10 >
  {
  };

    struct Idle10 : fsm::simple_state< Idle10, Idle1,
      fsm::transition< EvX, Idle00 > >
    {
    };

int main()
{
  InvalidTransitionTest machine;
  machine.initiate();
  return 0;
}
