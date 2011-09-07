
// Copyright 2005-2011 Daniel James.
// Copyright 2009 Pablo Halpern.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Allocator traits written by Daniel James based on Pablo Halpern's
// implementation.

#ifndef BOOST_UNORDERED_DETAIL_ALLOCATOR_UTILITIES_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALLOCATOR_UTILITIES_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/select_type.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/limits.hpp>
#include <boost/type_traits/add_lvalue_reference.hpp>

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

    // Explicitly call a destructor

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable:4100) // unreferenced formal parameter
#endif

    template <class T>
    inline void destroy(T* x) {
        x->~T();
    }

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

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
        typedef typename Alloc::BOOST_NESTED_TEMPLATE rebind<T>::other
            type;
    };
#   endif

    template <typename T> typename boost::add_lvalue_reference<T>::type make();
    struct choice9 { typedef char (&type)[9]; };
    struct choice8 : choice9 { typedef char (&type)[8]; };
    struct choice7 : choice8 { typedef char (&type)[7]; };
    struct choice6 : choice7 { typedef char (&type)[6]; };
    struct choice5 : choice6 { typedef char (&type)[5]; };
    struct choice4 : choice5 { typedef char (&type)[4]; };
    struct choice3 : choice4 { typedef char (&type)[3]; };
    struct choice2 : choice3 { typedef char (&type)[2]; };
    struct choice1 : choice2 { typedef char (&type)[1]; };
    choice1 choose();

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1400

    #define BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(tname)                       \
        template <typename Tp, typename Default>                            \
        struct default_type_ ## tname {                                     \
                                                                            \
            template <typename X>                                           \
            static choice1::type test(choice1, typename X::tname* = 0);     \
                                                                            \
            template <typename X>                                           \
            static choice2::type test(choice2, void* = 0);                  \
                                                                            \
            struct DefaultWrap { typedef Default tname; };                  \
                                                                            \
            enum { value = (1 == sizeof(test<Tp>(choose()))) };             \
                                                                            \
            typedef typename boost::detail::if_true<value>::                \
                BOOST_NESTED_TEMPLATE then<Tp, DefaultWrap>                 \
                ::type::tname type;                                         \
        }

#else

    template <typename T, typename T2>
    struct sfinae : T2 {};

    #define BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(tname)                       \
        template <typename Tp, typename Default>                            \
        struct default_type_ ## tname {                                     \
                                                                            \
            template <typename X>                                           \
            static typename sfinae<typename X::tname, choice1>::type        \
                test(choice1);                                              \
                                                                            \
            template <typename X>                                           \
            static choice2::type test(choice2);                             \
                                                                            \
            struct DefaultWrap { typedef Default tname; };                  \
                                                                            \
            enum { value = (1 == sizeof(test<Tp>(choose()))) };             \
                                                                            \
            typedef typename boost::detail::if_true<value>::                \
                BOOST_NESTED_TEMPLATE then<Tp, DefaultWrap>                 \
                ::type::tname type;                                         \
        }

#endif

    #define BOOST_UNORDERED_DEFAULT_TYPE(T,tname, arg)                      \
        typename default_type_ ## tname<T, arg>::type

    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(pointer);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(const_pointer);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(void_pointer);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(const_void_pointer);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(difference_type);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(size_type);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(propagate_on_container_copy_assignment);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(propagate_on_container_move_assignment);
    BOOST_UNORDERED_DEFAULT_TYPE_TMPLT(propagate_on_container_swap);

#if !defined(BOOST_NO_SFINAE_EXPR) || BOOST_WORKAROUND(BOOST_MSVC, >= 1500)

    template <typename T, unsigned int> struct expr_test;
    template <typename T> struct expr_test<T, sizeof(char)> : T {};
    template <typename U> static char for_expr_test(U const&);

#define BOOST_UNORDERED_CHECK_EXPRESSION(count, result, expression)         \
        template <typename U>                                               \
        static typename expr_test<                                          \
            BOOST_PP_CAT(choice, result),                                   \
            sizeof(for_expr_test(((expression), 0)))>::type test(           \
            BOOST_PP_CAT(choice, count))

#define BOOST_UNORDERED_DEFAULT_EXPRESSION(count, result)                   \
        template <typename U>                                               \
        static BOOST_PP_CAT(choice, result)::type test(                     \
            BOOST_PP_CAT(choice, count))

#define BOOST_UNORDERED_HAS_EXPRESSION(name, expression)                    \
    struct BOOST_PP_CAT(has_, name)                                         \
    {                                                                       \
        BOOST_UNORDERED_CHECK_EXPRESSION(1, 1, expression);                 \
        BOOST_UNORDERED_DEFAULT_EXPRESSION(2, 2);                           \
                                                                            \
        enum { value = sizeof(test<T>(choose())) == sizeof(choice1::type) };\
    }

    template <typename T>
    BOOST_UNORDERED_HAS_EXPRESSION(
        select_on_container_copy_construction,
        make<U const>().select_on_container_copy_construction()
    );

    // Only supporting the basic copy constructor for now.

    template <typename T, typename ValueType>
    BOOST_UNORDERED_HAS_EXPRESSION(
        construct,
        make<U>().construct(make<ValueType*>(), make<ValueType const>())
    );

    template <typename T, typename ValueType>
    BOOST_UNORDERED_HAS_EXPRESSION(
        destroy,
        make<U>().destroy(make<ValueType*>())
    );

    template <typename T>
    BOOST_UNORDERED_HAS_EXPRESSION(
        max_size,
        make<U const>().max_size()
    );

#else

   template <typename T> struct identity { typedef T type; };

