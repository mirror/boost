//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/test/test_tools.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvToB : fsm::event< EvToB > {};
struct EvToF : fsm::event< EvToF > {};
struct EvCheck : fsm::event< EvCheck > {};

struct A;
struct StateCastTest : fsm::state_machine< StateCastTest, A >
{
  template< class State >
  void AssertInState()
  {
    BOOST_REQUIRE( state_downcast< const State * >() != 0 );
    // TODO: Use BOOST_REQUIRE_NO_THROW as soon as it's available
    BOOST_CHECK_NO_THROW( state_downcast< const State & >() );
    BOOST_REQUIRE( state_cast< const State * >() != 0 );
    BOOST_CHECK_NO_THROW( state_cast< const State & >() );
  }

  template< class State >
  void AssertNotInState()
  {
    BOOST_REQUIRE( state_downcast< const State * >() == 0 );
    // TODO: Use BOOST_REQUIRE_THROW as soon as it's available
    BOOST_CHECK_THROW( state_downcast< const State & >(), std::bad_cast );
    BOOST_REQUIRE( state_cast< const State * >() == 0 );
    BOOST_CHECK_THROW( state_cast< const State & >(), std::bad_cast );
  }
};

template< class State, class FromState >
void AssertInState( const FromState & theState )
{
  BOOST_REQUIRE( theState.template state_downcast< const State * >() != 0 );
  // TODO: Use BOOST_REQUIRE_NO_THROW as soon as it's available
  BOOST_CHECK_NO_THROW( theState.template state_downcast< const State & >() );
  BOOST_REQUIRE( theState.template state_cast< const State * >() != 0 );
  BOOST_CHECK_NO_THROW( theState.template state_cast< const State & >() );
}

template< class State, class FromState >
void AssertNotInState( const FromState & theState )
{
  BOOST_REQUIRE( theState.template state_downcast< const State * >() == 0 );
  // TODO: Use BOOST_REQUIRE_THROW as soon as it's available
  BOOST_CHECK_THROW( theState.template state_downcast< const State & >(), std::bad_cast );
  BOOST_REQUIRE( theState.template state_cast< const State * >() == 0 );
  BOOST_CHECK_THROW( theState.template state_cast< const State & >(), std::bad_cast );
}

struct B;
struct C;
struct D;
struct A : fsm::simple_state<
  A, StateCastTest, fsm::transition< EvToB, B >, mpl::list< C, D > > {};

  struct E;
  struct C : fsm::simple_state< C, A::orthogonal< 0 >, fsm::no_reactions, E > {};

    struct E : fsm::state< E, C, fsm::custom_reaction< EvCheck > >
    {
      E( my_context ctx ) : my_base( ctx )
      {
        post_event( boost::intrusive_ptr< EvCheck >( new EvCheck() ) );
      }

      fsm::result react( const EvCheck & );
    };

    struct F : fsm::state< F, C, fsm::custom_reaction< EvCheck > >
    {
      F( my_context ctx ) : my_base( ctx )
      {
        post_event( boost::intrusive_ptr< EvCheck >( new EvCheck() ) );
      }

      fsm::result react( const EvCheck & );
    };

  struct G;
  struct D : fsm::simple_state< D, A::orthogonal< 1 >, fsm::no_reactions, G > {};
  
    struct G : fsm::simple_state< G, D > {};
    struct H : fsm::simple_state< H, D > {};

struct B : fsm::simple_state< B, StateCastTest, fsm::transition< EvToF, F > > {};

fsm::result E::react( const EvCheck & )
{
  AssertInState< A >( *this );
  AssertNotInState< B >( *this );
  AssertInState< C >( *this );
  AssertInState< D >( *this );
  AssertInState< E >( *this );
  AssertNotInState< F >( *this );
  AssertInState< G >( *this );
  AssertNotInState< H >( *this );
  return discard_event();
}

fsm::result F::react( const EvCheck & )
{
  AssertInState< A >( *this );
  AssertNotInState< B >( *this );
  AssertInState< C >( *this );
  AssertInState< D >( *this );
  AssertNotInState< E >( *this );
  AssertInState< F >( *this );
  AssertInState< G >( *this );
  AssertNotInState< H >( *this );
  return discard_event();
}


int test_main( int, char* [] )
{
  StateCastTest machine;

  machine.AssertNotInState< A >();
  machine.AssertNotInState< B >();
  machine.AssertNotInState< C >();
  machine.AssertNotInState< D >();
  machine.AssertNotInState< E >();
  machine.AssertNotInState< F >();
  machine.AssertNotInState< G >();
  machine.AssertNotInState< H >();

  machine.initiate();

  machine.AssertInState< A >();
  machine.AssertNotInState< B >();
  machine.AssertInState< C >();
  machine.AssertInState< D >();
  machine.AssertInState< E >();
  machine.AssertNotInState< F >();
  machine.AssertInState< G >();
  machine.AssertNotInState< H >();

  machine.process_event( EvToB() );

  machine.AssertNotInState< A >();
  machine.AssertInState< B >();
  machine.AssertNotInState< C >();
  machine.AssertNotInState< D >();
  machine.AssertNotInState< E >();
  machine.AssertNotInState< F >();
  machine.AssertNotInState< G >();
  machine.AssertNotInState< H >();

  machine.process_event( EvToF() );

  machine.AssertInState< A >();
  machine.AssertNotInState< B >();
  machine.AssertInState< C >();
  machine.AssertInState< D >();
  machine.AssertNotInState< E >();
  machine.AssertInState< F >();
  machine.AssertInState< G >();
  machine.AssertNotInState< H >();

  machine.terminate();

  machine.AssertNotInState< A >();
  machine.AssertNotInState< B >();
  machine.AssertNotInState< C >();
  machine.AssertNotInState< D >();
  machine.AssertNotInState< E >();
  machine.AssertNotInState< F >();
  machine.AssertNotInState< G >();
  machine.AssertNotInState< H >();

  return 0;
}
