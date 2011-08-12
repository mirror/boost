
// Copyright 2005-2011 Daniel James.
// Copyright 2009 Pablo Halpern.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Written by Daniel James using some code from Pablo Halpern's
// allocator traits implementation.

#ifndef BOOST_UNORDERED_DETAIL_ALLOCATOR_UTILITIES_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALLOCATOR_UTILITIES_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/select_type.hpp>

#if (defined(BOOST_NO_STD_ALLOCATOR) || defined(BOOST_DINKUMWARE_STDLIB)) \
    && !defined(__BORLANDC__)
#  define BOOST_UNORDERED_USE_ALLOCATOR_UTILITIES
#endif

#if defined(BOOST_UNORDERED_USE_ALLOCATOR_UTILITIES)
#  include <boost/detail/allocator_utilities.hpp>
#endif

#if BOOST_UNORDERED_USE_ALLOCATOR_TRAITS
#  include <memory>
#endif

#if !defined(BOOST_NO_0X_HDR_TYPE_TRAITS)
#include <type_traits>
namespace boost { namespace unordered { namespace detail {
    using std::integral_constant;
    using std::true_type;
    using std::false_type;
}}}
#else
namespace boost { namespace unordered { namespace detail {
    template <typename T, T Value>
    struct integral_constant { enum { value = Value }; };
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
}}}
#endif

// TODO: Use std::addressof if available?
#include <boost/utility/addressof.hpp>

namespace boost { namespace unordered { namespace detail {

#if BOOST_UNORDERED_USE_ALLOCATOR_TRAITS
    template <typename Alloc>
    struct allocator_traits : std::allocator_traits<Alloc> {};
    
    template <typename Alloc, typename T>
    struct rebind_wrap
    {
        typedef typename allocator_traits<Alloc>::rebind_alloc<T> type;
    };
#else
    // rebind_wrap
    //
    // Rebind allocators. For some problematic libraries, use rebind_to
    // from <boost/detail/allocator_utilities.hpp>.

#   if defined(BOOST_UNORDERED_USE_ALLOCATOR_UTILITIES)
    template <typename Alloc, typename T>
    struct rebind_wrap : ::boost::detail::allocator::rebind_to<Alloc, T> {};
#   else
    template <typename Alloc, typename T>
    struct rebind_wrap
    {
        typedef BOOST_DEDUCED_TYPENAME
            Alloc::BOOST_NESTED_TEMPLATE rebind<T>::other
            type;
    };
#   endif

    struct convertible_from_anything
    {
        template<typename T> convertible_from_anything(T const&);
    };

    // Infrastructure for providing a default type for Tp::tname if absent.
    #define BOOST_DEFAULT_TYPE_TMPLT(tname)                                 \
        template <typename Tp, typename Default>                            \
        struct default_type_ ## tname {                                     \
                                                                            \
            template <typename X>                                           \
            static char test(int, BOOST_DEDUCED_TYPENAME X::tname*);        \
                                                                            \
            template <typename X>                                           \
            static int test(convertible_from_anything, void*);              \
                                                                            \
            struct DefaultWrap { typedef Default tname; };                  \
                                                                            \
            static const bool value = (1 == sizeof(test<Tp>(0, 0)));        \
                                                                            \
            typedef BOOST_DEDUCED_TYPENAME                                  \
                boost::detail::if_true<value>::                             \
                BOOST_NESTED_TEMPLATE then<Tp, DefaultWrap>                 \
                ::type::tname type;                                         \
        }
    
    #define BOOST_DEFAULT_TYPE(T,tname, arg)                                \
        BOOST_DEDUCED_TYPENAME default_type_ ## tname<T, arg>::type

    BOOST_DEFAULT_TYPE_TMPLT(pointer);
    BOOST_DEFAULT_TYPE_TMPLT(const_pointer);
    BOOST_DEFAULT_TYPE_TMPLT(void_pointer);
    BOOST_DEFAULT_TYPE_TMPLT(const_void_pointer);
    BOOST_DEFAULT_TYPE_TMPLT(difference_type);
    BOOST_DEFAULT_TYPE_TMPLT(size_type);
    BOOST_DEFAULT_TYPE_TMPLT(propagate_on_container_copy_assignment);
    BOOST_DEFAULT_TYPE_TMPLT(propagate_on_container_move_assignment);
    BOOST_DEFAULT_TYPE_TMPLT(propagate_on_container_swap);

    template <typename Alloc>
    struct allocator_traits
    {
        typedef Alloc allocator_type;
        typedef typename Alloc::value_type value_type;

        typedef BOOST_DEFAULT_TYPE(Alloc, pointer, value_type*)
            pointer;

        // For now always use the allocator's const_pointer.

