#ifndef BOOST_FSM_DETAIL_LEAF_STATE_HPP_INCLUDED
#define BOOST_FSM_DETAIL_LEAF_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
    leaf_state(
      typename RttiPolicy::id_provider_type idProvider
    ) :
      base_type( idProvider )
    {
    }

    virtual ~leaf_state() {}

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
