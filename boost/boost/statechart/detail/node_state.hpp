#ifndef BOOST_FSM_NODE_STATE_HPP_INCLUDED
#define BOOST_FSM_NODE_STATE_HPP_INCLUDED
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
template< orthogonal_position_type noOfOrthogonalStates, class StateList >
class node_state : public universal_state< StateList >
{
    typedef universal_state< StateList > base_type;
  protected:
    //////////////////////////////////////////////////////////////////////////
    node_state()
    {
      for ( orthogonal_position_type pos = 0; pos < noOfOrthogonalStates; ++pos )
      {
        pInnerStates[ pos ] = 0;
      }
    }

    using base_type::set_context;

  public:
    //////////////////////////////////////////////////////////////////////////
    // CAUTION: The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void add_inner_state( orthogonal_position_type position,
                          universal_state< StateList > * pInnerState )
    {
      BOOST_ASSERT( ( position < noOfOrthogonalStates ) &&
                    ( pInnerStates[ position ] == 0 ) );
      pInnerStates[ position ] = pInnerState;
    }

    void remove_inner_state( orthogonal_position_type position )
    {
      BOOST_ASSERT( position < noOfOrthogonalStates );
      pInnerStates[ position ] = 0;
    }

    virtual void remove_from_state_list( StateList & states )
    {
      // Destroy inner states in the reverse order of construction
      for ( universal_state< StateList > ** pState =
              &pInnerStates[ noOfOrthogonalStates ]; 
            pState > &pInnerStates[ 0 ]; --pState )
      {
        // An inner orthogonal state might have been terminated long before,
        // that's why we have to check for 0 pointers
        if ( *( pState - 1 ) != 0 )
        {
          ( *( pState - 1 ) )->remove_from_state_list( states );
        }
      }
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    universal_state< StateList > * pInnerStates[ noOfOrthogonalStates ];
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
