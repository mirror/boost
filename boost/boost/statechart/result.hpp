#ifndef BOOST_STATECHART_RESULT_HPP_INCLUDED
#define BOOST_STATECHART_RESULT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2005
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



namespace boost
{
namespace statechart
{



//////////////////////////////////////////////////////////////////////////////
enum result
{
  no_reaction,
  do_forward_event,
  do_discard_event,
  do_defer_event
};



} // namespace statechart
} // namespace boost



#endif
