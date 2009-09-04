
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/unordered/detail/node.hpp>

namespace boost { namespace unordered_detail {
    
    ////////////////////////////////////////////////////////////////////////////
    // Explicitly call a destructor

#if defined(BOOST_MSVC)
#  define BOOST_UNORDERED_DESTRUCT(x, type) (x)->~type();
#else
#  define BOOST_UNORDERED_DESTRUCT(x, type) boost::unordered_detail::destroy(x)
    template <class T>
    void destroy(T* x) {
        x->~T();
    }
#endif

    // Constructors

    template <class A, class G>
    hash_buckets<A, G>::hash_buckets(node_allocator const& a, std::size_t bucket_count)
        : buckets_(), allocators_(a,a)
    {
        // The array constructor will clean up in the event of an
        // exception.
        allocator_array_constructor<bucket_allocator>
            constructor(bucket_alloc());

        // Creates an extra bucket to act as a sentinel.
        constructor.construct(bucket(), bucket_count + 1);

        // Set up the sentinel (node_ptr cast)
        bucket_ptr sentinel = constructor.get() + static_cast<ptrdiff_t>(bucket_count);
        sentinel->next_ = sentinel;

        // Only release the buckets once everything is successfully
        // done.
        this->buckets_ = constructor.release();
        this->bucket_count_ = bucket_count;
    }

    template <class A, class G>
    hash_buckets<A, G>::hash_buckets(hash_buckets& x, move_tag)
        : buckets_(), allocators_(x.allocators_)
    {
        this->buckets_ = x.buckets_;
        this->bucket_count_ = x.bucket_count_;
        x.buckets_ = bucket_ptr();
        x.bucket_count_ = 0;
    }

    template <class A, class G>
    hash_buckets<A, G>::hash_buckets(hash_buckets& x, value_allocator const& a, move_tag) :
         buckets_(), allocators_(a,a)
    {
        if(this->node_alloc() == x.node_alloc()) {
            this->buckets_ = x.buckets_;
            this->bucket_count_ = x.bucket_count_;
            x.buckets_ = bucket_ptr();
            x.bucket_count_ = 0;
        }
    }
    
    template <class A, class G>
    hash_buckets<A, G>::~hash_buckets()
    {
        if(this->buckets_) { delete_buckets(); }
    }

    // no throw
    template <class A, class G>
    inline void hash_buckets<A, G>::move(hash_buckets& other)
    {
    	BOOST_ASSERT(node_alloc() == other.node_alloc());
        delete_buckets();
        this->buckets_ = other.buckets_;
        this->bucket_count_ = other.bucket_count_;
        other.buckets_ = bucket_ptr();
        other.bucket_count_ = 0;
    }

    template <class A, class G>
    inline void hash_buckets<A, G>::swap(hash_buckets<A, G>& other)
    {
    	BOOST_ASSERT(node_alloc() == other.node_alloc());
        std::swap(buckets_, other.buckets_);
        std::swap(bucket_count_, other.bucket_count_);
    }
    
    // Buckets
    
    template <class A, class G>
    inline std::size_t hash_buckets<A, G>::bucket_count() const
    {
        return bucket_count_;
    }
    
    template <class A, class G>
    inline std::size_t hash_buckets<A, G>::bucket_from_hash(std::size_t hashed) const
    {
        return hashed % bucket_count_;
    }

    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::bucket_ptr
        hash_buckets<A, G>::bucket_ptr_from_hash(std::size_t hashed) const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(
            bucket_from_hash(hashed));
    }
    
    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::bucket_ptr
        hash_buckets<A, G>::buckets_begin() const
    {
        return buckets_;
    }

    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::bucket_ptr
        hash_buckets<A, G>::buckets_end() const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(bucket_count_);
    }

    template <class A, class G>
    inline std::size_t hash_buckets<A, G>::bucket_size(std::size_t index) const
    {
        bucket_ptr ptr = (buckets_ + static_cast<std::ptrdiff_t>(index))->next_;
        std::size_t count = 0;
        while(ptr) {
            ++count;
            ptr = next_node(ptr);
        }
        return count;
    }

    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::bucket_ptr
        hash_buckets<A, G>::get_bucket(std::size_t n) const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(n);
    }

    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::node_ptr
        hash_buckets<A, G>::bucket_begin(std::size_t n) const
    {
        return (buckets_ + static_cast<std::ptrdiff_t>(n))->next_;
    }

    template <class A, class G>
    inline BOOST_DEDUCED_TYPENAME hash_buckets<A, G>::node_ptr
        hash_buckets<A, G>::bucket_end(std::size_t) const
    {
        return node_ptr();
    }

    // Construct/destruct
    
    template <class A, class G>
    inline void hash_buckets<A, G>::destruct_node(node_ptr b)
    {
        node* raw_ptr = static_cast<node*>(&*b);
        BOOST_UNORDERED_DESTRUCT(&raw_ptr->value(), value_type);
        real_node_ptr n(node_alloc().address(*raw_ptr));
        node_alloc().destroy(n);
        node_alloc().deallocate(n, 1);
    }

    // Delete and clear buckets

    template <class A, class G>
    inline void hash_buckets<A, G>::delete_group(node_ptr first_node)
    {
        delete_nodes(first_node, node::next_group(first_node));
    }
    
    template <class A, class G>
    inline void hash_buckets<A, G>::delete_nodes(node_ptr begin, node_ptr end)
    {
        while(begin != end) {
            node_ptr node = begin;
            begin = next_node(begin);
            destruct_node(node);
        }
    }

    template <class A, class G>
    inline void hash_buckets<A, G>::delete_to_bucket_end(node_ptr begin)
    {
        while(BOOST_UNORDERED_BORLAND_BOOL(begin)) {
            node_ptr node = begin;
            begin = next_node(begin);
            destruct_node(node);
        }
    }

    template <class A, class G>
    inline void hash_buckets<A, G>::clear_bucket(bucket_ptr b)
    {
        node_ptr node_it = b->next_;
        b->next_ = node_ptr();

        while(node_it) {
            node_ptr node_to_destruct = node_it;
            node_it = next_node(node_it);
            destruct_node(node_to_destruct);
        }
    }

    template <class A, class G>
    inline void hash_buckets<A, G>::delete_buckets()
    {      
        for(bucket_ptr begin = this->buckets_begin(), end = this->buckets_end(); begin != end; ++begin) {
            clear_bucket(begin);
        }

        // Destroy the buckets (including the sentinel bucket).
        bucket_ptr end = this->buckets_end();
        ++end;
        for(bucket_ptr begin = this->buckets_begin(); begin != end; ++begin) {
            bucket_alloc().destroy(begin);
        }

        bucket_alloc().deallocate(this->buckets_begin(), this->bucket_count() + 1);

        this->buckets_ = bucket_ptr();
    }

    ////////////////////////////////////////////////////////////////////////////
    // hash_iterator_base implementation
    
    template <class BucketPtr>
    inline void hash_iterator_base<BucketPtr>::increment(node_ptr node) {
        while(!node) {
            ++bucket_;
            node = bucket_->next_;
        }

        node_ = node;
    }

    template <class BucketPtr>
    inline void hash_iterator_base<BucketPtr>::increment()
    {
        increment(next_node(node_));
    }
}}

#endif
