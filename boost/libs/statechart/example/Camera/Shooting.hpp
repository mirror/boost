#ifndef BOOST_FSM_EXAMPLE_SHOOTING_HPP
#define BOOST_FSM_EXAMPLE_SHOOTING_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include "Camera.hpp"

#include <boost/fsm/event.hpp>
#include <boost/fsm/simple_state.hpp>
#include <boost/fsm/state.hpp>
#include <boost/fsm/transition.hpp>
#include <boost/fsm/custom_reaction.hpp>
#include <boost/fsm/deferral.hpp>

#include <boost/mpl/list.hpp>
#include <boost/config.hpp>

#ifdef BOOST_INTEL
#  pragma warning( disable: 304 ) // access control not specified
#endif



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
