//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// This is a quick-and-dirty handcrafted state machine with two states and two
// transitions employing GOF-visitation (two virtual calls per event).
// It is used to make speed comparisons with boost::fsm machines.
//////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <iomanip>
#include <ctime>



const unsigned int noOfStates = 2;
const unsigned int noOfTransitions = 2;

// common prime factors of 2^n-1 for n in [1,8]
const unsigned int noOfEvents = 3 * 3 * 5 * 7 * 17 * 31 * 127;

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


//////////////////////////////////////////////////////////////////////////////
class BitMachine
{
  public:
    //////////////////////////////////////////////////////////////////////////
    BitMachine() : pCurrentState_( &Off::instance() ) {}

    void process_event( const event_base & evt )
    {
      pCurrentState_ = &evt.send( *pCurrentState_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
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

  std::cout << "boost::fsm Handcrafted example\n";
  std::cout << "Machine configuration: " << noOfStates <<
    " states interconnected with " << noOfTransitions << " transitions.\n\n";

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