        //typedef BOOST_DEFAULT_TYPE(Alloc, const_pointer,
        //    BOOST_DEDUCED_TYPENAME pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<const value_type>::other)
        //    const_pointer;

        typedef BOOST_DEFAULT_TYPE(Alloc, const_pointer, value_type const*)
            const_pointer;

        // I'm not using void pointers for now.

        //typedef BOOST_DEFAULT_TYPE(Alloc, void_pointer,
        //    BOOST_NESTED_TEMPLATE pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<void>::other)
        //    void_pointer;

        //typedef BOOST_DEFAULT_TYPE(Alloc, const_void_pointer,
        //    BOOST_DEDUCED_TYPENAME pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<const void>::other)
        //    const_void_pointer;

        typedef BOOST_DEFAULT_TYPE(Alloc, difference_type, std::ptrdiff_t)
            difference_type;

        typedef BOOST_DEFAULT_TYPE(Alloc, size_type, std::size_t)
            size_type;

        // TODO: rebind_alloc and rebind_traits

       static pointer allocate(Alloc& a, size_type n)
            { return a.allocate(n); }

        // I never use this, so I'll just comment it out for now.
        //
        //static pointer allocate(Alloc& a, size_type n, const_void_pointer hint)
        //    { return DEFAULT_FUNC(allocate, pointer)(a, n, hint); }
    
        static void deallocate(Alloc& a, pointer p, size_type n)
            { a.deallocate(p, n); }

        // Only support the basic copy constructor

        // template <typename T, typename... Args>
        // static void construct(Alloc& a, T* p, Args&&... args) {
        //     DEFAULT_FUNC(construct,void)(a, p, std::forward<Args>(args)...);
        // }

        template <typename T>
        static void construct(Alloc& a, T* p, T const& x) {
            a.construct(p, x);
        }

        template <typename T>
        static void destroy(Alloc& a, T* p) {
            // DEFAULT_FUNC(destroy,void)(a, p);
            a.destroy(p);
        }

        static size_type max_size(const Alloc& a)
            { return a.max_size(); }

        // Allocator propagation on construction

        static Alloc select_on_container_copy_construction(const Alloc& rhs) {
            //return BOOST_DEFAULT_FUNC(select_on_container_copy_construction,Alloc)(rhs);
            return rhs;
        }
    
        // Allocator propagation on assignment and swap.
        // Return true if lhs is modified.
        typedef BOOST_DEFAULT_TYPE(
            Alloc, propagate_on_container_copy_assignment, false_type)
            propagate_on_container_copy_assignment;
        typedef BOOST_DEFAULT_TYPE(
            Alloc,propagate_on_container_move_assignment, false_type)
            propagate_on_container_move_assignment;
        typedef BOOST_DEFAULT_TYPE(
            Alloc,propagate_on_container_swap,false_type)
            propagate_on_container_swap;
    };
#endif

    // allocator_array_constructor
    //
    // Allocate and construct an array in an exception safe manner, and
    // clean up if an exception is thrown before the container takes charge
    // of it.

    template <typename Allocator>
    struct allocator_array_constructor
    {
        typedef BOOST_DEDUCED_TYPENAME allocator_traits<Allocator>::pointer
            pointer;

        Allocator& alloc_;
        pointer ptr_;
        pointer constructed_;
        std::size_t length_;

        allocator_array_constructor(Allocator& a)
            : alloc_(a), ptr_(), constructed_(), length_(0)
        {
            constructed_ = pointer();
            ptr_ = pointer();
        }

        ~allocator_array_constructor() {
            if (ptr_) {
                for(pointer p = ptr_; p != constructed_; ++p)
                    allocator_traits<Allocator>::destroy(alloc_,
                    	boost::addressof(*p));

                allocator_traits<Allocator>::deallocate(alloc_, ptr_, length_);
            }
        }

        template <typename V>
        void construct(V const& v, std::size_t l)
        {
            BOOST_ASSERT(!ptr_);
            length_ = l;
            ptr_ = allocator_traits<Allocator>::allocate(alloc_, length_);
            pointer end = ptr_ + static_cast<std::ptrdiff_t>(length_);
            for(constructed_ = ptr_; constructed_ != end; ++constructed_)
                allocator_traits<Allocator>::construct(alloc_,
                	boost::addressof(*constructed_), v);
        }

        pointer get() const
        {
            return ptr_;
        }

        pointer release()
        {
            pointer p(ptr_);
            ptr_ = pointer();
            return p;
        }
    private:
        allocator_array_constructor(allocator_array_constructor const&);
        allocator_array_constructor& operator=(
            allocator_array_constructor const&);
    };
}}}

#if defined(BOOST_UNORDERED_USE_ALLOCATOR_UTILITIES)
#  undef BOOST_UNORDERED_USE_ALLOCATOR_UTILITIES
#endif

#endif
