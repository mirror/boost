
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_INSERT_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_INSERT_HPP_INCLUDED

#include <boost/unordered/detail/table.hpp>
#include <boost/unordered/detail/extract_key.hpp>

namespace boost { namespace unordered_detail {

    ////////////////////////////////////////////////////////////////////////////
    // A couple of convenience methods for adding nodes.

    // H = Has Func
    // P = Predicate
    // A = Value Allocator
    // K = Key Extractor

    template <class H, class P, class A, class K>
    class hash_unique_table :
        public hash_table<H, P, A, boost::unordered_detail::ungrouped, K>
        
    {
    public:
        typedef H hasher;
        typedef P key_equal;
        typedef A value_allocator;
        typedef K key_extractor;

        typedef hash_table<H, P, A, boost::unordered_detail::ungrouped, K> table;
        typedef hash_node_constructor<A, boost::unordered_detail::ungrouped> node_constructor;

        typedef BOOST_DEDUCED_TYPENAME table::key_type key_type;
        typedef BOOST_DEDUCED_TYPENAME table::value_type value_type;
        typedef BOOST_DEDUCED_TYPENAME table::node node;
        typedef BOOST_DEDUCED_TYPENAME table::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME table::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME table::iterator_base iterator_base;
        typedef BOOST_DEDUCED_TYPENAME table::extractor extractor;

        // Constructors

        hash_unique_table(std::size_t n, hasher const& hf, key_equal const& eq, value_allocator const& a)
            : table(n, hf, eq, a) {}
        hash_unique_table(hash_unique_table const& x)
            : table(x) {}
        hash_unique_table(hash_unique_table const& x, value_allocator const& a)
            : table(x, a) {}
        hash_unique_table(hash_unique_table& x, move_tag m)
            : table(x, m) {}
        hash_unique_table(hash_unique_table& x, value_allocator const& a, move_tag m)
            : table(x, a, m) {}
        ~hash_unique_table() {}

        // Insert methods

        std::pair<iterator_base, bool> emplace_impl_with_node(node_constructor& a);
        value_type& operator[](key_type const& k);

        // equals

        bool equals(hash_unique_table const&) const;
        static bool group_equals(node_ptr it1, node_ptr it2, set_extractor*);
        static bool group_equals(node_ptr it1, node_ptr it2, map_extractor*);

        inline node_ptr add_node(node_constructor& a, bucket_ptr bucket)
        {
            node_ptr n = a.release();
            node::add_to_bucket(n, *bucket);
            ++this->size_;
            if(bucket < this->cached_begin_bucket_) this->cached_begin_bucket_ = bucket;
            return n;
        }
        
#if defined(BOOST_UNORDERED_STD_FORWARD)

        // Emplace (unique keys)
        // (I'm using an overloaded emplace for both 'insert' and 'emplace')

        // if hash function throws, basic exception safety
        // strong otherwise
        template<class... Args>
        std::pair<iterator_base, bool> emplace(Args&&... args)
        {
            return emplace_impl(
                extractor::extract(std::forward<Args>(args)...),
                std::forward<Args>(args)...);
        }

        // Insert (unique keys)
        // (I'm using an overloaded emplace for both 'insert' and 'emplace')
        // I'm just ignoring hints here for now.

        // if hash function throws, basic exception safety
        // strong otherwise
        template<class... Args>
        iterator_base emplace_hint(iterator_base const&, Args&&... args)
        {
            return emplace_impl(
                extractor::extract(std::forward<Args>(args)...),
                std::forward<Args>(args)...).first;
        }

        template<class... Args>
        std::pair<iterator_base, bool> emplace_impl(key_type const& k, Args&&... args)
        {
            // No side effects in this initial code
            std::size_t hash_value = this->hash_function()(k);
            bucket_ptr bucket = this->bucket_ptr_from_hash(hash_value);
            node_ptr pos = find_iterator(bucket, k);

            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                // Found an existing key, return it (no throw).
                return std::pair<iterator_base, bool>(
                    iterator_base(bucket, pos), false);

            } else {
                // Doesn't already exist, add to bucket.
                // Side effects only in this block.

                // Create the node before rehashing in case it throws an
                // exception (need strong safety in such a case).
                node_constructor a(*this);
                a.construct(std::forward<Args>(args)...);

                // reserve has basic exception safety if the hash function
                // throws, strong otherwise.
                if(reserve_for_insert(this->size_ + 1))
                    bucket = this->bucket_ptr_from_hash(hash_value);

                // Nothing after this point can throw.

                return std::pair<iterator_base, bool>(iterator_base(bucket,
                    add_node(a, bucket)), true);
            }
        }

