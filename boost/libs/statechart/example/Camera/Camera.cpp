//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
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

bool NotShooting::handle_event( const EvShutterHalf & )
{
  if ( context< Camera >().IsBatteryLow() )
  {
    return false;
  }
  else
  {
    return transit_to< Shooting >();
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

bool Idle::handle_event( const EvConfig & )
{
  return transit_to< Configuring >();
}
