//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// The following code implements the state-machine (this is the version
// discussed in the tutorial):
//
//  --------------------------------
// |                                |
// |           O     Active         |
// |           |                    |<----
// |           v                    |     | EvReset
// |  ----------------------------  |     |
// | |                            | |-----
// | |         Stopped            | |
// |  ----------------------------  |
// |  |              ^              |
// |  | EvStartStop  | EvStartStop  |<-----O
// |  v              |              |
// |  ----------------------------  |
// | |                            | |
// | |         Running            | |
// |  ----------------------------  |
//  --------------------------------



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>

#include <boost/config.hpp>

#include <ctime>
#include <iostream>

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std
{
  using ::time;
  using ::time_t;
}
#endif

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#  pragma warning( disable: 444 ) // destructor for base is not virtual
#  pragma warning( disable: 981 ) // operands are evaluated in unspecified order
#endif



namespace fsm = boost::fsm;



struct EvStartStop : fsm::event< EvStartStop > {};
struct EvReset : fsm::event< EvReset > {};


struct IElapsedTime
{
  virtual double ElapsedTime() const = 0;
};


struct Active;
struct StopWatch : fsm::state_machine< StopWatch, Active > {};


struct Stopped;
struct Active : fsm::simple_state< Active, StopWatch,
  fsm::transition< EvReset, Active >, Stopped >
{
  public:
    Active() : elapsedTime_( 0.0 ) {}

    double & ElapsedTime()
    {
      return elapsedTime_;
    }

    double ElapsedTime() const
    {
      return elapsedTime_;
    }

  private:
    double elapsedTime_;
};

struct Running :
  IElapsedTime,
  fsm::simple_state< Running, Active,
    fsm::transition< EvStartStop, Stopped > >
{
  public:
    Running() : startTime_( std::time( 0 ) ) {}

    ~Running()
    {
      context< Active >().ElapsedTime() = ElapsedTime();
    }

    virtual double ElapsedTime() const
    {
      return context< Active >().ElapsedTime() +
        std::difftime( std::time( 0 ), startTime_ );
    }

  private:
    std::time_t startTime_;
};

struct Stopped :
  IElapsedTime,
  fsm::simple_state< Stopped, Active,
    fsm::transition< EvStartStop, Running > >
{
  virtual double ElapsedTime() const
  {
    return context< Active >().ElapsedTime();
  }
};


namespace
{
  char GetKey()
  {
    char key;
    std::cin >> key;
    return key;
  }
}

int main()
{
  std::cout << "boost::fsm StopWatch example\n\n";
  std::cout << "s<CR>: Starts/Stops stop watch\n";
  std::cout << "r<CR>: Resets stop watch\n";
  std::cout << "d<CR>: Displays the elapsed time in seconds\n";
  std::cout << "e<CR>: Exits the program\n\n";
  std::cout << "You may chain commands, e.g. rs<CR> resets and starts stop watch\n\n";
  
  StopWatch stopWatch;
  stopWatch.initiate();

  char key = GetKey();

  while ( key != 'e' )
  {
    switch( key )
    {
      case 'r':
      {
        stopWatch.process_event( EvReset() );
      }
      break;

      case 's':
      {
        stopWatch.process_event( EvStartStop() );
      }
      break;

      case 'd':
      {
        std::cout << "Elapsed time: " <<
          stopWatch.state_cast< const IElapsedTime & >().ElapsedTime() << "\n";
      }
      break;

      default:
      {
        std::cout << "Invalid key!\n";
      }
      break;
    }

    key = GetKey();
  }

  return 0;
}
