//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/transition.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/config.hpp>

#include <iostream>
#include <iomanip>


namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



//////////////////////////////////////////////////////////////////////////////
const unsigned int noOfBits = 5;
//////////////////////////////////////////////////////////////////////////////
// This program demonstrates the fact that measures must be taken to hide some
// of the complexity (e.g. in separate .cpp file) of a boost::fsm state
// machine once a certain size is reached.
// For this purpose, a state machine with exactly 2^noOfBits states (i.e.
// BitState< 0 > .. BitState< 2^noOfBits - 1 >) is generated . For the events
// EvFlipBit< 0 > .. EvFlipBit< noOfBits - 1 > there is a transition from each
// state to the state with the corresponding bit toggled. That is, there is a
// total of 2^noOfBits * noOfBits transitions.
// E.g. if the state machine is currently in state BitState< 5 > and receives
// EvFlipBit< 2 >, it transitions to state BitState< 1 >. If it is in
// BitState< 15 > and receives EvFlipBit< 4 > it transitions to BitState< 31 >
// etc.
// The maximum size of such a state machine depends on your compiler. The
// following table gives upper limits for noOfBits. From this, *rough*
// estimates for the maximum size of any "naively" implemented boost::fsm
// (i.e. no attempt is made to hide inner state implementation in a .cpp file)
// can be deduced.
//
// Compiler      | max. noOfBits | max. states | max. transitions
// --------------|---------------|-------------|-----------------
// MSVC 7.0      |     < 5       |    < 32     |      < 120
// MSVC 7.1      |     < 6       |    < 64     |      < 384
//
// CAUTION: Due to the fact that the amount of generated code more than
// *doubles* each time noOfBits is *incremented*, build times soar when
// noOfBits > 6.
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


template< unsigned int bitNo >
class EvFlipBit : public fsm::event< EvFlipBit > {};

template< unsigned int stateNo >
class BitState;
class BitMachine : public fsm::state_machine< BitMachine, BitState< 0 > > {};

using namespace mpl::placeholders;



template< class BitNo, class StateNo >
struct FlipTransition
{
  BOOST_STATIC_CONSTANT( unsigned int, nextStateNo=StateNo::value ^ ( 1 << BitNo::value ) );
  BOOST_STATIC_CONSTANT( unsigned int, bitNo=BitNo::value );

  typedef fsm::transition< 
    EvFlipBit< bitNo >,
    BitState< nextStateNo > > type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT( 2, FlipTransition, (BitNo, StateNo) )
};

template< unsigned int stateNo >
struct FlipTransitionList
{
  private:
    typedef mpl::fold<
      mpl::range_c< unsigned int, 0, noOfBits >,
      mpl::list<>, mpl::push_front< _, _ > >::type
      BitNumbers;
  public:
    typedef typename mpl::transform<
      BitNumbers,
      FlipTransition< _, mpl::integral_c< unsigned int, stateNo > > >::type type;
};

template< unsigned int stateNo >
class BitState : public fsm::simple_state<
  BitState, BitMachine, typename FlipTransitionList< stateNo >::type >
{
  public:
    BitState()
    {
      DisplayBits( stateNo );
    }
};



template< unsigned int msb >
void VisitAllStates( BitMachine & bitMachine )
{
  VisitAllStates< msb - 1 >( bitMachine );
  bitMachine.process_event( EvFlipBit< msb >() );
  VisitAllStates< msb - 1 >( bitMachine );
}

template<>
void VisitAllStates< 0 >( BitMachine & bitMachine )
{
  bitMachine.process_event( EvFlipBit< 0 >() );
}


char GetKey()
{
  char key;
  std::cin >> key;
  return key;
}


int main( int argc, char * argv[] )
{
  argc;
  argv;

  std::cout << "boost::fsm BitMachine example\n\n";
  for ( unsigned int bit = 0; bit < noOfBits; ++bit )
  {
    std::cout << bit - 0 << "<CR>: Flips bit " << bit - 0 << "\n";
  }

  std::cout << "a<CR>: Goes through all states automatically\n\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout << "You may chain commands, e.g. 31<CR> flips bits 3 and 1\n\n";


  BitMachine bitMachine;
  bitMachine.initiate();

  char key = GetKey();

  while ( key != 'e' )
  {
    if ( ( key >= '0' ) && ( key <= '0' + noOfBits - 1 ) || ( key == 'a' ) )
    {
      switch( key )
      {
        case '0':
        {
          bitMachine.process_event( EvFlipBit< 0 >() );
        }
        break;

        case '1':
        {
          bitMachine.process_event( EvFlipBit< 1 >() );
        }
        break;

        case '2':
        {
          bitMachine.process_event( EvFlipBit< 2 >() );
        }
        break;

        case '3':
        {
          bitMachine.process_event( EvFlipBit< 3 >() );
        }
        break;

        case '4':
        {
          bitMachine.process_event( EvFlipBit< 4 >() );
        }
        break;

        case '5':
        {
          bitMachine.process_event( EvFlipBit< 5 >() );
        }
        break;

        case '6':
        {
          bitMachine.process_event( EvFlipBit< 6 >() );
        }
        break;

        case '7':
        {
          bitMachine.process_event( EvFlipBit< 7 >() );
        }
        break;

        case '8':
        {
          bitMachine.process_event( EvFlipBit< 8 >() );
        }
        break;

        case '9':
        {
          bitMachine.process_event( EvFlipBit< 9 >() );
        }
        break;

        case 'a':
        {
          VisitAllStates< noOfBits - 1 >( bitMachine );
        }
        break;
      }
    }
    else
    {
      std::cout << "Invalid key!\n";
    }

    key = GetKey();
  }

 	return 0;
}
