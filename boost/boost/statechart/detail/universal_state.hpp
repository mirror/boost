#ifndef BOOST_FSM_UNIVERSAL_STATE_HPP_INCLUDED
#define BOOST_FSM_UNIVERSAL_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp>



namespace boost
{
namespace fsm
{
namespace detail
{



//////////////////////////////////////////////////////////////////////////////
template< class StateList >
class universal_state : public state_base
{
    typedef state_base base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    universal_state() {}

    template< class Context >
    void set_context( orthogonal_position_type position, Context * pContext )
    {
      pContext->add_inner_state( position, this );
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    virtual void remove_from_state_list(
      StateList & states, typename StateList::iterator & pUnstableState ) = 0;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
