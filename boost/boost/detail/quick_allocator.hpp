#ifndef BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED
#define BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED

#if _MSC_VER >= 1020
#pragma once
#endif

//
//  detail/quick_allocator.hpp
//
//  Copyright (c) 2003 David Abrahams
//  Copyright (c) 2003 Peter Dimov
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/config.hpp>

#include <boost/detail/lightweight_mutex.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/type_traits/alignment_of.hpp>

#include <deque>
#include <new>              // ::operator new, ::operator delete
#include <cstddef>          // std::size_t

namespace boost
{

namespace detail
{

template<unsigned size, unsigned align> union freeblock
{
    typedef typename boost::type_with_alignment<align>::type aligner_type;
    aligner_type aligner;
    char bytes[size];
    freeblock * next;
};

template<unsigned size, unsigned align> struct allocator_impl
{
    typedef freeblock<size, align> block;

    static lightweight_mutex mutex;
    static std::deque<block> store;
    static block * free;
    
    static inline void * alloc()
    {
#ifdef BOOST_HAS_THREADS
        lightweight_mutex::scoped_lock lock(mutex);
#endif
        if(block * x = free)
        {
            free = x->next;
            return x;
        }
        else
        {
            store.resize(store.size() + 1);
            return &store.back();
        }
    }

    static inline void * alloc(std::size_t n)
    {
        if(n != size) // class-specific new called for a derived object
        {
            return ::operator new(n);
        }
        else
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock(mutex);
#endif
            if(block * x = free)
            {
                free = x->next;
                return x;
            }
            else
            {
                store.resize(store.size() + 1);
                return &store.back();
            }
        }
    }

    static inline void dealloc(void * pv)
    {
        if(pv != 0) // 18.4.1.1/13
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock(mutex);
#endif
            block * pb = static_cast<block *>(pv);
            pb->next = free;
            free = pb;
        }
    }

    static inline void dealloc(void * pv, std::size_t n)
    {
        if(pv != 0) // 18.4.1.1/13
        {
            if(n != size) // class-specific delete called for a derived object
            {
                ::operator delete(pv);
            }
            else
            {
#ifdef BOOST_HAS_THREADS
                lightweight_mutex::scoped_lock lock(mutex);
#endif
                block * pb = static_cast<block *>(pv);
                pb->next = free;
                free = pb;
            }
        }
    }
};

template<unsigned size, unsigned align>
  lightweight_mutex allocator_impl<size, align>::mutex;

template<unsigned size, unsigned align>
  std::deque< freeblock<size, align> > allocator_impl<size, align>::store;

template<unsigned size, unsigned align>
  freeblock<size, align> * allocator_impl<size, align>::free = 0;

template<class T>
struct quick_allocator: public allocator_impl< sizeof(T), boost::alignment_of<T>::value >
{
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED
