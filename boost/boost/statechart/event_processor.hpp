#ifndef BOOST_FSM_EVENT_PROCESSOR_INCLUDED
#define BOOST_FSM_EVENT_PROCESSOR_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



namespace boost
{
namespace fsm
{


  
class event_base;



//////////////////////////////////////////////////////////////////////////////
template< class Worker >
class event_processor
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~event_processor() {}

    Worker & my_worker() const
    {
      return myWorker_;
    }

    typedef typename Worker::processor_handle processor_handle;

    processor_handle my_handle() const
    {
      return myHandle_;
    }

    void initiate()
    {
      initiate_impl();
    }

    void process_event( const event_base & evt )
    {
      process_event_impl( evt );
    }

    void terminate()
    {
      terminate_impl();
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    typedef typename Worker::processor_context processor_context;

    event_processor( const processor_context & myContext ) :
      myWorker_( myContext.my_worker() ),
      myHandle_( myContext.my_handle() )
    {
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual void initiate_impl() = 0;
    virtual void process_event_impl( const event_base & evt ) = 0;
    virtual void terminate_impl() = 0;

    Worker & myWorker_;
    const processor_handle myHandle_;
};



} // namespace fsm
} // namespace boost



#endif
