#ifndef SHOOTING_HPP
#define SHOOTING_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include "Camera.hpp"
#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_handler.hpp>
#include <boost/mpl/list.hpp>

namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvInFocus;
struct Focusing;
struct Shooting : public fsm::simple_state< Shooting, Camera,
  fsm::transition< EvShutterRelease, NotShooting >, Focusing >
{
  Shooting();
  ~Shooting();

  void DisplayFocused( const EvInFocus & )
  {
    std::cout << "Focused!\n";
  }
};

struct Focusing : public fsm::state< Focusing, Shooting,
  fsm::custom_handler< EvInFocus > >
{
  Focusing( my_context ctx );
  virtual bool handle_event( const EvInFocus & );
};



#endif
