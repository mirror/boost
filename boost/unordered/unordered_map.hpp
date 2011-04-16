
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/unordered for documentation

#ifndef BOOST_UNORDERED_UNORDERED_MAP_HPP_INCLUDED
#define BOOST_UNORDERED_UNORDERED_MAP_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/unordered/unordered_map_fwd.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered/detail/allocator_helpers.hpp>
#include <boost/unordered/detail/equivalent.hpp>
#include <boost/unordered/detail/unique.hpp>

#if defined(BOOST_NO_RVALUE_REFERENCES)
#include <boost/unordered/detail/move.hpp>
#endif

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
#if BOOST_MSVC >= 1400
#pragma warning(disable:4396) //the inline specifier cannot be used when a
                              // friend declaration refers to a specialization
                              // of a function template
#endif
#endif

namespace boost
{
    template <class K, class T, class H, class P, class A>
    class unordered_map
    {
    public:
        typedef K key_type;
        typedef std::pair<const K, T> value_type;
        typedef T mapped_type;
        typedef H hasher;
        typedef P key_equal;
        typedef A allocator_type;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
    private:
#endif

        typedef BOOST_DEDUCED_TYPENAME
            ::boost::unordered::detail::rebind_wrap<
                allocator_type, value_type>::type
            value_allocator;

        typedef ::boost::unordered::detail::map<K, H, P,
            value_allocator> types;
        typedef BOOST_DEDUCED_TYPENAME types::impl table;

        typedef BOOST_DEDUCED_TYPENAME types::node_ptr node_ptr;

    public:

        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::pointer pointer;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::const_pointer const_pointer;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::reference reference;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::const_reference const_reference;

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef ::boost::unordered::iterator_detail::cl_iterator<
            value_allocator, true> const_local_iterator;
        typedef ::boost::unordered::iterator_detail::l_iterator<
            value_allocator, true> local_iterator;
        typedef ::boost::unordered::iterator_detail::c_iterator<
            value_allocator, true> const_iterator;
        typedef ::boost::unordered::iterator_detail::iterator<
            value_allocator, true> iterator;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
    private:
#endif

        table table_;
        
        BOOST_DEDUCED_TYPENAME types::node_ptr const&
            get(const_iterator const& it)
        {
            return ::boost::unordered::detail::iterator_access::get(it);
        }

    public:

        // construct/destroy/copy

        explicit unordered_map(
                size_type = ::boost::unordered::detail::default_bucket_count,
                const hasher& = hasher(),
                const key_equal& = key_equal(),
                const allocator_type& = allocator_type());

        explicit unordered_map(allocator_type const&);

        unordered_map(unordered_map const&, allocator_type const&);

        template <class InputIt>
        unordered_map(InputIt f, InputIt l);

        template <class InputIt>
        unordered_map(
                InputIt, InputIt,
                size_type,
                const hasher& = hasher(),
                const key_equal& = key_equal());        

        template <class InputIt>
        unordered_map(
                InputIt, InputIt,
                size_type,
                const hasher&,
                const key_equal&,
                const allocator_type&);
        
        ~unordered_map();

#if !defined(BOOST_NO_RVALUE_REFERENCES)
        unordered_map(unordered_map const&);
        unordered_map(unordered_map&&);
        unordered_map(unordered_map&&, allocator_type const&);
        unordered_map& operator=(unordered_map const&);
        unordered_map& operator=(unordered_map&&);
#else
        unordered_map(::boost::unordered::detail::move_from<
                unordered_map<K,T,H,P,A>
            >);
#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0593)
        unordered_map& operator=(unordered_map);
#endif
#endif

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
        unordered_map(
                std::initializer_list<value_type>,
                size_type = ::boost::unordered::detail::default_bucket_count,
                const hasher& = hasher(),
                const key_equal&l = key_equal(),
                const allocator_type& = allocator_type());

        unordered_map& operator=(std::initializer_list<value_type>);
#endif

        allocator_type get_allocator() const
        {
            return table_.node_alloc();
        }

        // size and capacity

        bool empty() const
        {
            return table_.size_ == 0;
        }

        size_type size() const
        {
            return table_.size_;
        }

        size_type max_size() const;

        // iterators

        iterator begin()
        {
            return iterator(table_.begin());
        }

        const_iterator begin() const
        {
            return const_iterator(table_.begin());
        }

        iterator end()
        {
            return iterator();
        }

        const_iterator end() const
        {
            return const_iterator();
        }

        const_iterator cbegin() const
        {
            return const_iterator(table_.begin());
        }

