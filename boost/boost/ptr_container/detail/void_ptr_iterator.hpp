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

#ifndef BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_DETAIL_VOID_PTR_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/if.hpp>
#include <cassert>


namespace boost
{
    namespace ptr_container_detail
    {

        template
        < 
            class VoidIter, 
            class T
        >
        class void_ptr_iterator : public
            iterator_facade< void_ptr_iterator<VoidIter,T>, 
                             T,
                             BOOST_DEDUCED_TYPENAME iterator_category<VoidIter>::type,
                             T*&,
                             BOOST_DEDUCED_TYPENAME iterator_difference<VoidIter>::type >
        {
            typedef BOOST_DEDUCED_TYPENAME 
                     mpl::if_< boost::is_const<T>,
                               const void*,
                               void* >::type void_type;
        public:
            typedef VoidIter wrapped_type;
            typedef T*       value_type;
            typedef T*&      reference;
            typedef  BOOST_DEDUCED_TYPENAME iterator_difference<VoidIter>::type
                             difference_type;           
        private:
            
            VoidIter iter_;

        public:
            void_ptr_iterator() : iter_()
            { }

            void_ptr_iterator( VoidIter r ) : iter_(r)
            { }

            VoidIter base() const
            {
                return iter_;
            }
            
        private:
            friend class boost::iterator_core_access;

            reference dereference() const
            {
                return reinterpret_cast<reference>( const_cast<void_type&>( *iter_ ) );
            }

            bool equal( void_ptr_iterator r ) const
            {
                return iter_ == r.iter_;
            }

            void increment()
            {
                ++iter_;
            }

            void decrement()
            {
                --iter_;
            }

            void advance( difference_type n )
            {
                iter_ += n;
            }

            difference_type distance_to( void_ptr_iterator r ) const
            {
                return r.iter_ - iter_; 
            }

        }; // class 'void_ptr_iterator'


/*
        template
        < 
            class VoidContainer, 
            class T
        >
        struct iterator_of
        {
            typedef void_ptr_iterator
                    < BOOST_DEDUCED_TYPENAME VoidContainer::iterator,
                      BOOST_DEDUCED_TYPENAME Container::iterator >
                type;
        };

        template
        < 
            class VoidContainer, 
            class Container
        >
        struct const_iterator_of
        {
            typedef void_ptr_iterator
                    < BOOST_DEDUCED_TYPENAME VoidContainer::const_iterator,
                      BOOST_DEDUCED_TYPENAME Container::const_iterator >
                type;
        };

        template
        < 
            class VoidContainer, 
            class Container
        >
        struct reverse_iterator_of
        {
            typedef void_ptr_iterator
                    < BOOST_DEDUCED_TYPENAME VoidContainer::reverse_iterator,
                      BOOST_DEDUCED_TYPENAME Container::reverse_iterator >
                type;
        };

        template
        < 
            class VoidContainer, 
            class Container
        >
        struct const_reverse_iterator_of
        {
            typedef void_ptr_iterator
                    < BOOST_DEDUCED_TYPENAME VoidContainer::const_reverse_iterator,
                      BOOST_DEDUCED_TYPENAME Container::const_reverse_iterator >
                type;
        };
        */

    } // nameespace 'ptr_container_detail'
    
}

#endif
