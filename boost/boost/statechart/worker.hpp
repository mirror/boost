#ifndef BOOST_FSM_WORKER_HPP_INCLUDED
#define BOOST_FSM_WORKER_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/detail/rtti_policy.hpp>
#include <boost/fsm/detail/event_processor.hpp>

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>

#ifdef BOOST_HAS_THREADS
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#endif

#include <memory>   // std::allocator
#include <utility>  // std::pair
#include <list>



namespace boost
{
namespace fsm
{
namespace detail
{



template< class Worker >
class event_processor;



}



//////////////////////////////////////////////////////////////////////////////
template< class Allocator = std::allocator< void > >
class worker : noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    worker() : noOfTerminatedProcessors_( 0 ) {}

    ~worker()
    {
      BOOST_ASSERT( terminated() && processorList_.empty() );
    }

    void operator()()
    {
      // The only two functions that can throw in this function are initiate()
      // and process_event(). When an exception is thrown, we must terminate
      // all registered processors before returning to the caller.
      scope_guard guard( *this );

      if ( terminated() )
      {
        noOfTerminatedProcessors_ = 0;

        for (
          processor_list_type::iterator pProcessor = processorList_.begin();
          pProcessor != processorList_.end(); ++pProcessor )
        {
          noOfTerminatedProcessors_ +=
            ( *pProcessor )->initiate() ? 1 : 0;
        }
      }
      else
      {
        #ifdef BOOST_HAS_THREADS
        // Since operator() will never return before all machines are
        // terminated in multithreaded builds, getting here means that
        // operator() was erroneously called from two different threads.
        guard.dismiss();
        BOOST_ASSERT( false );
        #endif
      }

      while ( !terminated() )
      {
        queue_element element = get_element();

        if ( element.first != 0 )
        {
          noOfTerminatedProcessors_ +=
            element.first->process_event( element.second ) ? 1 : 0;
        }
        else
        {
          guard.dismiss();
          return;
        }
      }

      guard.dismiss();
    }

    bool terminated() const
    {
      return noOfTerminatedProcessors_ == processorList_.size();
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    friend class detail::event_processor< worker >;

    typedef detail::event_processor< worker > processor_type;
    typedef std::list< processor_type *, Allocator > processor_list_type;
    typedef intrusive_ptr< const event_base > event_ptr_type;
    typedef std::pair< processor_type *, event_ptr_type > queue_element;
    typedef std::list< queue_element, Allocator > event_queue_type;

    class scope_guard
    {
      public:
        scope_guard( worker & theWorker ) :
          worker_( theWorker ), dismissed_( false ) {}
        ~scope_guard() { if ( !dismissed_ ) worker_.terminate(); }
        void dismiss() { dismissed_ = true; }
      private:
        worker & worker_;
        bool dismissed_;
    };

    friend class scope_guard;


    void add_processor( processor_type & processor )
    {
      // A worker may not run when a processor is added
      BOOST_ASSERT( terminated() );
      processorList_.push_back( &processor );
      ++noOfTerminatedProcessors_;
    }

    void remove_processor( processor_type & processor )
    {
      // It is the users responsibility to ensure that an event_processor
      // object is not destructed before worker<>::operator()() returns
      BOOST_ASSERT( terminated() );
      processorList_.remove( &processor );
      --noOfTerminatedProcessors_;
    }

    void queue_event(
      processor_type & processor, const event_ptr_type & pEvent )
    {
      #ifdef BOOST_HAS_THREADS
      mutex::scoped_lock lock( mutex_ );
      #endif

      queue_.push_back( std::make_pair( &processor, pEvent ) );

      #ifdef BOOST_HAS_THREADS
      queueNotEmpty_.notify_one();
      #endif
    }


    queue_element get_element()
    {
      #ifdef BOOST_HAS_THREADS
      mutex::scoped_lock lock( mutex_ );

      while ( queue_.empty() )
      {
        queueNotEmpty_.wait( lock );
      }
      #else
      // If the queue happens to run empty in a single-threaded system,
      // waiting for new events (which means to loop indefinitely!) is
      // pointless as there is no way that new events could find their way
      // into the queue. The only sensible thing is to exit the loop and
      // return to the caller in this case, although the state machines
      // might not yet have terminated.
      // Users can then queue new events before calling operator() again.
      if ( queue_.empty() )
      {
        return queue_element( 0, 0 );
      }
      #endif

      queue_element result = queue_.front();
      queue_.pop_front();
      return result;
    }


    void terminate()
    {
      for ( processor_list_type::iterator pProcessor = processorList_.begin();
            pProcessor != processorList_.end(); ++pProcessor )
      {
        ( *pProcessor )->terminate();
      }

      noOfTerminatedProcessors_ = processorList_.size();
    }

    size_t noOfTerminatedProcessors_;
    processor_list_type processorList_;
    event_queue_type queue_;

    #ifdef BOOST_HAS_THREADS
    mutex mutex_;
    condition queueNotEmpty_;
    #endif
};



} // namespace fsm
} // namespace boost



#endif
