#ifndef BOOST_FSM_DETAIL_COUNTED_BASE_HPP_INCLUDED
#define BOOST_FSM_DETAIL_COUNTED_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/detail/lightweight_mutex.hpp>
#include <boost/assert.hpp> // BOOST_ASSERT
#include <boost/config.hpp> // BOOST_STATIC_CONSTANT

#include <limits> // std::numeric_limits



namespace boost
{
namespace fsm
{
namespace detail
{


  
template< bool NeedsLocking >
struct locked_base
{
  typedef ::boost::detail::lightweight_mutex::scoped_lock scoped_lock;
  mutable ::boost::detail::lightweight_mutex mutex_;
};

template<>
struct locked_base< false >
{
  typedef bool scoped_lock;
  BOOST_STATIC_CONSTANT( bool, mutex_ = false );
};

//////////////////////////////////////////////////////////////////////////////
template< typename CountType, bool NeedsLocking = true >
class counted_base : private locked_base< NeedsLocking >
{
  typedef locked_base< NeedsLocking > base_type;
  public:
    //////////////////////////////////////////////////////////////////////////
    virtual ~counted_base() {}

    bool ref_counted() const
    {
      return count_ != 0;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    counted_base() : count_( 0 ) {}

    // do nothing copy implementation is intentional (the number of
    // referencing pointers of the source and the destination is not changed
    // through the copy operation)
    counted_base( const counted_base & ) : count_( 0 ) {}
    counted_base & operator=( const counted_base & ) {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void add_ref() const
    {
      typename base_type::scoped_lock lock( base_type::mutex_ );
      lock;
      BOOST_ASSERT( count_ < std::numeric_limits< CountType >::max() );
      ++count_;
    }

    void release() const
    {
      bool shouldDelete = false;

      {
        // release the mutex in the base class before the base class object
        // is destroyed
        typename base_type::scoped_lock lock( base_type::mutex_ );
        lock;
        BOOST_ASSERT( count_ > 0 );
        shouldDelete = ( --count_ == 0 );
      }

      if ( shouldDelete )
      {
        delete this;
      }
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    mutable CountType count_;
};



#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
} // namespace boost
#endif



template< typename CountType, bool NeedsLocking >
inline void intrusive_ptr_add_ref(
  const ::boost::fsm::detail::counted_base< CountType, NeedsLocking > * pBase )
{
  pBase->add_ref();
}

template< typename CountType, bool NeedsLocking >
inline void intrusive_ptr_release(
  const ::boost::fsm::detail::counted_base< CountType, NeedsLocking > * pBase )
{
  pBase->release();
}



#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
} // namespace boost
#endif



#endif
