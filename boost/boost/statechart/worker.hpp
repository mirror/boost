#ifndef BOOST_FSM_WORKER_HPP_INCLUDED
#define BOOST_FSM_WORKER_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event_base.hpp>
#include <boost/fsm/event.hpp>
#include <boost/fsm/event_processor.hpp>

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#ifdef BOOST_HAS_THREADS
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/condition.hpp>
#endif

#include <set>
#include <memory>   // std::allocator, std::auto_ptr
#include <utility>  // std::pair



namespace boost
{
namespace fsm
{



template< class Allocator = std::allocator< void > >
class worker : noncopyable
{
    typedef event_processor< worker > processor_type;
    typedef std::auto_ptr< processor_type > processor_holder_type;
    typedef shared_ptr< processor_holder_type > processor_holder_ptr_type;
  public:
    //////////////////////////////////////////////////////////////////////////
    #ifdef BOOST_HAS_THREADS
    worker( bool waitOnEmptyQueue = true ) :
    #else
    worker() :
    #endif
      pProcessorContainer_( new processor_holder_type() ),
      processorHolderHandle_( pProcessorContainer_ ),
      #ifdef BOOST_HAS_THREADS
      waitOnEmptyQueue_( waitOnEmptyQueue ),
      #endif
      terminated_( false )
    {
      pProcessorContainer_->reset( new processor_container(
        processor_context( *this, processorHolderHandle_ ) ) );
    }

    typedef weak_ptr< processor_holder_type > processor_handle;

    class processor_context : noncopyable
    {
      processor_context(
        worker & theWorker, const processor_handle & theHandle
      ) :
        worker_( theWorker ),
        handle_( theHandle )
      {
      }

      worker & my_worker() const { return worker_; }
      const processor_handle & my_handle() const { return handle_; }

      worker & worker_;
      const processor_handle handle_;

      friend class worker;
      friend class event_processor< worker >;
    };

