#ifndef CONFIGURING_HPP
#define CONFIGURING_HPP
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include "Camera.hpp"
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>

namespace fsm = boost::fsm;



struct Configuring : fsm::simple_state< Configuring, NotShooting,
  fsm::transition< EvConfig, Idle > >
{
  Configuring();
  ~Configuring();
};



#endif
