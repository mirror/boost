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
#include <boost/fsm/deep_history.hpp>

#include <boost/mpl/list.hpp>
#include <boost/shared_ptr.hpp>


namespace fsm = boost::fsm;
namespace mpl = boost::mpl;


struct EvToB : fsm::event< EvToB > {};

struct EvToD : fsm::event< EvToD > {};
struct EvToDShallow : fsm::event< EvToDShallow > {};
struct EvToDDeep : fsm::event< EvToDDeep > {};

struct EvToF : fsm::event< EvToF > {};
struct EvToFShallow : fsm::event< EvToFShallow > {};
struct EvToFDeep : fsm::event< EvToFDeep > {};

struct EvToH : fsm::event< EvToH > {};
struct EvToI : fsm::event< EvToI > {};



struct A;
struct HistoryTest : fsm::state_machine< HistoryTest, A > {};

struct B;
struct D;
struct F;
struct H;
struct I;
struct A : fsm::simple_state< A, HistoryTest, mpl::list<
  fsm::transition< EvToB, B >,
  fsm::transition< EvToD, D >,
  fsm::transition< EvToDShallow, fsm::shallow_history< D > >,
  fsm::transition< EvToDDeep, fsm::deep_history< D > >,
  fsm::transition< EvToF, F >,
  fsm::transition< EvToFShallow, fsm::shallow_history< F > >,
  fsm::transition< EvToFDeep, fsm::deep_history< F > >,
  fsm::transition< EvToH, H >,
  fsm::transition< EvToI, I > >, B >
{
};

  struct B : fsm::simple_state< B, A > {};
  struct C : fsm::simple_state<
    C, A, fsm::no_reactions, D, fsm::has_full_history > {};

    struct D : fsm::simple_state< D, C > {};
    struct E : fsm::simple_state<
      E, C, fsm::no_reactions, F, fsm::has_full_history > {};

      struct F : fsm::simple_state< F, E > {};
      struct G : fsm::simple_state< G, E, fsm::no_reactions, H > {};

        struct H : fsm::simple_state< H, G > {};
        struct I : fsm::simple_state< I, G > {};

int test_main( int, char* [] )
{
  boost::shared_ptr< HistoryTest > pM =
    boost::shared_ptr< HistoryTest >( new HistoryTest() );

  try
  {
    pM->state_downcast< const B & >();
    return -1; // state_downcast is broken
  }
  catch ( const std::bad_cast & )
  {
    // state_downcast rightly throws on a terminated machine
  }

  pM->initiate();

  try
  {
    pM->state_downcast< const D & >();
    return -1; // state_downcast is broken
  }
  catch ( const std::bad_cast & )
  {
    // state_downcast rightly throws on a running machine in the wrong state.
  }

  pM->state_downcast< const B & >();

  // No history has been saved yet -> default state
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const D & >();
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const D & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  // Direct inner is E when history is saved -> F
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToH() );
  pM->state_downcast< const H & >();
  // Direct inner is E when history is saved -> F
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToF() );
  pM->state_downcast< const F & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  // Direct inner was E when history was saved -> F
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const F & >();

  pM->initiate();
  // History was cleared in termination -> default state
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const D & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->clear_shallow_history< C, 0 >();
  // History was cleared -> default state
  pM->process_event( EvToDShallow() );
  pM->state_downcast< const D & >();

  pM = boost::shared_ptr< HistoryTest >( new HistoryTest() );
  pM->initiate();
  pM->state_downcast< const B & >();

  // No history has been saved yet -> default state
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const D & >();
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const D & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const I & >();

  pM->process_event( EvToH() );
  pM->state_downcast< const H & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const H & >();

  pM->process_event( EvToF() );
  pM->state_downcast< const F & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const F & >();

  pM->initiate();
  // History was cleared in termination -> default state
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const D & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->clear_deep_history< C, 0 >();
  // History was cleared -> default state
  pM->process_event( EvToDDeep() );
  pM->state_downcast< const D & >();


  pM = boost::shared_ptr< HistoryTest >( new HistoryTest() );
  pM->initiate();
  pM->state_downcast< const B & >();

  // No history has been saved yet -> default state
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const F & >();
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  // Direct inner is G when history is saved -> H
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const H & >();

  pM->process_event( EvToH() );
  pM->state_downcast< const H & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  // Direct inner was G when history was saved -> H
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const H & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->initiate();
  // History was cleared in termination -> default state
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->clear_shallow_history< E, 0 >();
  // History was cleared -> default state
  pM->process_event( EvToFShallow() );
  pM->state_downcast< const F & >();

  pM = boost::shared_ptr< HistoryTest >( new HistoryTest() );
  pM->initiate();
  pM->state_downcast< const B & >();

  // No history has been saved yet -> default state
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const F & >();
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const I & >();

  pM->process_event( EvToH() );
  pM->state_downcast< const H & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const H & >();

  pM->process_event( EvToF() );
  pM->state_downcast< const F & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const F & >();

  pM->initiate();
  // History was cleared in termination -> default state
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const F & >();

  pM->process_event( EvToI() );
  pM->state_downcast< const I & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const B & >();
  pM->clear_deep_history< E, 0 >();
  // History was cleared -> default state
  pM->process_event( EvToFDeep() );
  pM->state_downcast< const F & >();

  return 0;
}
