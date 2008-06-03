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

#ifndef BOOST_PTR_CONTAINER_PTR_CIRCULAR_BUFFER_HPP
#define BOOST_PTR_CONTAINER_PTR_CIRCULAR_BUFFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/circular_buffer.hpp>
#include <boost/ptr_container/ptr_sequence_adapter.hpp>

namespace boost
{

    template
    < 
        class T, 
        class CloneAllocator = heap_clone_allocator,
        class Allocator      = std::allocator<void*>
    >
    class ptr_circular_buffer : public 
        ptr_sequence_adapter< T, 
                              boost::circular_buffer<void*,Allocator>, 
                              CloneAllocator >
    {  
        typedef ptr_sequence_adapter< T, 
                                      boost::circular_buffer<void*,Allocator>, 
                                      CloneAllocator > 
            base_type;

        typedef boost::circular_buffer<void*,Allocator>         circular_buffer_type;
        typedef ptr_circular_buffer<T,CloneAllocator,Allocator> this_type;
        
    public: // typedefs
        typedef typename base_type::value_type     value_type;
        typedef value_type*                        pointer;
        typedef const value_type*                  const_pointer;
        typedef typename base_type::size_type      size_type;
        typedef typename base_type::allocator_type allocator_type;
        typedef typename base_type::iterator       iterator;
        typedef typename base_type::auto_type      auto_type;
        
        typedef std::pair<pointer*,size_type>                 array_range;
        typedef std::pair<const_pointer*,size_type>           const_array_range;
        typedef typename circular_buffer_type::capacity_type  capacity_type;
        
    public: // allocators
        allocator_type& get_allocator() 
        {
            return this->base().get_allocator();
        }

        allocator_type get_allocator() const
        {
            return this->base().get_allocator();
        }

    public: // circular buffer functions
        array_range array_one() // nothrow
        {
            typename circular_buffer_type::array_range r = this->base().array_one();
            return array_range( static_cast<pointer>(r.first,r.second) );
        }

        const_array_range array_one() const // nothrow
        {
            typename circular_buffer_type::const_array_range r = this->base().array_one();
            return array_range( static_cast<pointer>(r.first,r.second) );
        }

        array_range array_two() // nothrow
        {
            typename circular_buffer_type::const_array_range r = this->base().array_two();
            return const_array_range( static_cast<pointer>(r.first,r.second) );
        }

        const_array_range array_two() const // nothrow
        {
            typename circular_buffer_type::const_array_range r = this->base().array_two();
            return const_array_range( static_cast<pointer>(r.first,r.second) );
        }

        pointer linearise() // nothrow
        {
            return this->base().linearise();
        }

        bool full() const // nothrow
        {
            return this->base().full();
        }

        size_type reserve() const // nothrow
        {
            return this->base().reserve();
        }

        capacity_type capacity() const // nothrow
        {
            return this->base().capacity();
        }

        void set_capacity( capacity_type new_capacity ) // strong
        {
            if( this->size() > new_capacity )
            {
                this->erase( this->begin() + new_capacity, this->end() );
            }
            this->base().set_capacity( new_capacity );
        }

        void rset_capacity( capacity_type new_capacity ) // strong
        {
            if( this->size() > new_capacity )
            {
                this->erase( this->begin(), 
                             this->begin() + (this->size()-new_capacity) );
            }
            this->base().rset_capacity( new_capacity );
        }

        using base_type::assign;

        void assign( size_type n, value_type to_clone ) // strong
        {
            base_type temp;
            for( size_type i = 0u; i != n; ++i )
               temp.push_back( this->null_policy_allocate_clone( to_clone ) );
            temp->base().set_capacity( n );
            this->swap( temp ); 
        }
        
        void assign( capacity_type capacity, size_type n, 
                     value_type to_clone ) // basic
        {
            this->assign( n, to_clone );
            this->base().set_capacity( capacity );
        }

        template< class InputIterator >
        void assign( capacity_type capacity, 
                     InputIterator first, InputIterator last ) // basic
        {
            this->assign( first, last );
            this->base().set_capacity( capacity );
        }

        void push_back( value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );            
            auto_type old_ptr;
            if( full() )
                old_ptr.reset( &*this->begin() );
            this->base().push_back( ptr );            
        }

        template< class U >
        void push_back( std::auto_ptr<U> ptr ) // nothrow
        {
            push_back( ptr.release() ); 
        }

        void push_front( value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            auto_type old_ptr;
            if( full() )
                old_ptr.reset( &*(--this->end()) );
            this->base().push_back( ptr );            
        }

        template< class U >
        void push_front( std::auto_ptr<U> ptr ) // nothrow
        {
            push_front( ptr.release() ); 
        }

        iterator insert( iterator pos, value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            auto_type new_ptr( ptr );
            iterator b = this->begin();
            if( full() && pos == b )
                return b;
            
            auto_type old_ptr;
            if( full() )
                old_ptr.reset( &*this->begin() );

            new_ptr.release();
            return this->base().insert( pos.base(), ptr );
        }

        template< class U >
        iterator insert( iterator pos, std::auto_ptr<U> ptr ) // nothrow
        {
            return insert( pos, ptr.release() );
        }

        template< class InputIterator >
        void insert( iterator pos, InputIterator first, InputIterator last )
        {
            // @todo
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( iterator before, const Range& r )
        {
            insert( before, boost::begin(r), boost::end(r) );
        }

#endif
           
        iterator rinsert( iterator pos, value_type ptr ) // nothrow
        {
            BOOST_ASSERT( capacity() > 0 );
            auto_type new_ptr( ptr );
            iterator b = this->end();
            if (full() && pos == b)
                return b;
            
            auto_type old_ptr;
            if( full() )
                old_ptr.reset( &this->back() );

            new_ptr.release();
            return this->base().rinsert( pos.base(), ptr );
        }

        template< class U >
        iterator rinsert( iterator pos, std::auto_ptr<U> ptr ) // nothrow
        {
            return rinsert( pos, ptr.release() );
        }

 
        template< class InputIterator >
        void rinsert( iterator pos, InputIterator first, InputIterator last )
        {
            // @todo
        }

#if defined(BOOST_NO_SFINAE) || defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#else
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        rinsert( iterator before, const Range& r )
        {
            rinsert( before, boost::begin(r), boost::end(r) );
        }

#endif

        void rerase( iterator pos )
        {
            // @todo
        }

        void rerase( iterator first, iterator last )
        {
            // @todo
        }

     
    public: // constructors
        
        BOOST_PTR_CONTAINER_DEFINE_SEQEUENCE_MEMBERS( ptr_circular_buffer, 
                                                      base_type,
                                                      this_type );
        
        explicit ptr_circular_buffer( capacity_type n,
                                      const allocator_type& alloc = allocator_type() )
          : base_type(alloc)
        {
            this->base().set_capacity( n );
        }        
    };

    //////////////////////////////////////////////////////////////////////////////
    // clonability

    template< typename T, typename CA, typename A >
    inline ptr_circular_buffer<T,CA,A>* new_clone( const ptr_circular_buffer<T,CA,A>& r )
    {
        return r.clone().release();
    }

    /////////////////////////////////////////////////////////////////////////
    // swap

    template< typename T, typename CA, typename A >
    inline void swap( ptr_circular_buffer<T,CA,A>& l, ptr_circular_buffer<T,CA,A>& r )
    {
        l.swap(r);
    }
    
}

#endif
