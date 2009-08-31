
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_MANAGER_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/unordered/detail/structure.hpp>

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
    hash_table_manager<A, G>::hash_table_manager()
        : structure(), allocators_() {}

    template <class A, class G>
    hash_table_manager<A, G>::hash_table_manager(value_allocator const& a)
        : structure(), allocators_(a,a) {}

    template <class A, class G>
    hash_table_manager<A, G>::hash_table_manager(hash_table_manager const& h)
        : structure(), allocators_(h.allocators_) {}

    template <class A, class G>
    hash_table_manager<A, G>::hash_table_manager(hash_table_manager& x, move_tag m)
        : structure(), allocators_(x.allocators_)
    {
        this->buckets_ = x.buckets_;
        this->cached_begin_bucket_ = x.cached_begin_bucket_;
        this->size_ = x.size_;
        this->bucket_count_ = x.bucket_count_;
        x.buckets_ = bucket_ptr();
        x.cached_begin_bucket_ = bucket_ptr();
        x.size_ = 0;
        x.bucket_count_ = 0;
    }

    template <class A, class G>
    hash_table_manager<A, G>::hash_table_manager(hash_table_manager& x, value_allocator const& a, move_tag m) :
         structure(), allocators_(a,a)
    {
        if(this->node_alloc() == x.node_alloc()) {
            this->buckets_ = x.buckets_;
            this->cached_begin_bucket_ = x.cached_begin_bucket_;
            this->size_ = x.size_;
            this->bucket_count_ = x.bucket_count_;
            x.buckets_ = bucket_ptr();
            x.cached_begin_bucket_ = bucket_ptr();
            x.size_ = 0;
            x.bucket_count_ = 0;
        }
    }
    
    template <class A, class G>
    hash_table_manager<A, G>::~hash_table_manager()
    {
        if(this->buckets_) { delete_buckets(); }
    }

    // no throw
    template <class A, class G>
    void hash_table_manager<A, G>::move(hash_table_manager& other)
    {
        delete_buckets();
        this->buckets_ = other.buckets_;
        this->cached_begin_bucket_ = other.cached_begin_bucket_;
        this->size_ = other.size_;
        this->bucket_count_ = other.bucket_count_;
        other.buckets_ = bucket_ptr();
        other.cached_begin_bucket_ = bucket_ptr();
        other.size_ = 0;
        other.bucket_count_ = 0;
    }

    // Construct/destruct
    
    template <class A, class G>
    void hash_table_manager<A, G>::create_buckets(std::size_t bucket_count) {
        BOOST_ASSERT(!this->buckets_ && !this->size_);
        
        // The array constructor will clean up in the event of an
        // exception.
        allocator_array_constructor<bucket_allocator>
            constructor(bucket_alloc());

        // Creates an extra bucket to act as a sentinel.
        constructor.construct(bucket(), bucket_count + 1);

        this->cached_begin_bucket_ = constructor.get() + static_cast<ptrdiff_t>(bucket_count);

        // Set up the sentinel (node_ptr cast)
        this->cached_begin_bucket_->next_ = this->cached_begin_bucket_;

        // Only release the buckets once everything is successfully
        // done.
        this->buckets_ = constructor.release();
        this->bucket_count_ = bucket_count;
    }

    template <class A, class G>
    void hash_table_manager<A, G>::destruct_node(node_ptr b)
    {
        node* raw_ptr = static_cast<node*>(&*b);
        BOOST_UNORDERED_DESTRUCT(&raw_ptr->value(), value_type);
        real_node_ptr n(node_alloc().address(*raw_ptr));
        node_alloc().destroy(n);
        node_alloc().deallocate(n, 1);
    }

    // Delete and clear buckets

    template <class A, class G>
    void hash_table_manager<A, G>::delete_group(node_ptr first_node)
    {
        delete_nodes(first_node, node::next_group(first_node));
    }
    
    template <class A, class G>
    void hash_table_manager<A, G>::delete_nodes(node_ptr begin, node_ptr end)
    {
        while(begin != end) {
            node_ptr node = begin;
            begin = next_node(begin);
            destruct_node(node);
        }
    }

    template <class A, class G>
    void hash_table_manager<A, G>::delete_to_bucket_end(node_ptr begin)
    {
        while(BOOST_UNORDERED_BORLAND_BOOL(begin)) {
            node_ptr node = begin;
            begin = next_node(begin);
            destruct_node(node);
        }
    }

    template <class A, class G>
    void hash_table_manager<A, G>::clear_bucket(bucket_ptr b)
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
    void hash_table_manager<A, G>::clear()
    {
        for(bucket_ptr begin = this->buckets_begin(), end = this->buckets_end(); begin != end; ++begin) {
            clear_bucket(begin);
        }

        this->cached_begin_bucket_ = this->buckets_end();
        this->size_ = 0;
    }

    template <class A, class G>
    void hash_table_manager<A, G>::delete_buckets()
    {      
        clear();

        // Destroy the buckets (including the sentinel bucket).
        bucket_ptr end = this->buckets_end();
        ++end;
        for(bucket_ptr begin = this->buckets_begin(); begin != end; ++begin) {
            bucket_alloc().destroy(begin);
        }

        bucket_alloc().deallocate(this->buckets_begin(), this->bucket_count() + 1);

        this->buckets_= bucket_ptr();
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_table_manager<A, G>::iterator_base
        hash_table_manager<A, G>::erase(iterator_base r)
    {
        BOOST_ASSERT(!r.is_end());
        iterator_base next = r;
        next.increment();
        this->unlink_node(r.bucket_, r.node_);
        destruct_node(r.node_);
        // r has been invalidated but its bucket is still valid
        this->recompute_begin_bucket(r.bucket_, next.bucket_);
        return next;
    }

    template <class A, class G>
    std::size_t hash_table_manager<A, G>::erase_group(node_ptr* it, bucket_ptr bucket)
    {
        node_ptr pos = *it;
        std::size_t count = this->unlink_group(it);
        delete_group(pos);

        this->recompute_begin_bucket(bucket);

        return count;
    }
    
    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_table_manager<A, G>::iterator_base
        hash_table_manager<A, G>::erase_range(iterator_base r1, iterator_base r2)
    {
        if(r1 != r2)
        {
            BOOST_ASSERT(!r1.is_end());

            if (r1.bucket_ == r2.bucket_) {
                this->unlink_nodes(r1.bucket_, r1.node_, r2.node_);
                delete_nodes(r1.node_, r2.node_);

                // No need to call recompute_begin_bucket because
                // the nodes are only deleted from one bucket, which
                // still contains r2 after the erase.
                BOOST_ASSERT(r1.bucket_->next_);
            }
            else {
                BOOST_ASSERT(r1.bucket_ < r2.bucket_);

                this->unlink_nodes(r1.bucket_,  r1.node_, node_ptr());
                delete_to_bucket_end(r1.node_);

                bucket_ptr i = r1.bucket_;
                for(++i; i != r2.bucket_; ++i) {
                    this->size_ -= node_count(i->next_, node_ptr());
                    clear_bucket(i);
                }

                if(!r2.is_end()) {
                    node_ptr first = r2.bucket_->next_;
                    this->unlink_nodes(r2.bucket_, r2.node_);
                    delete_nodes(first, r2.node_);
                }

                // r1 has been invalidated but its bucket is still
                // valid.
                this->recompute_begin_bucket(r1.bucket_, r2.bucket_);
            }
        }

        return r2;
    }

}}

#endif
