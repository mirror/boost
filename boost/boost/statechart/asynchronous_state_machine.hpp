#ifndef BOOST_FSM_ASYNCHRONOUS_STATE_MACHINE_HPP_INCLUDED
#define BOOST_FSM_ASYNCHRONOUS_STATE_MACHINE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/worker.hpp>

#include <boost/fsm/detail/event_processor.hpp>
#include <boost/fsm/detail/state_base.hpp>



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
template< class MostDerived,
          class InitialState,
          class Worker = worker<>,
          class Allocator = std::allocator< void >,
          class ExceptionTranslator = exception_translator<> >
class asynchronous_state_machine : public state_machine<
  MostDerived, InitialState, Allocator, ExceptionTranslator >,
  public detail::event_processor< Worker >
{
  typedef state_machine< MostDerived,
    InitialState, Allocator, ExceptionTranslator > machine_base;
  typedef detail::event_processor< Worker > processor_base;
  protected:
    //////////////////////////////////////////////////////////////////////////
    asynchronous_state_machine( Worker & myWorker ) :
      processor_base( myWorker )
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

    void terminate( machine_base::state_base_type & theState )
    {
      machine_base::terminate( theState );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    typedef typename processor_base::event_ptr_type event_ptr_type;

    virtual bool initiate_impl()
    {
      return machine_base::initiate();
    }

    virtual bool process_event_impl( const event_ptr_type & pEvent )
    {
      return machine_base::process_event( *pEvent );
    }

    virtual void terminate_impl()
    {
      return machine_base::terminate();
    }
};



} // namespace fsm
} // namespace boost



#endif
