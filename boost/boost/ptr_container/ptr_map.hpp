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

#ifndef BOOST_PTR_CONTAINER_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_PTR_MAP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <map>
#include <boost/ptr_container/ptr_map_adapter.hpp>

namespace boost
{
    
    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>,
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,void*> >
    >
    class ptr_map : 
        public ptr_map_adapter<T,std::map<Key,void*,Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_map_adapter<T,std::map<Key,void*,Compare,Allocator>,CloneAllocator>
            base_type;
    
    public:
        explicit ptr_map( const Compare& comp = Compare(),
                          const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }

        template< class InputIterator >
        ptr_map( InputIterator first, InputIterator last, 
                 const Compare& comp = Compare(),
                 const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }
        
        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_map, base_type );
        
    };
    


    template
    < 
        class Key, 
        class T, 
        class Compare        = std::less<Key>, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator< std::pair<const Key,void*> >
    >
    class ptr_multimap : 
        public ptr_multimap_adapter<T,std::multimap<Key,void*,Compare,Allocator>,CloneAllocator>
    {
        typedef ptr_multimap_adapter<T,std::multimap<Key,void*,Compare,Allocator>,CloneAllocator>
             base_type;
    
    public:
        explicit ptr_multimap( const Compare& comp = Compare(),
                               const Allocator& a  = Allocator() ) 
          : base_type( comp, a ) { }
        
        template< class InputIterator >
        ptr_multimap( InputIterator first, InputIterator last,
                      const Compare& comp = Compare(),
                      const Allocator& a  = Allocator() )
          : base_type( first, last, comp, a ) 
        { }
        
        BOOST_PTR_CONTAINER_DEFINE_RELEASE_AND_CLONE( ptr_multimap, 
                                                        base_type );

    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< class K, class T, class C, class CA, class A >
    inline ptr_map<K,T,C,CA,A>* new_clone( const ptr_map<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    template< class K, class T, class C, class CA, class A >
    inline ptr_multimap<K,T,C,CA,A>* new_clone( const ptr_multimap<K,T,C,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_map<K,T,C,CA,A>& l, ptr_map<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }

    template< typename K, typename T, typename C, typename CA, typename A >
    inline void swap( ptr_multimap<K,T,C,CA,A>& l, ptr_multimap<K,T,C,CA,A>& r )
    {
        l.swap(r);
    }


}

#endif
