#ifndef BOOST_FSM_ASYNCHRONOUS_STATE_MACHINE_HPP_INCLUDED
#define BOOST_FSM_ASYNCHRONOUS_STATE_MACHINE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/worker.hpp>
#include <boost/fsm/event_processor.hpp>



namespace boost
{
namespace fsm
{



class event_base;



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived,
          class InitialState,
          class Worker = worker<>,
          class Allocator = std::allocator< void >,
          class ExceptionTranslator = exception_translator<> >
class asynchronous_state_machine : public state_machine<
  MostDerived, InitialState, Allocator, ExceptionTranslator >,
  public event_processor< Worker >
{
  typedef state_machine< MostDerived,
    InitialState, Allocator, ExceptionTranslator > machine_base;
  typedef event_processor< Worker > processor_base;
  protected:
    //////////////////////////////////////////////////////////////////////////
    asynchronous_state_machine( const processor_context & myContext ) :
      processor_base( myContext )
    {
    }

    virtual ~asynchronous_state_machine() {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void terminate()
    {
      processor_base::terminate();
    }

    void terminate( asynchronous_state_machine & machine )
    {
      machine_base::terminate( machine );
    }

    void terminate( typename machine_base::state_base_type & theState )
    {
      machine_base::terminate( theState );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    virtual void initiate_impl()
    {
      machine_base::initiate();
    }

    virtual void process_event_impl( const event_base & evt )
    {
      machine_base::process_event( evt );
    }

    virtual void terminate_impl()
    {
      machine_base::terminate();
    }
};



} // namespace fsm
} // namespace boost



#endif
