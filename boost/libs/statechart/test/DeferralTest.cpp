//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/deferral.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>
#include <boost/intrusive_ptr.hpp>

#include <boost/test/test_tools.hpp>

#include <typeinfo>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;


template< class T >
boost::intrusive_ptr< T > MakeIntrusive( T * pT )
{
  return boost::intrusive_ptr< T >( pT );
}

struct EvLeafDeferred : fsm::event< EvLeafDeferred > {};
struct EvNodeDeferred : fsm::event< EvNodeDeferred > {};
struct EvSwitch : fsm::event< EvSwitch > {};
struct EvDestroy : fsm::event< EvDestroy > {};

struct Active;
struct DeferralTest : fsm::state_machine< DeferralTest, Active >
{
    //////////////////////////////////////////////////////////////////////////
    DeferralTest() : processedCount_( 0 ) {}

    void IncrementProcessedCount()
    {
      ++processedCount_;
    }

    unsigned int ProcessedCount() const
    {
      return processedCount_;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    unsigned int processedCount_;
};

struct Dead : fsm::simple_state<
  Dead, DeferralTest, fsm::custom_reaction< EvNodeDeferred > >
{
  fsm::result react( const EvNodeDeferred & )
  {
    outermost_context().IncrementProcessedCount();
    return discard_event();
  }
};

struct Idle;
struct Active : fsm::simple_state< Active, DeferralTest, mpl::list<
  fsm::custom_reaction< EvLeafDeferred >,
  fsm::deferral< EvNodeDeferred >,
  fsm::transition< EvDestroy, Dead > >, Idle >
{
  fsm::result react( const EvLeafDeferred & )
  {
    outermost_context().IncrementProcessedCount();
    return discard_event();
  }
};

  struct Running : fsm::simple_state< Running, Active,
    fsm::transition< EvSwitch, Idle > >
  {
  };

  struct Idle : fsm::simple_state< Idle, Active, mpl::list<
    fsm::transition< EvSwitch, Running >,
    fsm::deferral< EvLeafDeferred > > >
  {
  };


int test_main( int, char* [] )
{
  DeferralTest machine;
  machine.initiate();
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 0 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 0 );
  machine.process_event( *MakeIntrusive( new EvLeafDeferred() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 0 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 1 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 1 );
  machine.process_event( *MakeIntrusive( new EvLeafDeferred() ) );
  machine.process_event( *MakeIntrusive( new EvLeafDeferred() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 1 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 3 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 3 );
  machine.process_event( *MakeIntrusive( new EvNodeDeferred() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 3 );
  machine.process_event( *MakeIntrusive( new EvSwitch() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 3 );
  machine.process_event( *MakeIntrusive( new EvNodeDeferred() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 3 );
  machine.process_event( *MakeIntrusive( new EvDestroy() ) );
  BOOST_REQUIRE( machine.ProcessedCount() == 5 );
  return 0;
}
