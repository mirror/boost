//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
const unsigned int noOfBits = 6;
#define CUSTOMIZE_MEMORY_MANAGEMENT
// #define BOOST_FSM_USE_NATIVE_RTTI
//////////////////////////////////////////////////////////////////////////////
// This program demonstrates the fact that measures must be taken to hide some
// of the complexity (e.g. in separate .cpp file) of a boost::fsm state
// machine once a certain size is reached.
// For this purpose, a state machine with exactly 2^noOfBits states (i.e.
// BitState< 0 > .. BitState< 2^noOfBits - 1 >) is generated. For the events
// EvFlipBit< 0 > .. EvFlipBit< noOfBits - 1 > there is a transition from each
// state to the state with the corresponding bit toggled. That is, there is a
// total of 2^noOfBits * noOfBits transitions.
// E.g. if the state machine is currently in state BitState< 5 > and receives
// EvFlipBit< 2 >, it transitions to state BitState< 1 >. If it is in
// BitState< 15 > and receives EvFlipBit< 4 > it transitions to BitState< 31 >
// etc.
// The maximum size of such a state machine depends on your compiler. The
// following table gives upper limits for noOfBits. From this, rough
// estimates for the maximum size of any "naively" implemented boost::fsm
// machine (i.e. no attempt is made to hide inner state implementation in a
// .cpp file) can be deduced.
//
// NOTE: Due to the fact that the amount of generated code more than
// *doubles* each time noOfBits is *incremented*, build times soar when
// noOfBits > 6.

// Compiler      | max. noOfBits b | max. states s  | max. transitions t
// --------------|-----------------|----------------|-------------------
// MSVC 7.1      |      b < 7      |  64 < s < 128  |  384 < t <  896
// GCC 3.2 *     |      b < 8      | 128 < s < 256  |  896 < t < 2048
//
// * ICE for b = 8
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/config.hpp>
#include <boost/assert.hpp>

#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable: 4800 ) // forcing value to bool 'true' or 'false'
#pragma warning( disable: 4127 ) // conditional expression is constant
#endif

#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#define BOOST_NO_MT
#include <boost/pool/pool_alloc.hpp>
#endif

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#include <iostream>
#include <iomanip>
#include <ctime>

#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#include "UniqueObject.hpp"
#endif



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



const unsigned int noOfStates = 1 << noOfBits;
const unsigned int noOfTransitions = noOfStates * noOfBits;

// common prime factors of 2^n-1 for n in [1,8]
const unsigned int noOfEvents = 3 * 3 * 5 * 7 * 17 * 31 * 127;
const unsigned int noOfLaps = noOfEvents / ( noOfStates - 1 );

unsigned long eventsSentTotal = 0;



//////////////////////////////////////////////////////////////////////////////
void DisplayBits( unsigned int number )
{
  char buffer[ noOfBits + 1 ];
  buffer[ noOfBits ] = 0;

  for ( unsigned int bit = 0; bit < noOfBits; ++bit )
  {
    buffer[ bit ] = number & ( 1 << ( noOfBits - bit - 1 ) ) ? '1' : '0';
  }

  std::cout << "Current state: " << std::setw( 4 ) <<
    number << " (" << buffer << ")" << std::endl;
}


//////////////////////////////////////////////////////////////////////////////
template< unsigned int bitNo >
struct EvFlipBit : fsm::event< EvFlipBit< bitNo > > {};

const fsm::event_base * pFlipBitEvents[ 10 ] = { 0 };

template< unsigned int stateNo >
struct BitState;
//////////////////////////////////////////////////////////////////////////////
#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
struct BitMachine : fsm::state_machine< BitMachine, BitState< 0 >,
  boost::fast_pool_allocator< int > > {};
#else
struct BitMachine : fsm::state_machine< BitMachine, BitState< 0 > > {};
#endif


//////////////////////////////////////////////////////////////////////////////
template< class BitNo, class StateNo >
struct FlipTransition
{
  BOOST_STATIC_CONSTANT(
    unsigned int, nextStateNo=StateNo::value ^ ( 1 << BitNo::value ) );
  BOOST_STATIC_CONSTANT( unsigned int, bitNo=BitNo::value );

  typedef fsm::transition< 
    EvFlipBit< bitNo >,
    BitState< nextStateNo > > type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT( 2, FlipTransition, (BitNo, StateNo) )
};

//////////////////////////////////////////////////////////////////////////////
template< unsigned int stateNo >
struct FlipTransitionList
{
  private:
    //////////////////////////////////////////////////////////////////////////
    typedef mpl::fold<
      mpl::range_c< unsigned int, 0, noOfBits >,
      mpl::list<>, mpl::push_front< _, _ > >::type
      BitNumbers;

  public:
    //////////////////////////////////////////////////////////////////////////
    typedef typename mpl::transform< BitNumbers,
      FlipTransition< _, mpl::integral_c< unsigned int, stateNo > > >::type type;
};


//////////////////////////////////////////////////////////////////////////////
struct IDisplay
{
  virtual void DisplayBits() const = 0;
};


