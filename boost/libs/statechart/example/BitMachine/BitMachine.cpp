//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
#ifndef NO_OF_BITS
#  define NO_OF_BITS 4
#endif
// #define CUSTOMIZE_MEMORY_MANAGEMENT
// #define BOOST_STATECHART_USE_NATIVE_RTTI
//////////////////////////////////////////////////////////////////////////////
// This program demonstrates the fact that measures must be taken to hide some
// of the complexity (e.g. in separate .cpp file) of a Boost.Statechart state
// machine once a certain size is reached.
// For this purpose, a state machine with exactly 2^NO_OF_BITS states (i.e.
// BitState< 0 > .. BitState< 2^NO_OF_BITS - 1 >) is generated. For the events
// EvFlipBit< 0 > .. EvFlipBit< NO_OF_BITS - 1 > there is a transition from
// each state to the state with the corresponding bit toggled. That is, there
// is a total of 2^NO_OF_BITS * NO_OF_BITS transitions.
// E.g. if the state machine is currently in state BitState< 5 > and receives
// EvFlipBit< 2 >, it transitions to state BitState< 1 >. If it is in
// BitState< 15 > and receives EvFlipBit< 4 > it transitions to BitState< 31 >
// etc.
// The maximum size of such a state machine depends on your compiler. The
// following table gives upper limits for NO_OF_BITS. From this, rough
// estimates for the maximum size of any "naively" implemented Boost.Statechart
// machine (i.e. no attempt is made to hide inner state implementation in a
// .cpp file) can be deduced.
//
// NOTE: Due to the fact that the amount of generated code more than
// *doubles* each time NO_OF_BITS is *incremented*, build times on most
// compilers soar when NO_OF_BITS > 6.
//
// Compiler      | max. NO_OF_BITS b | max. states s  |
// --------------|-------------------|----------------|
// MSVC 7.1      |      b < 6        |  32 < s <  64  |
// GCC 3.4.2 (1) |      b < 8        | 128 < s < 256  |
//
// (1) This is a practical rather than a hard limit, caused by a compiler
//     memory footprint that was significantly larger than the 1GB physical
//     memory installed in the test machine. The resulting frequent swapping
//     led to compilation times of hours rather than minutes.
//////////////////////////////////////////////////////////////////////////////



#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
#  include "UniqueObject.hpp"
#endif

#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

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

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std
{
  using ::clock_t;
  using ::clock;
}
#endif



#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#  pragma warning( disable: 444 ) // destructor for base is not virtual
#  pragma warning( disable: 981 ) // operands are evaluated in unspecified order
#endif



namespace sc = boost::statechart;
namespace mpl = boost::mpl;
using namespace mpl::placeholders;



//////////////////////////////////////////////////////////////////////////////
template< unsigned int bitNo >
struct EvFlipBit : sc::event< EvFlipBit< bitNo > > {};

template< unsigned int stateNo >
struct BitState;
//////////////////////////////////////////////////////////////////////////////
#ifdef CUSTOMIZE_MEMORY_MANAGEMENT
struct BitMachine : sc::state_machine< BitMachine, BitState< 0 >,
  boost::fast_pool_allocator< int > > {};
#else
struct BitMachine : sc::state_machine< BitMachine, BitState< 0 > > {};
#endif

//////////////////////////////////////////////////////////////////////////////
struct IDisplay
{
  virtual void Display() const = 0;
};

namespace
{
  const unsigned int noOfStates = 1 << NO_OF_BITS;
  const unsigned int noOfTransitions = noOfStates * NO_OF_BITS;

  // common prime factors of 2^n-1 for n in [1,8]
  const unsigned int noOfEvents = 3 * 3 * 5 * 7 * 17 * 31 * 127;
  const unsigned int noOfLaps = noOfEvents / ( noOfStates - 1 );

  unsigned long eventsSentTotal = 0;

  ////////////////////////////////////////////////////////////////////////////
  void DisplayBits( unsigned int number )
  {
    char buffer[ NO_OF_BITS + 1 ];
    buffer[ NO_OF_BITS ] = 0;

    for ( unsigned int bit = 0; bit < NO_OF_BITS; ++bit )
    {
      buffer[ bit ] = number & ( 1 << ( NO_OF_BITS - bit - 1 ) ) ? '1' : '0';
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
  boost::intrusive_ptr< const sc::event_base > pFlipBitEvents[ NO_OF_BITS ];

  ////////////////////////////////////////////////////////////////////////////
  template< unsigned int arraySize >
  void FillEventArray()
  {
    pFlipBitEvents[ arraySize - 1 ] =
      boost::intrusive_ptr< const sc::event_base >(
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

  typedef sc::transition< 
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
      mpl::range_c< unsigned int, 0, NO_OF_BITS >,
      mpl::list<>, mpl::push_front< _, _ > >::type
      BitNumbers;

  public:
    //////////////////////////////////////////////////////////////////////////
    typedef typename mpl::transform< BitNumbers,
      FlipTransition< _, mpl::integral_c< unsigned int, stateNo > > >::type type;
};

//////////////////////////////////////////////////////////////////////////////
template< unsigned int stateNo >
struct BitState : sc::simple_state< BitState< stateNo >, BitMachine >,
  #ifdef CUSTOMIZE_MEMORY_MANAGEMENT
  IDisplay, UniqueObject< BitState< stateNo > >
  #else
  IDisplay
  #endif
{
  #ifdef CUSTOMIZE_MEMORY_MANAGEMENT
  static void * operator new( size_t size )
  {
    return UniqueObject< BitState< stateNo > >::operator new( size );
  }

  static void operator delete( void * p, size_t size )
  {
    UniqueObject< BitState< stateNo > >::operator delete( p, size );
  }
  #endif

  typedef typename FlipTransitionList< stateNo >::type reactions;

  virtual void Display() const
  {
    DisplayBits( stateNo );
  }
};



//////////////////////////////////////////////////////////////////////////////
int main()
{
  FillEventArray< NO_OF_BITS >();

  std::cout << "Boost.Statechart BitMachine example\n";
  std::cout << "Machine configuration: " << noOfStates <<
    " states interconnected with " << noOfTransitions << " transitions.\n\n";

  for ( unsigned int bit = 0; bit < NO_OF_BITS; ++bit )
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
    if ( ( key >= '0' ) && ( key < static_cast< char >( '0' + NO_OF_BITS ) ) )
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
          VisitAllStates< NO_OF_BITS - 1, true >( bitMachine );
        }
        break;

        case 'p':
        {
          std::cout << "\nSending " << noOfEvents << " events. Please wait...\n";

          const unsigned long startEvents2 = eventsSentTotal;
          const std::clock_t startTime2 = std::clock();

          for ( unsigned int lap = 0; lap < noOfLaps; ++lap )
          {
            VisitAllStates< NO_OF_BITS - 1, false >( bitMachine );
          }

          const std::clock_t elapsedTime2 = std::clock() - startTime2;
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
