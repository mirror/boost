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
#include <boost/assert.hpp>

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



//////////////////////////////////////////////////////////////////////////////
struct id_provider
{
  const void * pCustomId_;
  #if defined( BOOST_ENABLE_ASSERT_HANDLER ) || defined( _DEBUG )
  const std::type_info * pCustomIdType_;
  #endif
};

template< class MostDerived >
struct id_holder
{
  static id_provider idProvider_;
};

template< class MostDerived >
id_provider id_holder< MostDerived >::idProvider_;



//////////////////////////////////////////////////////////////////////////////
struct rtti_policy
{
  #ifdef BOOST_FSM_USE_NATIVE_RTTI
  class id_type
  {
    public:
      ////////////////////////////////////////////////////////////////////////
      explicit id_type( const std::type_info & id ) : id_( id ) {}

      bool operator==( id_type right ) const
      {
        return id_ == right.id_ != 0;
      }
      bool operator!=( id_type right ) const { return !( *this == right ); }

      bool operator<( id_type right ) const
      {
        return id_.before( right.id_ ) != 0;
      }
      bool operator>( id_type right ) const { return right < *this; }
      bool operator>=( id_type right ) const { return !( *this < right ); }
      bool operator<=( id_type right ) const { return !( right < *this ); }

    private:
      ////////////////////////////////////////////////////////////////////////
      const std::type_info & id_;
  };

  typedef bool id_provider_type; // dummy
  #else
  typedef const void * id_type;
  typedef const id_provider & id_provider_type;
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
        return id_type( typeid( *this ) );
        #else
        return &idProvider_;
        #endif
      }

      #ifndef BOOST_FSM_USE_NATIVE_RTTI
      template< typename CustomId >
      const CustomId * custom_dynamic_type_ptr() const
      {
        BOOST_ASSERT(
          ( idProvider_.pCustomIdType_ == 0 ) ||
          ( *idProvider_.pCustomIdType_ == typeid( CustomId ) ) );
        return static_cast< const CustomId * >( idProvider_.pCustomId_ );
      }
      #endif

    protected:
      ////////////////////////////////////////////////////////////////////////
      virtual ~base_type() {}

    #ifdef BOOST_FSM_USE_NATIVE_RTTI
      base_type( id_provider_type ) {}
    #else
      base_type(
        id_provider_type idProvider
      ) :
        idProvider_( idProvider )
      {
      }

    private:
      ////////////////////////////////////////////////////////////////////////
      id_provider_type idProvider_;
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
        return id_type( typeid( const MostDerived ) );
        #else
        return &id_holder< MostDerived >::idProvider_;
        #endif
      }

      #ifndef BOOST_FSM_USE_NATIVE_RTTI
      template< class CustomId >
      static const CustomId * custom_static_type_ptr()
      {
        BOOST_ASSERT(
          ( id_holder< MostDerived >::idProvider_.pCustomIdType_ == 0 ) ||
          ( *id_holder< MostDerived >::idProvider_.pCustomIdType_ ==
            typeid( CustomId ) ) );
        return static_cast< const CustomId * >(
          id_holder< MostDerived >::idProvider_.pCustomId_ );
      }

      template< class CustomId >
      static void custom_static_type_ptr( const CustomId * pCustomId )
      {
        #if defined( BOOST_ENABLE_ASSERT_HANDLER ) || defined( _DEBUG )
        id_holder< MostDerived >::idProvider_.pCustomIdType_ =
          &typeid( CustomId );
        #endif
        id_holder< MostDerived >::idProvider_.pCustomId_ = pCustomId;
      }
      #endif

    protected:
      ////////////////////////////////////////////////////////////////////////
      virtual ~derived_type() {}

      #ifdef BOOST_FSM_USE_NATIVE_RTTI
      derived_type() : Base( false ) {}
      #else
      derived_type() : Base( id_holder< MostDerived >::idProvider_ ) {}
      #endif
  };
};



} // namespace detail
} // namespace fsm
} // namespace boost



#endif
