//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

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
        template
        < 
            class I,    // original iterator 
            class K,    // key type
            class V,    // mapped type
            class B = I // base-type 
        > 
        class ptr_map_iterator
        {
            I iter_;
            typedef K              key_type;

            struct pair_ref
            {
                const key_type&  first;
                V* const         second;

                pair_ref( const key_type& k, V* v )
                : first(k), second(v)
                { }
                
                pair_ref( const pair_ref& p )
                : first(p.first), second(p.second)
                { }

                //
                // Allow pointer p = &*iter;
                //
                pair_ref( const pair_ref* p )
                : first(p->first), second(p->second)
                { }

                //
                // Trick ptr_map_iterator::operator->()
                // into accepting this class as return value.
                //
                const pair_ref* operator->() const
                {
                    return this;
                }
            };
            
        public:
            typedef std::ptrdiff_t difference_type;
            typedef pair_ref       value_type;
            typedef pair_ref       pointer;
            typedef pair_ref       reference;
            typedef                std::bidirectional_iterator_tag  iterator_category;        

        public:
            ptr_map_iterator()                                  {}
            ptr_map_iterator( const I& i ) : iter_( i )         {}
            
            template< class MutableIterator, class K2, class V2, class B2 >
            ptr_map_iterator( const ptr_map_iterator<MutableIterator,K2,V2,B2>& r ) 
             : iter_(r.base())
            { }

            //
            // This one is needed when constructing an iterator
            // from a reverse_iterator in base().
            //
            template< class ReverseIter >
            ptr_map_iterator( const ReverseIter& r )
             : iter_(r.base())
            { }
            
            reference operator*() const
            {
                return reference( iter_->first, this->value_ptr() );
            }

            pointer operator->() const
            {
                return this->operator*();
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

            B base() const
            {
                return iter_;
            }

            const key_type& key() const
            {
                return iter_->first;
            }

            V& value() const
            {
                BOOST_ASSERT( iter_->second && "indirecting null pointer in map iterator" );
                return *this->value_ptr();                                
            }

            V* value_ptr() const
            {
                return static_cast<V*>( iter_->second );
            }

       }; // class 'ptr_map_iterator'


       
       template< class I, class K, class V, class B, class I2, class K2, class V2, class B2 >
       inline bool operator==( const ptr_map_iterator<I,K,V,B>& l, 
                               const ptr_map_iterator<I2,K2,V2,B2>& r )
       {
           return l.base() == r.base();
       }


      
       template< class I, class K, class V, class B, class I2, class K2, class V2, class B2 >
       inline bool operator!=( const ptr_map_iterator<I,K,V,B>& l, 
                               const ptr_map_iterator<I2,K2,V2,B2>& r )
       {
           return l.base() != r.base();
       }
}

#endif
