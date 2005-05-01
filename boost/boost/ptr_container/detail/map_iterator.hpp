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
#include <cassert>
#include <utility>

namespace boost
{
    //namespace ptr_container_detail
    //{
        template
        < 
            typename I, // original iterator 
            typename K, // key type
            typename V  // return value type of operator*()
        > 
        class ptr_map_iterator
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
            ptr_map_iterator()                                  {}
            ptr_map_iterator( const I& i ) : iter_( i )         {}
            
            template< class MutableIterator, class K2, class V2 >
            ptr_map_iterator( const ptr_map_iterator<MutableIterator,K2,V2>& r ) 
             : iter_(r.base())
            { }
            
            V& operator*() const
            {
                return *static_cast<V*>( iter_->second );
            }

            V* operator->() const
            {
                return static_cast<V*>( iter_->second );
            }
            
            ptr_map_iterator& operator++()
            {
                ++iter_;
                return *this;
            }

            ptr_map_iterator operator++(int)
            {
                ptr_map_iterator res = *this;
                ++iter_;
                return res;
            }

            ptr_map_iterator& operator--()
            {
                --iter_;
                return *this;
            }

            ptr_map_iterator operator--(int)
            {
                ptr_map_iterator res = *this;
                --iter_;
                return res;

            }

            I base() const
            {
                return iter_;
            }

            key_type key() const
            {
                return iter_->first;
            }

            friend inline bool operator==( ptr_map_iterator l, ptr_map_iterator r )
            {
                return l.iter_ == r.iter_;
            }

            friend inline bool operator!=( ptr_map_iterator l, ptr_map_iterator r )
            {
                return l.iter_ != r.iter_;
            }
            
       }; // class 'ptr_map_iterator'
    //} // namespace 'ptr_container_detail'
}

#endif
