
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This contains the basic data structure, apart from the actual values. There's
// no construction or deconstruction here. So this only depends on the pointer
// type.

#ifndef BOOST_UNORDERED_DETAIL_FWD_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_FWD_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/iterator.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/unordered/detail/allocator_helpers.hpp>

// This header defines most of the classes used to implement the unordered
// containers. It doesn't include the insert methods as they require a lot
// of preprocessor metaprogramming - they are in insert.hpp

// Template parameters:
//
// H = Hash Function
// P = Predicate
// A = Value Allocator
// G = Grouped/Ungrouped
// K = Key Extractor

#include <boost/config.hpp>

#if defined(BOOST_HAS_RVALUE_REFS) && defined(BOOST_HAS_VARIADIC_TMPL)
#   if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
        // STLport doesn't have std::forward.
#   else
#       define BOOST_UNORDERED_STD_FORWARD
#   endif
#endif

#if !defined(BOOST_UNORDERED_EMPLACE_LIMIT)
#define BOOST_UNORDERED_EMPLACE_LIMIT 10
#endif

namespace boost { namespace unordered_detail {

    static const float minimum_max_load_factor = 1e-3f;
    static const std::size_t default_initial_bucket_count = 11;
    struct move_tag {};

    // hash_bucket
    
    template <class A>
    class hash_bucket
    {
        hash_bucket& operator=(hash_bucket const&);
    public:
        typedef hash_bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME
            boost::unordered_detail::rebind_wrap<A, bucket>::type
            bucket_allocator;
        typedef BOOST_DEDUCED_TYPENAME bucket_allocator::pointer bucket_ptr;
        typedef bucket_ptr node_ptr;
    
        node_ptr next_;

        hash_bucket() : next_() {}
        
        // Only copy construct when allocating.
        hash_bucket(hash_bucket const& x) : next_()
            { BOOST_ASSERT(!x.next_); }
    };

    template <class A>
    struct ungrouped_node_base : hash_bucket<A> {
        typedef hash_bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME bucket::node_ptr node_ptr;

        ungrouped_node_base() : bucket() {}
        static inline node_ptr& next_group(node_ptr ptr);
        static inline std::size_t group_count(node_ptr ptr);
        static inline void add_to_bucket(node_ptr n, bucket& b);
        static inline void add_group_to_bucket(node_ptr n, bucket& b);
        static inline void add_after_node(node_ptr n, node_ptr position);
        static void unlink_node(bucket& b, node_ptr node);
        static void unlink_nodes(bucket& b, node_ptr begin, node_ptr end);
        static void unlink_nodes(bucket& b, node_ptr end);
        static inline void unlink_group(node_ptr* b);
    };

    template <class A>
    struct grouped_node_base : hash_bucket<A>
    {
        typedef hash_bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME bucket::node_ptr node_ptr;

        node_ptr group_prev_;

        grouped_node_base() : bucket(), group_prev_() {}
        static inline node_ptr& group_prev(node_ptr ptr);
        static inline node_ptr& next_group(node_ptr ptr);
        static inline std::size_t group_count(node_ptr ptr);
        static inline void add_to_bucket(node_ptr n, bucket& b);
        static inline void add_group_to_bucket(node_ptr n, bucket& b);
        static inline void add_after_node(node_ptr n, node_ptr position);
        static void unlink_node(bucket& b, node_ptr node);
        static void unlink_nodes(bucket& b, node_ptr begin, node_ptr end);
        static void unlink_nodes(bucket& b, node_ptr end);
        static inline void unlink_group(node_ptr* b);

    private:
        static inline node_ptr split_group(node_ptr split);
        static inline grouped_node_base& get(node_ptr ptr)
            { return static_cast<grouped_node_base&>(*ptr); }
    };

    struct ungrouped
    {
        template <class A>
        struct base {
            typedef ungrouped_node_base<A> type;
        };
    };

