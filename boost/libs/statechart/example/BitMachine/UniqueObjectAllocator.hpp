#ifndef UNIQUE_OBJECT_ALLOCATOR_HPP_INCLUDED
#define UNIQUE_OBJECT_ALLOCATOR_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

#include <cstddef> // size_t



//////////////////////////////////////////////////////////////////////////////
template< class T >
class UniqueObjectAllocator
{
  public:
    //////////////////////////////////////////////////////////////////////////
    static void * allocate( size_t size )
    {
      size;
      BOOST_ASSERT( !constructed_ && ( size == sizeof( T ) ) );
      constructed_ = true;
      return &storage_.data[ 0 ];
    }

    static void deallocate( void * p, size_t size )
    {
      p;
      size;
      BOOST_ASSERT( constructed_ &&
        ( p == &storage_.data[ 0 ] ) && ( size == sizeof( T ) ) );
      constructed_ = false;
    }

  private:
    //////////////////////////////////////////////////////////////////////////
    union storage
    {
      char data[ sizeof( T ) ];
      typename boost::type_with_alignment<
        boost::alignment_of< T >::value >::type aligner_;
    };

    static bool constructed_;
    static storage storage_;
};

template< class T >
bool UniqueObjectAllocator< T >::constructed_ = false;
template< class T >
typename UniqueObjectAllocator< T >::storage UniqueObjectAllocator< T >::storage_;



#endif
