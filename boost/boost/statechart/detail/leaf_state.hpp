#ifndef BOOST_FSM_DETAIL_LEAF_STATE_HPP_INCLUDED
#define BOOST_FSM_DETAIL_LEAF_STATE_HPP_INCLUDED
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
template< class Allocator, class RttiPolicy >
class leaf_state : public state_base< Allocator, RttiPolicy >
{
  typedef state_base< Allocator, RttiPolicy > base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    leaf_state( typename RttiPolicy::id_type id ) : base_type( id ) {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void set_list_position( typename state_list_type::iterator listPosition )
    {
      listPosition_ = listPosition;
    }

    typedef typename base_type::state_list_type state_list_type;

    virtual void remove_from_state_list(
      state_list_type & states, typename state_list_type::iterator & )
    {
      // Because the list owns the leaf_state, this leads to the immediate
      // termination of this state.
      states.erase( listPosition_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    typename state_list_type::iterator listPosition_;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
