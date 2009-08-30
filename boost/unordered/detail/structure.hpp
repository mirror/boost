
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This contains the basic data structure, apart from the actual values. There's
// no construction or deconstruction here. So this only depends on the pointer
// type.

#ifndef BOOST_UNORDERED_DETAIL_STRUCTURE_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_STRUCTURE_HPP_INCLUDED

#include <boost/unordered/detail/node.hpp>

namespace boost { namespace unordered_detail {

    ////////////////////////////////////////////////////////////////////////////
    // hash_structure implementation
    
    template <class A, class G>
    void hash_structure<A, G>::swap(hash_structure<A, G>& other)
    {
        std::swap(buckets_, other.buckets_);
        std::swap(cached_begin_bucket_, other.cached_begin_bucket_);
        std::swap(size_, other.size_);
        std::swap(bucket_count_, other.bucket_count_);
    }

    template <class A, class G>
    std::size_t hash_structure<A, G>::bucket_count() const
    {
        return bucket_count_;
    }
    
    template <class A, class G>
    std::size_t hash_structure<A, G>::bucket_from_hash(std::size_t hashed) const
    {
        return hashed % bucket_count_;
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::bucket_ptr
        hash_structure<A, G>::bucket_ptr_from_hash(std::size_t hashed) const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(
            bucket_from_hash(hashed));
    }
    
    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::bucket_ptr
        hash_structure<A, G>::buckets_begin() const
    {
        return buckets_;
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::bucket_ptr
        hash_structure<A, G>::buckets_end() const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(bucket_count_);
    }

    template <class A, class G>
    std::size_t hash_structure<A, G>::bucket_size(std::size_t index) const
    {
        bucket_ptr ptr = (buckets_ + static_cast<std::ptrdiff_t>(index))->next_;
        std::size_t count = 0;
        while(ptr) {
            ++count;
            ptr = next_node(ptr);
        }
        return count;
    }
    
    // Link a node
    
    template <class A, class G>
    void hash_structure<A, G>::link_node(node_ptr n, node_ptr position)
    {
        node_base::add_after_node(n, position);
        ++size_;
    }

    template <class A, class G>
    void hash_structure<A, G>::link_node_in_bucket(node_ptr n, bucket_ptr bucket)
    {
        node_base::add_to_bucket(n, *bucket);
        ++size_;
        if(bucket < cached_begin_bucket_) cached_begin_bucket_ = bucket;
    }
    
    template <class A, class G>
    void hash_structure<A, G>::unlink_node(bucket_ptr bucket, node_ptr pos)
    {
        --size_;
        node_base::unlink_node(*bucket, pos);
    }

    template <class A, class G>
    void hash_structure<A, G>::unlink_nodes(
        bucket_ptr bucket, node_ptr begin, node_ptr end)
    {
        size_ -= node_count(begin, end);
        node_base::unlink_nodes(*bucket, begin, end);
    }

    template <class A, class G>
    void hash_structure<A, G>::unlink_nodes(bucket_ptr bucket, node_ptr end)
    {
        size_ -= node_count(bucket->next_, end);
        node_base::unlink_nodes(*bucket, end);
    }

    template <class A, class G>
    std::size_t hash_structure<A, G>::unlink_group(node_ptr* pos)
    {
        std::size_t count = node_base::group_count(*pos);
        size_ -= count;
        node_base::unlink_group(pos);
        return count;
    }

    template <class A, class G>
    void hash_structure<A, G>::link_group(
        node_ptr n, bucket_ptr bucket, std::size_t count)
    {
        node_base::add_group_to_bucket(n, *bucket);
        size_ += count;
        if(bucket < cached_begin_bucket_) cached_begin_bucket_ = bucket;
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::bucket_ptr
        hash_structure<A, G>::get_bucket(std::size_t n) const
    {
        return buckets_ + static_cast<std::ptrdiff_t>(n);
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::node_ptr
        hash_structure<A, G>::bucket_begin(std::size_t n) const
    {
        return (buckets_ + static_cast<std::ptrdiff_t>(n))->next_;
    }

    template <class A, class G>
    BOOST_DEDUCED_TYPENAME hash_structure<A, G>::node_ptr
        hash_structure<A, G>::bucket_end(std::size_t) const
    {
        return node_ptr();
    }

    // recompute_begin_bucket
    //
    // After an erase cached_begin_bucket_ might be left pointing to
    // an empty bucket, so this is called to update it
    //
    // no throw

    template <class A, class G>
    void hash_structure<A, G>::recompute_begin_bucket(bucket_ptr b)
    {
        BOOST_ASSERT(!(b < cached_begin_bucket_));

        if(b == cached_begin_bucket_)
        {
            if (size_ != 0) {
                while (!cached_begin_bucket_->next_)
                    ++cached_begin_bucket_;
            } else {
                cached_begin_bucket_ = buckets_end();
            }
        }
    }

    // This is called when a range has been erased
    //
    // no throw

    template <class A, class G>
    void hash_structure<A, G>::recompute_begin_bucket(bucket_ptr b1, bucket_ptr b2)
    {
        BOOST_ASSERT(!(b1 < cached_begin_bucket_) && !(b2 < b1));
        BOOST_ASSERT(BOOST_UNORDERED_BORLAND_BOOL(b2->next_));

        if(b1 == cached_begin_bucket_ && !b1->next_)
            cached_begin_bucket_ = b2;
    }

    // no throw
    template <class A, class G>
    inline float hash_structure<A, G>::load_factor() const
    {
        BOOST_ASSERT(bucket_count_ != 0);
        return static_cast<float>(size_)
            / static_cast<float>(bucket_count_);
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
