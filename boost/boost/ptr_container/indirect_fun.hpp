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

#ifndef BOOST_PTR_CONTAINER_INDIRECT_FUN_HPP
#define BOOST_PTR_CONTAINER_INDIRECT_FUN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif

#include <boost/config.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/cast.hpp>
#include <boost/assert.hpp>
#include <boost/pointee.hpp>

namespace boost
{


    template< class Fun >
    class indirect_fun
    {
        Fun fun;
    public:
        indirect_fun() : fun(Fun())
        { }
        
        indirect_fun( Fun f ) : fun(f)
        { }
    
        template< class T >
        BOOST_DEDUCED_TYPENAME result_of< Fun( BOOST_DEDUCED_TYPENAME pointee<T>::type ) >::type 
        operator()( const T& r ) const
        { 
            return fun( *r );
        }
    
        template< class T, class U >
        BOOST_DEDUCED_TYPENAME result_of< Fun( BOOST_DEDUCED_TYPENAME pointee<T>::type, 
                                               BOOST_DEDUCED_TYPENAME pointee<U>::type ) >::type
        operator()( const T& r, const U& r2 ) const
        { 
            return fun( *r, *r2 ); 
        }
    };

    template< class Fun >
    inline indirect_fun<Fun> make_indirect_fun( Fun f )
    {
        return indirect_fun<Fun>( f );
    }


    template< class Fun, class Arg1, class Arg2 = Arg1 >
    class void_ptr_indirect_fun
    {
        Fun fun;
    public:
        
        void_ptr_indirect_fun() : fun(Fun())
        { }

        void_ptr_indirect_fun( Fun f ) : fun(f)
        { }

        BOOST_DEDUCED_TYPENAME result_of< Fun( Arg1 ) >::type 
        operator()( const void* r ) const
        { 
            return fun( * static_cast<const Arg1*>( r ) );
        }

        BOOST_DEDUCED_TYPENAME result_of< Fun( Arg1, Arg2 ) >::type 
        operator()( const void* l, const void* r ) const
        { 
            return fun( * static_cast<const Arg1*>( l ), * static_cast<const Arg2*>( r ) );
        }
    };

    template< class Fun, class Arg >
    inline void_ptr_indirect_fun<Fun,Arg> make_void_ptr_indirect_fun( Fun f )
    {
        return void_ptr_indirect_fun<Fun,Arg>( f );
    }
     
} // namespace 'boost'

#endif