//////////////////////////////////////////////////////////////////////////////
template< unsigned int stateNo >
struct BitState :
  fsm::simple_state< BitState< stateNo >, BitMachine,
    typename FlipTransitionList< stateNo >::type >,
  #ifdef CUSTOMIZE_MEMORY_MANAGEMENT
  IDisplay, UniqueObject< BitState< stateNo > >
  #else
  IDisplay
  #endif
{
  virtual void DisplayBits() const
  {
    ::DisplayBits( stateNo );
  }
};


//////////////////////////////////////////////////////////////////////////////
void DisplayMachineState( const BitMachine & bitMachine )
{
  bitMachine.state_cast< const IDisplay & >().DisplayBits();
}

template< unsigned int msb, bool display >
void VisitAllStates( BitMachine & bitMachine )
{
  VisitAllStates< msb - 1, display >( bitMachine );
  bitMachine.process_event( *pFlipBitEvents[ msb ] );
  ++eventsSentTotal;

#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable: 4127 )
#endif
  if ( display )
  {
    DisplayMachineState( bitMachine );
  }
#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

  VisitAllStates< msb - 1, display >( bitMachine );
}

template<>
void VisitAllStates< 0, false >( BitMachine & bitMachine )
{
  bitMachine.process_event( *pFlipBitEvents[ 0 ] );
  ++eventsSentTotal;
}

template<>
void VisitAllStates< 0, true >( BitMachine & bitMachine )
{
  bitMachine.process_event( *pFlipBitEvents[ 0 ] );
  ++eventsSentTotal;
  DisplayMachineState( bitMachine );
}


char GetKey()
{
  char key;
  std::cin >> key;
  return key;
}


//////////////////////////////////////////////////////////////////////////////
int main( int argc, char * argv[] )
{
  argc;
  argv;

  BOOST_ASSERT( noOfBits <= 10 );

  const EvFlipBit< 0 > flip0;
  const EvFlipBit< 1 > flip1;
  const EvFlipBit< 2 > flip2;
  const EvFlipBit< 3 > flip3;
  const EvFlipBit< 4 > flip4;
  const EvFlipBit< 5 > flip5;
  const EvFlipBit< 6 > flip6;
  const EvFlipBit< 7 > flip7;
  const EvFlipBit< 8 > flip8;
  const EvFlipBit< 9 > flip9;

  pFlipBitEvents[ 0 ] = &flip0;
  pFlipBitEvents[ 1 ] = &flip1;
  pFlipBitEvents[ 2 ] = &flip2;
  pFlipBitEvents[ 3 ] = &flip3;
  pFlipBitEvents[ 4 ] = &flip4;
  pFlipBitEvents[ 5 ] = &flip5;
  pFlipBitEvents[ 6 ] = &flip6;
  pFlipBitEvents[ 7 ] = &flip7;
  pFlipBitEvents[ 8 ] = &flip8;
  pFlipBitEvents[ 9 ] = &flip9;

  std::cout << "boost::fsm BitMachine example\n";
  std::cout << "Machine configuration: " << noOfStates <<
    " states interconnected with " << noOfTransitions << " transitions.\n\n";

  for ( unsigned int bit = 0; bit < noOfBits; ++bit )
  {
    std::cout << bit - 0 << "<CR>: Flips bit " << bit - 0 << "\n";
  }

  std::cout << "a<CR>: Goes through all states automatically\n";
  std::cout << "p<CR>: Performance test\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout << "You may chain commands, e.g. 31<CR> flips bits 3 and 1\n\n";


  BitMachine bitMachine;
  bitMachine.initiate();

  char key = GetKey();

  while ( key != 'e' )
  {
    if ( ( key >= '0' ) && ( key < '0' + noOfBits ) )
    {
      bitMachine.process_event( *pFlipBitEvents[ key - '0' ] );
      ++eventsSentTotal;
      DisplayMachineState( bitMachine );
    }
    else
    {
      switch( key )
      {
        case 'a':
        {
          VisitAllStates< noOfBits - 1, true >( bitMachine );
        }
        break;

        case 'p':
        {
          std::cout << "\nSending " << noOfEvents << " events. Please wait...\n";

          const unsigned long startEvents2 = eventsSentTotal;
          const std::clock_t startTime2 = std::clock();

          for ( unsigned int lap = 0; lap < noOfLaps; ++lap )
          {
            VisitAllStates< noOfBits - 1, false >( bitMachine );
          }

          const std::clock_t elapsedTime2 = std::clock() - startTime2;
          const unsigned int eventsSent2 = eventsSentTotal - startEvents2;
          std::cout << "Time to dispatch one event and\n" <<
                       "perform the resulting transition: ";
          std::cout << elapsedTime2 * 1000.0 / eventsSent2 << " microseconds\n\n";
        }
        break;

        default:
        {
          std::cout << "Invalid key!\n";
        }
      }
    }

    key = GetKey();
  }

 	return 0;
}
