//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
const unsigned int noOfBits = 5;
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
// *doubles* each time noOfBits is *incremented*, build times on most
// compilers soar when noOfBits > 6.
//
// Compiler      | max. noOfBits b | max. states s  |
// --------------|-----------------|----------------|
// MSVC 7.1      |      b < 7      |  64 < s < 128  |
// GCC 3.2 (1)   |      b < 8      | 128 < s < 256  |
// Intel 7.0 (2) |      b < 8      | 128 < s < 256  |
// Intel 8.0 (2) |      b < 9      | 256 < s < 512  |
//
// (1) ICE for b = 8
// (2) These are practical rather than hard limits, caused by a compiler
//     memory footprint that was significantly larger than the 1GB physical
//     memory installed in the test machine. The resulting frequent swapping
//     led to compilation times of hours rather than minutes.
//////////////////////////////////////////////////////////////////////////////



#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#  include "UniqueObject.hpp"
#endif

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
#include <boost/intrusive_ptr.hpp>

#ifdef BOOST_MSVC
#  pragma warning( push )
#  pragma warning( disable: 4127 ) // conditional expression is constant
#  pragma warning( disable: 4800 ) // forcing value to bool 'true' or 'false'
#endif

#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#  define BOOST_NO_MT
#  include <boost/pool/pool_alloc.hpp>
#endif

#ifdef BOOST_MSVC
#  pragma warning( pop )
#endif

#include <iostream>
#include <iomanip>
#include <ctime>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#  pragma warning( disable: 444 ) // destructor for base is not virtual
#  pragma warning( disable: 981 ) // operands are evaluated in unspecified order
#endif



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



//////////////////////////////////////////////////////////////////////////////
template< unsigned int bitNo >
struct EvFlipBit : fsm::event< EvFlipBit< bitNo > > {};

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
struct IDisplay
{
  virtual void Display() const = 0;
};

namespace
{
  const unsigned int noOfStates = 1 << noOfBits;
  const unsigned int noOfTransitions = noOfStates * noOfBits;

  // common prime factors of 2^n-1 for n in [1,8]
  const unsigned int noOfEvents = 3 * 3 * 5 * 7 * 17 * 31 * 127;
  const unsigned int noOfLaps = noOfEvents / ( noOfStates - 1 );

  unsigned long eventsSentTotal = 0;

  ////////////////////////////////////////////////////////////////////////////
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
  
  ////////////////////////////////////////////////////////////////////////////
  void DisplayMachineState( const BitMachine & bitMachine )
  {
    bitMachine.state_cast< const IDisplay & >().Display();
  }

  ////////////////////////////////////////////////////////////////////////////
  boost::intrusive_ptr< const fsm::event_base > pFlipBitEvents[ noOfBits ];

  ////////////////////////////////////////////////////////////////////////////
  template< unsigned int arraySize >
  void FillEventArray()
  {
    pFlipBitEvents[ arraySize - 1 ] =
      boost::intrusive_ptr< const fsm::event_base >(
        new EvFlipBit< arraySize - 1 >() );
    FillEventArray< arraySize - 1 >();
  }

  template<>
  void FillEventArray< 0 >() {}

  ////////////////////////////////////////////////////////////////////////////
  template< typename T >
  T AvoidConstantWarning( T value ) { return value; }

  ////////////////////////////////////////////////////////////////////////////
  template< unsigned int msb, bool display >
  void VisitAllStates( BitMachine & bitMachine )
  {
    VisitAllStates< msb - 1, display >( bitMachine );
    bitMachine.process_event( *pFlipBitEvents[ msb ] );
    ++eventsSentTotal;

    if ( AvoidConstantWarning( display ) )
    {
      DisplayMachineState( bitMachine );
    }

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

  ////////////////////////////////////////////////////////////////////////////
  char GetKey()
  {
    char key;
    std::cin >> key;
    return key;
  }
}



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
  virtual void Display() const
  {
    DisplayBits( stateNo );
  }
};



//////////////////////////////////////////////////////////////////////////////
int main()
{
  FillEventArray< noOfBits >();

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

          #ifdef BOOST_NO_STDC_NAMESPACE
          const clock_t startTime2 = clock();
          #else
          const std::clock_t startTime2 = std::clock();
          #endif

          for ( unsigned int lap = 0; lap < noOfLaps; ++lap )
          {
            VisitAllStates< noOfBits - 1, false >( bitMachine );
          }

          #ifdef BOOST_NO_STDC_NAMESPACE
          const clock_t elapsedTime2 = clock() - startTime2;
          #else
          const std::clock_t elapsedTime2 = std::clock() - startTime2;
          #endif
          const unsigned int eventsSent2 = eventsSentTotal - startEvents2;
          std::cout << "Time to dispatch one event and\n" <<
                       "perform the resulting transition: ";
          std::cout << elapsedTime2 / static_cast< double >( CLOCKS_PER_SEC ) *
            1000000.0 / eventsSent2 << " microseconds\n\n";
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