        const_iterator cend() const
        {
            return const_iterator();
        }

        // modifiers

#if defined(BOOST_UNORDERED_STD_FORWARD)
        template <class... Args>
        std::pair<iterator, bool> emplace(Args&&...);
        template <class... Args>
        iterator emplace_hint(const_iterator, Args&&...);
#else

        #if !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x5100))
        std::pair<iterator, bool> emplace(value_type const& = value_type());
        iterator emplace_hint(const_iterator, value_type const& = value_type());
        #endif

#define BOOST_UNORDERED_EMPLACE(z, n, _)                                       \
            template <                                                         \
                BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                            \
            >                                                                  \
            std::pair<iterator, bool> emplace(                                 \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                          \
            );                                                                 \
                                                                               \
            template <                                                         \
                BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                            \
            >                                                                  \
            iterator emplace_hint(const_iterator,                              \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                          \
            );

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_EMPLACE, _)

#undef BOOST_UNORDERED_EMPLACE

#endif

        std::pair<iterator, bool> insert(const value_type&);
        iterator insert(const_iterator, const value_type&);
        template <class InputIt> void insert(InputIt, InputIt);

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
        void insert(std::initializer_list<value_type>);
#endif

        iterator erase(const_iterator);
        size_type erase(const key_type&);
        iterator erase(const_iterator, const_iterator);
        void quick_erase(const_iterator it) { erase(it); }
        void erase_return_void(const_iterator it) { erase(it); }

        void clear();
        void swap(unordered_map&);

        // observers

        hasher hash_function() const;
        key_equal key_eq() const;

        mapped_type& operator[](const key_type&);
        mapped_type& at(const key_type&);
        mapped_type const& at(const key_type&) const;

        // lookup

        iterator find(const key_type&);
        const_iterator find(const key_type&) const;

        template <class CompatibleKey, class CompatibleHash,
            class CompatiblePredicate>
        iterator find(
                CompatibleKey const&,
                CompatibleHash const&,
                CompatiblePredicate const&);

        template <class CompatibleKey, class CompatibleHash,
            class CompatiblePredicate>
        const_iterator find(
                CompatibleKey const&,
                CompatibleHash const&,
                CompatiblePredicate const&) const;

        size_type count(const key_type&) const;

        std::pair<iterator, iterator>
        equal_range(const key_type&);
        std::pair<const_iterator, const_iterator>
        equal_range(const key_type&) const;

        // bucket interface

        size_type bucket_count() const
        {
            return table_.bucket_count_;
        }

        size_type max_bucket_count() const
        {
            return table_.max_bucket_count();
        }

        size_type bucket_size(size_type n) const;

        size_type bucket(const key_type& k) const
        {
            return table_.hash_function()(k) % table_.bucket_count_;
        }

        local_iterator begin(size_type n)
        {
            return local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        const_local_iterator begin(size_type n) const
        {
            return const_local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        local_iterator end(size_type)
        {
            return local_iterator();
        }

        const_local_iterator end(size_type) const
        {
            return const_local_iterator();
        }

        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }

        // hash policy

        float max_load_factor() const
        {
            return table_.mlf_;
        }

        float load_factor() const;
        void max_load_factor(float);
        void rehash(size_type n);

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
        friend bool operator==<K,T,H,P,A>(
                unordered_map const&, unordered_map const&);
        friend bool operator!=<K,T,H,P,A>(
                unordered_map const&, unordered_map const&);
#endif
    }; // class template unordered_map

    template <class K, class T, class H, class P, class A>
    class unordered_multimap
    {
    public:

        typedef K key_type;
        typedef std::pair<const K, T> value_type;
        typedef T mapped_type;
        typedef H hasher;
        typedef P key_equal;
        typedef A allocator_type;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
    private:
#endif

        typedef BOOST_DEDUCED_TYPENAME
            ::boost::unordered::detail::rebind_wrap<
                allocator_type, value_type>::type
            value_allocator;

        typedef ::boost::unordered::detail::multimap<K, H, P,
            value_allocator> types;
        typedef BOOST_DEDUCED_TYPENAME types::impl table;

        typedef BOOST_DEDUCED_TYPENAME types::node_ptr node_ptr;

