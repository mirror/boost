#ifndef INTEGER_RTTI_POLICY_HPP_INCLUDED
#define INTEGER_RTTI_POLICY_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/assert.hpp>



#ifdef BOOST_MSVC
// We permanently turn off the following level 4 warnings because users will
// have to do so themselves anyway if we turn them back on
#pragma warning( disable: 4511 ) // copy constructor could not be generated
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#endif



//////////////////////////////////////////////////////////////////////////////
template< typename IdType >
IdType GetUniqueId()
{
  static IdType currentId = 0;
  return ++currentId;
}



//////////////////////////////////////////////////////////////////////////////
template< typename IdType, class Tag >
class IntegerId
{
  public:
    //////////////////////////////////////////////////////////////////////////
    static IdType GetId()
    {
      // The following assert fails if there is static initialisation order
      // problem. That is, an event or a state is created before main() is
      // entered, which is not allowed with this rtti policy implementation.
      BOOST_ASSERT( id_ > 0 );
      return id_;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    static const IdType id_;
};

template< typename IdType, class Tag >
const IdType IntegerId< IdType, Tag >::id_ = GetUniqueId< IdType >();



//////////////////////////////////////////////////////////////////////////////
template< typename IdType = unsigned int >
struct IntegerRttiPolicy
{
  typedef IdType id_type;

  ////////////////////////////////////////////////////////////////////////////
  template< class Base >
  class base_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      id_type dynamic_type() const
      {
        return id_;
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
      base_type( id_type id ) : id_( id ) {}

    private:
      ////////////////////////////////////////////////////////////////////////
      const id_type id_;
  };

  ////////////////////////////////////////////////////////////////////////////
  template< class MostDerived, class Base >
  class derived_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      static id_type static_type()
      {
        return IntegerId< id_type, MostDerived >::GetId();
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
      derived_type() : Base( static_type() ) {}
  };
};



#endif
