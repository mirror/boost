// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_LIST_OF_HPP
#define BOOST_ASSIGN_LIST_OF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/assign/assignment_exception.hpp>
#include <boost/config.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/mpl/if.hpp>
#include <deque>
#include <cstddef>
#include <utility>

//###
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// BCB requires full type definition for is_array<> to work correctly.
#include <boost/array.hpp>
#endif

namespace boost
{

// this here is necessary to avoid compiler error in <boost/array.hpp>
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    template< class T, std::size_t sz >
    class array;
#endif    
    
namespace assign_detail
{
    template< class T, std::size_t sz >
    type_traits::yes_type is_array( const array<T,sz>* );
    type_traits::no_type is_array( ... );
    template< class T, class U >
    type_traits::yes_type is_pair( const std::pair<T,U>* );
    type_traits::no_type is_pair( ... ); 
 
    
    struct array_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct adapter_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct pair_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    struct default_type_tag
    {
    #if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    private:
      char dummy_;  // BCB would by default use 8 bytes
    #endif
    };
    


    template< class T > 
    class generic_list : public std::deque<T> 
    {
        typedef std::deque<T> base;
    public:
        using base::iterator;
        using base::value_type;
        using base::const_iterator;

    public:
        generic_list& operator()()
        {
            this->push_back( T() );
            return *this;
        }
        
        template< class U >
        generic_list& operator()( const U u )
        {
            this->push_back( u );
            return *this;
        }
        

//###        
#ifndef BOOST_ASSIGNMENT_MAX_PARAMS // use user's value
#define BOOST_ASSIGNMENT_MAX_PARAMS 4
#endif        
#define BOOST_ASSIGNMENT_PARAMS1(n) BOOST_PP_ENUM_PARAMS(n, class U)
#define BOOST_ASSIGNMENT_PARAMS2(n) BOOST_PP_ENUM_BINARY_PARAMS(n, U, u)
#define BOOST_ASSIGNMENT_PARAMS3(n) BOOST_PP_ENUM_PARAMS(n, u)

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGNMENT_MAX_PARAMS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class U, BOOST_ASSIGNMENT_PARAMS1(n) > \
    generic_list& operator()(U u, BOOST_ASSIGNMENT_PARAMS2(n) ) \
    { \
        this->push_back(T(u, BOOST_ASSIGNMENT_PARAMS3(n))); \
        return *this; \
    } \
    /**/
        
#include BOOST_PP_LOCAL_ITERATE()

        
        template< class U >
        generic_list& operator,( U u )
        {
            this->push_back( u );
            return *this;
        }
        
        template< class U >
        generic_list& repeat( std::size_t sz, U u )
        {
            std::size_t i = 0;
            while( i++ != sz )
                this->push_back( u );
            return *this;
        }
        
        template< class Nullary_function >
        generic_list& repeat_fun( std::size_t sz, Nullary_function fun )
        {
            std::size_t i = 0;
            while( i++ != sz )
                this->push_back( fun() );
            return *this;
        }
        
        template< class Container >
        operator Container() const
        {
            static Container* c = 0;
            BOOST_STATIC_CONSTANT( bool, is_array_flag = sizeof( is_array( c ) ) 
                                   == sizeof( type_traits::yes_type ) );
            
//            BOOST_DEDUCED_TYPENAME Container::value_type* v = 0;
//            BOOST_STATIC_CONSTANT( bool, is_pair_flag = sizeof( is_pair( v ) )
//                                   == sizeof( type_traits::yes_type ) );
                
            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< is_array_flag,
                                                      array_type_tag,
                                             default_type_tag >::type tag_type;
//            typedef BOOST_DEDUCED_TYPENAME mpl::if_c< is_pair_flag,
//                                                      pair_type_tag,
//                                          default_type_tag >::type pair_tag_type;
            
            return convert( c, tag_type() );
        }
        
        template< class Container >
        Container convert( const Container*, default_type_tag ) const
        {

#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
// old Dinkumware doesn't support iterator type as template
            Container result;
            BOOST_DEDUCED_TYPENAME std::deque<T>::const_iterator 
                it = this->begin(), end = this->end();
            while( it != end )
            {
                result.insert( result.end(), *it );
                ++it;
            }
            return result;
#else
            return Container( this->begin(), this->end() );
#endif
        }
        