    public:

        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::pointer pointer;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::const_pointer const_pointer;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::reference reference;
        typedef BOOST_DEDUCED_TYPENAME
            value_allocator::const_reference const_reference;

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef ::boost::unordered::iterator_detail::cl_iterator<
            value_allocator, false> const_local_iterator;
        typedef ::boost::unordered::iterator_detail::l_iterator<
            value_allocator, false> local_iterator;
        typedef ::boost::unordered::iterator_detail::c_iterator<
            value_allocator, false> const_iterator;
        typedef ::boost::unordered::iterator_detail::iterator<
            value_allocator, false> iterator;

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
    private:
#endif

        table table_;
        
        BOOST_DEDUCED_TYPENAME types::node_ptr const&
            get(const_iterator const& it)
        {
            return ::boost::unordered::detail::iterator_access::get(it);
        }

    public:

        // construct/destroy/copy

        explicit unordered_multimap(
                size_type = ::boost::unordered::detail::default_bucket_count,
                const hasher& = hasher(),
                const key_equal& = key_equal(),
                const allocator_type& = allocator_type());

        explicit unordered_multimap(allocator_type const&);

        unordered_multimap(unordered_multimap const&, allocator_type const&);

        template <class InputIt>
        unordered_multimap(InputIt, InputIt);

        template <class InputIt>
        unordered_multimap(
                InputIt, InputIt,
                size_type,
                const hasher& = hasher(),
                const key_equal& = key_equal());

        template <class InputIt>
        unordered_multimap(
                InputIt, InputIt,
                size_type,
                const hasher&,
                const key_equal&,
                const allocator_type&);

        ~unordered_multimap();

#if !defined(BOOST_NO_RVALUE_REFERENCES)
        unordered_multimap(unordered_multimap const&);
        unordered_multimap(unordered_multimap&&);
        unordered_multimap(unordered_multimap&&, allocator_type const&);
        unordered_multimap& operator=(unordered_multimap const&);
        unordered_multimap& operator=(unordered_multimap&&);
#else
        unordered_multimap(::boost::unordered::detail::move_from<
                unordered_multimap<K,T,H,P,A>
            >);

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0593)
        unordered_multimap& operator=(unordered_multimap);
#endif
#endif

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
        unordered_multimap(
                std::initializer_list<value_type>,
                size_type = ::boost::unordered::detail::default_bucket_count,
                const hasher& = hasher(),
                const key_equal&l = key_equal(),
                const allocator_type& = allocator_type());

        unordered_multimap& operator=(std::initializer_list<value_type>);
#endif

        allocator_type get_allocator() const
        {
            return table_.node_alloc();
        }

        // size and capacity

        bool empty() const
        {
            return table_.size_ == 0;
        }

        size_type size() const
        {
            return table_.size_;
        }

        size_type max_size() const;

        // iterators

        iterator begin()
        {
            return iterator(table_.begin());
        }

        const_iterator begin() const
        {
            return const_iterator(table_.begin());
        }

        iterator end()
        {
            return iterator();
        }

        const_iterator end() const
        {
            return const_iterator();
        }

        const_iterator cbegin() const
        {
            return const_iterator(table_.begin());
        }

        const_iterator cend() const
        {
            return const_iterator();
        }

        // modifiers

#if defined(BOOST_UNORDERED_STD_FORWARD)
        template <class... Args>
        iterator emplace(Args&&...);
        template <class... Args>
        iterator emplace_hint(const_iterator, Args&&...);
#else

        #if !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x5100))
        iterator emplace(value_type const& = value_type());
        iterator emplace_hint(const_iterator, value_type const& = value_type());
        #endif

#define BOOST_UNORDERED_EMPLACE(z, n, _)                                       \
            template <                                                         \
                BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                            \
            >                                                                  \
            iterator emplace(                                                  \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                          \
            );                                                                 \
                                                                               \
            template <                                                         \
                BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                            \
            >                                                                  \
            iterator emplace_hint(const_iterator,                              \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                          \
            );

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_EMPLACE, _)

#undef BOOST_UNORDERED_EMPLACE

#endif

        iterator insert(const value_type&);
        iterator insert(const_iterator, const value_type&);
        template <class InputIt>
        void insert(InputIt, InputIt);

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
        void insert(std::initializer_list<value_type>);
