//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Shooting.hpp"
#include <iostream>



Shooting::Shooting()
{
  std::cout << "Entering Shooting\n";
}

Shooting::~Shooting()
{
  std::cout << "Exiting Shooting\n";
}


struct Storing : public fsm::simple_state< Storing, Shooting >
{
  Storing()
  {
    std::cout << "Picture taken!\n";
  }
};


struct Focused : public fsm::simple_state< Focused, Shooting,
  fsm::custom_reaction< EvShutterFull > >
{
  virtual fsm::result react( const EvShutterFull & );
};

fsm::result Focused::react( const EvShutterFull & )
{
  if ( context< Camera >().IsMemoryAvailable() )
  {
    return transit< Storing >();
  }
  else
  {
    std::cout << "Cache memory full. Please wait...\n";
    return discard_event();
  }
}


struct EvInFocus : public fsm::event< EvInFocus > {};

Focusing::Focusing( my_context ctx ) : my_base( ctx )
{
  post_event( boost::intrusive_ptr< EvInFocus >( new EvInFocus() ) );
}

fsm::result Focusing::react( const EvInFocus & evt )
{
  return transit< Focused >( &Shooting::DisplayFocused, evt );
}
