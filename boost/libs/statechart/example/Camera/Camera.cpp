//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include "Precompiled.hpp"
#include "Camera.hpp"
#include "Configuring.hpp"
#include "Shooting.hpp"



NotShooting::NotShooting()
{
  std::cout << "Entering NotShooting\n";
}

NotShooting::~NotShooting()
{
  std::cout << "Exiting NotShooting\n";
}

fsm::result NotShooting::react( const EvShutterHalf & )
{
  if ( context< Camera >().IsBatteryLow() )
  {
    return forward_event();
  }
  else
  {
    return transit< Shooting >();
  }
}


Idle::Idle()
{
  std::cout << "Entering Idle\n";
}

Idle::~Idle()
{
  std::cout << "Exiting Idle\n";
}

fsm::result Idle::react( const EvConfig & )
{
  return transit< Configuring >();
}
