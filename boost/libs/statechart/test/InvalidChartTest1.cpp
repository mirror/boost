//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>



namespace fsm = boost::fsm;



struct A;
struct InvalidChartTest : fsm::state_machine< InvalidChartTest, A > {};

struct A : fsm::simple_state< A, InvalidChartTest > {};

  // A does not have inner states
  struct B : fsm::simple_state< B, A > {};


int main()
{
  InvalidChartTest machine;
  machine.initiate();
  return 0;
}
