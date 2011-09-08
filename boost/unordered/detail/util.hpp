
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_UTIL_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_UTIL_HPP_INCLUDED

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <boost/limits.hpp>
#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/detail/select_type.hpp>
#include <boost/assert.hpp>
#include <boost/iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_empty.hpp>
#if defined(BOOST_NO_RVALUE_REFERENCES)
#include <boost/type_traits/is_class.hpp>
#endif
#include <boost/throw_exception.hpp>
#include <boost/move/move.hpp>
#include <boost/swap.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/tuple/tuple.hpp>
#if !defined(BOOST_NO_0X_HDR_TUPLE) || defined(BOOST_HAS_TR1_TUPLE)
#include <tuple>
#endif
#include <boost/unordered/detail/allocator_helpers.hpp>

// Template parameters:
//
// H = Hash Function
// P = Predicate
// A = Value Allocator
// G = Bucket group policy, 'grouped' or 'ungrouped'
// E = Key Extractor

#if !defined(BOOST_NO_RVALUE_REFERENCES) && \
        !defined(BOOST_NO_VARIADIC_TEMPLATES)
#   if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
#   elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
#   elif defined(_LIBCPP_VERSION)
#       define BOOST_UNORDERED_STD_FORWARD_MOVE
#   elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
#       if defined(__GLIBCXX__) && __GLIBCXX__ >= 20090804
#           define BOOST_UNORDERED_STD_FORWARD_MOVE
#       endif
#    elif defined(__STL_CONFIG_H)
#    elif defined(__MSL_CPP__)
#    elif defined(__IBMCPP__)
#    elif defined(MSIPL_COMPILE_H)
#    elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
        // Visual C++. A version check would be a good idea.
#       define BOOST_UNORDERED_STD_FORWARD_MOVE    
#   endif
#endif

#if !defined(BOOST_UNORDERED_EMPLACE_LIMIT)
#define BOOST_UNORDERED_EMPLACE_LIMIT 10
#endif

#if defined(__SUNPRO_CC)
#define BOOST_UNORDERED_USE_RV_REF 0
#else
#define BOOST_UNORDERED_USE_RV_REF 1
#endif

#if !defined(BOOST_UNORDERED_STD_FORWARD_MOVE)

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params) \
    BOOST_PP_ENUM_PARAMS_Z(z, num_params, class Arg)

#define BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params) \
    BOOST_PP_ENUM_##z(num_params, BOOST_UNORDERED_FUNCTION_PARAMS2, _)
