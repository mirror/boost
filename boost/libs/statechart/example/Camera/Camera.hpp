#ifndef CAMERA_HPP
#define CAMERA_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/custom_handler.hpp>

namespace fsm = boost::fsm;



class EvShutterHalf : public fsm::event< EvShutterHalf > {};
class EvShutterFull : public fsm::event< EvShutterFull > {};
class EvShutterRelease : public fsm::event< EvShutterRelease > {};
class EvConfig : public fsm::event< EvConfig > {};


struct NotShooting;
struct Camera : public fsm::state_machine< Camera, NotShooting >
{
    bool IsMemoryAvailable() const { return true; }
    bool IsBatteryLow() const { return false; }
};


// With fsm::transition the target state must be a complete type. That is,
// Configuring.hpp and Shooting.hpp would have to be included in this header.
// Instead, a custom handler is used. This allows us to make the transitions
// in the respective .cpp files and to loosen the coupling to the target
// states.
struct Idle;
struct NotShooting : public fsm::simple_state< NotShooting, Camera,
  fsm::custom_handler< EvShutterHalf >, Idle >
{
  NotShooting();
  ~NotShooting();

  virtual bool handle_event( const EvShutterHalf & );
};

struct Idle : public fsm::simple_state< Idle, NotShooting,
  fsm::custom_handler< EvConfig > >
{
  Idle();
  ~Idle();

  virtual bool handle_event( const EvConfig & );
};



#endif
