#ifndef CONFIGURING_HPP
#define CONFIGURING_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Camera.hpp"

#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/transition.hpp>

#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#endif



namespace fsm = boost::fsm;



struct Configuring : fsm::simple_state< Configuring, NotShooting,
  fsm::transition< EvConfig, Idle > >
{
  Configuring();
  ~Configuring();
};



#endif
