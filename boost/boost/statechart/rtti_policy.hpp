#ifndef BOOST_FSM_RTTI_POLICY_HPP_INCLUDED
#define BOOST_FSM_RTTI_POLICY_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <typeinfo> // std::type_info



#ifdef BOOST_MSVC
// We permanently turn off the following level 4 warnings because users will
// have to do so themselves anyway if we turn them back on
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



namespace boost
{
namespace fsm
{



//////////////////////////////////////////////////////////////////////////////
struct rtti_policy
{
  typedef const std::type_info & id_type;

  ////////////////////////////////////////////////////////////////////////////
  template< class Base >
  class base_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      id_type dynamic_type() const
      {
        // On MSVC7.1 event dispatch is quite a bit faster when each object
        // stores a reference to its type_info object during construction
        // instead of returning typeid( *this ) here.
        // The resulting increase in state size will not be noticeable under
        // almost all circumstances (the memory footprint of a very complex
        // state machine could grow by maybe 100 bytes).
        return id_;
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
      base_type( id_type id ) : id_( id ) {}

    private:
      ////////////////////////////////////////////////////////////////////////
      id_type id_;
  };

  ////////////////////////////////////////////////////////////////////////////
  template< class MostDerived, class Base >
  class derived_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      static id_type static_type()
      {
        return typeid( MostDerived );
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
      derived_type() : Base( static_type() ) {}
  };
};



} // namespace fsm
} // namespace boost



#endif
