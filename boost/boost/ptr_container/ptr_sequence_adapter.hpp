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

#ifndef BOOST_ptr_container_PTR_SEQUENCE_ADAPTER_HPP
#define BOOST_ptr_container_PTR_SEQUENCE_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif


#include <boost/ptr_container/detail/reversible_ptr_container.hpp>
#include <boost/ptr_container/ptr_predicate.hpp>
#include <boost/ptr_container/detail/void_ptr_iterator.hpp>
#include <boost/range/reverse_iterator.hpp>
#include <boost/range/const_reverse_iterator.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost
{   
    template
    < 
        class T, 
        class VoidPtrSeq
    >
    struct sequence_config
    {
        typedef BOOST_DEDUCED_TYPENAME remove_nullable<T>::type
                    U;
        typedef VoidPtrSeq
                    void_container_type;

        typedef BOOST_DEDUCED_TYPENAME VoidPtrSeq::allocator_type
                    allocator_type;
        
        typedef U   value_type;

        typedef ptr_container_detail::void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSeq::iterator, U > 
                    ptr_iterator;
       
        typedef boost::indirect_iterator<ptr_iterator> 
                    iterator;
        
        typedef ptr_container_detail::void_ptr_iterator<
                        BOOST_DEDUCED_TYPENAME VoidPtrSeq::const_iterator, const U >
                    ptr_const_iterator;
        
        typedef boost::indirect_iterator<ptr_const_iterator>
                    const_iterator;
        
        typedef ptr_container_detail::void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSeq::reverse_iterator, U >
                   ptr_reverse_iterator;
        
        typedef boost::indirect_iterator<ptr_reverse_iterator>
                   reverse_iterator;
        
        typedef ptr_container_detail::void_ptr_iterator<
                       BOOST_DEDUCED_TYPENAME VoidPtrSeq::const_reverse_iterator, const U >
                   ptr_const_reverse_iterator;
        
        typedef boost::indirect_iterator<ptr_const_reverse_iterator>
                   const_reverse_iterator;

        typedef value_type 
                    object_type;

        template< class Iter >
        static BOOST_DEDUCED_TYPENAME Iter::wrapped_type get_base( Iter i )
        {
            return i.base();
        }

        template< class Iter >
        static U* get_pointer( boost::indirect_iterator<Iter> i )
        {
            return static_cast<U*>( *i.base() );
        }
        
        template< class Iter >
        static U* get_pointer( Iter i )
        {
            return &*i;
        }

        template< class Iter >
        static const U* get_const_pointer( boost::indirect_iterator<Iter> i )
        {
            return static_cast<const U*>( *i.base() );
        }

        template< class Iter >
        static const U* get_const_pointer( Iter i )
        {
            return &*i;
        }

        BOOST_STATIC_CONSTANT(bool, allow_null = is_nullable<T>::value );
    };


    
    template
    < 
        class T,
        class VoidPtrSeq, 
        class CloneAllocator = heap_clone_allocator
    >
    class ptr_sequence_adapter : public 
        ptr_container_detail::reversible_ptr_container< sequence_config<T,VoidPtrSeq>, 
                                            CloneAllocator >
    {
        typedef ptr_container_detail::reversible_ptr_container< sequence_config<T,VoidPtrSeq>,
                                                    CloneAllocator >
             base_type;
        
        typedef BOOST_DEDUCED_TYPENAME base_type::scoped_deleter scoped_deleter;
        
    public:
        typedef BOOST_DEDUCED_TYPENAME base_type::value_type  value_type; 
        typedef BOOST_DEDUCED_TYPENAME base_type::reference   reference; 
        typedef BOOST_DEDUCED_TYPENAME base_type::auto_type   auto_type; 
            
        BOOST_PTR_CONTAINER_DEFINE_CONSTRUCTORS( ptr_sequence_adapter, 
                                                   base_type );
    
        template< class PtrContainer >
        ptr_sequence_adapter( std::auto_ptr<PtrContainer> clone )
          : base_type( clone )
        { }

        template< class PtrContainer >
        void operator=( std::auto_ptr<PtrContainer> clone )    
        {
            base_type::operator=( clone );
        }

        /////////////////////////////////////////////////////////////
        // modifiers
        /////////////////////////////////////////////////////////////

        void push_back( value_type x )  // strong               
        {
            this->enforce_null_policy( x, "Null pointer in 'push_back()'" );

            auto_type ptr( x );                // notrow
            this->c_private().push_back( x );  // strong, commit
            ptr.release();                     // nothrow
        }

        void push_front( value_type x )                
        {
            this->enforce_null_policy( x, "Null pointer in 'push_front()'" );

            auto_type ptr( x );                // nothrow
            this->c_private().push_front( x ); // strong, commit
            ptr.release();                     // nothrow
        } 

        auto_type pop_back()
        {
            if( this->empty() ) 
                throw bad_ptr_container_operation( "'pop_back()' "
                                                     " on empty container" );
            auto_type ptr( static_cast<value_type>( 
                         this->c_private().back() ) ); // nothrow
            this->c_private().pop_back();              // nothrow
            return ptr_container_detail::move( ptr );                        // nothrow
        }

        auto_type pop_front()
        {
            if( this->empty() ) 
                throw bad_ptr_container_operation( "'pop_front()' on" 
                                                     " empty container" ); 
            auto_type ptr( this->c_private().front() ); // nothrow 
            this->c_private().pop_front();              // nothrow
            return ptr_container_detail::move( ptr ); 
        }
        
        reference front()        
        { 
            BOOST_ASSERT( !::boost::is_null( this->begin() ) );
            if( this->empty() )
                throw bad_ptr_container_operation( "accessing 'front()' on empty container" );
            return *this->begin(); 
        }

        const_reference front() const  
        {
            BOOST_ASSERT( !::boost::is_null( this->begin() ) );
            if( this->empty() )
                throw bad_ptr_container_operation( "accessing 'front()' on empty container" );
            return *this->begin(); 
        }

        reference back()
        {
            BOOST_ASSERT( !::boost::is_null( --this->end() ) );
            if( this->empty() )
                throw bad_ptr_container_operation( "accessing 'back()' on empty container" );
            return *--this->end(); 
        }

        const_reference back() const
        {
            BOOST_ASSERT( !::boost::is_null( --this->end() ) );
            if( this->empty() )
                throw bad_ptr_container_operation( "accessing 'back()' on empty container" );
            return *--this->end(); 
        }

    public: // deque/vector inerface
        
        reference operator[]( size_type n ) // nothrow 
        {
            BOOST_ASSERT( n < this->size() );
            BOOST_ASSERT( !this->is_null( n ) );
            return *static_cast<value_type>( this->c_private()[n] ); 
        }
        
        const_reference operator[]( size_type n ) const // nothrow  
        { 
            BOOST_ASSERT( n < this->size() ); 
            BOOST_ASSERT( !this->is_null( n ) );
            return *static_cast<value_type>( this->c_private()[n] );
        }
        
        reference at( size_type n )
        {
            if( n >= this->size() )
                throw bad_index( "'at()' out of bounds" );
            BOOST_ASSERT( !this->is_null( n ) );
            return (*this)[n];
        }
        
        const_reference at( size_type n ) const
        {
            if( n >= this->size() )
                throw bad_index( "'at()' out of bounds" );
            BOOST_ASSERT( !this->is_null( n ) );
            return (*this)[n]; 
        }
        
    public: // vector interface
        
        size_type capacity() const
        {
            return this->c_private().capacity();
        }
        
        void reserve( size_type n )
        {
            this->c_private().reserve( n ); 
        }
          
    public: // list interface
        
        void splice( iterator before, ptr_sequence_adapter& x )                    
        {
            BOOST_ASSERT( &x != this );
            this->c_private().splice( before.base(), x.c_private() );
        }

        void splice( iterator before, ptr_sequence_adapter& x, iterator i ) 
        {
            BOOST_ASSERT( &x != this );
            this->c_private().splice( before.base(), x.c_private(), 
                                      i.base() );
        }

        void splice( iterator before, ptr_sequence_adapter& x, 
                     iterator first, iterator last )
        {
            BOOST_ASSERT( &x != this );
            this->c_private().splice( before.base(), x.c_private(), 
                                      first.base(), last.base() );
        }

        template< class Range >
        void splice( iterator before, ptr_sequence_adapter& x,
                     const Range& r )
        {
            splice( before, x, begin(r), end(r) );
        }

        void merge( ptr_sequence_adapter& x )                                 
        {
            merge( x, indirected2< std::less<value_type> >() );
        }

        template< typename Compare > 
        void merge( ptr_sequence_adapter& x, Compare comp )                   
        {
            this->c_private().merge( x.c_private(), comp );
        }

        void sort()                                                    
        { 
            sort( std::less<value_type>() ); 
        };

        template< typename Compare > 
        void sort( Compare comp )                             
        {
            this->c_private().sort( indirected2<Compare>( comp ) );
        }

        void reverse()
        {
            this->c_private().reverse(); 
        }

    public: // assign, insert, transfer

        // overhead: 1 heap allocation (very cheap compared to cloning)
        template< class InputIterator >
        void assign( InputIterator first, InputIterator last ) // strong
        { 
            base_type temp( first, last );
            this->swap( temp );
        }

        template< class Range >
        void assign( const Range& r )
        {
            assign( this->adl_begin(r), this->adl_end(r ) );
        }

    private:
        template< class I >
        void insert_impl( iterator before, I first, I last, std::input_iterator_tag ) // strong
        {
            ptr_sequence_adapter temp(first,last);  // strong
            transfer( before, temp );               // strong, commit
        }

        template< class I >
        void insert_impl( iterator before, I first, I last, std::forward_iterator_tag ) // strong
        {
            if( first == last ) 
                return;
            scoped_deleter sd( first, last );                // strong
            this->insert_clones_and_release( sd, before );   // strong, commit 
        }

    public:

        using base_type::insert;
        
        template< class InputIterator >
        void insert( iterator before, InputIterator first, InputIterator last ) // strong
        {
            insert_impl( before, first, last, BOOST_DEDUCED_TYPENAME
                         iterator_category<InputIterator>::type() );
        } 

#if BOOST_NO_SFINAE
#else
        template< class Range >
        BOOST_DEDUCED_TYPENAME
        boost::disable_if< ptr_container_detail::is_pointer_or_integral<Range> >::type
        insert( iterator before, const Range& r )// ptr_container_detail::is_range_tag )
        {
            insert( before, this->adl_begin(r), this->adl_end(r) );
        }

#endif

        /*
        auto_type release( size_type at )
        {
            if( at < size() )
                throw bad_ptr_container_operation( "'release()' out of bounds" ); 

            auto_type ptr( this->c_private()[at] );
            this->c_private().erase( .... )
        }*/

        void transfer( iterator before, 
                       iterator first, 
                       iterator last, 
                       ptr_sequence_adapter& from ) // strong
        {
            BOOST_ASSERT( &from != this );
            if( from.empty() )
                return;
            this->c_private().
                insert( before.base().base(), 
                        first.base().base(), last.base().base() ); // strong
            from.c_private().erase( first.base().base(),
                                    last.base().base() ); // nothrow
        }

        void transfer( iterator before, 
                       iterator object, 
                       ptr_sequence_adapter& from ) // strong
        {
            BOOST_ASSERT( &from != this );
            if( from.empty() )
                return;
            this->c_private().
                insert( before.base().base(),
                        *object.base().base() );                 // strong
            from.c_private().erase( object.base().base() );      // nothrow
        }

#if BOOST_NO_SFINAE
#else
        
        template< class Range >
        BOOST_DEDUCED_TYPENAME boost::disable_if< boost::is_same< Range,
                                                                  iterator > >::type
        transfer( iterator before, const Range& r, ptr_sequence_adapter& from ) // strong
        {
            transfer( before, this->adl_begin(r), this->adl_end(r), from );
        }

#endif
        
        void transfer( iterator before, ptr_sequence_adapter& from ) // strong
        {
            BOOST_ASSERT( &from != this );
            if( from.empty() )
                return;
            this->c_private().
                insert( before.base().base(),
                        from.ptr_begin(), from.ptr_end() ); // strong
            from.c_private().clear();                       // nothrow
        }

    public: // null functions
         
        bool is_null( size_type idx ) const
        {
            BOOST_ASSERT( idx < this->size() );
            return this->c_private()[idx] == 0;
        }
    };

} // namespace 'boost'  

#endif
