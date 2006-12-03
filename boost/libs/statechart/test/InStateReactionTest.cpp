//////////////////////////////////////////////////////////////////////////////
// Copyright 2005-2006 Andreas Huber Doenni
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/in_state_reaction.hpp>
#include <boost/statechart/result.hpp>

#include <boost/mpl/list.hpp>

#include <boost/test/test_tools.hpp>

namespace sc = boost::statechart;
namespace mpl = boost::mpl;


struct E : sc::event< E > {};
struct F : sc::event< F > {};
struct G : sc::event< G > {};
struct H : sc::event< H > {};

struct A;
struct InStateReactionTest :
  sc::state_machine< InStateReactionTest, A > {};

struct B;
struct A : sc::simple_state< A, InStateReactionTest, B >
{
  A() : eventCount_( 0 ) {}

  // The following 3 functions could be implemented with one function
  // template, but this causes problems with CW and Intel 9.1.
  void IncrementCount( const sc::event_base & ) { ++eventCount_; }
  void IncrementCount( const E & ) { ++eventCount_; }
  void IncrementCount( const G & ) { ++eventCount_; }

  typedef mpl::list<
    sc::in_state_reaction< E, A, &A::IncrementCount >,
    sc::in_state_reaction< sc::event_base, A, &A::IncrementCount >
  > reactions;

  unsigned int eventCount_;
};

  struct B : sc::simple_state< B, A >
  {
    B() : eventCount_( 0 ) {}

    void IncrementCount( const F & )
    {
      ++eventCount_;
    }

    typedef mpl::list<
      sc::in_state_reaction< F, B, &B::IncrementCount >,
      sc::in_state_reaction< G, A, &A::IncrementCount >
    > reactions;

    unsigned int eventCount_;
  };



int test_main( int, char* [] )
{
  InStateReactionTest machine;
  machine.initiate();

  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 0 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 0 );
  machine.process_event( F() );
  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 0 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 1 );
  machine.process_event( E() );
  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 1 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 1 );
  machine.process_event( E() );
  machine.process_event( F() );
  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 2 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 2 );
  machine.process_event( G() );
  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 3 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 2 );
  machine.process_event( H() );
  BOOST_REQUIRE( machine.state_downcast< const A & >().eventCount_ == 4 );
  BOOST_REQUIRE( machine.state_downcast< const B & >().eventCount_ == 2 );

  return 0;
}
