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

    // It may seem odd to use such small pages.
    //
    // However, on a typical Windows implementation that uses
    // the OS allocator, "normal size" pages interact with the
    // "ordinary" operator new, slowing it down dramatically.
    //
    // 512 byte pages are handled by the small object allocator,
    // and don't interfere with ::new.
    //
    // The other alternative is to use much bigger pages (1M.)

#if defined(BOOST_QA_PAGE_SIZE)

    enum { items_per_page = BOOST_QA_PAGE_SIZE / size };

#else

    enum { items_per_page = 496 / size }; // 1048560 / size

#endif

#ifdef BOOST_HAS_THREADS
    static lightweight_mutex mutex;
#endif

    static block * free;
    static block * page;
    static unsigned last;

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
            if(last == items_per_page)
            {
                // "Listen to me carefully: there is no memory leak"
                // -- Scott Meyers, Eff C++ 2nd Ed Item 10
                page = ::new block[items_per_page];
                last = 0;
            }

            return &page[last++];
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
                if(last == items_per_page)
                {
                    page = ::new block[items_per_page];
                    last = 0;
                }

                return &page[last++];
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
        if(n != size) // class-specific delete called for a derived object
        {
            ::operator delete(pv);
        }
        else if(pv != 0) // 18.4.1.1/13
        {
#ifdef BOOST_HAS_THREADS
            lightweight_mutex::scoped_lock lock(mutex);
#endif
            block * pb = static_cast<block *>(pv);
            pb->next = free;
            free = pb;
        }
    }
};

#ifdef BOOST_HAS_THREADS
template<unsigned size, unsigned align>
  lightweight_mutex allocator_impl<size, align>::mutex;
#endif

template<unsigned size, unsigned align>
  freeblock<size, align> * allocator_impl<size, align>::free = 0;

template<unsigned size, unsigned align>
  freeblock<size, align> * allocator_impl<size, align>::page = 0;

template<unsigned size, unsigned align>
  unsigned allocator_impl<size, align>::last = allocator_impl<size, align>::items_per_page;

template<class T>
struct quick_allocator: public allocator_impl< sizeof(T), boost::alignment_of<T>::value >
{
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_DETAIL_QUICK_ALLOCATOR_HPP_INCLUDED
