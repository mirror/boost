//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
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
  fsm::custom_handler< EvShutterFull > >
{
  virtual bool handle_event( const EvShutterFull & );
};

bool Focused::handle_event( const EvShutterFull & )
{
  if ( context< Camera >().IsMemoryAvailable() )
  {
    return transit_to< Storing >();
  }
  else
  {
    std::cout << "Cache memory full. Please wait...\n";
    // Indicate that we have consumed the event. So, the 
    // dispatch algorithm will stop looking for a handler.
    return true;
  }
}


struct EvInFocus : public fsm::event< EvInFocus > {};

Focusing::Focusing( my_context ctx ) : my_base( ctx )
{
  post_event( boost::shared_ptr< EvInFocus >( new EvInFocus() ) );
}

bool Focusing::handle_event( const EvInFocus & evt )
{
  return transit_to< Focused >( &Shooting::DisplayFocused, evt );
}
