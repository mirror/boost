#ifndef UNIQUE_OBJECT_HPP_INCLUDED
#define UNIQUE_OBJECT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2002-2003 Andreas Huber Doenni, Switzerland
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//////////////////////////////////////////////////////////////////////////////



#include "UniqueObjectAllocator.hpp"



//////////////////////////////////////////////////////////////////////////////
template< class Derived >
class UniqueObject
{
  public:
    //////////////////////////////////////////////////////////////////////////
    static void * operator new( size_t size )
    {
      return UniqueObjectAllocator< Derived >::allocate( size );
    }

    static void operator delete( void * p, size_t size )
    {
      UniqueObjectAllocator< Derived >::deallocate( p, size );
    }

  protected:
    //////////////////////////////////////////////////////////////////////////
    UniqueObject() {}
    ~UniqueObject() {}
};



#endif
