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

#include <boost/test/test_tools.hpp>


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

struct EvToM : fsm::event< EvToM > {};
struct EvToQ : fsm::event< EvToQ > {};


struct A;
struct HistoryTest : fsm::state_machine< HistoryTest, A > {};

struct B;
struct D;
struct F;
struct H;
struct I;
struct M;
struct Q;
struct A : fsm::simple_state< A, HistoryTest, mpl::list<
  fsm::transition< EvToB, B >,
  fsm::transition< EvToD, D >,
  fsm::transition< EvToDShallow, fsm::shallow_history< D > >,
  fsm::transition< EvToDDeep, fsm::deep_history< D > >,
  fsm::transition< EvToF, F >,
  fsm::transition< EvToFShallow, fsm::shallow_history< F > >,
  fsm::transition< EvToFDeep, fsm::deep_history< F > >,
  fsm::transition< EvToH, H >,
  fsm::transition< EvToI, I >,
  fsm::transition< EvToM, M >,
  fsm::transition< EvToQ, Q > >, B >
{
};

  struct J;
  struct N;
  struct B : fsm::simple_state<
    B, A, fsm::no_reactions,
    mpl::list< fsm::shallow_history< J >, fsm::deep_history< N > >,
    fsm::has_full_history > {};

    struct J : fsm::simple_state< J, B::orthogonal< 0 > > {};
    struct L;
    struct K : fsm::simple_state<
      K, B::orthogonal< 0 >, fsm::no_reactions, L > {};

      struct L : fsm::simple_state< L, K > {};
      struct M : fsm::simple_state< M, K > {};

    struct N : fsm::simple_state< N, B::orthogonal< 1 > > {};
    struct P;
    struct O : fsm::simple_state<
      O, B::orthogonal< 1 >, fsm::no_reactions, P > {};

      struct P : fsm::simple_state< P, O > {};
      struct Q : fsm::simple_state< Q, O > {};

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

  // state_downcast sanity check
  // TODO: Use BOOST_REQUIRE_THROW as soon as it's available
  BOOST_CHECK_THROW( pM->state_downcast< const B & >(), std::bad_cast );
  pM->initiate();
  BOOST_CHECK_THROW( pM->state_downcast< const D & >(), std::bad_cast );

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

  // Given that history transitions and history initial states are implemented
  // with the same code we just make a few sanity checks and trust that the
  // rest will work just like we tested above.
  pM->process_event( EvToB() );
  pM->state_downcast< const J & >();
  pM->state_downcast< const N & >();
  pM->process_event( EvToM() );
  pM->state_downcast< const M & >();
  // Direct inner is K when history is saved -> L
  pM->process_event( EvToB() );
  pM->state_downcast< const L & >();

  pM->state_downcast< const N & >();
  pM->process_event( EvToQ() );
  pM->state_downcast< const Q & >();
  pM->process_event( EvToB() );
  pM->state_downcast< const Q & >();

  return 0;
}