    struct grouped
    {
        template <class A>
        struct base {
            typedef grouped_node_base<A> type;
        };
    };

    template <class ValueType>
    struct value_base
    {
        typedef ValueType value_type;
        BOOST_DEDUCED_TYPENAME boost::aligned_storage<
            sizeof(value_type),
            ::boost::alignment_of<value_type>::value>::type data_;

        void* address() { return this; }
        value_type& value() { return *(ValueType*) this; }
    };

    // Node

    template <class NodeBase, class ValueType>
    class hash_node : public NodeBase, public value_base<ValueType>
    {
    public:
        typedef ValueType value_type;
        typedef BOOST_DEDUCED_TYPENAME NodeBase::node_ptr node_ptr;

        static value_type& get_value(node_ptr p) { return static_cast<hash_node&>(*p).value(); }
    };

    // Iterator Base

    template <class BucketPtr>
    class hash_iterator_base
    {
    public:
        typedef BucketPtr bucket_ptr;
        typedef BucketPtr node_ptr;

        bucket_ptr bucket_;
        node_ptr node_;

        hash_iterator_base() : bucket_(), node_() {}
        explicit hash_iterator_base(bucket_ptr b) : bucket_(b), node_(b->next_) {}
        hash_iterator_base(bucket_ptr b, node_ptr n) : bucket_(b), node_(n) {}
        
        bool operator==(hash_iterator_base const& x) const { return node_ == x.node_; }
        bool operator!=(hash_iterator_base const& x) const { return node_ != x.node_; }
        bool is_end() const { return node_ == bucket_; }
        node_ptr get() const { return node_; }
        void increment(node_ptr node);
        void increment();
    };

    // hash_table_manager
    //
    // This is responsible for allocating and deallocating buckets and nodes.
    //
    // Notes:
    // 1. For the sake exception safety the allocators themselves don't allocate anything.
    // 2. It's the callers responsibility to allocate the buckets before calling any of the
    //    methods (other than getters and setters).

    template <class A, class G>
    struct hash_table_manager
    {
        // Types

        typedef A value_allocator;
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

        typedef hash_bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME G::BOOST_NESTED_TEMPLATE base<A>::type
            node_base;
        typedef hash_node<node_base, value_type> node;

        typedef BOOST_DEDUCED_TYPENAME node::bucket_allocator bucket_allocator;
        typedef BOOST_DEDUCED_TYPENAME node::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME node::node_ptr node_ptr;

        typedef BOOST_DEDUCED_TYPENAME rebind_wrap<value_allocator, node>::type node_allocator;
        typedef BOOST_DEDUCED_TYPENAME node_allocator::pointer real_node_ptr;

        typedef hash_iterator_base<bucket_ptr> iterator_base;

        // Members

        bucket_ptr buckets_;
        bucket_ptr cached_begin_bucket_;
        std::size_t size_;
        std::size_t bucket_count_;
        boost::compressed_pair<bucket_allocator, node_allocator> allocators_;
        
        // Data access

        bucket_allocator const& bucket_alloc() const { return allocators_.first(); }
        node_allocator const& node_alloc() const { return allocators_.second(); }
        bucket_allocator& bucket_alloc() { return allocators_.first(); }
        node_allocator& node_alloc() { return allocators_.second(); }
        iterator_base begin() const { return iterator_base(this->cached_begin_bucket_); }
        iterator_base end() const { return iterator_base(this->buckets_end()); }
        std::size_t max_bucket_count() const {
            // -1 to account for the sentinel.
            return prev_prime(this->bucket_alloc().max_size() - 1);
        }

        // Constructors
        //
        // The copy constructor doesn't copy the buckets.

        hash_table_manager();
        explicit hash_table_manager(value_allocator const& a);
        explicit hash_table_manager(hash_table_manager const& h);
        hash_table_manager(hash_table_manager& x, move_tag m);
        hash_table_manager(hash_table_manager& x, value_allocator const& a, move_tag m);
        ~hash_table_manager();
        
