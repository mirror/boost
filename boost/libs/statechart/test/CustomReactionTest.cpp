//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include <boost/test/test_tools.hpp>

#include <set>
#include <map>
#include <string>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvToC : fsm::event< EvToC > {};
struct EvToD : fsm::event< EvToD > {};

struct EvDiscardNever : fsm::event< EvDiscardNever > {};
struct EvDiscardInB : fsm::event< EvDiscardInB > {};
struct EvDiscardInD : fsm::event< EvDiscardInD > {};

struct EvTransit : fsm::event< EvTransit > {};
struct EvTransitWithAction : fsm::event< EvTransitWithAction > {};
struct EvDefer : fsm::event< EvDefer > {};
struct EvTerminate : fsm::event< EvTerminate > {};


struct A;
struct CustomReactionTest : fsm::state_machine< CustomReactionTest, A >
{
  public:
    //////////////////////////////////////////////////////////////////////////
    CustomReactionTest();

    void Visited( const state_base_type & stt )
    {
      const StateNamesMap::const_iterator found =
        stateNamesMap_.find( stt.dynamic_type() );
      BOOST_REQUIRE( found != stateNamesMap_.end() );
      visitedStates_.insert( found->second );
    }

    void ClearVisited()
    {
      visitedStates_.clear();
    }

    void AssertVisitedAll( const std::string & stateNames ) const
    {
      for ( std::string::const_iterator expectedName = stateNames.begin();
        expectedName != stateNames.end(); ++expectedName )
      {
        BOOST_REQUIRE( visitedStates_.find(
          std::string( 1, *expectedName ) ) != visitedStates_.end() );
      }
    }

    void AssertVisitedOne( const std::string & stateNames ) const
    {
      size_t found = 0;

      for ( std::string::const_iterator actualName = stateNames.begin();
        actualName != stateNames.end(); ++actualName )
      {
        found = found + ( visitedStates_.find(
          std::string( 1, *actualName ) ) != visitedStates_.end() ) ? 1 : 0;
      }

      BOOST_REQUIRE( found == 1 );
    }

    void TransitionAction( const EvTransitWithAction & ) {}

  private:
    //////////////////////////////////////////////////////////////////////////
    typedef std::map< state_base_type::id_type, std::string > StateNamesMap;
    typedef std::set< std::string > VisitedStates;

    StateNamesMap stateNamesMap_;
    VisitedStates visitedStates_;
};

