#ifndef BOOST_FSM_DETAIL_COUNTED_BASE_HPP_INCLUDED
#define BOOST_FSM_DETAIL_COUNTED_BASE_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// (c) Copyright Andreas Huber Doenni 2002-2004
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////



#include <boost/detail/atomic_count.hpp>
#include <boost/config.hpp> // BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP



namespace boost
{
namespace fsm
{
namespace detail
{


  
template< bool NeedsLocking >
struct count_base
{
  count_base() : count_( 0 ) {}
  mutable boost::detail::atomic_count count_;
};

template<>
struct count_base< false >
{
  count_base() : count_( 0 ) {}
  mutable long count_;
};

//////////////////////////////////////////////////////////////////////////////
template< bool NeedsLocking = true >
class counted_base : private count_base< NeedsLocking >
{
  typedef count_base< NeedsLocking > base_type;
  public:
    //////////////////////////////////////////////////////////////////////////
    bool ref_counted() const
    {
      return base_type::count_ != 0;
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    counted_base() {}
    virtual ~counted_base() {}

    // do nothing copy implementation is intentional (the number of
    // referencing pointers of the source and the destination is not changed
    // through the copy operation)
    counted_base( const counted_base & ) {}
    counted_base & operator=( const counted_base & ) {}

  public:
    //////////////////////////////////////////////////////////////////////////
    // The following declarations should be private.
    // They are only public because many compilers lack template friends.
    //////////////////////////////////////////////////////////////////////////
    void add_ref() const
    {
      ++base_type::count_;
    }

    void release() const
    {
      if ( --base_type::count_ == 0 )
      {
        delete this;
      }
    }
};



#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
#endif



template< bool NeedsLocking >
inline void intrusive_ptr_add_ref(
  const ::boost::fsm::detail::counted_base< NeedsLocking > * pBase )
{
  pBase->add_ref();
}

template< bool NeedsLocking >
inline void intrusive_ptr_release(
  const ::boost::fsm::detail::counted_base< NeedsLocking > * pBase )
{
  pBase->release();
}



#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace detail
} // namespace fsm
#endif



} // namespace boost



#endif