        // no throw
        void swap(hash_table_manager& other);
        void move(hash_table_manager& other);

        // Buckets
        
        void create_buckets(std::size_t bucket_count);
        std::size_t bucket_count() const;
        std::size_t bucket_from_hash(std::size_t hashed) const;
        bucket_ptr bucket_ptr_from_hash(std::size_t hashed) const;
        bucket_ptr buckets_begin() const;
        bucket_ptr buckets_end() const;
        std::size_t bucket_size(std::size_t index) const;
        bucket_ptr get_bucket(std::size_t n) const;
        node_ptr bucket_begin(std::size_t n) const;
        node_ptr bucket_end(std::size_t) const;

        // Alloc/Dealloc
        
        void destruct_node(node_ptr);

        // 
        void delete_buckets();
        void clear();
        void clear_bucket(bucket_ptr);
        void delete_group(node_ptr first_node);
        void delete_nodes(node_ptr begin, node_ptr end);
        void delete_to_bucket_end(node_ptr begin);

        // Erase
        //
        // no throw

        iterator_base erase(iterator_base r);
        std::size_t erase_group(node_ptr* it, bucket_ptr bucket);
        iterator_base erase_range(iterator_base r1, iterator_base r2);

        // recompute_begin_bucket
        //
        // After an erase cached_begin_bucket_ might be left pointing to
        // an empty bucket, so this is called to update it
        //
        // no throw

        void recompute_begin_bucket(bucket_ptr b);

        // This is called when a range has been erased
        //
        // no throw

        void recompute_begin_bucket(bucket_ptr b1, bucket_ptr b2);
        
        // no throw
        float load_factor() const;
    };

    template <class H, class P, class A, class G, class K>
    class hash_table :
        public hash_table_manager<A, G>
        
    {
    public:
        typedef H hasher;
        typedef P key_equal;
        typedef A value_allocator;
        typedef G grouped;
        typedef K key_extractor;
        typedef hash_table_manager<A, G> manager;
        
        typedef BOOST_DEDUCED_TYPENAME value_allocator::value_type value_type;
        typedef BOOST_DEDUCED_TYPENAME key_extractor::BOOST_NESTED_TEMPLATE apply<value_type>
            extractor;    
        typedef BOOST_DEDUCED_TYPENAME extractor::key_type key_type;

        typedef BOOST_DEDUCED_TYPENAME manager::node node;
        typedef BOOST_DEDUCED_TYPENAME manager::bucket bucket;
        typedef BOOST_DEDUCED_TYPENAME manager::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME manager::bucket_ptr bucket_ptr;

        typedef BOOST_DEDUCED_TYPENAME manager::iterator_base iterator_base;

        // Types for storing functions

        typedef boost::compressed_pair<hasher, key_equal> functions;
        typedef bool functions_ptr;

        typedef BOOST_DEDUCED_TYPENAME boost::aligned_storage<
            sizeof(functions),
            ::boost::alignment_of<functions>::value>::type aligned_function;

        // Members
        
        bool func_; // The currently active functions.
        aligned_function funcs_[2];
        float mlf_;
        std::size_t max_load_;
        
        // Buffered Functions

        functions* get_functions(bool which) {
            return static_cast<functions*>(static_cast<void*>(&this->funcs_[which]));
        }
        functions const* get_functions(bool which) const {
            return static_cast<functions const*>(static_cast<void const*>(&this->funcs_[which]));
        }
        functions const& current() const {
            return *this->get_functions(this->func_);
        }
        hasher const& hash_function() const {
            return this->current().first();
        }
        key_equal const& key_eq() const {
            return this->current().second();
        }
        functions_ptr buffer_functions(hash_table const& x) {
            functions_ptr ptr = !func_;
            *this->get_functions(ptr) = x.current();
            return ptr;
        }
        void set_functions(functions_ptr ptr) {
            BOOST_ASSERT(ptr != func_);
             func_ = ptr;
        }

        // Helper methods

        bool equal(key_type const& k, value_type const& v) const;
        node_ptr find_iterator(bucket_ptr bucket, key_type const& k) const;
        node_ptr find_iterator(key_type const& k) const;
        node_ptr* find_for_erase(bucket_ptr bucket, key_type const& k) const;
        
        // Load methods

        std::size_t max_size() const;
        std::size_t bucket_index(key_type const& k) const;
        void max_load_factor(float z);
        std::size_t min_buckets_for_size(std::size_t n) const;
        void calculate_max_load();

        // Constructors

        hash_table(std::size_t n, hasher const& hf, key_equal const& eq, value_allocator const& a);
        hash_table(hash_table const& x);
        hash_table(hash_table const& x, value_allocator const& a);
        hash_table(hash_table& x, move_tag m);
        hash_table(hash_table& x, value_allocator const& a, move_tag m);
        ~hash_table();
        hash_table& operator=(hash_table const&);

        // Swap & Move

        void swap(hash_table& x);
        void move(hash_table& x);

        // Reserve and rehash

        bool reserve(std::size_t n);
        bool reserve_for_insert(std::size_t n);
        void rehash(std::size_t n);
        void rehash_impl(std::size_t n);

        // Move/copy buckets

        void move_buckets_to(manager& dst);
        void copy_buckets_to(manager& dst) const;

        // Misc. key methods

        std::size_t erase_key(key_type const& k);
        std::size_t count(key_type const& k) const;
        iterator_base find(key_type const& k) const;
        value_type& at(key_type const& k) const;
        std::pair<iterator_base, iterator_base> equal_range(key_type const& k) const;
    };