        /*
        template< class Container >
        Container convert( Container*, default_type_tag, pair_type_tag ) const
        {
        
            Container result;
            BOOST_DEDUCED_TYPENAME std::deque<T>::const_iterator
                 it = this->begin(), end = this->end();
            while( it != end )
            {
                BOOST_DEDUCED_TYPENAME Container::key_type   
                    key;
                key   = it->first; 
                BOOST_DEDUCED_TYPENAME Container::mapped_type 
                    value;
                value = it->second;
                result.insert( result.end(), std::make_pair( key, value ) );
            }
        
            return result;
        }
        */
        
        template< class Array >
        Array convert( const Array*, array_type_tag ) const
        {
            Array array;
            if( array.size() < this->size() )
                throw assign::assignment_exception( "array initialized with too many elements" );
            std::size_t n = 0; 
            BOOST_DEDUCED_TYPENAME std::deque<T>::const_iterator 
                i = this->begin(), end = this->end();
            for( ; i != end; ++i, ++n )
                array[n] = *i;
            for( ; n < array.size(); ++n )
                array[n] = BOOST_DEDUCED_TYPENAME Array::value_type();
            return array; 
        }
        
        template< class Adapter >
        Adapter convert_to_adapter() const
        {
            Adapter a;
            BOOST_DEDUCED_TYPENAME std::deque<T>::const_iterator 
                i = this->begin(), end = this->end();
            for( ; i != end; ++i )
                a.push( *i );
            return a;
        }
        
    private:
        struct adapter_converter;
        friend struct adapter_converter;
        
        struct adapter_converter
        {
            const generic_list& gl;
            adapter_converter( const generic_list& this_ ) : gl( this_ )
            {}
            
            adapter_converter( const adapter_converter& r ) 
            : gl( r.gl )
            { }
            
            template< class Adapter >
            operator Adapter() const
            {
                return gl.convert_to_adapter<Adapter>();
            }
        };
        
    public: 
        template< class Container >
        Container to_container( Container& c ) const
        {
            return convert( &c, default_type_tag() ); 
        }
        
        adapter_converter to_adapter() const
        {
            return adapter_converter( *this );
        }
        
        template< class Adapter >
        Adapter to_adapter( Adapter& ) const
        {
            return convert_to_adapter<Adapter>(); 
        }

        template< class Array >
        Array to_array( Array& a ) const
        {
            return convert( &a, array_type_tag() );
        }
    };
    
    /*
    template< class T, class U >
    inline generic_list<T> operator+( const generic_list<T>& l, const generic_list<U>& r )
    {
        generic_list<T> res( l );
        res += r;
        return res;
    }
    */
    
} // namespace 'assign_detail'

namespace assign
{
    template< class T >
    inline assign_detail::generic_list<T>
    list_of()
    {
        return assign_detail::generic_list<T>();
    }
    
    template< class T >
    inline assign_detail::generic_list<T> 
    list_of( T t )
    {
        return assign_detail::generic_list<T>()( t );
    }
    
    
#define BOOST_PP_LOCAL_LIMITS (1, BOOST_ASSIGNMENT_MAX_PARAMS)
#define BOOST_PP_LOCAL_MACRO(n) \
    template< class T, class U, BOOST_ASSIGNMENT_PARAMS1(n) > \
    inline assign_detail::generic_list<T> \
    list_of(U u, BOOST_ASSIGNMENT_PARAMS2(n) ) \
    { \
        return assign_detail::generic_list<T>()(u, BOOST_ASSIGNMENT_PARAMS3(n)); \
    } \
    /**/
    
#include BOOST_PP_LOCAL_ITERATE()


    template< class Key, class T >
    inline assign_detail::generic_list< std::pair<Key,T> >
    map_list_of( Key k, T t )
    {
        return assign_detail::generic_list< std::pair<Key,T> >()( k, t );
    }


} // namespace 'assign'
} // namespace 'boost'


//###
#undef BOOST_ASSIGNMENT_MAX_PARAMS         
#undef BOOST_ASSIGNMENT_PARAMS1
#undef BOOST_ASSIGNMENT_PARAMS2
#undef BOOST_ASSIGNMENT_PARAMS3


#endif