    template< class Processor >
    processor_handle create_processor()
    {
      // We must lock during the addition to the queue as well as throughout
      // the construction because the event needs to be modified *after*
      // being added to the queue (see below why).
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif

      // The processor constructor might call destroy_processor with its own
      // handle (a bit strange but legal). For this case we must queue the
      // event *before* constructing the processor.
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ) ) );
      return pProcessor;
    }

    template< class Processor, typename Param1 >
    processor_handle create_processor( Param1 param1 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ), param1 ) );
      return pProcessor;
    }

    template< class Processor, typename Param1, typename Param2 >
    processor_handle create_processor( Param1 param1, Param2 param2 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ), param1, param2 ) );
      return pProcessor;
    }

    template<
      class Processor, typename Param1, typename Param2, typename Param3 >
    processor_handle create_processor(
      Param1 param1, Param2 param2, Param3 param3 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ), param1, param2, param3 ) );
      return pProcessor;
    }

    template<
      class Processor, typename Param1, typename Param2,
      typename Param3, typename Param4 >
    processor_handle create_processor(
      Param1 param1, Param2 param2, Param3 param3, Param4 param4 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ),
        param1, param2, param3, param4 ) );
      return pProcessor;
    }

    template<
      class Processor, typename Param1, typename Param2,
      typename Param3, typename Param4, typename Param5 >
    processor_handle create_processor(
      Param1 param1, Param2 param2,
      Param3 param3, Param4 param4, Param5 param5 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ),
        param1, param2, param3, param4, param5 ) );
      return pProcessor;
    }

    template<
      class Processor, typename Param1, typename Param2,
      typename Param3, typename Param4, typename Param5, typename Param6 >
    processor_handle create_processor(
      Param1 param1, Param2 param2, Param3 param3,
      Param4 param4, Param5 param5, Param6 param6 )
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif
      processor_holder_ptr_type pProcessor = queue_empty_event_unlocked();
      pProcessor->reset( new Processor(
        processor_context( *this, pProcessor ),
        param1, param2, param3, param4, param5, param6 ) );
      return pProcessor;
    }

    void destroy_processor( processor_handle processor )
    {
      queue_event( processorHolderHandle_, make_event( new internal_event(
        processor, internal_event::destroy_processor ) ) );
    }

    void initiate_processor( processor_handle processor )
    {
      queue_event( processorHolderHandle_, make_event( new internal_event(
        processor, internal_event::initiate_processor ) ) );
    }

    void terminate_processor( processor_handle processor )
    {
      queue_event( processorHolderHandle_, make_event( new internal_event(
        processor, internal_event::terminate_processor ) ) );
    }

    typedef intrusive_ptr< const event_base > event_ptr_type;

    void queue_event(
      const processor_handle & processor, const event_ptr_type & pEvent )
    {
      BOOST_ASSERT( pEvent.get() != 0 );

      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );
      #endif

      queue_event_unlocked( processor, pEvent );
    }

    void terminate()
    {
      queue_event( 
        processorHolderHandle_, make_event( new internal_event() ) );
    }

    // Is not mutex-protected! Must only be called from the thread that also
    // calls operator().
    bool terminated() const
    {
      return terminated_;
    }

    unsigned long operator()( unsigned long maxEventCount = 0 )
    {
      unsigned long eventCount = 0;

      while ( !terminated() &&
        ( ( maxEventCount == 0 ) || ( eventCount < maxEventCount ) ) )
      {
        queue_element element = dequeue_event();

        if ( element.second.get() == 0 )
        {
          // element.second can only be null when the queue is empty, which
          // only happens in ST builds or when users pass false to the worker
          // constructor
          return eventCount;
        }

        // If we get here element.first can be only null because the processor
        // referred to by the handle has been destroyed.
        processor_holder_ptr_type pProcessorHolder = element.first.lock();
        ++eventCount;

        if ( pProcessorHolder != 0 )
        {
          BOOST_ASSERT( &( ( *pProcessorHolder )->my_worker() ) == this );
          ( *pProcessorHolder )->process_event( *element.second );
        }
      }

      return eventCount;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    struct internal_event : event< internal_event >
    {
      enum action_type
      {
        create_processor,
        destroy_processor,
        initiate_processor,
        terminate_processor,
        terminate_worker
      };

      internal_event() : action_( terminate_worker ) {}

      internal_event( const processor_holder_ptr_type & pProcessorHolder ) :
        pProcessorHolder_( pProcessorHolder ),
        action_( create_processor )
      {
      }

      internal_event( processor_handle processor, action_type action ) :
        processor_( processor ),
        action_( action )
      {
        BOOST_ASSERT( 
          ( action != create_processor ) && ( action != terminate_worker ) );
      }

      const processor_holder_ptr_type pProcessorHolder_;
      const processor_handle processor_;
      const action_type action_;
    };

    class processor_container : public processor_type
    {
      public:
        processor_container(
          const typename processor_type::processor_context & myContext
        ) :
          processor_type( myContext )
        {
        }

      private:
        virtual void initiate_impl() {}

        virtual void process_event_impl( const event_base & eventBase )
        {
          const internal_event & evt =
            *polymorphic_downcast< const internal_event * >( &eventBase );

          switch ( evt.action_ )
          {
            case internal_event::create_processor:
            {
              processorSet_.insert( evt.pProcessorHolder_ );
            }
            break;

            case internal_event::destroy_processor:
            {
              const processor_holder_ptr_type pProcessorHolder =
                evt.processor_.lock();

              if ( pProcessorHolder != 0 )
              {
                processorSet_.erase( pProcessorHolder );
              }
            }
            break;

            case internal_event::initiate_processor:
            {
              const processor_holder_ptr_type pProcessorHolder =
                evt.processor_.lock();

              if ( pProcessorHolder != 0 )
              {
                ( *pProcessorHolder )->initiate();
              }
            }
            break;
            case internal_event::terminate_processor:
            {
              const processor_holder_ptr_type pProcessorHolder =
                evt.processor_.lock();

              if ( pProcessorHolder != 0 )
              {
                ( *pProcessorHolder )->terminate();
              }
            }
            break;
            case internal_event::terminate_worker:
            {
              my_worker().terminated_ = true;
            }
            break;
            default:
            {
              BOOST_ASSERT( false );
            }
            break;
          }
        }

        virtual void terminate_impl() {}

        typedef std::set< 
          processor_holder_ptr_type, 
          std::less< processor_holder_ptr_type >, Allocator
        > event_processor_set_type;
        event_processor_set_type processorSet_;
    };

    friend class processor_container;

    processor_holder_ptr_type queue_empty_event_unlocked()
    {
      processor_holder_ptr_type pProcessorHolder(
        new processor_holder_type() );
      queue_event_unlocked(
        processorHolderHandle_,
        make_event( new internal_event( pProcessorHolder ) ) );
      return pProcessorHolder;
    }

    void queue_event_unlocked(
      const processor_handle & processor, const event_ptr_type & pEvent )
    {
      BOOST_ASSERT( &( ( *processor.lock() )->my_worker() ) == this );
      eventQueue_.push_back( std::make_pair( processor, pEvent ) );

      #ifdef BOOST_HAS_THREADS
      queueNotEmpty_.notify_one();
      #endif
    }

    typedef std::pair< processor_handle, event_ptr_type > queue_element;

    queue_element dequeue_event()
    {
      #ifdef BOOST_HAS_THREADS
      recursive_mutex::scoped_lock lock( mutex_ );

      if ( !waitOnEmptyQueue_ && eventQueue_.empty() )
      {
        return queue_element( processor_handle(), 0 );
      }

      while ( eventQueue_.empty() )
      {
        queueNotEmpty_.wait( lock );
      }
      #else
      // If the queue happens to run empty in a single-threaded system,
      // waiting for new events (which means to loop indefinitely!) is
      // pointless as there is no way that new events could find their way
      // into the queue. The only sensible thing is to exit the loop and
      // return to the caller in this case.
      // Users can then queue new events before calling operator() again.
      if ( eventQueue_.empty() )
      {
        return queue_element( processor_handle(), 0 );
      }
      #endif

      queue_element result = eventQueue_.front();
      eventQueue_.pop_front();
      return result;
    }

    static event_ptr_type make_event( const event_base * pEvent )
    {
      return event_ptr_type( pEvent );
    }

    const processor_holder_ptr_type pProcessorContainer_;
    const processor_handle processorHolderHandle_;

    typedef std::list< queue_element, Allocator > event_queue_type;
    event_queue_type eventQueue_;

    #ifdef BOOST_HAS_THREADS
    // We need a recursive_mutex because we must call external code while
    // mutex_ is in locked state. The external code might in turn call
    // queue_event, which also needs to lock (see create_processor for
    // details).
    recursive_mutex mutex_;
    condition queueNotEmpty_;
    const bool waitOnEmptyQueue_;
    #endif

    bool terminated_;
};



} // namespace fsm
} // namespace boost



#endif
