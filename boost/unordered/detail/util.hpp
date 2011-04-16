
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
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
#include <boost/compressed_pair.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/throw_exception.hpp>
#include <boost/unordered/detail/allocator_helpers.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>

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
        // STLport doesn't have std::forward.
#   else
#       define BOOST_UNORDERED_STD_FORWARD
#   endif
#endif

#if !defined(BOOST_UNORDERED_EMPLACE_LIMIT)
#define BOOST_UNORDERED_EMPLACE_LIMIT 10
#endif

#if !defined(BOOST_UNORDERED_STD_FORWARD)

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#define BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params) \
    BOOST_PP_ENUM_PARAMS_Z(z, num_params, class Arg)
#define BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params) \
    BOOST_PP_ENUM_BINARY_PARAMS_Z(z, num_params, Arg, const& arg)
#define BOOST_UNORDERED_CALL_PARAMS(z, num_params) \
    BOOST_PP_ENUM_PARAMS_Z(z, num_params, arg)

#endif

namespace boost { namespace unordered { namespace detail {

    static const float minimum_max_load_factor = 1e-3f;
    static const std::size_t default_bucket_count = 11;
    struct move_tag {};

    template <class T> class unique_table;
    template <class T> class equivalent_table;
    template <class Alloc, bool Unique> class node_constructor;
    template <class ValueType>
    struct set_extractor;
    template <class Key, class ValueType>
    struct map_extractor;
    struct no_key;

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
    // pair_cast - because some libraries don't have the full pair constructors.

#if 0
    template <class Dst1, class Dst2, class Src1, class Src2>
    inline std::pair<Dst1, Dst2> pair_cast(std::pair<Src1, Src2> const& x)
    {
        return std::pair<Dst1, Dst2>(Dst1(x.first), Dst2(x.second));
    }

#define BOOST_UNORDERED_PAIR_CAST(First, Last, Argument) \
    ::boost::unordered::detail::pair_cast<First, Last>(Argument)
#else
#define BOOST_UNORDERED_PAIR_CAST(First, Last, Argument) \
    Argument
#endif
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
        BOOST_DEDUCED_TYPENAME ::boost::iterator_traversal<I>::type
            iterator_traversal_tag;
        return insert_size(i, j, iterator_traversal_tag);
    }
    
    template <class I>
    inline std::size_t initial_size(I i, I j,
        std::size_t num_buckets = ::boost::unordered::detail::default_bucket_count)
    {
        return (std::max)(static_cast<std::size_t>(insert_size(i, j)) + 1,
            num_buckets);
    }
}}}

#endif