    // Iterator Access

    class iterator_access
    {
    public:
        template <class Iterator>
        static BOOST_DEDUCED_TYPENAME Iterator::base const& get(Iterator const& it) {
            return it.base_;
        }
    };

    // Iterators

    template <class A, class G> class hash_iterator;
    template <class A, class G> class hash_const_iterator;
    template <class A, class G> class hash_local_iterator;
    template <class A, class G> class hash_const_local_iterator;

    // Local Iterators
    //
    // all no throw

    template <class A, class G>
    class hash_local_iterator
        : public boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::pointer,
            BOOST_DEDUCED_TYPENAME A::reference>
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef hash_table_manager<A, G> manager;
        typedef BOOST_DEDUCED_TYPENAME manager::node_ptr ptr;
        typedef BOOST_DEDUCED_TYPENAME manager::node node;
        typedef hash_const_local_iterator<A, G> const_local_iterator;

        friend class hash_const_local_iterator<A, G>;
        ptr ptr_;

    public:
        hash_local_iterator() : ptr_() {}
        explicit hash_local_iterator(ptr x) : ptr_(x) {}
        BOOST_DEDUCED_TYPENAME A::reference operator*() const
            { return node::get_value(ptr_); }
        value_type* operator->() const { return &node::get_value(ptr_); }
        hash_local_iterator& operator++() { ptr_ = next_node(ptr_); return *this; }
        hash_local_iterator operator++(int) { hash_local_iterator tmp(ptr_); ptr_ = next_node(ptr_); return tmp; }
        bool operator==(hash_local_iterator x) const { return ptr_ == x.ptr_; }
        bool operator==(const_local_iterator x) const { return ptr_ == x.ptr_; }
        bool operator!=(hash_local_iterator x) const { return ptr_ != x.ptr_; }
        bool operator!=(const_local_iterator x) const { return ptr_ != x.ptr_; }
    };

    template <class A, class G>
    class hash_const_local_iterator
        : public boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::const_pointer,
            BOOST_DEDUCED_TYPENAME A::const_reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef hash_table_manager<A, G> manager;
        typedef BOOST_DEDUCED_TYPENAME manager::node_ptr ptr;
        typedef BOOST_DEDUCED_TYPENAME manager::node node;
        typedef hash_local_iterator<A, G> local_iterator;
        friend class hash_local_iterator<A, G>;
        ptr ptr_;

