#ifndef BOOST_FSM_LEAF_STATE_HPP_INCLUDED
#define BOOST_FSM_LEAF_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/universal_state.hpp>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{
namespace detail
{



//////////////////////////////////////////////////////////////////////////////
template< class StateList >
class leaf_state : public universal_state< StateList >
{
    typedef universal_state< StateList > base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    leaf_state() {}

    using base_type::set_context;

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void set_list_position( typename StateList::iterator listPosition )
    {
      listPosition_ = listPosition;
    }

    virtual void remove_from_state_list( StateList & states )
    {
      // Because the list owns the leaf_state, this leads to the immediate
      // termination of this state.
      states.erase( listPosition_ );
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    typename StateList::iterator listPosition_;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
