//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// The following example program demonstrates the use of orthogonal states and
// state_downcast to query the state of orthogonal regions.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include <iostream>

namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvNumLockPressed : fsm::event< EvNumLockPressed > {};
struct EvCapsLockPressed : fsm::event< EvCapsLockPressed > {};
struct EvScrollLockPressed : fsm::event< EvScrollLockPressed > {};
struct EvRequestShutdown : fsm::event< EvRequestShutdown > {};

struct Active;
struct Keyboard : fsm::state_machine< Keyboard, Active > {};

struct NumLockOff;
struct CapsLockOff;
struct ScrollLockOff;
struct Active: fsm::simple_state<
  Active, Keyboard, fsm::custom_reaction< EvRequestShutdown >,
  mpl::list< NumLockOff, CapsLockOff, ScrollLockOff > >
{
  Active()
  {
    std::cout << "Entering Active\n";
  }

  ~Active()
  {
    std::cout << "Exiting Active\n";
  }

  fsm::result react( const EvRequestShutdown & )
  {
    if ( ( state_downcast< const NumLockOff * >() != 0 ) &&
         ( state_downcast< const CapsLockOff * >() != 0 ) &&
         ( state_downcast< const ScrollLockOff * >() != 0 ) )
    {
      std::cout << "Shutdown request accepted\n";
      return terminate();
    }
    else
    {
      std::cout << "Ignoring shutdown request\n";
      return discard_event();
    }
  }
};

struct NumLockOn : fsm::simple_state<
  NumLockOn, Active::orthogonal< 0 >,
  fsm::transition< EvNumLockPressed, NumLockOff > >
{
  NumLockOn()
  {
    std::cout << "NumLockOn\n";
  }
};

struct NumLockOff : fsm::simple_state<
  NumLockOff, Active::orthogonal< 0 >,
  fsm::transition< EvNumLockPressed, NumLockOn > >
{
  NumLockOff()
  {
    std::cout << "NumLockOff\n";
  }
};

struct CapsLockOn : fsm::simple_state<
  CapsLockOn, Active::orthogonal< 1 >,
  fsm::transition< EvCapsLockPressed, CapsLockOff > >
{
  CapsLockOn()
  {
    std::cout << "CapsLockOn\n";
  }
};

struct CapsLockOff : fsm::simple_state<
  CapsLockOff, Active::orthogonal< 1 >,
  fsm::transition< EvCapsLockPressed, CapsLockOn > >
{
  CapsLockOff()
  {
    std::cout << "CapsLockOff\n";
  }
};

struct ScrollLockOn : fsm::simple_state<
  ScrollLockOn, Active::orthogonal< 2 >,
  fsm::transition< EvScrollLockPressed, ScrollLockOff > >
{
  ScrollLockOn()
  {
    std::cout << "ScrollLockOn\n";
  }
};

struct ScrollLockOff : fsm::simple_state<
  ScrollLockOff, Active::orthogonal< 2 >,
  fsm::transition< EvScrollLockPressed, ScrollLockOn > >
{
  ScrollLockOff()
  {
    std::cout << "ScrollLockOff\n";
  }
};


int main()
{
  std::cout << "boost::fsm Keyboard example\n\n";
  Keyboard keyboard;
  keyboard.initiate();
  keyboard.process_event( EvNumLockPressed() );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvCapsLockPressed() );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvScrollLockPressed() );
  keyboard.process_event( EvRequestShutdown() );

  keyboard.process_event( EvNumLockPressed() );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvCapsLockPressed() );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvScrollLockPressed() );
  keyboard.process_event( EvRequestShutdown() );

  return 0;
}