#define BOOST_UNORDERED_FUNCTION_PARAMS2(z, i, _) \
    BOOST_FWD_REF(Arg##i) arg##i

#define BOOST_UNORDERED_CALL_PARAMS(z, num_params) \
    BOOST_PP_ENUM_##z(num_params, BOOST_UNORDERED_CALL_PARAMS2, _)
#define BOOST_UNORDERED_CALL_PARAMS2(z, i, _) \
    boost::forward<Arg##i>(arg##i)

#endif

namespace boost { namespace unordered { namespace detail {

    static const float minimum_max_load_factor = 1e-3f;
    static const std::size_t default_bucket_count = 11;
    struct move_tag {};

    struct empty_emplace {};

    template <class T> class unique_table;
    template <class T> class equivalent_table;
    template <class Alloc, bool Unique> class node_constructor;
    template <class ValueType>
    struct set_extractor;
    template <class Key, class ValueType>
    struct map_extractor;
    struct no_key;

#if !defined(BOOST_NO_RVALUE_REFERENCES)

#define BOOST_UNORDERED_RV_REF(T) BOOST_RV_REF(T)

#else

    struct please_ignore_this_overload {
        typedef please_ignore_this_overload type;
    };

    template <typename T>
    struct rv_ref_impl {
        typedef BOOST_RV_REF(T) type;
    };

    template <typename T>
    struct rv_ref :
        boost::detail::if_true<
            boost::is_class<T>::value
        >::BOOST_NESTED_TEMPLATE then <
            rv_ref_impl<T>,
            please_ignore_this_overload
        >::type
    {};

#define BOOST_UNORDERED_RV_REF(T) \
    typename ::boost::unordered::detail::rv_ref<T>::type

#endif

    ////////////////////////////////////////////////////////////////////////////
    // convert double to std::size_t

    inline std::size_t double_to_size_t(double f)
    {
        return f >= static_cast<double>(
            (std::numeric_limits<std::size_t>::max)()) ?
            (std::numeric_limits<std::size_t>::max)() :
            static_cast<std::size_t>(f);
    }

    ////////////////////////////////////////////////////////////////////////////
    // primes

#define BOOST_UNORDERED_PRIMES \
    (5ul)(11ul)(17ul)(29ul)(37ul)(53ul)(67ul)(79ul) \
    (97ul)(131ul)(193ul)(257ul)(389ul)(521ul)(769ul) \
    (1031ul)(1543ul)(2053ul)(3079ul)(6151ul)(12289ul)(24593ul) \
    (49157ul)(98317ul)(196613ul)(393241ul)(786433ul) \
    (1572869ul)(3145739ul)(6291469ul)(12582917ul)(25165843ul) \
    (50331653ul)(100663319ul)(201326611ul)(402653189ul)(805306457ul) \
    (1610612741ul)(3221225473ul)(4294967291ul)

    template<class T> struct prime_list_template
    {
        static std::size_t const value[];

#if !defined(SUNPRO_CC)
        static std::ptrdiff_t const length;
#else
        static std::ptrdiff_t const length
            = BOOST_PP_SEQ_SIZE(BOOST_UNORDERED_PRIMES);
#endif
    };

    template<class T>
    std::size_t const prime_list_template<T>::value[] = {
        BOOST_PP_SEQ_ENUM(BOOST_UNORDERED_PRIMES)
    };

#if !defined(SUNPRO_CC)
    template<class T>
    std::ptrdiff_t const prime_list_template<T>::length
        = BOOST_PP_SEQ_SIZE(BOOST_UNORDERED_PRIMES);
#endif

#undef BOOST_UNORDERED_PRIMES

    typedef prime_list_template<std::size_t> prime_list;

    // no throw
    inline std::size_t next_prime(std::size_t num) {
        std::size_t const* const prime_list_begin = prime_list::value;
        std::size_t const* const prime_list_end = prime_list_begin +
            prime_list::length;
        std::size_t const* bound =
            std::lower_bound(prime_list_begin, prime_list_end, num);
        if(bound == prime_list_end)
            bound--;
        return *bound;
    }

    // no throw
    inline std::size_t prev_prime(std::size_t num) {
        std::size_t const* const prime_list_begin = prime_list::value;
        std::size_t const* const prime_list_end = prime_list_begin +
            prime_list::length;
        std::size_t const* bound =
            std::upper_bound(prime_list_begin,prime_list_end, num);
        if(bound != prime_list_begin)
            bound--;
        return *bound;
    }

    ////////////////////////////////////////////////////////////////////////////
    // insert_size/initial_size

#if !defined(BOOST_NO_STD_DISTANCE)
    using ::std::distance;
#else
    template <class ForwardIterator>
    inline std::size_t distance(ForwardIterator i, ForwardIterator j) {
        std::size_t x;
        std::distance(i, j, x);
        return x;
    }
#endif

    template <class I>
    inline std::size_t insert_size(I i, I j, ::boost::forward_traversal_tag)
    {
        return std::distance(i, j);
    }

    template <class I>
    inline std::size_t insert_size(I, I, ::boost::incrementable_traversal_tag)
    {
        return 1;
    }

    template <class I>
    inline std::size_t insert_size(I i, I j)
    {
        return insert_size(i, j,
            typename ::boost::iterator_traversal<I>::type());
    }
    
    template <class I>
    inline std::size_t initial_size(I i, I j,
        std::size_t num_buckets = ::boost::unordered::detail::default_bucket_count)
    {
        return (std::max)(static_cast<std::size_t>(insert_size(i, j)) + 1,
            num_buckets);
    }

    ////////////////////////////////////////////////////////////////////////////
    // compressed_pair

    template <typename T, int Index>
    struct compressed_base : private T
    {
        compressed_base(T const& x) : T(x) {}
        compressed_base(T& x, move_tag) : T(boost::move(x)) {}

        T& get() { return *this; }
        T const& get() const { return *this; }
    };
    
    template <typename T, int Index>
    struct uncompressed_base
    {
        uncompressed_base(T const& x) : value_(x) {}
        uncompressed_base(T& x, move_tag) : value_(boost::move(x)) {}

        T& get() { return value_; }
        T const& get() const { return value_; }
    private:
        T value_;
    };
    
    template <typename T, int Index>
    struct generate_base
      : boost::detail::if_true<
            boost::is_empty<T>::value
        >:: BOOST_NESTED_TEMPLATE then<
            compressed_base<T, Index>,
            uncompressed_base<T, Index>
        >
    {};
    
    template <typename T1, typename T2>
    struct compressed_pair
      : private generate_base<T1, 1>::type,
        private generate_base<T2, 2>::type
    {
        typedef typename generate_base<T1, 1>::type base1;
        typedef typename generate_base<T2, 2>::type base2;

        typedef T1 first_type;
        typedef T2 second_type;
        
        first_type& first() {
            return static_cast<base1*>(this)->get();
        }

        first_type const& first() const {
            return static_cast<base1 const*>(this)->get();
        }

        second_type& second() {
            return static_cast<base2*>(this)->get();
        }

        second_type const& second() const {
            return static_cast<base2 const*>(this)->get();
        }

        template <typename First, typename Second>
        compressed_pair(First const& x1, Second const& x2)
            : base1(x1), base2(x2) {}

        compressed_pair(compressed_pair const& x)
            : base1(x.first()), base2(x.second()) {}

        compressed_pair(compressed_pair& x, move_tag m)
            : base1(x.first(), m), base2(x.second(), m) {}

        void assign(compressed_pair const& x)
        {
            first() = x.first();
            second() = x.second();
        }

        void move_assign(compressed_pair& x)
        {
            first() = boost::move(x.first());
            second() = boost::move(x.second());
        }
        
        void swap(compressed_pair& x)
        {
            boost::swap(first(), x.first());
            boost::swap(second(), x.second());
        }

    private:
        // Prevent assignment just to make use of assign or
        // move_assign explicit.
        compressed_pair& operator=(compressed_pair const&);
    };
}}}

#endif