    public:
        hash_const_local_iterator() : ptr_() {}
        explicit hash_const_local_iterator(ptr x) : ptr_(x) {}
        hash_const_local_iterator(local_iterator x) : ptr_(x.ptr_) {}
        BOOST_DEDUCED_TYPENAME A::const_reference
            operator*() const { return node::get_value(ptr_); }
        value_type const* operator->() const { return &node::get_value(ptr_); }
        hash_const_local_iterator& operator++() { ptr_ = next_node(ptr_); return *this; }
        hash_const_local_iterator operator++(int) { hash_const_local_iterator tmp(ptr_); ptr_ = next_node(ptr_); return tmp; }
        bool operator==(local_iterator x) const { return ptr_ == x.ptr_; }
        bool operator==(hash_const_local_iterator x) const { return ptr_ == x.ptr_; }
        bool operator!=(local_iterator x) const { return ptr_ != x.ptr_; }
        bool operator!=(hash_const_local_iterator x) const { return ptr_ != x.ptr_; }
    };

    // iterators
    //
    // all no throw


    template <class A, class G>
    class hash_iterator
        : public boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::pointer,
            BOOST_DEDUCED_TYPENAME A::reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef hash_table_manager<A, G> manager;
        typedef BOOST_DEDUCED_TYPENAME manager::node node;
        typedef BOOST_DEDUCED_TYPENAME manager::iterator_base base;
        typedef hash_const_iterator<A, G> const_iterator;
        friend class hash_const_iterator<A, G>;
        base base_;

    public:

        hash_iterator() : base_() {}
        explicit hash_iterator(base const& x) : base_(x) {}
        BOOST_DEDUCED_TYPENAME A::reference
            operator*() const { return node::get_value(base_.get()); }
        value_type* operator->() const { return &node::get_value(base_.get()); }
        hash_iterator& operator++() { base_.increment(); return *this; }
        hash_iterator operator++(int) { hash_iterator tmp(base_); base_.increment(); return tmp; }
        bool operator==(hash_iterator const& x) const { return base_ == x.base_; }
        bool operator==(const_iterator const& x) const { return base_ == x.base_; }
        bool operator!=(hash_iterator const& x) const { return base_ != x.base_; }
        bool operator!=(const_iterator const& x) const { return base_ != x.base_; }
    };

    template <class A, class G>
    class hash_const_iterator
        : public boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::const_pointer,
            BOOST_DEDUCED_TYPENAME A::const_reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef hash_table_manager<A, G> manager;
        typedef BOOST_DEDUCED_TYPENAME manager::node node;
        typedef BOOST_DEDUCED_TYPENAME manager::iterator_base base;
        typedef hash_iterator<A, G> iterator;
        friend class hash_iterator<A, G>;
        friend class iterator_access;
        base base_;

    public:

        hash_const_iterator() : base_() {}
        explicit hash_const_iterator(base const& x) : base_(x) {}
        hash_const_iterator(iterator const& x) : base_(x.base_) {}
        BOOST_DEDUCED_TYPENAME A::const_reference
            operator*() const { return node::get_value(base_.get()); }
        value_type const* operator->() const { return &node::get_value(base_.get()); }
        hash_const_iterator& operator++() { base_.increment(); return *this; }
        hash_const_iterator operator++(int) { hash_const_iterator tmp(base_); base_.increment(); return tmp; }
        bool operator==(iterator const& x) const { return base_ == x.base_; }
        bool operator==(hash_const_iterator const& x) const { return base_ == x.base_; }
        bool operator!=(iterator const& x) const { return base_ != x.base_; }
        bool operator!=(hash_const_iterator const& x) const { return base_ != x.base_; }
    };
}}

#endif
