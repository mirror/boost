//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/rtti_policy.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state_machine.hpp>

#include <boost/fsm/transition.hpp>
#include <boost/fsm/termination.hpp>

#include <iostream>
#include <iomanip>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



//////////////////////////////////////////////////////////////////////////////
// Displays the runtime sizes of states
//////////////////////////////////////////////////////////////////////////////
struct DummyEvent1 : fsm::event< DummyEvent1 > {};
struct DummyEvent2 : fsm::event< DummyEvent2 > {};
struct DummyEvent3 : fsm::event< DummyEvent3 > {};
struct DummyEvent4 : fsm::event< DummyEvent4 > {};


struct UnconnectedOuterState;
struct DummyMachine : fsm::state_machine< DummyMachine, UnconnectedOuterState > {};


struct UnconnectedInnerState;
struct UnconnectedOuterState : fsm::simple_state< UnconnectedOuterState, DummyMachine, fsm::no_reactions, mpl::list< UnconnectedInnerState > > {};
struct UnconnectedInnerState : fsm::simple_state< UnconnectedInnerState, UnconnectedOuterState > {};

struct OneTransitionInnerState;
struct OneTransitionOuterState :
  fsm::simple_state< OneTransitionOuterState, DummyMachine, 
    fsm::termination< DummyEvent1 >, OneTransitionInnerState > {};
struct OneTransitionInnerState :
  fsm::simple_state< OneTransitionInnerState, OneTransitionOuterState, 
    fsm::termination< DummyEvent1 > > {};

struct TwoTransitionInnerState;
struct TwoTransitionOuterState : fsm::simple_state< TwoTransitionOuterState, DummyMachine,
  mpl::list<
    fsm::termination< DummyEvent1 >,
    fsm::termination< DummyEvent2 > >,
  TwoTransitionInnerState > {};
struct TwoTransitionInnerState : fsm::simple_state< TwoTransitionInnerState, TwoTransitionOuterState, 
  mpl::list<
    fsm::termination< DummyEvent1 >,
    fsm::termination< DummyEvent2 > > > {};

struct ThreeTransitionInnerState;
struct ThreeTransitionOuterState : fsm::simple_state< ThreeTransitionOuterState, DummyMachine, 
  mpl::list<
    fsm::termination< DummyEvent1 >,
    fsm::termination< DummyEvent2 >,
    fsm::termination< DummyEvent3 > >,
  ThreeTransitionInnerState > {};
struct ThreeTransitionInnerState : fsm::simple_state< ThreeTransitionInnerState, ThreeTransitionOuterState, 
  mpl::list<
    fsm::termination< DummyEvent1 >,
    fsm::termination< DummyEvent2 >,
    fsm::termination< DummyEvent3 > > > {};


int main( int argc, char * argv[] )
{
  argc;
  argv;

  std::cout << std::left <<
    "boost::fsm::state sizes\n\n" <<
    std::setw( 50 ) << "detail::counted_base< unsigned char, false >: " <<
      sizeof( fsm::detail::counted_base< unsigned char, false > ) << "\n" <<
    std::setw( 50 ) << "detail::state_base< ... >: " <<
    sizeof( fsm::detail::state_base< std::allocator< void >, fsm::rtti_policy > ) << "\n" <<
    std::setw( 50 ) << "detail::leaf_state< ... >: " <<
      sizeof( fsm::detail::leaf_state< 
        std::allocator< void >, fsm::rtti_policy > ) << "\n" <<
    std::setw( 50 ) << "detail::node_state< 1, ... >: " <<
      sizeof( fsm::detail::node_state< 1,
        std::allocator< void >, fsm::rtti_policy > ) << "\n" <<
    std::setw( 50 ) << "detail::node_state< 2, ... >: " <<
      sizeof( fsm::detail::node_state< 2,
        std::allocator< void >, fsm::rtti_policy > ) << "\n" <<
    std::setw( 50 ) << "detail::node_state< 3, ... >: " <<
      sizeof( fsm::detail::node_state< 3,
        std::allocator< void >, fsm::rtti_policy > ) << "\n\n" <<

    std::setw( 50 ) << "simple_state< _, _, no_transitions, _ >: " <<
      sizeof( UnconnectedOuterState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _ >: " <<
      sizeof( UnconnectedInnerState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _ >, _ >: " <<
      sizeof( OneTransitionOuterState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _ > >: " <<
      sizeof( OneTransitionInnerState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _, _ >, _ >: " <<
      sizeof( TwoTransitionOuterState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _, _ > >: " <<
      sizeof( TwoTransitionInnerState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _, _, _ >, _ >: " <<
      sizeof( ThreeTransitionOuterState ) << "\n" <<
    std::setw( 50 ) << "simple_state< _, _, mpl::list< _, _, _ > >: " <<
      sizeof( ThreeTransitionInnerState ) << std::endl;

	return 0;
}