#endif

        iterator erase(const_iterator);
        size_type erase(const key_type&);
        iterator erase(const_iterator, const_iterator);
        void quick_erase(const_iterator position) { erase(position); }
        void erase_return_void(const_iterator position) { erase(position); }

        void clear();
        void swap(unordered_multimap&);

        // observers

        hasher hash_function() const;
        key_equal key_eq() const;

        // lookup

        iterator find(const key_type&);
        const_iterator find(const key_type&) const;

        template <class CompatibleKey, class CompatibleHash,
            class CompatiblePredicate>
        iterator find(
                CompatibleKey const&,
                CompatibleHash const&,
                CompatiblePredicate const&);

        template <class CompatibleKey, class CompatibleHash,
            class CompatiblePredicate>
        const_iterator find(
                CompatibleKey const&,
                CompatibleHash const&,
                CompatiblePredicate const&) const;

        size_type count(const key_type&) const;

        std::pair<iterator, iterator>
        equal_range(const key_type&);
        std::pair<const_iterator, const_iterator>
        equal_range(const key_type&) const;

        // bucket interface

        size_type bucket_count() const
        {
            return table_.bucket_count_;
        }

        size_type max_bucket_count() const
        {
            return table_.max_bucket_count();
        }

        size_type bucket_size(size_type) const;

        size_type bucket(const key_type& k) const
        {
            return table_.hash_function()(k) % table_.bucket_count_;
        }

        local_iterator begin(size_type n)
        {
            return local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        const_local_iterator begin(size_type n) const
        {
            return const_local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        local_iterator end(size_type)
        {
            return local_iterator();
        }

        const_local_iterator end(size_type) const
        {
            return const_local_iterator();
        }

        const_local_iterator cbegin(size_type n) const
        {
            return const_local_iterator(
                table_.bucket_begin(n), n, table_.bucket_count_);
        }

        const_local_iterator cend(size_type) const
        {
            return const_local_iterator();
        }

        // hash policy

        float max_load_factor() const
        {
            return table_.mlf_;
        }

        float load_factor() const;
        void max_load_factor(float);
        void rehash(size_type);

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0582)
        friend bool operator==<K,T,H,P,A>(
            unordered_multimap const&, unordered_multimap const&);
        friend bool operator!=<K,T,H,P,A>(
            unordered_multimap const&, unordered_multimap const&);
#endif
    }; // class template unordered_multimap

////////////////////////////////////////////////////////////////////////////////

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            size_type n, const hasher &hf, const key_equal &eql,
            const allocator_type &a)
      : table_(n, hf, eql, a)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(allocator_type const& a)
      : table_(::boost::unordered::detail::default_bucket_count,
            hasher(), key_equal(), a)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            unordered_map const& other, allocator_type const& a)
      : table_(other.table_, a)
    {
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(InputIt f, InputIt l)
      : table_(::boost::unordered::detail::initial_size(f, l),
        hasher(), key_equal(), allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql)
      : table_(::boost::unordered::detail::initial_size(f, l, n),
            hf, eql, allocator_type())
    {
        table_.insert_range(f, l);
    }
    
    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_map<K,T,H,P,A>::unordered_map(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql,
            const allocator_type &a)
      : table_(::boost::unordered::detail::initial_size(f, l, n), hf, eql, a)
    {
        table_.insert_range(f, l);
    }
    
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::~unordered_map() {}

#if !defined(BOOST_NO_RVALUE_REFERENCES)
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(unordered_map const& other)
      : table_(other.table_)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(unordered_map&& other)
      : table_(other.table_, ::boost::unordered::detail::move_tag())
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            unordered_map&& other, allocator_type const& a)
      : table_(other.table_, a, ::boost::unordered::detail::move_tag())
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>& unordered_map<K,T,H,P,A>::
        operator=(unordered_map const& x)
    {
        table_ = x.table_;
        return *this;
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>& unordered_map<K,T,H,P,A>::
        operator=(unordered_map&& x)
    {
        table_.move(x.table_);
        return *this;
    }
#else
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            ::boost::unordered::detail::move_from<unordered_map<K,T,H,P,A> >
                other)
      : table_(other.source.table_, ::boost::unordered::detail::move_tag())
    {
    }

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0593)
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>& unordered_map<K,T,H,P,A>::
        operator=(unordered_map x)
    {
        table_.move(x.table_);
        return *this;
    }
#endif
#endif

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>::unordered_map(
            std::initializer_list<value_type> list, size_type n,
            const hasher &hf, const key_equal &eql, const allocator_type &a)
      : table_(
            ::boost::unordered::detail::initial_size(
                list.begin(), list.end(), n),
            hf, eql, a)
    {
        table_.insert_range(list.begin(), list.end());
    }

    template <class K, class T, class H, class P, class A>
    unordered_map<K,T,H,P,A>& unordered_map<K,T,H,P,A>::operator=(
            std::initializer_list<value_type> list)
    {
        table_.clear();
        table_.insert_range(list.begin(), list.end());
        return *this;
    }
