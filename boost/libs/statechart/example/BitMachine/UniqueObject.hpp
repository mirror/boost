#ifndef UNIQUE_OBJECT_HPP_INCLUDED
#define UNIQUE_OBJECT_HPP_INCLUDED
//////////////////////////////////////////////////////////////////////////////
// Copyright (c) Andreas Huber Doenni 2002-2004.
// Use, modification and distribution are subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
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
