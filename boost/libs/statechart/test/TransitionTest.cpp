//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "OuterOrthogonal.hpp"

#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/transition.hpp>

#include <boost/mpl/list.hpp>

#include <boost/array.hpp>
#include <boost/test/test_tools.hpp>

#include <typeinfo>
#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



typedef std::list< std::string > ActionDescriptionSequence;
typedef void Action( ActionDescriptionSequence & );
typedef Action * ActionPtr;
const int maxSequenceLength = 30;
typedef ActionPtr ActionSequence[ maxSequenceLength ];



const std::string entry = "Entry: ";

template< class State >
void Entry( ActionDescriptionSequence & sequence )
{
  sequence.push_back( entry + typeid( State ).name() );
}

const std::string exitFunction = "exit(): ";

template< class State >
void ExitFn( ActionDescriptionSequence & sequence )
{
  sequence.push_back( exitFunction + typeid( State ).name() );
}

const std::string destructor = "Destructor: ";

template< class State >
void Dtor( ActionDescriptionSequence & sequence )
{
  sequence.push_back( destructor + typeid( State ).name() );
}

template< class State >
void Exit( ActionDescriptionSequence & sequence )
{
  ExitFn< State >( sequence );
  Dtor< State >( sequence );
}

void Trans( ActionDescriptionSequence & sequence )
{
  return sequence.push_back( "Transition" );
}



struct C : fsm::event< C > {};



struct S0;
struct TransitionTest : fsm::state_machine< TransitionTest, S0 >
{
    //////////////////////////////////////////////////////////////////////////
    ~TransitionTest()
    {
      // Since state destructors access the state machine object, we need to
      // make sure that all states are destructed before the superclass
      // destructor is called.
      terminate();
    }

    void CompareToExpectedActionSequence( ActionSequence & actions )
    {
      expectedSequence_.clear();

      for ( ActionPtr * pCurrent = &actions[ 0 ];
        ( pCurrent != &actions[ maxSequenceLength ] ) && ( *pCurrent != 0 );
        ++pCurrent )
      {
        ( *pCurrent )( expectedSequence_ );
      }

      if ( ( expectedSequence_.size() != actualSequence_.size() ) ||
        !std::equal( expectedSequence_.begin(),
          expectedSequence_.end(), actualSequence_.begin() ) )
      {
        std::stringstream stream;
        stream << "\nExpected action sequence:\n";
        std::copy(
          expectedSequence_.begin(), expectedSequence_.end(),
          std::ostream_iterator< std::string >( stream, "\n" ) );
        stream << "\nActual action sequence:\n";
        std::copy(
          actualSequence_.begin(), actualSequence_.end(),
          std::ostream_iterator< std::string >( stream, "\n" ) );

        BOOST_FAIL( stream.str().c_str() );
      }

      actualSequence_.clear();
    }

    template< class State >
    void ActualEntry()
    {
      StoreActualAction( &::Entry< State > );
    }

    template< class State >
    void ActualExitFunction()
    {
      StoreActualAction( &::ExitFn< State > );
    }
    
    template< class State >
    void ActualDestructor()
    {
      StoreActualAction( &::Dtor< State > );
    }
    
    void ActualTransition()
    {
      StoreActualAction( &::Trans );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    void StoreActualAction( ActionPtr pAction )
    {
      pAction( actualSequence_ );
    }

    ActionDescriptionSequence actualSequence_;
    ActionDescriptionSequence expectedSequence_;
};

struct S1;
struct S0 : Orthogonal0< S0, TransitionTest, fsm::no_reactions, S1 >
{
  S0( my_context ctx ) : my_base( ctx ) {}
};

  struct S21;
  struct S2 : Orthogonal2< S2, S0, mpl::list<
    fsm::transition< C, S1 > >, S21 >
  {
    S2( my_context ctx ) : my_base( ctx ) {}
  };

    struct S211;
    struct S21 : Orthogonal1< S21, S2::orthogonal< 2 >, fsm::no_reactions, S211 >
    {
      S21( my_context ctx ) : my_base( ctx ) {}
    };

      struct S211 : InnermostDefault< S211, S21::orthogonal< 1 > >
      {
        S211( my_context ctx ) : my_base( ctx ) {}
      };

  struct S11;
  struct S1 : Orthogonal1< S1, S0, fsm::transition< C, S2 >, S11 >
  {
    S1( my_context ctx ) : my_base( ctx ) {}
  };

    struct S11 : InnermostDefault< S11, S1::orthogonal< 1 > >
    {
      S11( my_context ctx ) : my_base( ctx ) {}
    };


int test_main( int, char* [] )
{
  TransitionTest machine;

  machine.initiate();

  ActionSequence initSequence = 
  {
    Entry< S0 >,
    Entry< S1 >,
    Entry< Default0< S1 > >,
    Entry< S11 >,
    Entry< Default2< S1 > >,
    Entry< Default1< S0 > >,
    Entry< Default2< S0 > >
  };

  machine.CompareToExpectedActionSequence( initSequence );
  machine.terminate();
  return 0;
}
