#ifndef CAMERA_HPP
#define CAMERA_HPP
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/custom_reaction.hpp>

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


struct Idle;
struct NotShooting : public fsm::simple_state< NotShooting, Camera,
  fsm::custom_reaction< EvShutterHalf >, Idle >
{
  NotShooting();
  ~NotShooting();

  virtual fsm::result react( const EvShutterHalf & );
};

struct Idle : public fsm::simple_state< Idle, NotShooting,
  fsm::custom_reaction< EvConfig > >
{
  Idle();
  ~Idle();

  virtual fsm::result react( const EvConfig & );
};



#endif
