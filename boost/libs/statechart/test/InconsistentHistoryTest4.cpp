//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/deep_history.hpp>
#include <boost/fsm/transition.hpp>



namespace fsm = boost::fsm;



struct EvX : fsm::event< EvX > {};

struct A;
struct InconsistentHistoryTest : fsm::state_machine<
  InconsistentHistoryTest, A > {};
struct B;
// A only has shallow history
struct A : fsm::simple_state< A, InconsistentHistoryTest,
  fsm::transition< EvX, fsm::deep_history< B > >,
  B, fsm::has_shallow_history > {};
struct B : fsm::simple_state< B, A > {};

int main()
{
  InconsistentHistoryTest machine;
  machine.initiate();
  return 0;
}
