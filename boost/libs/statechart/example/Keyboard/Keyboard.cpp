//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
// The following example program demonstrates the use of orthogonal states and
// state_downcast to query the state of orthogonal regions.
// Moreover, the use of the state type information interface is also shown.
//////////////////////////////////////////////////////////////////////////////
// #define BOOST_FSM_USE_NATIVE_RTTI


#include <boost/fsm/event.hpp>
#include <boost/fsm/state_machine.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>

#include <boost/mpl/list.hpp>

#include <iostream>
#include <iomanip>

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
      std::cout << "Ignoring shutdown request\n\n";
      return discard_event();
    }
  }
};

struct NumLockOn : fsm::simple_state<
  NumLockOn, Active::orthogonal< 0 >,
  fsm::transition< EvNumLockPressed, NumLockOff > > {};

struct NumLockOff : fsm::simple_state<
  NumLockOff, Active::orthogonal< 0 >,
  fsm::transition< EvNumLockPressed, NumLockOn > > {};

struct CapsLockOn : fsm::simple_state<
  CapsLockOn, Active::orthogonal< 1 >,
  fsm::transition< EvCapsLockPressed, CapsLockOff > > {};

struct CapsLockOff : fsm::simple_state<
  CapsLockOff, Active::orthogonal< 1 >,
  fsm::transition< EvCapsLockPressed, CapsLockOn > > {};

struct ScrollLockOn : fsm::simple_state<
  ScrollLockOn, Active::orthogonal< 2 >,
  fsm::transition< EvScrollLockPressed, ScrollLockOff > > {};

struct ScrollLockOff : fsm::simple_state<
  ScrollLockOff, Active::orthogonal< 2 >,
  fsm::transition< EvScrollLockPressed, ScrollLockOn > > {};


void DisplayStateConfiguration( const Keyboard & keyboard )
{
  char orthogonalRegion = 'a';

  for ( Keyboard::state_iterator pLeafState = keyboard.state_begin();
    pLeafState != keyboard.state_end(); ++pLeafState )
  {
    std::cout << "Orthogonal region " << orthogonalRegion << ": ";

    const Keyboard::state_base_type * pState = &*pLeafState;

    while ( pState != 0 )
    {
      if ( pState != &*pLeafState )
      {
        std::cout << " -> ";
      }

      #ifdef BOOST_FSM_USE_NATIVE_RTTI
      std::cout << std::setw( 15 ) << typeid( *pState ).name();
      #else
      std::cout << std::setw( 15 ) <<
        pState->custom_dynamic_type_ptr< char >();
      #endif
      pState = pState->outer_state_ptr();
    }

    std::cout << "\n";
    ++orthogonalRegion;
  }

  std::cout << "\n";
}



int main()
{
  #ifndef BOOST_FSM_USE_NATIVE_RTTI
  Active::custom_static_type_ptr( "Active" );
  NumLockOn::custom_static_type_ptr( "NumLockOn" );
  NumLockOff::custom_static_type_ptr( "NumLockOff" );
  CapsLockOn::custom_static_type_ptr( "CapsLockOn" );
  CapsLockOff::custom_static_type_ptr( "CapsLockOff" );
  ScrollLockOn::custom_static_type_ptr( "ScrollLockOn" );
  ScrollLockOff::custom_static_type_ptr( "ScrollLockOff" );
  #endif

  std::cout << "boost::fsm Keyboard example\n\n";
  Keyboard keyboard;
  keyboard.initiate();
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvNumLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvCapsLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvScrollLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );

  keyboard.process_event( EvNumLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvCapsLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );
  keyboard.process_event( EvScrollLockPressed() );
  DisplayStateConfiguration( keyboard );
  keyboard.process_event( EvRequestShutdown() );

  return 0;
}
