#ifndef BOOST_FSM_DETAIL_RTTI_POLICY_HPP_INCLUDED
#define BOOST_FSM_DETAIL_RTTI_POLICY_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/config.hpp>

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
namespace detail
{



// #define BOOST_FSM_USE_NATIVE_RTTI

#ifndef BOOST_FSM_USE_NATIVE_RTTI
//////////////////////////////////////////////////////////////////////////////
template< class MostDerived >
struct id_provider
{
  static bool dummy_;
};

template< class MostDerived >
bool id_provider< MostDerived >::dummy_;

template< class MostDerived >
struct id_holder
{
  static void * pId_;
};

template< class MostDerived >
void * id_holder< MostDerived >::pId_ = &id_provider< MostDerived >::dummy_;
#endif


//////////////////////////////////////////////////////////////////////////////
struct rtti_policy
{
  #ifdef BOOST_FSM_USE_NATIVE_RTTI
  class id_type
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      id_type( const std::type_info & id ) : id_( id ) {}

      friend bool operator==( id_type left, id_type right )
      {
        return left.id_ == right.id_ != 0;
      }
      friend bool operator!=( id_type left, id_type right )
      {
        return !( left == right );
      }

      friend bool operator<( id_type left, id_type right )
      {
        return left.id_.before( right.id_ ) != 0;
      }
      friend bool operator>( id_type left, id_type right )
      {
        return right < left;
      }
      friend bool operator>=( id_type left, id_type right )
      {
        return !( left < right );
      }
      friend bool operator<=( id_type left, id_type right )
      {
        return !( right < left );
      }

    private:
      ////////////////////////////////////////////////////////////////////////
      const std::type_info & id_;
  };
  #else
  typedef void * id_type;
  #endif

  ////////////////////////////////////////////////////////////////////////////
  template< class Base >
  class base_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      id_type dynamic_type() const
      {
        #ifdef BOOST_FSM_USE_NATIVE_RTTI
        return typeid( *this );
        #else
        return id_;
        #endif
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
    #ifdef BOOST_FSM_USE_NATIVE_RTTI
      base_type( id_type ) {}
    #else
      base_type( id_type id ) : id_( id ) {}

    private:
      ////////////////////////////////////////////////////////////////////////
      const id_type id_;
    #endif
  };

  ////////////////////////////////////////////////////////////////////////////
  template< class MostDerived, class Base >
  class derived_type : public Base
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      static id_type static_type()
      {
        #ifdef BOOST_FSM_USE_NATIVE_RTTI
        return typeid( const MostDerived );
        #else
        return id_holder< MostDerived >::pId_;
        #endif
      }

    protected:
      ////////////////////////////////////////////////////////////////////////
      derived_type() : Base( static_type() ) {}
  };
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