        template<class... Args>
        std::pair<iterator_base, bool> emplace_impl(no_key, Args&&... args)
        {
            // Construct the node regardless - in order to get the key.
            // It will be discarded if it isn't used
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);
            return emplace_impl_with_node(a);
        }
#else
        template <class Arg0>
        std::pair<iterator_base, bool> emplace(Arg0 const& arg0)
        {
            return emplace_impl(extractor::extract(arg0), arg0);
        }

        template <class Arg0>
        iterator_base emplace_hint(iterator_base const&, Arg0 const& arg0)
        {
            return emplace_impl(extractor::extract(arg0), arg0).first;
        }

#define BOOST_UNORDERED_INSERT_IMPL(z, n, _)                                    \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        std::pair<iterator_base, bool> emplace(                                 \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                                \
        )                                                                       \
        {                                                                       \
            return emplace_impl(extractor::extract(arg0, arg1),                 \
                BOOST_UNORDERED_CALL_PARAMS(z, n));                             \
        }                                                                       \
                                                                                \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        iterator_base emplace_hint(iterator_base const& it,                     \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                                \
        )                                                                       \
        {                                                                       \
            return emplace_impl(extractor::extract(arg0, arg1),                 \
                BOOST_UNORDERED_CALL_PARAMS(z, n)).first;                       \
        }                                                                       \
        BOOST_UNORDERED_INSERT_IMPL2(z, n, _)

#define BOOST_UNORDERED_INSERT_IMPL2(z, n, _)                                   \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        std::pair<iterator_base, bool> emplace_impl(key_type const& k,          \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                                \
        )                                                                       \
        {                                                                       \
            std::size_t hash_value = this->hash_function()(k);                  \
            bucket_ptr bucket                                                   \
                = this->bucket_ptr_from_hash(hash_value);                       \
            node_ptr pos = find_iterator(bucket, k);                            \
                                                                                \
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {                            \
                return std::pair<iterator_base, bool>(                          \
                    iterator_base(bucket, pos), false);                         \
            } else {                                                            \
                node_constructor a(*this);                                      \
                a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));                 \
                                                                                \
                if(reserve_for_insert(this->size_ + 1))                         \
                    bucket = this->bucket_ptr_from_hash(hash_value);            \
                                                                                \
                return std::pair<iterator_base, bool>(iterator_base(bucket,     \
                    add_node(a, bucket)), true);                                \
            }                                                                   \
        }                                                                       \
                                                                                \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        std::pair<iterator_base, bool> emplace_impl(no_key,                     \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                               \
        {                                                                       \
            node_constructor a(*this);                                          \
            a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));                     \
            return emplace_impl_with_node(a);                                   \
        }

        BOOST_UNORDERED_INSERT_IMPL2(1, 1, _)

        BOOST_PP_REPEAT_FROM_TO(2, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_INSERT_IMPL, _)

#undef BOOST_UNORDERED_INSERT_IMPL

