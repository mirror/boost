
// Copyright (C) 2008-2011 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_FWD_HPP_INCLUDED
#define BOOST_UNORDERED_FWD_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <memory>
#include <functional>
#include <boost/functional/hash_fwd.hpp>

namespace boost
{
namespace unordered
{
    template <class K,
        class T,
        class H = hash<K>,
        class P = std::equal_to<K>,
        class A = std::allocator<std::pair<const K, T> > >
    class unordered_map;
    template <class K, class T, class H, class P, class A>
    inline bool operator==(unordered_map<K, T, H, P, A> const&,
        unordered_map<K, T, H, P, A> const&);
    template <class K, class T, class H, class P, class A>
    inline bool operator!=(unordered_map<K, T, H, P, A> const&,
        unordered_map<K, T, H, P, A> const&);
    template <class K, class T, class H, class P, class A>
    inline void swap(unordered_map<K, T, H, P, A>&,
            unordered_map<K, T, H, P, A>&);

    template <class K,
        class T,
        class H = hash<K>,
        class P = std::equal_to<K>,
        class A = std::allocator<std::pair<const K, T> > >
    class unordered_multimap;
    template <class K, class T, class H, class P, class A>
    inline bool operator==(unordered_multimap<K, T, H, P, A> const&,
        unordered_multimap<K, T, H, P, A> const&);
    template <class K, class T, class H, class P, class A>
    inline bool operator!=(unordered_multimap<K, T, H, P, A> const&,
        unordered_multimap<K, T, H, P, A> const&);
    template <class K, class T, class H, class P, class A>
    inline void swap(unordered_multimap<K, T, H, P, A>&,
            unordered_multimap<K, T, H, P, A>&);

    template <class T,
        class H = hash<T>,
        class P = std::equal_to<T>,
        class A = std::allocator<T> >
    class unordered_set;
    template <class T, class H, class P, class A>
    inline bool operator==(unordered_set<T, H, P, A> const&,
        unordered_set<T, H, P, A> const&);
    template <class T, class H, class P, class A>
    inline bool operator!=(unordered_set<T, H, P, A> const&,
        unordered_set<T, H, P, A> const&);
    template <class T, class H, class P, class A>
    inline void swap(unordered_set<T, H, P, A> &m1,
            unordered_set<T, H, P, A> &m2);

    template <class T,
        class H = hash<T>,
        class P = std::equal_to<T>,
        class A = std::allocator<T> >
    class unordered_multiset;
    template <class T, class H, class P, class A>
    inline bool operator==(unordered_multiset<T, H, P, A> const&,
        unordered_multiset<T, H, P, A> const&);
    template <class T, class H, class P, class A>
    inline bool operator!=(unordered_multiset<T, H, P, A> const&,
        unordered_multiset<T, H, P, A> const&);
    template <class T, class H, class P, class A>
    inline void swap(unordered_multiset<T, H, P, A> &m1,
            unordered_multiset<T, H, P, A> &m2);

}
}

#endif
