#ifndef BOOST_FSM_UNIVERSAL_STATE_HPP_INCLUDED
#define BOOST_FSM_UNIVERSAL_STATE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/fsm/detail/state_base.hpp>



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
class universal_state : public state_base
{
    typedef state_base base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    universal_state() {}

    template< class Context >
    void set_context( orthogonal_position_type position, Context * pContext )
    {
      base_type::set_context( pContext );
      pContext->add_inner_state( position, this );
    }

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    virtual void remove_from_state_list( StateList & states ) = 0;
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