#endif

        // if hash function throws, or inserting > 1 element, basic exception safety
        // strong otherwise
        template <class InputIterator>
        void insert_range(InputIterator i, InputIterator j)
        {
            if(i != j)
                return insert_range_impl(extractor::extract(*i), i, j);
        }
        
        template <class InputIterator>
        void insert_range_impl(key_type const&, InputIterator i, InputIterator j)
        {
            node_constructor a(*this);

            for (; i != j; ++i) {
                // No side effects in this initial code
                std::size_t hash_value = this->hash_function()(extractor::extract(*i));
                bucket_ptr bucket = this->bucket_ptr_from_hash(hash_value);
                node_ptr pos = find_iterator(bucket, extractor::extract(*i));

                if (!BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                    // Doesn't already exist, add to bucket.
                    // Side effects only in this block.

                    // Create the node before rehashing in case it throws an
                    // exception (need strong safety in such a case).
                    a.construct(*i);

                    // reserve has basic exception safety if the hash function
                    // throws, strong otherwise.
                    if(this->size_ + 1 >= this->max_load_) {
                        reserve_for_insert(this->size_ + insert_size(i, j));
                        bucket = this->bucket_ptr_from_hash(hash_value);
                    }

                    // Nothing after this point can throw.
                    add_node(a, bucket);
                }
            }
        }

        template <class InputIterator>
        void insert_range_impl(no_key, InputIterator i, InputIterator j)
        {
            node_constructor a(*this);

            for (; i != j; ++i) {
                // No side effects in this initial code
                a.construct(*i);
                emplace_impl_with_node(a);
            }
        }
    };

    template <class H, class P, class A, class K>
    class hash_equivalent_table :
        public hash_table<H, P, A, boost::unordered_detail::grouped, K>
        
    {
    public:
        typedef H hasher;
        typedef P key_equal;
        typedef A value_allocator;
        typedef K key_extractor;

        typedef hash_table<H, P, A, boost::unordered_detail::grouped, K> table;
        typedef hash_node_constructor<A, boost::unordered_detail::grouped> node_constructor;

        typedef BOOST_DEDUCED_TYPENAME table::key_type key_type;
        typedef BOOST_DEDUCED_TYPENAME table::value_type value_type;
        typedef BOOST_DEDUCED_TYPENAME table::node node;
        typedef BOOST_DEDUCED_TYPENAME table::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME table::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME table::iterator_base iterator_base;
        typedef BOOST_DEDUCED_TYPENAME table::extractor extractor;

        // Constructors

        hash_equivalent_table(std::size_t n, hasher const& hf, key_equal const& eq, value_allocator const& a)
            : table(n, hf, eq, a) {}
        hash_equivalent_table(hash_equivalent_table const& x)
            : table(x) {}
        hash_equivalent_table(hash_equivalent_table const& x, value_allocator const& a)
            : table(x, a) {}
        hash_equivalent_table(hash_equivalent_table& x, move_tag m)
            : table(x, m) {}
        hash_equivalent_table(hash_equivalent_table& x, value_allocator const& a, move_tag m)
            : table(x, a, m) {}
        ~hash_equivalent_table() {}

        // Insert methods

        iterator_base emplace_impl(node_constructor& a);
        iterator_base emplace_hint_impl(iterator_base const& it, node_constructor& a);
        void emplace_impl_no_rehash(node_constructor& a);

        // equals

        bool equals(hash_equivalent_table const&) const;
        static bool group_equals(node_ptr it1, node_ptr it2, set_extractor*);
        static bool group_equals(node_ptr it1, node_ptr it2, map_extractor*);

        inline node_ptr add_node(node_constructor& a, bucket_ptr bucket, node_ptr pos)
        {
            node_ptr n = a.release();
            if(BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                node::add_after_node(n, pos);                
            }
            else {
                node::add_to_bucket(n, *bucket);
                if(bucket < this->cached_begin_bucket_) this->cached_begin_bucket_ = bucket;
            }
            ++this->size_;
            return n;
        }

    public:

        // Insert functions
        //
        // basic exception safety, if hash function throws
        // strong otherwise.

#if defined(BOOST_UNORDERED_STD_FORWARD)

        // Emplace (equivalent key containers)
        // (I'm using an overloaded emplace for both 'insert' and 'emplace')

        // if hash function throws, basic exception safety
        // strong otherwise
        template <class... Args>
        iterator_base emplace(Args&&... args)
        {
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);

            return emplace_impl(a);
        }

        // Emplace (equivalent key containers)
        // (I'm using an overloaded emplace for both 'insert' and 'emplace')

        // if hash function throws, basic exception safety
        // strong otherwise
        template <class... Args>
        iterator_base emplace_hint(iterator_base const& it, Args&&... args)
        {
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);

            return emplace_hint_impl(it, a);
        }

#else

#define BOOST_UNORDERED_INSERT_IMPL(z, n, _)                                    \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        iterator_base emplace(                                                  \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                                \
        )                                                                       \
        {                                                                       \
            node_constructor a(*this);                                          \
            a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));                     \
            return emplace_impl(a);                                             \
        }                                                                       \
                                                                                \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                          \
        iterator_base emplace_hint(iterator_base const& it,                     \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n)                                \
        )                                                                       \
        {                                                                       \
            node_constructor a(*this);                                          \
            a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));                     \
            return emplace_hint_impl(it, a);                                    \
        }

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_INSERT_IMPL, _)

