//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// The following code implements the state-machine:
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

#include <ctime>
#include <iostream>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvStartStop : fsm::event< EvStartStop > {};
struct EvReset : fsm::event< EvReset > {};


struct IElapsedTime
{
  virtual std::clock_t ElapsedTime() const = 0;
};


struct Active;
struct StopWatch : fsm::state_machine< StopWatch, Active > {};


struct Stopped;
struct Active : fsm::simple_state< Active, StopWatch,
  fsm::transition< EvReset, Active >, Stopped >
{
  public:
    Active() : elapsedTime_( 0 ) {}

    std::clock_t & ElapsedTime()
    {
      return elapsedTime_;
    }

    std::clock_t ElapsedTime() const
    {
      return elapsedTime_;
    }

  private:
    std::clock_t elapsedTime_;
};

struct Running :
  IElapsedTime,
  fsm::simple_state< Running, Active,
    fsm::transition< EvStartStop, Stopped > >
{
  public:
    Running() : startTime_( std::clock() ) {}

    ~Running()
    {
      context< Active >().ElapsedTime() = ElapsedTime();
    }

    virtual std::clock_t ElapsedTime() const
    {
      return context< Active >().ElapsedTime() + std::clock() - startTime_;
    }

  private:
    std::clock_t startTime_;
};

struct Stopped :
  IElapsedTime,
  fsm::simple_state< Stopped, Active,
    fsm::transition< EvStartStop, Running > >
{
  virtual std::clock_t ElapsedTime() const
  {
    return context< Active >().ElapsedTime();
  }
};



char GetKey()
{
  char key;
  std::cin >> key;
  return key;
}

int main()
{
  std::cout << "boost::fsm StopWatch example\n\n";
  std::cout << "s<CR>: Starts/Stops stop watch\n";
  std::cout << "r<CR>: Resets stop watch\n";
  std::cout << "d<CR>: Displays the elapsed time in milliseconds\n";
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
