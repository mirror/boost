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

#ifndef BOOST_PTR_CONTAINER_PTR_PREDICATE_HPP
#define BOOST_PTR_CONTAINER_PTR_PREDICATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>
#include <boost/type_traits/function_traits.hpp>
#include <boost/assert.hpp>
#include <functional>

namespace boost
{

    template< class T >
    struct ptr_equal_to : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l == *r;
        }
    };
    
    template< class T >
    struct ptr_not_equal_to : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l != *r;
        }
    };
    
    template< class T >
    struct ptr_greater : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l > *r;
        }
    };
    
    template< class T >
    struct ptr_less : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l < *r;
        }

        bool operator()( const void* l, const void* r ) const
        {
            BOOST_ASSERT( l != 0 && "null error" );
            BOOST_ASSERT( r != 0 && "null error" );
            return *reinterpret_cast<const T*>(l) < 
                   *reinterpret_cast<const T*>(r);
        }
    };
    
    template< class T >
    struct ptr_greater_equal : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l >= *r;
        }
    };

    template< class T >
    struct ptr_less_equal : public std::binary_function<T*,T*,bool>
    {
        bool operator()( const T* l, const T* r ) const
        {
            return *l <= *r;
        }
    };

    template< class Predicate >
    class indirected1
    {
        Predicate pred_;
    public:
        
        typedef BOOST_DEDUCED_TYPENAME function_traits<Predicate>::arg1_type* 
                     argument_type;
        typedef bool result_type;
        
    public:
        indirected1()
        { }
        
        indirected1( Predicate pred ) : pred_( pred )
        { }
        
        template< class T >
        bool operator()( const T* x ) const
        {
            return pred_( *x );
        }        
    };
    
    template< class BinaryPredicate >
    class indirected2
    {
        BinaryPredicate pred_;
    public:
       // typedef BOOST_DEDUCED_TYPENAME function_traits<BinaryPredicate>::arg1_type*
       //        first_argument_type;
       // typedef BOOST_DEDUCED_TYPENAME function_traits<BinaryPredicate>::arg2_type*
       //        second_argument_type;
       // typedef bool result_type;
        
    public:
        indirected2()
        { }
        
        indirected2( BinaryPredicate pred ) : pred_( pred )
        { }
        
        template< class T >
        bool operator()( const T* l, const T* r ) const
        {
            return pred_( *l, *r );
        }
    };
    
} // namespace 'boost'

#endif