#undef BOOST_UNORDERED_INSERT_IMPL
#endif

        // Insert from iterator range (equivalent key containers)

    private:

        // if hash function throws, or inserting > 1 element, basic exception safety
        // strong otherwise
        template <class I>
        void insert_for_range(I i, I j, forward_traversal_tag)
        {
            std::size_t distance = unordered_detail::distance(i, j);
            if(distance == 1) {
                emplace(*i);
            }
            else {
                // Only require basic exception safety here
                reserve_for_insert(this->size_ + distance);
                node_constructor a(*this);

                for (; i != j; ++i) {
                    a.construct(*i);
                    emplace_impl_no_rehash(a);
                }
            }
        }

        // if hash function throws, or inserting > 1 element, basic exception safety
        // strong otherwise
        template <class I>
        void insert_for_range(I i, I j,
                boost::incrementable_traversal_tag)
        {
            node_constructor a(*this);
            for (; i != j; ++i) {
                a.construct(*i);
                emplace_impl(a);
            }
        }

    public:

        // if hash function throws, or inserting > 1 element, basic exception safety
        // strong otherwise
        template <class I>
        void insert_range(I i, I j)
        {
            BOOST_DEDUCED_TYPENAME boost::iterator_traversal<I>::type
                iterator_traversal_tag;
            insert_for_range(i, j, iterator_traversal_tag);
        }
    };

    ////////////////////////////////////////////////////////////////////////////
    // Unique insert methods

    template <class H, class P, class A, class K>
    std::pair<
        BOOST_DEDUCED_TYPENAME hash_unique_table<H, P, A, K>::iterator_base,
        bool>
    hash_unique_table<H, P, A, K>
        ::emplace_impl_with_node(node_constructor& a)
    {
        // No side effects in this initial code
        key_type const& k = extractor::extract(a.get()->value());
        std::size_t hash_value = this->hash_function()(k);
        bucket_ptr bucket = this->bucket_ptr_from_hash(hash_value);
        node_ptr pos = find_iterator(bucket, k);
        
        if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
            // Found an existing key, return it (no throw).
            return std::pair<iterator_base, bool>(
                iterator_base(bucket, pos), false);
        } else {
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(reserve_for_insert(this->size_ + 1))
                bucket = this->bucket_ptr_from_hash(hash_value);

            // Nothing after this point can throw.

            return std::pair<iterator_base, bool>(iterator_base(bucket,
                add_node(a, bucket)), true);
        }
    }

    // if hash function throws, basic exception safety
    // strong otherwise
    template <class H, class P, class A, class K>
    BOOST_DEDUCED_TYPENAME hash_unique_table<H, P, A, K>::value_type&
        hash_unique_table<H, P, A, K>
            ::operator[](key_type const& k)
    {
        typedef BOOST_DEDUCED_TYPENAME value_type::second_type mapped_type;

        std::size_t hash_value = this->hash_function()(k);
        bucket_ptr bucket = this->bucket_ptr_from_hash(hash_value);
        node_ptr pos = find_iterator(bucket, k);

        if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
            return node::get_value(pos);
        }
        else {
            // Side effects only in this block.

            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct_pair(k, (mapped_type*) 0);

            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(reserve_for_insert(this->size_ + 1))
                bucket = this->bucket_ptr_from_hash(hash_value);

            // Nothing after this point can throw.

            return node::get_value(add_node(a, bucket));
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Insert methods

    template <class H, class P, class A, class K>
    BOOST_DEDUCED_TYPENAME hash_equivalent_table<H, P, A, K>::iterator_base
        hash_equivalent_table<H, P, A, K>
            ::emplace_impl(node_constructor& a)
    {
        key_type const& k = extractor::extract(a.get()->value());
        std::size_t hash_value = this->hash_function()(k);
        bucket_ptr bucket = this->bucket_ptr_from_hash(hash_value);
        node_ptr position = find_iterator(bucket, k);

        // reserve has basic exception safety if the hash function
        // throws, strong otherwise.
        if(reserve_for_insert(this->size_ + 1))
            bucket = this->bucket_ptr_from_hash(hash_value);

        // I'm relying on node_ptr not being invalidated by
        // the rehash here.
        return iterator_base(bucket, add_node(a, bucket, position));
    }
    
    template <class H, class P, class A, class K>
    BOOST_DEDUCED_TYPENAME hash_equivalent_table<H, P, A, K>::iterator_base
        hash_equivalent_table<H, P, A, K>
            ::emplace_hint_impl(iterator_base const& it, node_constructor& a)
    {
        // equal can throw, but with no effects
        if (it.is_end() ||
            !equal(extractor::extract(a.get()->value()), node::get_value(it.get()))) {
            // Use the standard emplace if the iterator doesn't point
            // to a matching key.
            return emplace_impl(a);
        }
        else {
            // Find the first node in the group - so that the node
            // will be added at the end of the group.

            node_ptr start(it.node_);
            while(node::next_group(start) == start)
                start = node::group_prev(start);

            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            bucket_ptr bucket = reserve_for_insert(this->size_ + 1) ?
                get_bucket(this->bucket_index(
                    extractor::extract(a.get()->value()))) : it.bucket_;

            // Nothing after this point can throw

            return iterator_base(bucket, add_node(a, bucket, start));
        }
    }

    template <class H, class P, class A, class K>
    void hash_equivalent_table<H, P, A, K>
            ::emplace_impl_no_rehash(node_constructor& a)
    {
        key_type const& k = extractor::extract(a.get()->value());
        bucket_ptr bucket = this->get_bucket(this->bucket_index(k));
        add_node(a, bucket, find_iterator(bucket, k));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Equalilty check

    template <class H, class P, class A, class K>
    inline bool hash_equivalent_table<H, P, A, K>
        ::group_equals(node_ptr it1, node_ptr it2, set_extractor*)
    {
        return node::group_count(it1) == node::group_count(it2);
    }

    template <class H, class P, class A, class K>
    inline bool hash_equivalent_table<H, P, A, K>
        ::group_equals(node_ptr it1, node_ptr it2, map_extractor*)
    {
        node_ptr end1 = node::next_group(it1);
        node_ptr end2 = node::next_group(it2);

        do {
            if(node::get_value(it1).second != node::get_value(it2).second) return false;
            it1 = next_node(it1);
            it2 = next_node(it2);
        } while(it1 != end1 && it2 != end2);
        return it1 == end1 && it2 == end2;
    }

    template <class H, class P, class A, class K>
    bool hash_equivalent_table<H, P, A, K>
        ::equals(hash_equivalent_table<H, P, A, K> const& other) const
    {
        if(this->size_ != other.size_) return false;

        for(bucket_ptr i = this->cached_begin_bucket_, j = this->buckets_end(); i != j; ++i)
        {
            for(node_ptr it(i->next_); BOOST_UNORDERED_BORLAND_BOOL(it); it = node::next_group(it))
            {
                node_ptr other_pos = other.find_iterator(extractor::extract(node::get_value(it)));
                if(!BOOST_UNORDERED_BORLAND_BOOL(other_pos) ||
                    !group_equals(it, other_pos, (K*)0))
                    return false;
            }
        }

        return true;
    }

    template <class H, class P, class A, class K>
    inline bool hash_unique_table<H, P, A, K>
        ::group_equals(node_ptr, node_ptr, set_extractor*)
    {
        return true;
    }

    template <class H, class P, class A, class K>
    inline bool hash_unique_table<H, P, A, K>
        ::group_equals(node_ptr it1, node_ptr it2, map_extractor*)
    {
        return node::get_value(it1).second == node::get_value(it2).second;
    }

    template <class H, class P, class A, class K>
    bool hash_unique_table<H, P, A, K>
        ::equals(hash_unique_table<H, P, A, K> const& other) const
    {
        if(this->size_ != other.size_) return false;

        for(bucket_ptr i = this->cached_begin_bucket_, j = this->buckets_end(); i != j; ++i)
        {
            for(node_ptr it(i->next_); BOOST_UNORDERED_BORLAND_BOOL(it); it = node::next_group(it))
            {
                node_ptr other_pos = other.find_iterator(extractor::extract(node::get_value(it)));
                if(!BOOST_UNORDERED_BORLAND_BOOL(other_pos) ||
                    !group_equals(it, other_pos, (K*)0))
                    return false;
            }
        }

        return true;
    }

}}

#endif
