#ifndef SHOOTING_HPP
#define SHOOTING_HPP
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
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
#include <boost/fsm/custom_reaction.hpp>
#include <boost/fsm/deferral.hpp>
#include <boost/mpl/list.hpp>



namespace fsm = boost::fsm;
namespace mpl = boost::mpl;



struct EvInFocus : fsm::event< EvInFocus > {};

struct Focusing;
struct Shooting : fsm::simple_state< Shooting, Camera,
  fsm::transition< EvShutterRelease, NotShooting >, Focusing >
{
  Shooting();
  ~Shooting();

  void DisplayFocused( const EvInFocus & )
  {
    std::cout << "Focused!\n";
  }
};

struct Focusing : fsm::state< Focusing, Shooting, mpl::list<
  fsm::custom_reaction< EvInFocus >, fsm::deferral< EvShutterFull > > >
{
  Focusing( my_context ctx );
  fsm::result react( const EvInFocus & );
};



#endif
