//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
#define USE_TWO_WORKER_THREADS // ignored for single-threaded builds
//////////////////////////////////////////////////////////////////////////////
// The following example program demonstrates the use of asynchronous state
// machines. First, it creates two objects of the same simple state machine
// mimicking a table tennis player. It then sends an event (the ball) to the
// first state machine. Upon reception, the first machine sends a similar
// event to the second state machine, which then sends the event back to the
// first machine. The two machines continue to bounce the event back and forth
// until one machine "has enough" and aborts the game. The two players don't
// "know" each other, they can only pass the ball back and forth because the
// event representing the ball also carries two boost::function objects.
// Both reference the worker<>::queue_event() function, binding the worker and
// the handle of the opponent. One can be used to return the ball to the
// opponent and the other can be used to abort the game.
// Depending on whether the program is compiled single-threaded or
// multi-threaded and the USE_TWO_WORKER_THREADS define above, the two
// machines either run in the same thread without/with mutex locking or in two
// different threads with mutex locking.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/asynchronous_state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>
#include <boost/fsm/worker.hpp>

#include <boost/mpl/list.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp>
#ifdef BOOST_HAS_THREADS
#include <boost/thread/thread.hpp>
#endif

#include <iostream>
#include <ctime>

namespace fsm = boost::fsm;
namespace mpl = boost::mpl;


const unsigned int noOfEvents = 1000000;

template< class T >
boost::intrusive_ptr< T > MakeIntrusive( T * pObject )
{
  return boost::intrusive_ptr< T >( pObject );
}


struct BallReturned : fsm::event< BallReturned >
{
  boost::function1< void, const boost::intrusive_ptr< const BallReturned > & >
    returnToOpponent;
  boost::function0< void > abortGame;
};

struct GameAborted : fsm::event< GameAborted > {};


struct Waiting;
struct Player : fsm::asynchronous_state_machine< Player, Waiting >
{
  typedef fsm::asynchronous_state_machine< Player, Waiting > BaseType;
  public:
    Player( 
      const processor_context & myContext,
      unsigned int maxNoOfReturns
    ) :
      BaseType( myContext ),
      maxNoOfReturns_( maxNoOfReturns ),
      noOfReturns_( 0 ),
      pBallReturned_( new BallReturned() )
    {
      // as we will always return the same event to the opponent, we construct
      // and fill it here so that we can reuse it over and over
      pBallReturned_->returnToOpponent = boost::bind(
        &fsm::worker<>::queue_event, &my_worker(), my_handle(), _1 );
      pBallReturned_->abortGame = boost::bind(
        &fsm::worker<>::queue_event,
        &my_worker(), my_handle(),  MakeIntrusive( new GameAborted() ) );
      my_worker().initiate_processor( my_handle() );
    }

    void ReturnToOpponent( const BallReturned & ballReturned )
    {
      ++totalNoOfProcessedEvents_;

      if ( noOfReturns_++ < maxNoOfReturns_ )
      {
        ballReturned.returnToOpponent( pBallReturned_ );
      }
      else
      {
        ballReturned.abortGame();
        post_event(
          boost::intrusive_ptr< GameAborted >( new GameAborted() ) );
      }
    }

    static unsigned int GetTotalNoOfProcessedEvents()
    {
      return totalNoOfProcessedEvents_;
    }

  private:
    static unsigned int totalNoOfProcessedEvents_;
    const unsigned int maxNoOfReturns_;
    unsigned int noOfReturns_;
    const boost::intrusive_ptr< BallReturned > pBallReturned_;
};

unsigned int Player::totalNoOfProcessedEvents_ = 0;


struct Waiting : fsm::simple_state< Waiting, Player, mpl::list<
  fsm::transition< BallReturned, Waiting, Player, &Player::ReturnToOpponent >,
  fsm::custom_reaction< GameAborted > > >
{
  fsm::result react( const GameAborted & )
  {
    outermost_context_type & machine = outermost_context();
    machine.my_worker().destroy_processor( machine.my_handle() );
    machine.my_worker().terminate();
    return terminate();
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
  std::cout << "boost::fsm PingPong example\n\n";
  std::cout << "Threading configuration:\n";
  #ifdef BOOST_HAS_THREADS
  std::cout << "Multi-threaded build with ";
  #ifdef USE_TWO_WORKER_THREADS
  std::cout << 2;
  #else
  std::cout << 1;
  #endif
  std::cout << " worker thread(s).\n";
  #else
  std::cout << "Single-threaded build\n";
  #endif
  
  std::cout << "\np<CR>: Performance test\n";
  std::cout << "e<CR>: Exits the program\n\n";

  char key = GetKey();

  while ( key != 'e' )
  {
    switch( key )
    {
      case 'p':
      {
        fsm::worker<> worker1;

        #ifdef USE_TWO_WORKER_THREADS
        #ifdef BOOST_HAS_THREADS
        fsm::worker<> worker2;
        #else
        fsm::worker<> & worker2 = worker1;
        #endif
        #else
        fsm::worker<> & worker2 = worker1;
        #endif

        fsm::worker<>::processor_handle player1 = 
          worker1.create_processor< Player >( noOfEvents / 2 );
        fsm::worker<>::processor_handle player2 = 
          worker2.create_processor< Player >( noOfEvents / 2 );

        boost::intrusive_ptr< BallReturned > pInitialBall = new BallReturned();
        pInitialBall->returnToOpponent = boost::bind( 
          &fsm::worker<>::queue_event, &worker1, player1, _1 );
        pInitialBall->abortGame = boost::bind(
          &fsm::worker<>::queue_event, 
          &worker1, player1, MakeIntrusive( new GameAborted() ) );

        worker2.queue_event( player2, pInitialBall );

        std::cout << "\nHaving players return the ball " <<
          noOfEvents << " times. Please wait...\n";

        const unsigned int prevCount = Player::GetTotalNoOfProcessedEvents();
        const std::clock_t startTime = std::clock();

        #ifdef USE_TWO_WORKER_THREADS
        #ifdef BOOST_HAS_THREADS
        boost::thread otherThread(
          boost::bind( &fsm::worker<>::operator(), &worker2, 0 ) );
        worker1();
        otherThread.join();
        #else
        worker1();
        #endif
        #else
        worker1();
        #endif

        const std::clock_t elapsedTime = std::clock() - startTime;
        std::cout << "Time to send and dispatch one event and\n" <<
                     "perform the resulting transition: ";
        std::cout << elapsedTime / static_cast< double >( CLOCKS_PER_SEC ) *
          1000000.0 / ( Player::GetTotalNoOfProcessedEvents() - prevCount )
          << " microseconds\n\n";
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