#define BOOST_UNORDERED_CHECK_MEMBER(count, result, name, member)           \
                                                                            \
    typedef typename identity<member>::type BOOST_PP_CAT(check, count);     \
                                                                            \
    template <BOOST_PP_CAT(check, count) e>                                 \
    struct BOOST_PP_CAT(test, count) {                                      \
        typedef BOOST_PP_CAT(choice, result) type;                          \
    };                                                                      \
                                                                            \
    template <class U> static typename                                      \
        BOOST_PP_CAT(test, count)<&U::name>::type                           \
        test(BOOST_PP_CAT(choice, count))

#define BOOST_UNORDERED_DEFAULT_MEMBER(count, result)                       \
    template <class U> static BOOST_PP_CAT(choice, result)::type            \
        test(BOOST_PP_CAT(choice, count))


    template <typename T>
    struct has_select_on_container_copy_construction
    {
        BOOST_UNORDERED_CHECK_MEMBER(1, 1,
            select_on_container_copy_construction,
            T (T::*)() const);
        BOOST_UNORDERED_DEFAULT_MEMBER(2, 2);
 
        enum { value = sizeof(test<T>(choose())) == sizeof(choice1::type) };
    };

    // Detection isn't reliable enough, so just assume that we have these
    // functions.
    
    template <typename Alloc, typename value_type>
    struct has_construct : true_type {};
    template <typename Alloc, typename value_type>
    struct has_destroy : true_type {};
    template <typename Alloc>
    struct has_max_size : true_type {};

#endif

    template <typename Alloc>
    inline typename boost::enable_if<
            has_select_on_container_copy_construction<Alloc>, Alloc
        >::type call_select_on_container_copy_construction(const Alloc& rhs)
    {
        return rhs.select_on_container_copy_construction();
    }

    template <typename Alloc>
    inline typename boost::disable_if<
            has_select_on_container_copy_construction<Alloc>, Alloc
        >::type call_select_on_container_copy_construction(const Alloc& rhs)
    {
        return rhs;
    }

    template <typename SizeType, typename Alloc>
    SizeType call_max_size(const Alloc& a,
        typename boost::enable_if<has_max_size<Alloc>, void*>::type = 0)
    {
        return a.max_size();
    }

    template <typename SizeType, typename Alloc>
    SizeType call_max_size(const Alloc&,
        typename boost::disable_if<has_max_size<Alloc>, void*>::type = 0)
    {
        return std::numeric_limits<SizeType>::max();
    }

    template <typename Alloc>
    struct allocator_traits
    {
        typedef Alloc allocator_type;
        typedef typename Alloc::value_type value_type;

        typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, pointer, value_type*)
            pointer;

        // For now always use the allocator's const_pointer.

        //typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, const_pointer,
        //    typename pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<const value_type>::other)
        //    const_pointer;

        typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, const_pointer,
            value_type const*) const_pointer;

        // I'm not using void pointers for now.

        //typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, void_pointer,
        //    BOOST_NESTED_TEMPLATE pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<void>::other)
        //    void_pointer;

        //typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, const_void_pointer,
        //    typename pointer_traits<pointer>::
        //    BOOST_NESTED_TEMPLATE rebind<const void>::other)
        //    const_void_pointer;

        typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, difference_type,
            std::ptrdiff_t) difference_type;

        typedef BOOST_UNORDERED_DEFAULT_TYPE(Alloc, size_type, std::size_t)
            size_type;

        // TODO: rebind_alloc and rebind_traits

       static pointer allocate(Alloc& a, size_type n)
            { return a.allocate(n); }

        // I never use this, so I'll just comment it out for now.
        //
        //static pointer allocate(Alloc& a, size_type n,
        //        const_void_pointer hint)
        //    { return DEFAULT_FUNC(allocate, pointer)(a, n, hint); }
    
        static void deallocate(Alloc& a, pointer p, size_type n)
            { a.deallocate(p, n); }

    public:

        // Only supporting the basic copy constructor for now.

        template <typename T>
        static void construct(Alloc& a, T* p, T const& x, typename
                boost::enable_if<has_construct<Alloc, T>, void*>::type = 0)
        {
            a.construct(p, x);
        }

        template <typename T>
        static void construct(Alloc&, T* p, T const& x, typename
                boost::disable_if<has_construct<Alloc, T>, void*>::type = 0)
        {
            new ((void*) p) T(x);
        }

        template <typename T>
        static void destroy(Alloc& a, T* p, typename
                boost::enable_if<has_destroy<Alloc, T>, void*>::type = 0)
        {
            a.destroy(p);
        }

        template <typename T>
        static void destroy(Alloc&, T* p, typename
                boost::disable_if<has_destroy<Alloc, T>, void*>::type = 0)
        {
            ::boost::unordered::detail::destroy(p);
        }

        static size_type max_size(const Alloc& a)
        {
            return boost::unordered::detail::call_max_size<size_type>(a);
        }

        // Allocator propagation on construction
        
        static Alloc select_on_container_copy_construction(Alloc const& rhs)
        {
            return boost::unordered::detail::
                call_select_on_container_copy_construction(rhs);
        }
    
        // Allocator propagation on assignment and swap.
        // Return true if lhs is modified.
        typedef BOOST_UNORDERED_DEFAULT_TYPE(
            Alloc, propagate_on_container_copy_assignment, false_type)
            propagate_on_container_copy_assignment;
        typedef BOOST_UNORDERED_DEFAULT_TYPE(
            Alloc,propagate_on_container_move_assignment, false_type)
            propagate_on_container_move_assignment;
        typedef BOOST_UNORDERED_DEFAULT_TYPE(
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
        typedef typename allocator_traits<Allocator>::pointer
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
