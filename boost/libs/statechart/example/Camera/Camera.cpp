//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
