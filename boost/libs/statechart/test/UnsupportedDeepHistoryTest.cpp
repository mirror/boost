//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/deep_history.hpp>

#include <boost/mpl/list.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct A;
struct UnsupportedDeepHistoryTest : fsm::state_machine<
  UnsupportedDeepHistoryTest, A > {};

struct B;
struct A : fsm::simple_state< A, UnsupportedDeepHistoryTest,
  fsm::no_reactions, B, fsm::has_deep_history > {};

  struct C;
  struct D;
  struct B : fsm::simple_state< B, A, fsm::no_reactions, mpl::list< C, D > > {};

    struct C : fsm::simple_state< C, B::orthogonal< 0 > > {};
    struct D : fsm::simple_state< D, B::orthogonal< 1 > > {};


int main()
{
  UnsupportedDeepHistoryTest machine;
  machine.initiate();
  return 0;
}
