//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/event_receiver.hpp>
#include <boost/fsm/state_machine.hpp>

#include <iostream>
#include <stdexcept>
#include <time.h>
#include <windows.h>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4702 ) // unreachable code
#endif



//////////////////////////////////////////////////////////////////////////////
// The following code implements the state-machine:
//  ------------------------------                 ----------------
// |                              |     EvStop    |                |
// |           0     Active       |-------------->|                |
// |           |                  |               |    Stopped     |
// |           v                  |   EvStart *   |                |
// |  --------------------------  |<--------------|                |
// | |                          | |                ----------------
// | |      Running             | |                   ^         ^
// |  --------------------------  |                   |         |
// |   |            ^             |                   |         |
// |   | EvPause    | EvContinue  |--------------------         0
// |   V            |             |  simple_exception_event
// |  --------------------------  |
// | |                          | |
// | |        Paused            | |    * with transition action
// |  --------------------------  |
//  ------------------------------                              
//
class Stopped;
class StopWatch : public boost::fsm::state_machine< StopWatch >
{
  private:
    //////////////////////////////////////////////////////////////////////////
    class EvStart : public boost::fsm::event< EvStart > {};
    class EvStop : public boost::fsm::event< EvStop > {};
    class EvPause : public boost::fsm::event< EvPause > {};
    class EvContinue : public boost::fsm::event< EvContinue > {};

  public:
    //////////////////////////////////////////////////////////////////////////
    StopWatch() : base_type( static_cast< Stopped * >( 0 ) ) {}

    void Start()
    {
      process_event( EvStart() );
    }

    void Stop()
    {
      process_event( EvStop() );
    }

    void Pause()
    {
      process_event( EvPause() );
    }

    void Continue()
    {
      process_event( EvContinue() );
    }


    const clock_t ElapsedTime() const
    {
      return current_state< StateInterface >().ElapsedTime();
    }

    class StateInterface
    {
      public:
        virtual const clock_t ElapsedTime() const = 0;
    };

  private:
    //////////////////////////////////////////////////////////////////////////
    friend class Stopped;
    friend class Active;
    friend class Running;
    friend class Paused;


    void StoppedActiveTransition( const EvStart & )
    {
      std::cout << "Transit Stopped -> Active\n";
    }
};

class Running;
class Active : public boost::fsm::state< Active, StopWatch, Running >,
               public boost::fsm::event_receiver< StopWatch::EvStop >,
               public boost::fsm::event_receiver< boost::fsm::simple_exception_event >,
               public StopWatch::StateInterface
{
  public:
    Active( context_ptr_type pContext ) :
      base_type( pContext ),
      elapsedTime_( 0 )
    {
      std::cout << "Active entry\n";
    }

    ~Active()
    {
      std::cout << "Active exit\n";
    }

    void AddElapsedTime( clock_t elapsedTime )
    {
      elapsedTime_ += elapsedTime;
    }

    virtual const clock_t ElapsedTime() const
    {
      return elapsedTime_;
    }

  private:
    virtual const bool receive( const StopWatch::EvStop & )
    {
      return transit_to< Stopped >();
    }

    virtual const bool receive( const boost::fsm::simple_exception_event & )
    {
      return transit_to< Stopped >();
    }

    clock_t elapsedTime_;
};

class Paused;
class Running : public boost::fsm::state< Running, Active >,
                public boost::fsm::event_receiver< StopWatch::EvPause >,
                public StopWatch::StateInterface
{
  public:
    Running( context_ptr_type pContext ) :
      base_type( pContext ),
      startTime_( clock() )
    {
      std::cout << "Running entry\n";
    }

    ~Running()
    {
      context< Active >().AddElapsedTime( clock() - startTime_ );
      std::cout << "Running exit\n";
    }

  private:
    virtual const bool receive( const StopWatch::EvPause & )
    {
      return transit_to< Paused >();
    }

    virtual const clock_t ElapsedTime() const
    {
      return context< Active >().ElapsedTime() + clock() - startTime_;
    }

    clock_t startTime_;
};

class Paused : public boost::fsm::state< Paused, Active >,
               public boost::fsm::event_receiver< StopWatch::EvContinue >
{
  public:
    Paused( context_ptr_type pContext ) : base_type( pContext )
    {
      // uncomment the following line to test exception behavior
      // throw std::runtime_error( "Houston, we have a problem!" );
      std::cout << "Paused entry\n";
    }

    ~Paused()
    {
      std::cout << "Paused exit\n";
    }

  private:
    virtual const bool receive( const StopWatch::EvContinue & )
    {
      return transit_to< Running >();
    }
};


class Stopped : public boost::fsm::state< Stopped, StopWatch >,
                public boost::fsm::event_receiver< StopWatch::EvStart >,
                public StopWatch::StateInterface
{
  public:
    Stopped( context_ptr_type pContext ) : base_type( pContext )
    {
      std::cout << "Stopped entry\n";
    }

    ~Stopped()
    {
      std::cout << "Stopped exit\n";
    }

  private:
    virtual const bool receive( const StopWatch::EvStart & evt )
    {
      return transit_to< Active >( &StopWatch::StoppedActiveTransition, evt );
    }

    virtual const clock_t ElapsedTime() const
    {
      return 0;
    }
};


bool boost_error( char const *, char const *, char const *, long )
{
  return true;
}


int main( int argc, char * argv[] )
{
  argc;
  argv;

  StopWatch stopWatch;
  stopWatch.Start();
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  stopWatch.Pause();
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  stopWatch.Continue();
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  stopWatch.Stop();
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );
  std::cout << stopWatch.ElapsedTime() << "\n";
  Sleep( 1000 );

	return 0;
}