struct B;
struct A : fsm::simple_state< A, CustomReactionTest, mpl::list<
  fsm::custom_reaction< EvTransit >,
  fsm::custom_reaction< EvTransitWithAction >,
  fsm::custom_reaction< EvDefer >,
  fsm::custom_reaction< EvTerminate >,
  fsm::custom_reaction< EvDiscardNever >,
  fsm::custom_reaction< EvDiscardInB >,
  fsm::custom_reaction< EvDiscardInD > >, B >
{
  fsm::result react( const EvDiscardNever & )
  {
    outermost_context().Visited( *this );
    return forward_event();
  }

  fsm::result react( const EvDiscardInB & )
  {
    BOOST_FAIL( "An event discarded in B must never reach A" );
    return discard_event();
  }

  fsm::result react( const EvDiscardInD & )
  {
    BOOST_FAIL( "An event discarded in D must never reach B" );
    return discard_event();
  }

  // The following code is here just to make sure that calls to the transit<>,
  // defer_event and terminate functions actually compile.
  // Their functionality is tested extensively in TransitionTest,
  // DeferralTest and TerminationTest with appropriate reactions. Internally,
  // these reactions call exactly the same functions as the following custom
  // reactions call.
  fsm::result react( const EvTransit & )
  {
    return transit< A >();
  }

  fsm::result react( const EvTransitWithAction & evt )
  {
    return transit< A >( &CustomReactionTest::TransitionAction, evt );
  }

  fsm::result react( const EvDefer & )
  {
    return defer_event();
  }

  fsm::result react( const EvTerminate & )
  {
    return terminate();
  }
};

  struct C;
  struct B : fsm::simple_state< B, A, mpl::list<
    fsm::custom_reaction< EvDiscardNever >,
    fsm::custom_reaction< EvDiscardInB >,
    fsm::custom_reaction< EvDiscardInD > >, C >
  {
    fsm::result react( const EvDiscardNever & )
    {
      outermost_context().Visited( *this );
      return forward_event();
    }

    fsm::result react( const EvDiscardInB & )
    {
      outermost_context().Visited( *this );
      return discard_event();
    }

    fsm::result react( const EvDiscardInD & )
    {
      BOOST_FAIL( "An event discarded in D must never reach B" );
      return discard_event();
    }
  };

    struct E;
    struct F;
    struct D : fsm::simple_state< D, B, mpl::list<
      fsm::transition< EvToC, C >,
      fsm::custom_reaction< EvDiscardNever >,
      fsm::custom_reaction< EvDiscardInB >,
      fsm::custom_reaction< EvDiscardInD > >, mpl::list< E, F > >
    {
      fsm::result react( const EvDiscardNever & )
      {
        outermost_context().Visited( *this );
        return forward_event();
      }

      fsm::result react( const EvDiscardInB & )
      {
        outermost_context().Visited( *this );
        return forward_event();
      }

      fsm::result react( const EvDiscardInD & )
      {
        outermost_context().Visited( *this );
        return discard_event();
      }
    };

      struct E : fsm::simple_state< E, D::orthogonal< 0 >, mpl::list<
        fsm::custom_reaction< EvDiscardNever >,
        fsm::custom_reaction< EvDiscardInB >,
        fsm::custom_reaction< EvDiscardInD > > >
      {
        fsm::result react( const EvDiscardNever & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }

        fsm::result react( const EvDiscardInB & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }

        fsm::result react( const EvDiscardInD & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }
      };

      struct F : fsm::simple_state< F, D::orthogonal< 1 >, mpl::list<
        fsm::custom_reaction< EvDiscardNever >,
        fsm::custom_reaction< EvDiscardInB >,
        fsm::custom_reaction< EvDiscardInD > > >
      {
        fsm::result react( const EvDiscardNever & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }

        fsm::result react( const EvDiscardInB & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }

        fsm::result react( const EvDiscardInD & )
        {
          outermost_context().Visited( *this );
          return forward_event();
        }
      };

    struct C : fsm::simple_state< C, B, mpl::list<
      fsm::transition< EvToD, D >,
      fsm::custom_reaction< EvDiscardNever >,
      fsm::custom_reaction< EvDiscardInB >,
      fsm::custom_reaction< EvDiscardInD > > >
    {
      fsm::result react( const EvDiscardNever & )
      {
        outermost_context().Visited( *this );
        return forward_event();
      }

      fsm::result react( const EvDiscardInB & )
      {
        outermost_context().Visited( *this );
        return forward_event();
      }

      fsm::result react( const EvDiscardInD & )
      {
        outermost_context().Visited( *this );
        return forward_event();
      }
    };

CustomReactionTest::CustomReactionTest()
{
  // We're not using custom type information to make this test work even when
  // BOOST_FSM_USE_NATIVE_RTTI is defined
  stateNamesMap_[ A::static_type() ] = "A";
  stateNamesMap_[ B::static_type() ] = "B";
  stateNamesMap_[ C::static_type() ] = "C";
  stateNamesMap_[ D::static_type() ] = "D";
  stateNamesMap_[ E::static_type() ] = "E";
  stateNamesMap_[ F::static_type() ] = "F";
}

int test_main( int, char* [] )
{
  CustomReactionTest machine;
  machine.initiate();

  machine.process_event( EvDiscardNever() );
  machine.AssertVisitedAll( "ABC" );
  machine.ClearVisited();

  machine.process_event( EvDiscardInB() );
  machine.AssertVisitedAll( "BC" );
  machine.process_event( EvToD() );
  machine.ClearVisited();

  machine.process_event( EvDiscardNever() );
  machine.AssertVisitedAll( "ABDEF" );
  machine.ClearVisited();

  machine.process_event( EvDiscardInD() );
  machine.AssertVisitedAll( "D" );
  machine.AssertVisitedOne( "EF" );
  machine.ClearVisited();

  machine.process_event( EvDiscardInB() );
  machine.AssertVisitedAll( "BD" );
  machine.AssertVisitedOne( "EF" );
  machine.ClearVisited();

  return 0;
}
