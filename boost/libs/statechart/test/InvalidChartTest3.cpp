//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>

#include <boost/mpl/list.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct A;
struct InvalidChartTest : fsm::state_machine< InvalidChartTest, A > {};
struct B;
struct C;
struct A : fsm::simple_state<
  A, InvalidChartTest, fsm::no_reactions, mpl::list< B, C > > {};

// B resides in the 0th region not the 1st
struct B : fsm::simple_state< B, A::orthogonal< 1 > > {};
struct C : fsm::simple_state< C, A::orthogonal< 1 > > {};

int main()
{
  InvalidChartTest machine;
  machine.initiate();
  return 0;
}