#endif

    // size and capacity

    template <class K, class T, class H, class P, class A>
    std::size_t unordered_map<K,T,H,P,A>::max_size() const
    {
        return table_.max_size();
    }

    // modifiers

#if defined(BOOST_UNORDERED_STD_FORWARD)
    template <class K, class T, class H, class P, class A>
    template <class... Args>
    std::pair<BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator, bool>
        unordered_map<K,T,H,P,A>::emplace(Args&&... args)
    {
        return BOOST_UNORDERED_PAIR_CAST(iterator, bool,
            table_.emplace(std::forward<Args>(args)...));
    }

    template <class K, class T, class H, class P, class A>
    template <class... Args>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::emplace_hint(const_iterator, Args&&... args)
    {
        return iterator(table_.emplace(std::forward<Args>(args)...).first);
    }
#else

#if !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x5100))
    template <class K, class T, class H, class P, class A>
    std::pair<BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator, bool>
        unordered_map<K,T,H,P,A>::emplace(value_type const& v)
    {
        return BOOST_UNORDERED_PAIR_CAST(iterator, bool, table_.emplace(v));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::emplace_hint(
            const_iterator, value_type const& v)
    {
        return iterator(table_.emplace(v).first);
    }
#endif

#define BOOST_UNORDERED_EMPLACE(z, n, _)                                    \
        template <class K, class T, class H, class P, class A>              \
        template <                                                          \
            BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                             \
        >                                                                   \
        std::pair<                                                          \
                BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator,  \
                bool>                                                       \
            unordered_map<K,T,H,P,A>::emplace(                              \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                      \
        {                                                                   \
            return                                                          \
                BOOST_UNORDERED_PAIR_CAST(iterator, bool,                   \
                    table_.emplace(                                         \
                        BOOST_UNORDERED_CALL_PARAMS(z, n)));                \
        }                                                                   \
                                                                            \
        template <class K, class T, class H, class P, class A>              \
        template <                                                          \
            BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                             \
        >                                                                   \
        BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator           \
            unordered_map<K,T,H,P,A>::emplace_hint(                         \
                const_iterator,                                             \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                       \
        )                                                                   \
        {                                                                   \
            return iterator(table_.emplace(                                 \
                BOOST_UNORDERED_CALL_PARAMS(z, n)).first);                  \
        }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
        BOOST_UNORDERED_EMPLACE, _)

#undef BOOST_UNORDERED_EMPLACE

#endif

    template <class K, class T, class H, class P, class A>
    std::pair<BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator, bool>
        unordered_map<K,T,H,P,A>::insert(const value_type& obj)
    {
        return BOOST_UNORDERED_PAIR_CAST(iterator, bool, table_.insert(obj));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::insert(const_iterator, const value_type& obj)
    {
        return iterator(table_.emplace(obj).first);
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    void unordered_map<K,T,H,P,A>::insert(InputIt first, InputIt last)
    {
        table_.insert_range(first, last);
    }

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
    template <class K, class T, class H, class P, class A>
    void unordered_map<K,T,H,P,A>::insert(
            std::initializer_list<value_type> list)
    {
        table_.insert_range(list.begin(), list.end());
    }
#endif

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::erase(const_iterator position)
    {
        return iterator(table_.erase(get(position)));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::size_type
        unordered_map<K,T,H,P,A>::erase(const key_type& k)
    {
        return table_.erase_key(k);
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::erase(
            const_iterator first, const_iterator last)
    {
        return iterator(table_.erase_range(get(first), get(last)));
    }

    template <class K, class T, class H, class P, class A>
    void unordered_map<K,T,H,P,A>::clear()
    {
        table_.clear();
    }

    template <class K, class T, class H, class P, class A>
    void unordered_map<K,T,H,P,A>::swap(unordered_map& other)
    {
        table_.swap(other.table_);
    }

    // observers

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::hasher
        unordered_map<K,T,H,P,A>::hash_function() const
    {
        return table_.hash_function();
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::key_equal
        unordered_map<K,T,H,P,A>::key_eq() const
    {
        return table_.key_eq();
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::mapped_type&
        unordered_map<K,T,H,P,A>::operator[](const key_type &k)
    {
        return table_[k].second;
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::mapped_type&
        unordered_map<K,T,H,P,A>::at(const key_type& k)
    {
        return table_.at(k).second;
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::mapped_type const&
        unordered_map<K,T,H,P,A>::at(const key_type& k) const
    {
        return table_.at(k).second;
    }

    // lookup

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::find(const key_type& k)
    {
        return iterator(table_.find_node(k));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::const_iterator
        unordered_map<K,T,H,P,A>::find(const key_type& k) const
    {
        return const_iterator(table_.find_node(k));
    }

    template <class K, class T, class H, class P, class A>
    template <class CompatibleKey, class CompatibleHash,
        class CompatiblePredicate>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator
        unordered_map<K,T,H,P,A>::find(
            CompatibleKey const& k,
            CompatibleHash const& hash,
            CompatiblePredicate const& eq)
    {
        return iterator(table_.generic_find_node(k, hash, eq));
    }

    template <class K, class T, class H, class P, class A>
    template <class CompatibleKey, class CompatibleHash,
        class CompatiblePredicate>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::const_iterator
        unordered_map<K,T,H,P,A>::find(
            CompatibleKey const& k,
            CompatibleHash const& hash,
            CompatiblePredicate const& eq) const
    {
        return const_iterator(table_.generic_find_node(k, hash, eq));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::size_type
        unordered_map<K,T,H,P,A>::count(const key_type& k) const
    {
        return table_.count(k);
    }

    template <class K, class T, class H, class P, class A>
    std::pair<
            BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator,
            BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::iterator>
        unordered_map<K,T,H,P,A>::equal_range(const key_type& k)
    {
        return BOOST_UNORDERED_PAIR_CAST(iterator, iterator,
            table_.equal_range(k));
    }

    template <class K, class T, class H, class P, class A>
    std::pair<
            BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::const_iterator,
            BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::const_iterator>
        unordered_map<K,T,H,P,A>::equal_range(const key_type& k) const
    {
        return BOOST_UNORDERED_PAIR_CAST(const_iterator, const_iterator,
            table_.equal_range(k));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_map<K,T,H,P,A>::size_type
        unordered_map<K,T,H,P,A>::bucket_size(size_type n) const
    {
        return table_.bucket_size(n);
    }

    // hash policy

    template <class K, class T, class H, class P, class A>
    float unordered_map<K,T,H,P,A>::load_factor() const
    {
        return table_.load_factor();
    }

    template <class K, class T, class H, class P, class A>
    void unordered_map<K,T,H,P,A>::max_load_factor(float m)
    {
        table_.max_load_factor(m);
    }

    template <class K, class T, class H, class P, class A>
    void unordered_map<K,T,H,P,A>::rehash(size_type n)
    {
        table_.rehash(n);
    }

    template <class K, class T, class H, class P, class A>
    inline bool operator==(
            unordered_map<K,T,H,P,A> const& m1,
            unordered_map<K,T,H,P,A> const& m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_map<K,T,H,P,A> x; };
#endif
        return m1.table_.equals(m2.table_);
    }

    template <class K, class T, class H, class P, class A>
    inline bool operator!=(
            unordered_map<K,T,H,P,A> const& m1,
            unordered_map<K,T,H,P,A> const& m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_map<K,T,H,P,A> x; };
#endif
        return !m1.table_.equals(m2.table_);
    }

    template <class K, class T, class H, class P, class A>
    inline void swap(
            unordered_map<K,T,H,P,A> &m1,
            unordered_map<K,T,H,P,A> &m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_map<K,T,H,P,A> x; };
#endif
        m1.swap(m2);
    }

////////////////////////////////////////////////////////////////////////////////

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            size_type n, const hasher &hf, const key_equal &eql,
            const allocator_type &a)
      : table_(n, hf, eql, a)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(allocator_type const& a)
      : table_(::boost::unordered::detail::default_bucket_count,
            hasher(), key_equal(), a)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            unordered_multimap const& other, allocator_type const& a)
      : table_(other.table_, a)
    {
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(InputIt f, InputIt l)
      : table_(::boost::unordered::detail::initial_size(f, l),
        hasher(), key_equal(), allocator_type())
    {
        table_.insert_range(f, l);
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql)
      : table_(::boost::unordered::detail::initial_size(f, l, n),
            hf, eql, allocator_type())
    {
        table_.insert_range(f, l);
    }
    
    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            InputIt f, InputIt l,
            size_type n,
            const hasher &hf,
            const key_equal &eql,
            const allocator_type &a)
      : table_(::boost::unordered::detail::initial_size(f, l, n), hf, eql, a)
    {
        table_.insert_range(f, l);
    }
    
    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::~unordered_multimap() {}

#if !defined(BOOST_NO_RVALUE_REFERENCES)
    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            unordered_multimap const& other)
      : table_(other.table_)
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            unordered_multimap&& other)
      : table_(other.table_, ::boost::unordered::detail::move_tag())
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            unordered_multimap&& other, allocator_type const& a)
      : table_(other.table_, a, ::boost::unordered::detail::move_tag())
    {
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>& unordered_multimap<K,T,H,P,A>::
        operator=(unordered_multimap const& x)
    {
        table_ = x.table_;
        return *this;
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>& unordered_multimap<K,T,H,P,A>::
        operator=(unordered_multimap&& x)
    {
        table_.move(x.table_);
        return *this;
    }

#else

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            ::boost::unordered::detail::move_from<
                unordered_multimap<K,T,H,P,A> > other)
      : table_(other.source.table_, ::boost::unordered::detail::move_tag())
    {
    }

#if !BOOST_WORKAROUND(__BORLANDC__, < 0x0593)
    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>& unordered_multimap<K,T,H,P,A>::
        operator=(unordered_multimap x)
    {
        table_.move(x.table_);
        return *this;
    }
#endif
#endif

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>::unordered_multimap(
            std::initializer_list<value_type> list, size_type n,
            const hasher &hf, const key_equal &eql, const allocator_type &a)
      : table_(
            ::boost::unordered::detail::initial_size(
                list.begin(), list.end(), n),
            hf, eql, a)
    {
        table_.insert_range(list.begin(), list.end());
    }

    template <class K, class T, class H, class P, class A>
    unordered_multimap<K,T,H,P,A>& unordered_multimap<K,T,H,P,A>::operator=(
            std::initializer_list<value_type> list)
    {
        table_.clear();
        table_.insert_range(list.begin(), list.end());
        return *this;
    }
#endif

    // size and capacity

    template <class K, class T, class H, class P, class A>
    std::size_t unordered_multimap<K,T,H,P,A>::max_size() const
    {
        return table_.max_size();
    }

    // modifiers

#if defined(BOOST_UNORDERED_STD_FORWARD)

    template <class K, class T, class H, class P, class A>
    template <class... Args>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::emplace(Args&&... args)
    {
        return iterator(table_.emplace(std::forward<Args>(args)...));
    }

    template <class K, class T, class H, class P, class A>
    template <class... Args>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::emplace_hint(
            const_iterator, Args&&... args)
    {
        return iterator(table_.emplace(std::forward<Args>(args)...));
    }

#else

#if !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x5100))
    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::emplace(value_type const& v)
    {
        return iterator(table_.emplace(v));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::emplace_hint(
            const_iterator, value_type const& v)
    {
        return iterator(table_.emplace(v));
    }
#endif

#define BOOST_UNORDERED_EMPLACE(z, n, _)                                    \
        template <class K, class T, class H, class P, class A>              \
        template <                                                          \
            BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                             \
        >                                                                   \
        BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator      \
            unordered_multimap<K,T,H,P,A>::emplace(                         \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                      \
        {                                                                   \
            return iterator(table_.emplace(                                 \
                BOOST_UNORDERED_CALL_PARAMS(z, n)));                        \
        }                                                                   \
                                                                            \
        template <class K, class T, class H, class P, class A>              \
        template <                                                          \
            BOOST_UNORDERED_TEMPLATE_ARGS(z, n)                             \
        >                                                                   \
        BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator      \
            unordered_multimap<K,T,H,P,A>::emplace_hint(                    \
                const_iterator,                                             \
                BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                      \
        {                                                                   \
            return iterator(table_.emplace(                                 \
                BOOST_UNORDERED_CALL_PARAMS(z, n)));                        \
        }

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
        BOOST_UNORDERED_EMPLACE, _)

#undef BOOST_UNORDERED_EMPLACE

#endif

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::insert(const value_type& obj)
    {
        return iterator(table_.emplace(obj));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::insert(
            const_iterator, const value_type& obj)
    {
        return iterator(table_.emplace(obj));
    }

    template <class K, class T, class H, class P, class A>
    template <class InputIt>
    void unordered_multimap<K,T,H,P,A>::insert(InputIt first, InputIt last)
    {
        table_.insert_range(first, last);
    }

#if !defined(BOOST_NO_0X_HDR_INITIALIZER_LIST)
    template <class K, class T, class H, class P, class A>
    void unordered_multimap<K,T,H,P,A>::insert(
            std::initializer_list<value_type> list)
    {
        table_.insert_range(list.begin(), list.end());
    }
#endif

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::erase(const_iterator position)
    {
        return iterator(table_.erase(get(position)));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::size_type
        unordered_multimap<K,T,H,P,A>::erase(const key_type& k)
    {
        return table_.erase_key(k);
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::erase(
            const_iterator first, const_iterator last)
    {
        return iterator(table_.erase_range(get(first), get(last)));
    }

    template <class K, class T, class H, class P, class A>
    void unordered_multimap<K,T,H,P,A>::clear()
    {
        table_.clear();
    }

    template <class K, class T, class H, class P, class A>
    void unordered_multimap<K,T,H,P,A>::swap(unordered_multimap& other)
    {
        table_.swap(other.table_);
    }

    // observers

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::hasher
        unordered_multimap<K,T,H,P,A>::hash_function() const
    {
        return table_.hash_function();
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::key_equal
        unordered_multimap<K,T,H,P,A>::key_eq() const
    {
        return table_.key_eq();
    }

    // lookup

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::find(const key_type& k)
    {
        return iterator(table_.find_node(k));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::const_iterator
        unordered_multimap<K,T,H,P,A>::find(const key_type& k) const
    {
        return const_iterator(table_.find_node(k));
    }

    template <class K, class T, class H, class P, class A>
    template <class CompatibleKey, class CompatibleHash,
        class CompatiblePredicate>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator
        unordered_multimap<K,T,H,P,A>::find(
            CompatibleKey const& k,
            CompatibleHash const& hash,
            CompatiblePredicate const& eq)
    {
        return iterator(table_.generic_find_node(k, hash, eq));
    }

    template <class K, class T, class H, class P, class A>
    template <class CompatibleKey, class CompatibleHash,
        class CompatiblePredicate>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::const_iterator
        unordered_multimap<K,T,H,P,A>::find(
            CompatibleKey const& k,
            CompatibleHash const& hash,
            CompatiblePredicate const& eq) const
    {
        return const_iterator(table_.generic_find_node(k, hash, eq));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::size_type
        unordered_multimap<K,T,H,P,A>::count(const key_type& k) const
    {
        return table_.count(k);
    }

    template <class K, class T, class H, class P, class A>
    std::pair<
            BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator,
            BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::iterator>
        unordered_multimap<K,T,H,P,A>::equal_range(const key_type& k)
    {
        return BOOST_UNORDERED_PAIR_CAST(iterator, iterator,
            table_.equal_range(k));
    }

    template <class K, class T, class H, class P, class A>
    std::pair<
            BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::const_iterator,
            BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::const_iterator>
        unordered_multimap<K,T,H,P,A>::equal_range(const key_type& k) const
    {
        return BOOST_UNORDERED_PAIR_CAST(const_iterator, const_iterator,
            table_.equal_range(k));
    }

    template <class K, class T, class H, class P, class A>
    BOOST_DEDUCED_TYPENAME unordered_multimap<K,T,H,P,A>::size_type
        unordered_multimap<K,T,H,P,A>::bucket_size(size_type n) const
    {
        return table_.bucket_size(n);
    }

    // hash policy

    template <class K, class T, class H, class P, class A>
    float unordered_multimap<K,T,H,P,A>::load_factor() const
    {
        return table_.load_factor();
    }

    template <class K, class T, class H, class P, class A>
    void unordered_multimap<K,T,H,P,A>::max_load_factor(float m)
    {
        table_.max_load_factor(m);
    }

    template <class K, class T, class H, class P, class A>
    void unordered_multimap<K,T,H,P,A>::rehash(size_type n)
    {
        table_.rehash(n);
    }

    template <class K, class T, class H, class P, class A>
    inline bool operator==(
            unordered_multimap<K,T,H,P,A> const& m1,
            unordered_multimap<K,T,H,P,A> const& m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_multimap<K,T,H,P,A> x; };
#endif
        return m1.table_.equals(m2.table_);
    }

    template <class K, class T, class H, class P, class A>
    inline bool operator!=(
            unordered_multimap<K,T,H,P,A> const& m1,
            unordered_multimap<K,T,H,P,A> const& m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_multimap<K,T,H,P,A> x; };
#endif
        return !m1.table_.equals(m2.table_);
    }

    template <class K, class T, class H, class P, class A>
    inline void swap(
            unordered_multimap<K,T,H,P,A> &m1,
            unordered_multimap<K,T,H,P,A> &m2)
    {
#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x0613))
        struct dummy { unordered_multimap<K,T,H,P,A> x; };
#endif
        m1.swap(m2);
    }


} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_UNORDERED_UNORDERED_MAP_HPP_INCLUDED
