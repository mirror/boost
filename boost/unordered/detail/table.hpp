
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/iterator/iterator_categories.hpp>

#include <boost/unordered/detail/buckets.hpp>
#include <boost/unordered/detail/util.hpp>

namespace boost { namespace unordered_detail {

    ////////////////////////////////////////////////////////////////////////////
    // Helper methods

    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    inline bool hash_table<H, P, A, G, K>
        ::equal(key_type const& k, value_type const& v) const
    {
        return this->key_eq()(k, extractor::extract(v));
    }

    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    inline BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::node_ptr
        hash_table<H, P, A, G, K>
            ::find_iterator(bucket_ptr bucket, key_type const& k) const
    {
        node_ptr it = bucket->next_;
        while (BOOST_UNORDERED_BORLAND_BOOL(it) && !equal(k, node::get_value(it))) {
            it = node::next_group(it);
        }

        return it;
    }

    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    inline BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::node_ptr
        hash_table<H, P, A, G, K>
            ::find_iterator(key_type const& k) const
    {
        return find_iterator(this->get_bucket(this->bucket_index(k)), k);
    }

    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::node_ptr*
        hash_table<H, P, A, G, K>
            ::find_for_erase(bucket_ptr bucket, key_type const& k) const
    {
        node_ptr* it = &bucket->next_;
        while(BOOST_UNORDERED_BORLAND_BOOL(*it) && !equal(k, node::get_value(*it)))
            it = &node::next_group(*it);

        return it;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Load methods

    // no throw
    template <class H, class P, class A, class G, class K>
    std::size_t hash_table<H, P, A, G, K>
        ::max_size() const
    {
        using namespace std;

        // size < mlf_ * count
        return double_to_size_t(ceil(
                (double) this->mlf_ * this->max_bucket_count())) - 1;
    }

    // strong safety
    template <class H, class P, class A, class G, class K>
    std::size_t hash_table<H, P, A, G, K>
        ::bucket_index(key_type const& k) const
    {
        // hash_function can throw:
        return this->bucket_from_hash(this->hash_function()(k));
    }


    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::max_load_factor(float z)
    {
        BOOST_ASSERT(z > 0);
        mlf_ = (std::max)(z, minimum_max_load_factor);
        this->calculate_max_load();
    }

    // no throw
    template <class H, class P, class A, class G, class K>
    std::size_t hash_table<H, P, A, G, K>
        ::min_buckets_for_size(std::size_t n) const
    {
        BOOST_ASSERT(this->mlf_ != 0);

        using namespace std;

        // From 6.3.1/13:
        // size < mlf_ * count
        // => count > size / mlf_
        //
        // Or from rehash post-condition:
        // count > size / mlf_
        return double_to_size_t(floor(n / (double) mlf_)) + 1;
    }

    // no throw
    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::calculate_max_load()
    {
        using namespace std;

        // From 6.3.1/13:
        // Only resize when size >= mlf_ * count
        max_load_ = double_to_size_t(ceil((double) mlf_ * this->bucket_count()));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Constructors

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>
        ::hash_table(std::size_t n, hasher const& hf, key_equal const& eq, value_allocator const& a) :
            buckets(a, next_prime(n)), func_(false), cached_begin_bucket_(), size_(), mlf_(1.0f), max_load_(0)
    {
        std::uninitialized_fill((functions*)this->funcs_, (functions*)this->funcs_+2,
            functions(hf, eq));
        this->cached_begin_bucket_ = this->buckets_end();
        this->calculate_max_load();
    }

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>
        ::hash_table(hash_table const& x) :
            buckets(x.node_alloc(), next_prime(x.min_buckets_for_size(x.size_))), func_(false), cached_begin_bucket_(), size_(), mlf_(x.mlf_), max_load_(0)
    {
        std::uninitialized_fill((functions*)this->funcs_, (functions*)this->funcs_+2,
            x.current());
        this->calculate_max_load();
        x.copy_buckets_to(*this);
        this->size_ = x.size_;
        this->recompute_begin_bucket();
    }

    // Copy Construct with allocator

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>
        ::hash_table(hash_table const& x, value_allocator const& a) :
            buckets(a, next_prime(x.min_buckets_for_size(x.size_))), func_(false), cached_begin_bucket_(), size_(), mlf_(x.mlf_), max_load_(0)
    {
        std::uninitialized_fill((functions*)this->funcs_, (functions*)this->funcs_+2,
            x.current());
        this->cached_begin_bucket_ = this->buckets_end();
        this->calculate_max_load();
        x.copy_buckets_to(*this);
        this->size_ = x.size_;
        this->recompute_begin_bucket();
    }

    // Move Construct

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>
        ::hash_table(hash_table& x, move_tag m) :
            buckets(x, m), func_(false), cached_begin_bucket_(), size_(), mlf_(x.mlf_), max_load_(0)
    {
        this->cached_begin_bucket_ = x.cached_begin_bucket_;
        this->size_ = x.size_;
        x.cached_begin_bucket_ = bucket_ptr();
        x.size_ = 0;

        // TODO: Shouldn't I move the functions if poss.
        std::uninitialized_fill((functions*)this->funcs_, (functions*)this->funcs_+2,
            x.current());
    }

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>
        ::hash_table(hash_table& x, value_allocator const& a, move_tag m) :
            buckets(x, a, m), func_(false), cached_begin_bucket_(), size_(), mlf_(x.mlf_), max_load_(0)
    {
        std::uninitialized_fill((functions*)this->funcs_, (functions*)this->funcs_+2,
            x.current());

        this->calculate_max_load(); // no throw

        if(!this->buckets_) {
            buckets new_buckets(this->node_alloc(), x.min_buckets_for_size(x.size_));
            x.copy_buckets_to(new_buckets);
            new_buckets.swap(*this);
            this->size_ = x.size_;
            this->recompute_begin_bucket();
        }
        else {
            this->cached_begin_bucket_ = x.cached_begin_bucket_;
            this->size_ = x.size_;
            x.cached_begin_bucket_ = bucket_ptr();
            x.size_ = 0;
        }
    }

    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>::~hash_table()
    {
        BOOST_UNORDERED_DESTRUCT(this->get_functions(false), functions);
        BOOST_UNORDERED_DESTRUCT(this->get_functions(true), functions);
    }

    // TODO: Reuse current nodes amd buckets?
    template <class H, class P, class A, class G, class K>
    hash_table<H, P, A, G, K>& hash_table<H, P, A, G, K>::operator=(hash_table const& x)
    {
        if(this != &x) {
            this->clear();                        // no throw
            this->set_functions(
                this->buffer_functions(x));       // throws, strong
            this->mlf_ = x.mlf_;                  // no throw
            buckets new_buckets(this->node_alloc(), x.min_buckets_for_size(x.size_));
            x.copy_buckets_to(new_buckets);
            new_buckets.swap(*this);
            this->calculate_max_load();           // no throw
            this->size_ = x.size_;
            this->recompute_begin_bucket();
        }

        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swap & Move
    
    // Swap
    //
    // Strong exception safety
    //
    // Can throw if hash or predicate object's copy constructor throws
    // or if allocators are unequal.

    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::swap(hash_table& x)
    {
        // The swap code can work when swapping a container with itself
        // but it triggers an assertion in buffered_functions.
        // At the moment, I'd rather leave that assertion in and add a
        // check here, rather than remove the assertion. I might change
        // this at a later date.
        if(this == &x) return;

        // These can throw, but they only affect the function objects
        // that aren't in use so it is strongly exception safe, via.
        // double buffering.
        functions_ptr new_func_this = this->buffer_functions(x);
        functions_ptr new_func_that = x.buffer_functions(*this);

        if(this->node_alloc() == x.node_alloc()) {
            this->buckets::swap(x); // No throw
            std::swap(this->cached_begin_bucket_, x.cached_begin_bucket_);
            std::swap(this->size_, x.size_);
        }
        else {
            // Create new buckets in separate hash_buckets objects
            // which will clean up if anything throws an exception.
            // (all can throw, but with no effect as these are new objects).

            buckets new_this(this->node_alloc(), x.min_buckets_for_size(x.size_));
            x.copy_buckets_to(new_this);

            buckets new_that(x.node_alloc(), this->min_buckets_for_size(this->size_));
            copy_buckets_to(new_that);

            // Modifying the data, so no throw from now on.
            
            this->buckets::swap(new_this);
            x.buckets::swap(new_that);
            std::swap(this->size_, x.size_);
            this->recompute_begin_bucket();
            x.recompute_begin_bucket();
        }

        // The rest is no throw.

        std::swap(this->mlf_, x.mlf_);

        this->set_functions(new_func_this);
        x.set_functions(new_func_that);

        //TODO: Test that this works:
        this->calculate_max_load();
        x.calculate_max_load();
    }
    
    // Move
    //
    // Strong exception safety (might change unused function objects)
    //
    // Can throw if hash or predicate object's copy constructor throws
    // or if allocators are unequal.

    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::move(hash_table& x)
    {
        // This can throw, but it only affects the function objects
        // that aren't in use so it is strongly exception safe, via.
        // double buffering.
        functions_ptr new_func_this = this->buffer_functions(x);

        if(this->node_alloc() == x.node_alloc()) {
            this->buckets::move(x); // no throw
            this->size_ = x.size_;
            this->cached_begin_bucket_ = x.cached_begin_bucket_;
            x.size_ = 0;
            x.cached_begin_bucket_ = bucket_ptr();
        }
        else {
            // Create new buckets in separate HASH_TABLE_DATA objects
            // which will clean up if anything throws an exception.
            // (all can throw, but with no effect as these are new objects).
            
            buckets new_this(this->node_alloc(), next_prime(x.min_buckets_for_size(x.size_)));
            x.copy_buckets_to(new_this);

            // Start updating the data here, no throw from now on.
            this->buckets::move(new_this);
            this->size_ = x.size_;
            this->recompute_begin_bucket();
        }

        // We've made it, the rest is no throw.
        this->mlf_ = x.mlf_;
        this->set_functions(new_func_this);

        this->calculate_max_load();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Reserve & Rehash

    // basic exception safety
    template <class H, class P, class A, class G, class K>
    inline bool hash_table<H, P, A, G, K>
        ::reserve(std::size_t n)
    {
        bool need_to_reserve = n >= this->max_load_;
        // throws - basic:
        if (need_to_reserve) rehash_impl(this->min_buckets_for_size(n));
        BOOST_ASSERT(n < this->max_load_ || n > max_size());
        return need_to_reserve;
    }

    // basic exception safety
    template <class H, class P, class A, class G, class K>
    inline bool hash_table<H, P, A, G, K>
        ::reserve_for_insert(std::size_t n)
    {
        bool need_to_reserve = n >= this->max_load_;
        // throws - basic:
        if (need_to_reserve) {
            std::size_t s = this->size_;
            s = s + (s >> 1);
            s = s > n ? s : n;
            rehash_impl(this->min_buckets_for_size(s));
        }
        BOOST_ASSERT(n < this->max_load_ || n > max_size());
        return need_to_reserve;
    }

    // if hash function throws, basic exception safety
    // strong otherwise.
    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::rehash(std::size_t n)
    {
        using namespace std;

        // no throw:
        std::size_t min_size = this->min_buckets_for_size(this->size_);
        // basic/strong:
        rehash_impl(min_size > n ? min_size : n);

        BOOST_ASSERT((float) this->bucket_count() > (float) this->size_ / this->mlf_
                && this->bucket_count() >= n);
    }

    // if hash function throws, basic exception safety
    // strong otherwise

    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::rehash_impl(std::size_t n)
    {
        n = next_prime(n); // no throw

        if (n == this->bucket_count())  // no throw
            return;

        // Save the size to restore it if successful
        std::size_t size = this->size_;

        // Create another buckets to move the nodes into.
        buckets dst(this->node_alloc(), n);// throws, separate

        // Move the nodes to dst.
        hasher const& hf = this->hash_function();
        bucket_ptr end = this->buckets_end();

        for(; this->cached_begin_bucket_ != end; ++this->cached_begin_bucket_) {
            bucket_ptr src_bucket = this->cached_begin_bucket_;
            while(src_bucket->next_) {
                // Move the first group of equivalent nodes in
                // src_bucket to dst.

                // This next line throws iff the hash function throws.
                bucket_ptr dst_bucket = dst.bucket_ptr_from_hash(
                        hf(extractor::extract(node::get_value(src_bucket->next_))));

                
                node_ptr n = src_bucket->next_;
                this->size_ -= node::group_count(n);
                node::unlink_group(&src_bucket->next_);
                node::add_group_to_bucket(n, *dst_bucket);
            }
        }

        // Swap the new nodes back into the container and setup the local
        // variables.
        dst.swap(*this);                        // no throw
        this->size_ = size;
        this->recompute_begin_bucket();         // no throw
        this->calculate_max_load();             // no throw
    }

    ////////////////////////////////////////////////////////////////////////////
    // copy_buckets_to

    // copy_buckets_to
    //
    // basic excpetion safety. If an exception is thrown this will
    // leave dst partially filled.

    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>
        ::copy_buckets_to(buckets& dst) const
    {
        BOOST_ASSERT(this->buckets_ && dst.buckets_);

        hasher const& hf = this->hash_function();
        bucket_ptr end = this->buckets_end();

        hash_node_constructor<A, G> a(dst);

        // no throw:
        for(bucket_ptr i = this->cached_begin_bucket_; i != end; ++i) {
            // no throw:
            for(node_ptr it = i->next_; it;) {
                // hash function can throw.
                bucket_ptr dst_bucket = dst.bucket_ptr_from_hash(
                        hf(extractor::extract(node::get_value(it))));
                // throws, strong

                node_ptr group_end = node::next_group(it);

                a.construct(node::get_value(it));
                node_ptr n = a.release();
                node::add_to_bucket(n, *dst_bucket);
        
                for(it = next_node(it); it != group_end; it = next_node(it)) {
                    a.construct(node::get_value(it));
                    node::add_after_node(a.release(), n);
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    // Misc. key methods

    // strong exception safety

    // count
    //
    // strong exception safety, no side effects

    template <class H, class P, class A, class G, class K>
    std::size_t hash_table<H, P, A, G, K>
        ::count(key_type const& k) const
    {
        if(!this->size_) return 0;
        node_ptr it = find_iterator(k); // throws, strong
        return BOOST_UNORDERED_BORLAND_BOOL(it) ? node::group_count(it) : 0;
    }

    // find
    //
    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::iterator_base
        hash_table<H, P, A, G, K>
            ::find(key_type const& k) const
    {
        if(!this->size_) return this->end();

        bucket_ptr bucket = this->get_bucket(this->bucket_index(k));
        node_ptr it = find_iterator(bucket, k);

        if (BOOST_UNORDERED_BORLAND_BOOL(it))
            return iterator_base(bucket, it);
        else
            return this->end();
    }

    template <class H, class P, class A, class G, class K>
    BOOST_DEDUCED_TYPENAME A::value_type&
        hash_table<H, P, A, G, K>
            ::at(key_type const& k) const
    {
        if(!this->size_)
            throw std::out_of_range("Unable to find key in unordered_map.");

        bucket_ptr bucket = this->get_bucket(this->bucket_index(k));
        node_ptr it = find_iterator(bucket, k);

        if (BOOST_UNORDERED_BORLAND_BOOL(it))
            return node::get_value(it);
        else
            throw std::out_of_range("Unable to find key in unordered_map.");
    }

    // equal_range
    //
    // strong exception safety, no side effects
    template <class H, class P, class A, class G, class K>
    std::pair<
        BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::iterator_base,
        BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::iterator_base
    >
    hash_table<H, P, A, G, K>
        ::equal_range(key_type const& k) const
    {
        if(!this->size_)
            return std::pair<iterator_base, iterator_base>(this->end(), this->end());

        bucket_ptr bucket = this->get_bucket(this->bucket_index(k));
        node_ptr it = find_iterator(bucket, k);
        if (BOOST_UNORDERED_BORLAND_BOOL(it)) {
            iterator_base first(iterator_base(bucket, it));
            iterator_base second(first);
            second.increment(node::next_group(second.node_));
            return std::pair<iterator_base, iterator_base>(first, second);
        }
        else {
            return std::pair<iterator_base, iterator_base>(this->end(), this->end());
        }
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // Erase methods    
    
    template <class H, class P, class A, class G, class K>
    void hash_table<H, P, A, G, K>::clear()
    {
        for(bucket_ptr begin = this->buckets_begin(), end = this->buckets_end(); begin != end; ++begin) {
            this->clear_bucket(begin);
        }

        this->cached_begin_bucket_ = this->buckets_end();
        this->size_ = 0;
    }

    template <class H, class P, class A, class G, class K>
    std::size_t hash_table<H, P, A, G, K>
        ::erase_key(key_type const& k)
    {
        // No side effects in initial section
        bucket_ptr bucket = this->get_bucket(this->bucket_index(k));
        node_ptr* it = this->find_for_erase(bucket, k);

        // No throw.
        return *it ? this->erase_group(it, bucket) : 0;
    }


    template <class H, class P, class A, class G, class K>
    BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::iterator_base
        hash_table<H, P, A, G, K>::erase(iterator_base r)
    {
        BOOST_ASSERT(!r.is_end());
        iterator_base next = r;
        next.increment();
        --this->size_;
        node::unlink_node(*r.bucket_, r.node_);
        this->destruct_node(r.node_);
        // r has been invalidated but its bucket is still valid
        this->recompute_begin_bucket(r.bucket_, next.bucket_);
        return next;
    }

    template <class H, class P, class A, class G, class K>
    inline std::size_t hash_table<H, P, A, G, K>::erase_group(node_ptr* it, bucket_ptr bucket)
    {
        node_ptr pos = *it;
        std::size_t count = node::group_count(*it);
        this->size_ -= count;
        node::unlink_group(it);
        this->delete_group(pos);
        this->recompute_begin_bucket(bucket);
        return count;
    }
    
    template <class H, class P, class A, class G, class K>
    BOOST_DEDUCED_TYPENAME hash_table<H, P, A, G, K>::iterator_base
        hash_table<H, P, A, G, K>::erase_range(iterator_base r1, iterator_base r2)
    {
        if(r1 != r2)
        {
            BOOST_ASSERT(!r1.is_end());

            if (r1.bucket_ == r2.bucket_) {
                this->size_ -= node_count(r1.node_, r2.node_);
                node::unlink_nodes(*r1.bucket_, r1.node_, r2.node_);
                this->delete_nodes(r1.node_, r2.node_);

                // No need to call recompute_begin_bucket because
                // the nodes are only deleted from one bucket, which
                // still contains r2 after the erase.
                BOOST_ASSERT(r1.bucket_->next_);
            }
            else {
                BOOST_ASSERT(r1.bucket_ < r2.bucket_);

                this->size_ -= node_count(r1.node_, node_ptr());
                node::unlink_nodes(*r1.bucket_, r1.node_, node_ptr());
                this->delete_to_bucket_end(r1.node_);

                bucket_ptr i = r1.bucket_;
                for(++i; i != r2.bucket_; ++i) {
                    this->size_ -= node_count(i->next_, node_ptr());
                    this->clear_bucket(i);
                }

                if(!r2.is_end()) {
                    node_ptr first = r2.bucket_->next_;
                    this->size_ -= node_count(r2.bucket_->next_, r2.node_);
                    node::unlink_nodes(*r2.bucket_, r2.node_);
                    this->delete_nodes(first, r2.node_);
                }

                // r1 has been invalidated but its bucket is still
                // valid.
                this->recompute_begin_bucket(r1.bucket_, r2.bucket_);
            }
        }

        return r2;
    }


    template <class H, class P, class A, class G, class K>
    inline void hash_table<H, P, A, G, K>::recompute_begin_bucket()
    {
        if (this->size_ != 0) {
            this->cached_begin_bucket_ = this->buckets_begin();
            while (!this->cached_begin_bucket_->next_)
                ++this->cached_begin_bucket_;
        } else {
            this->cached_begin_bucket_ = this->buckets_end();
        }
    }

    // recompute_begin_bucket
    //
    // After an erase cached_begin_bucket_ might be left pointing to
    // an empty bucket, so this is called to update it
    //
    // no throw

    template <class H, class P, class A, class G, class K>
    inline void hash_table<H, P, A, G, K>::recompute_begin_bucket(bucket_ptr b)
    {
        BOOST_ASSERT(!(b < this->cached_begin_bucket_));

        if(b == this->cached_begin_bucket_)
        {
            if (this->size_ != 0) {
                while (!this->cached_begin_bucket_->next_)
                    ++this->cached_begin_bucket_;
            } else {
                this->cached_begin_bucket_ = this->buckets_end();
            }
        }
    }

    // This is called when a range has been erased
    //
    // no throw

    template <class H, class P, class A, class G, class K>
    inline void hash_table<H, P, A, G, K>::recompute_begin_bucket(bucket_ptr b1, bucket_ptr b2)
    {
        BOOST_ASSERT(!(b1 < this->cached_begin_bucket_) && !(b2 < b1));
        BOOST_ASSERT(BOOST_UNORDERED_BORLAND_BOOL(b2->next_));

        if(b1 == this->cached_begin_bucket_ && !b1->next_)
            this->cached_begin_bucket_ = b2;
    }

    // no throw
    template <class H, class P, class A, class G, class K>
    inline float hash_table<H, P, A, G, K>::load_factor() const
    {
        BOOST_ASSERT(this->bucket_count_ != 0);
        return static_cast<float>(this->size_)
            / static_cast<float>(this->bucket_count_);
	}

}}

#endif
