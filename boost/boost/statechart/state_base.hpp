#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP
//////////////////////////////////////////////////////////////////////////////
// (c) 2002 Andreas Huber, Zurich, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>



#ifdef _MSC_VER
// these appear with warning level 4 only
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
class state_base : boost::noncopyable
{
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~state_base() {}

    state_base * const outer_state_ptr() const
    {
      return pOuterState_;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    state_base( state_base * pOuterState ) : pOuterState_( pOuterState ) {}
    // as the top context is not derived from state_base, the following
    // overload will only be called when the top context is passed
    state_base( ... ) : pOuterState_( 0 ) {}

  private:
    //////////////////////////////////////////////////////////////////////////
    state_base * const pOuterState_;
};



} // namespace fsm
} // namespace boost



#endif
