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

#ifndef BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/operators.hpp>
#include <cassert>
#include <utility>

namespace boost
{
    namespace ptr_container
    {
        namespace ptr_container_detail
        {
            template
            < 
                typename I, // original iterator 
                typename K, // key type
                typename V  // return value type of operator*()
            > 
            class map_iterator : 
                bidirectional_iterator_helper< map_iterator<I,K,V>, 
                                               std::pair<K,V*>,  
                                               std::ptrdiff_t, 
                                               std::pair<K,V*>*,  
                                               V& >     
            {
                I iter_;
                typedef K              key_type;
                
            public:
                typedef std::ptrdiff_t difference_type;
                typedef V              value_type;
                typedef V*             pointer;
                typedef V&             reference;
                typedef                std::bidirectional_iterator_tag  iterator_category;        
                
            public:
                map_iterator()                                           {}
                explicit map_iterator( const I& i ) : iter_( i )         {}
                
                map_iterator( const map_iterator& r ) : iter_( r.iter_ ) {}
                
                map_iterator& operator=( const map_iterator& r ) 
                {
                    iter_ = r.iter_;
                    return *this;
                }
                
                V& operator*() const
                {
                    return *static_cast<V*>( iter_->second );
                }

                V* operator->() const
                {
                    return static_cast<V*>( iter_->second );
                }
                
                map_iterator& operator++()
                {
                    ++iter_;
                    return *this;
                }
                
                map_iterator& operator--()
                {
                    --iter_;
                    return *this;
                }

                bool operator==( const map_iterator& r ) const
                {
                    return iter_ == r.iter_;
                }
                
                I base() const
                {
                    return iter_;
                }
                
                key_type key() const
                {
                    return iter_->first;
                }
                
            }; // class 'map_iterator'
        } // namespace 'ptr_container_detail'
    } // namespace 'ptr_container'
    
}

#endif
