//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_CLONE_INSERTER_HPP
#define BOOST_PTR_CONTAINER_CLONE_INSERTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>
#include <iterator>
#include <memory>

namespace boost
{
namespace ptr_container
{
    template< class PtrContainer >
    class clone_back_insert_iterator;

    template< class PtrContainer >
    class clone_front_insert_iterator;
    
    template< class PtrContainer >
    class clone_insert_iterator;

    template< class PtrContainer >
    clone_back_insert_iterator<PtrContainer> 
    clone_back_inserter( PtrContainer& cont );

    template< class PtrContainer >
    clone_front_insert_iterator<PtrContainer> 
    clone_front_inserter( PtrContainer& cont );

    template< class PtrContainer >
    clone_insert_iterator<PtrContainer> 
    clone_inserter( PtrContainer& cont, 
                    typename PtrContainer::iterator before );

    //////////////////////////////////////////////////////////////////////////
    // Implementation
    ////////////////////////////////////////////////////////////////////////// 


    template< class PtrContainer >
    class clone_back_insert_iterator :
        public std::iterator<std::output_iterator_tag,void,void,void,void>
    {
    public:
        typedef PtrContainer container_type;

    public:
        explicit clone_back_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        clone_back_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            container->push_back( obj );
            return *this;
        }

        template< class T >
        clone_back_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_back( r );
            return *this;
        }

        clone_back_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_back( container_type::clone_allocator_type::
                                  allocate_clone(r) );
            return *this;
        }

        clone_back_insert_iterator& operator*()
        { 
            return *this;
        }

        clone_back_insert_iterator& operator++()
        { 
            return *this;
        }

        clone_back_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class clone_front_insert_iterator :
        public std::iterator<std::output_iterator_tag,void,void,void,void>
    {
    public:
        typedef PtrContainer container_type;

    public:
        explicit clone_front_insert_iterator( PtrContainer& cont )
        : container(&cont)
        { }

        clone_front_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            container->push_front( obj );
            return *this;
        }

        template< class T >
        clone_front_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            container->push_front( r );
            return *this;
        }
        
        clone_front_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            container->push_front( container_type::clone_allocator_type::
                                   allocate_clone(r) );
            return *this;
        }

        clone_front_insert_iterator& operator*()
        { 
            return *this;
        }

        clone_front_insert_iterator& operator++()
        { 
            return *this;
        }

        clone_front_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer* container;
    };


    
    template< class PtrContainer >
    class clone_insert_iterator :
        public std::iterator<std::output_iterator_tag,void,void,void,void>
    {
    public:
        typedef PtrContainer container_type;

    public:
        clone_insert_iterator( PtrContainer& cont,
                               typename PtrContainer::iterator before )
        : container(&cont), iter(before)
        { }

        clone_insert_iterator& 
        operator=( typename PtrContainer::value_type r )
        {
            typename PtrContainer::value_type obj = 0;
            if( r != 0 )
                obj = container_type::clone_allocator_type::allocate_clone(*r);

            iter = container->insert( iter, obj );
            return *this;
        }

        template< class T >
        clone_insert_iterator& 
        operator=( std::auto_ptr<T> r )
        {
            iter = container->insert( iter, r );
            return *this;
        }
        
        clone_insert_iterator& 
        operator=( typename PtrContainer::const_reference r )
        {
            iter = container->insert( iter, container_type::clone_allocator_type::
                                            allocate_clone(r) );
            return *this;
        }

        clone_insert_iterator& operator*()
        { 
            return *this;
        }

        clone_insert_iterator& operator++()
        { 
            return *this;
        }

        clone_insert_iterator operator++(int)
        { 
            return *this;
        }
        
    protected:
        PtrContainer*                    container;
        typename PtrContainer::iterator  iter;
    };

    template< class PtrContainer >
    inline clone_back_insert_iterator<PtrContainer> 
    clone_back_inserter( PtrContainer& cont )
    {
        return clone_back_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline clone_front_insert_iterator<PtrContainer> 
    clone_front_inserter( PtrContainer& cont )
    {
        return clone_front_insert_iterator<PtrContainer>( cont );
    }

    template< class PtrContainer >
    inline clone_insert_iterator<PtrContainer> 
    clone_inserter( PtrContainer& cont, 
                    typename PtrContainer::iterator before )
    {
        return clone_insert_iterator<PtrContainer>( cont, before );
    }
    
} // namespace 'ptr_container'
} // namespace 'boost'

#endif
