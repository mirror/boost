//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct A;
struct InconsistentHistoryTest : fsm::state_machine<
  InconsistentHistoryTest, A > {};
struct B;
struct A : fsm::simple_state<
  A, InconsistentHistoryTest, fsm::no_reactions, B > {};
struct B : fsm::simple_state< B, A > {};

int main()
{
  InconsistentHistoryTest machine;
  machine.initiate();
  // A does not have history
  machine.clear_deep_history< A, 0 >();
  return 0;
}
