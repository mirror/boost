/**
 * Pointer Container Library
 * (C) Thorsten Ottosen 2003-2005
 * 
 * Permission to copy, use, modify,
 * sell and distribute this software is granted provided this
 * copyright notice appears in all copies. This software is provided
 * "as is" without express or implied warranty, and with no claim as
 * to its suitability for any purpose.
 *
 * See http://www.boost.org/libs/ptr_container for documentation.
 *
 */

#ifndef BOOST_PTR_CONTAINER_PTR_DEQUE_HPP
#define BOOST_PTR_CONTAINER_PTR_DEQUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <deque>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>

namespace boost
{
    
    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_deque : public 
        ptr_sequence_adapter< T,
                              std::deque<void*,Allocator>,     
                              CloneAllocator >
    {
         typedef   ptr_sequence_adapter< T,
                                         std::deque<void*,Allocator>,     
                                         CloneAllocator >
          base_class;

    public:
      BOOST_PTR_CONTAINER_DEFINE_NON_INHERITED_MEMBERS( ptr_deque, 
                                                          base_class );

    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability
    
    template< typename T, typename CA, typename A >
    inline ptr_deque<T,CA,A>* new_clone( const ptr_deque<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_deque<T,CA,A>& l, ptr_deque<T,CA,A>& r )
    {
        l.swap(r);
    }
}

//#undef BOOST_FORWARD_TYPEDEF
//#undef BOOST_PTR_CONTAINER_RELEASE_AND_CLONE

#endif
