//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



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
// following table gives upper limits for noOfBits. From this, rough
// estimates for the maximum size of any "naively" implemented boost::fsm
// (i.e. no attempt is made to hide inner state implementation in a .cpp file)
// can be deduced.
//
// Compiler      | max. noOfBits b | max. states s | max. transitions t
// --------------|-----------------|---------------|-------------------
// MSVC 7.0      |      b < 5      |  16 < s < 32  |  64 < t < 160
// MSVC 7.1      |      b < 6      |  32 < s < 64  |  160 < t < 384
//
// CAUTION: Due to the fact that the amount of generated code more than
// *doubles* each time noOfBits is *incremented*, build times soar when
// noOfBits > 6.
//////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <iomanip>
#include <ctime>



const unsigned int noOfStates = 2;
const unsigned int noOfTransitions = 2;

const unsigned int noOfEvents = 3 * 3 * 5 * 7 * 31 * 127;

unsigned long eventsSentTotal = 0;



class EvFlipBit;
//////////////////////////////////////////////////////////////////////////////
class state_base
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~state_base() {};

    virtual const state_base & react( const EvFlipBit & toEvent ) const = 0;

  protected:
    //////////////////////////////////////////////////////////////////////////
    state_base() {}
};

//////////////////////////////////////////////////////////////////////////////
template< class Derived >
class state : public state_base
{
  public:
    static const Derived & instance()
    {
      return instance_;
    }

  private:
    static const Derived instance_;
};

template< class Derived >
const Derived state< Derived >::instance_;



//////////////////////////////////////////////////////////////////////////////
class event_base
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~event_base() {}

  protected:
    //////////////////////////////////////////////////////////////////////////
    event_base() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    virtual const state_base & send( const state_base & toState ) const = 0;
};

//////////////////////////////////////////////////////////////////////////////
template< class Derived >
class event : public event_base
{
  protected:
    //////////////////////////////////////////////////////////////////////////
    event() {}

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual const state_base & send( const state_base & toState ) const
    {
      return toState.react( *static_cast< const Derived * >( this ) );
    }
};


//////////////////////////////////////////////////////////////////////////////
class EvFlipBit : public event< EvFlipBit > {};
const EvFlipBit flip;


class BitMachine
{
  public:
    BitMachine() : pCurrentState_( &Off::instance() ) {}

    void process_event( const event_base & evt )
    {
      pCurrentState_ = &evt.send( *pCurrentState_ );
    }

  private:
    struct On : public state< On >
    {
      virtual const state_base & react( const EvFlipBit & ) const
      {
        return Off::instance();
      }
    };

    struct Off : state< Off >
    {
      virtual const state_base & react( const EvFlipBit & ) const
      {
        return On::instance();
      }
    };

    const state_base * pCurrentState_;
};



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

  std::cout << "boost::fsm Handcrafted example\n\n";
  std::cout << "p<CR>: Performance test\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout <<
    "You may chain commands, e.g. pe<CR> performs a test and then exits the program\n\n";

  BitMachine bitMachine;

  char key = GetKey();

  while ( key != 'e' )
  {
    switch ( key )
    {
      case 'p':
      {
        std::cout << "\nSending " << noOfEvents <<
          " events. Please wait...\n";

        const unsigned long startEvents2 = eventsSentTotal;
        const std::clock_t startTime2 = std::clock();

        for ( unsigned int eventNo = 0; eventNo < noOfEvents; ++eventNo )
        {
          bitMachine.process_event( flip );
          ++eventsSentTotal;
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

    key = GetKey();
  }

 	return 0;
}
