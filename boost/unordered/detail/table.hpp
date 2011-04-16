
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED

#include <boost/unordered/detail/buckets.hpp>

namespace boost { namespace unordered { namespace detail {

    // This implements almost all of the required functionality, apart
    // from some things that are specific to containers with unique and
    // equivalent keys which is implemented in unique_table and
    // equivalent_table. See unique.hpp and equivalent.hpp for
    // their declaration and implementation.

    template <class T>
    class table : public T::buckets, public T::buffered_functions
    {
        table(table const&);
    public:
        typedef BOOST_DEDUCED_TYPENAME T::hasher hasher;
        typedef BOOST_DEDUCED_TYPENAME T::key_equal key_equal;
        typedef BOOST_DEDUCED_TYPENAME T::value_allocator value_allocator;
        typedef BOOST_DEDUCED_TYPENAME T::key_type key_type;
        typedef BOOST_DEDUCED_TYPENAME T::value_type value_type;
        typedef BOOST_DEDUCED_TYPENAME T::buffered_functions base;
        typedef BOOST_DEDUCED_TYPENAME T::buckets buckets;
        typedef BOOST_DEDUCED_TYPENAME T::extractor extractor;
        typedef BOOST_DEDUCED_TYPENAME T::node_constructor node_constructor;

        typedef BOOST_DEDUCED_TYPENAME T::node node;
        typedef BOOST_DEDUCED_TYPENAME T::bucket bucket;
        typedef BOOST_DEDUCED_TYPENAME T::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME T::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME T::node_allocator node_allocator;
        typedef BOOST_DEDUCED_TYPENAME T::iterator_pair iterator_pair;

        // Members
        
        std::size_t size_;
        float mlf_;
        std::size_t max_load_;

        // Helper methods

        key_type const& get_key(value_type const& v) const {
            return extractor::extract(v);
        }

    private:
        // pre: this->buckets_ != null
        template <class Key, class Pred>
        node_ptr find_node_impl(
                std::size_t bucket_index,
                std::size_t hash,
                Key const& k,
                Pred const& eq) const
        {
            node_ptr n = this->buckets_[bucket_index].next_;
            if (!n) return n;
            n = n->next_;
    
            for (;;)
            {
                if (!n) return n;
                std::size_t node_hash = node::get_hash(n);
                if (hash == node_hash)
                {
                    if (eq(k, get_key(node::get_value(n))))
                        return n;
                }
                else
                {
                    if (node_hash % this->bucket_count_ != bucket_index)
                        return node_ptr();
                }
                n = node::next_group(n);
            }
        }

    public:
        template <class Key, class Hash, class Pred>
        node_ptr generic_find_node(
                Key const& k,
                Hash const& hash_function,
                Pred const& eq) const
        {
            if (!this->size_) return node_ptr();
            std::size_t hash = hash_function(k);
            return find_node_impl(hash % this->bucket_count_, hash, k, eq);
        }
        
        node_ptr find_node(
                std::size_t bucket_index,
                std::size_t hash,
                key_type const& k) const
        {
            if (!this->size_) return node_ptr();
            return find_node_impl(bucket_index, hash, k, this->key_eq());
        }

        node_ptr find_node(key_type const& k) const
        {
            if (!this->size_) return node_ptr();
            std::size_t hash = this->hash_function()(k);
            return find_node_impl(hash % this->bucket_count_, hash, k,
                this->key_eq());
        }

        node_ptr find_matching_node(node_ptr n) const
        {
            // For some stupid reason, I decided to support equality comparison
            // when different hash functions are used. So I can't use the hash
            // value from the node here.
    
            return find_node(get_key(node::get_value(n)));
        }

        ////////////////////////////////////////////////////////////////////////
        // Load methods

        std::size_t max_size() const
        {
            using namespace std;
    
            // size < mlf_ * count
            return double_to_size_t(ceil(
                    (double) this->mlf_ * this->max_bucket_count())) - 1;
        }

        std::size_t calculate_max_load()
        {
            BOOST_ASSERT(this->buckets_);

            using namespace std;
    
            // From 6.3.1/13:
            // Only resize when size >= mlf_ * count
            return double_to_size_t(ceil((double) mlf_ * this->bucket_count_));
        }

        void max_load_factor(float z)
        {
            BOOST_ASSERT(z > 0);
            mlf_ = (std::max)(z, minimum_max_load_factor);
            if (BOOST_UNORDERED_BORLAND_BOOL(this->buckets_))
                this->max_load_ = this->calculate_max_load();
        }

        std::size_t min_buckets_for_size(std::size_t size) const
        {
            BOOST_ASSERT(this->mlf_ != 0);
    
            using namespace std;
    
            // From 6.3.1/13:
            // size < mlf_ * count
            // => count > size / mlf_
            //
            // Or from rehash post-condition:
            // count > size / mlf_
            return next_prime(double_to_size_t(floor(size / (double) mlf_)) + 1);
        }

        float load_factor() const
        {
            BOOST_ASSERT(this->bucket_count_ != 0);
            return static_cast<float>(this->size_)
                / static_cast<float>(this->bucket_count_);
        }

        ////////////////////////////////////////////////////////////////////////
        // Constructors

        table(
                std::size_t num_buckets,
                hasher const& hf,
                key_equal const& eq,
                node_allocator const& a)
          : buckets(a, next_prime(num_buckets)),
            base(hf, eq),
            size_(),
            mlf_(1.0f),
            max_load_(0)
        {
        }

        table(table const& x, node_allocator const& a)
          : buckets(a, x.min_buckets_for_size(x.size_)),
            base(x),
            size_(x.size_),
            mlf_(x.mlf_),
            max_load_(0)
        {
            if(x.size_) {
                x.copy_buckets_to(*this);
                this->max_load_ = calculate_max_load();
            }
        }

        table(table& x, move_tag)
          : buckets(x.node_alloc(), x.bucket_count_),
            base(x),
            size_(0),
            mlf_(1.0f),
            max_load_(0)
        {
            this->partial_swap(x);
        }

        table(table& x, node_allocator const& a, move_tag)
          : buckets(a, x.bucket_count_),
            base(x),
            size_(0),
            mlf_(x.mlf_),
            max_load_(0)
        {
            if(a == x.node_alloc()) {
                this->partial_swap(x);
            }
            else if(x.size_) {
                x.copy_buckets_to(*this);
                this->size_ = x.size_;
                this->max_load_ = calculate_max_load();
            }
        }

        ~table()
        {}

        table& operator=(table const& x)
        {
            table tmp(x, this->node_alloc());
            this->fast_swap(tmp);
            return *this;
        }

        // Iterators

        node_ptr begin() const {
            return !this->buckets_ ?
                node_ptr() : this->buckets_[this->bucket_count_].next_;
        }

        ////////////////////////////////////////////////////////////////////////
        // Swap & Move

        void swap(table& x)
        {
            if(this->node_alloc() == x.node_alloc()) {
                if(this != &x) this->fast_swap(x);
            }
            else {
                this->slow_swap(x);
            }
        }

        void fast_swap(table& x)
        {
            // These can throw, but they only affect the function objects
            // that aren't in use so it is strongly exception safe, via.
            // double buffering.
            {
                set_hash_functions<hasher, key_equal> op1(*this, x);
                set_hash_functions<hasher, key_equal> op2(x, *this);
                op1.commit();
                op2.commit();
            }
            this->buckets::swap(x); // No throw
            std::swap(this->size_, x.size_);
            std::swap(this->mlf_, x.mlf_);
            std::swap(this->max_load_, x.max_load_);
        }

        void slow_swap(table& x)
        {
            if(this == &x) return;
    
            {
                // These can throw, but they only affect the function objects
                // that aren't in use so it is strongly exception safe, via.
                // double buffering.
                set_hash_functions<hasher, key_equal> op1(*this, x);
                set_hash_functions<hasher, key_equal> op2(x, *this);
            
                // Create new buckets in separate buckets objects
                // which will clean up if anything throws an exception.
                // (all can throw, but with no effect as these are new objects).
            
                buckets b1(this->node_alloc(), x.min_buckets_for_size(x.size_));
                if (x.size_) x.copy_buckets_to(b1);
            
                buckets b2(x.node_alloc(), this->min_buckets_for_size(this->size_));
                if (this->size_) this->copy_buckets_to(b2);
            
                // Modifying the data, so no throw from now on.
            
                b1.swap(*this);
                b2.swap(x);
                op1.commit();
                op2.commit();
            }
            
            std::swap(this->size_, x.size_);
    
            this->max_load_ = !this->buckets_ ? 0 : this->calculate_max_load();
            x.max_load_ = !x.buckets_ ? 0 : x.calculate_max_load();
        }

        void partial_swap(table& x)
        {
            this->buckets::swap(x); // No throw
            std::swap(this->size_, x.size_);
            std::swap(this->mlf_, x.mlf_);
            std::swap(this->max_load_, x.max_load_);
        }

        void move(table& x)
        {
            // This can throw, but it only affects the function objects
            // that aren't in use so it is strongly exception safe, via.
            // double buffering.
            set_hash_functions<hasher, key_equal> new_func_this(*this, x);
    
            if(this->node_alloc() == x.node_alloc()) {
                this->buckets::move(x); // no throw
                this->size_ = x.size_;
                this->max_load_ = x.max_load_;
                x.size_ = 0;
            }
            else {
                // Create new buckets in separate buckets
                // which will clean up if anything throws an exception.
                // (all can throw, but with no effect as these are new objects).
                
                buckets b(this->node_alloc(), x.min_buckets_for_size(x.size_));
                if (x.size_) x.copy_buckets_to(b);
    
                // Start updating the data here, no throw from now on.
                this->size_ = x.size_;
                b.swap(*this);
                this->max_load_ = x.size_ ? calculate_max_load() : 0;
            }
    
            // We've made it, the rest is no throw.
            this->mlf_ = x.mlf_;
            new_func_this.commit();
        }

        ////////////////////////////////////////////////////////////////////////
        // Key methods

        std::size_t count(key_type const& k) const
        {
            if(!this->size_) return 0;
            return node::group_count(find_node(k));
        }

        value_type& at(key_type const& k) const
        {
            if (this->size_) {
                node_ptr it = find_node(k);
                if (BOOST_UNORDERED_BORLAND_BOOL(it))
                    return node::get_value(it);
            }
    
            ::boost::throw_exception(
                std::out_of_range("Unable to find key in unordered_map."));
        }

        iterator_pair equal_range(key_type const& k) const
        {
            if(!this->size_)
                return iterator_pair(node_ptr(), node_ptr());
    
            node_ptr ptr = find_node(k);
            return iterator_pair(ptr, !ptr ? ptr : node::next_group(ptr));
        }

        // Erase
        //
        // no throw

        void clear()
        {
            if(!this->size_) return;
    
            bucket_ptr end = this->get_bucket(this->bucket_count_);
    
            node_ptr n = (end)->next_;
            while(BOOST_UNORDERED_BORLAND_BOOL(n))
            {
                node_ptr node_to_delete = n;
                n = n->next_;
                delete_node(node_to_delete);
            }
    
            ++end;
            for(bucket_ptr begin = this->buckets_; begin != end; ++begin) {
                begin->next_ = bucket_ptr();
            }
    
            this->size_ = 0;
        }

        std::size_t erase_key(key_type const& k)
        {
            if(!this->size_) return 0;
    
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            bucket_ptr bucket = this->get_bucket(bucket_index);
    
            node_ptr prev = bucket->next_;
            if (!prev) return 0;
    
            for (;;)
            {
                if (!prev->next_) return 0;
                std::size_t node_hash = node::get_hash(prev->next_);
                if (node_hash % this->bucket_count_ != bucket_index)
                    return 0;
                if (node_hash == hash &&
                    this->key_eq()(k, get_key(node::get_value(prev->next_))))
                    break;
                prev = node::next_group2(prev);
            }
    
            node_ptr pos = prev->next_;
            node_ptr end = node::next_group(pos);
            prev->next_ = end;
    
            this->fix_buckets(bucket, prev, end);
    
            std::size_t count = this->delete_nodes(pos, end);
            this->size_ -= count;
    
            return count;
        }

        node_ptr erase(node_ptr r)
        {
            BOOST_ASSERT(r);
            node_ptr next = r->next_;
    
            bucket_ptr bucket = this->get_bucket(
                node::get_hash(r) % this->bucket_count_);
            node_ptr prev = node::unlink_node(*bucket, r);
    
            this->fix_buckets(bucket, prev, next);
    
            this->delete_node(r);
            --this->size_;
    
            return next;
        }

        node_ptr erase_range(node_ptr r1, node_ptr r2)
        {
            if (r1 == r2) return r2;
    
            std::size_t bucket_index = node::get_hash(r1) % this->bucket_count_;
            node_ptr prev = node::unlink_nodes(
                this->buckets_[bucket_index], r1, r2);
            this->fix_buckets_range(bucket_index, prev, r1, r2);
            this->size_ -= this->delete_nodes(r1, r2);
    
            return r2;
        }

        // Reserve and rehash

        bool reserve_for_insert(std::size_t);
        void rehash(std::size_t);
        void rehash_impl(std::size_t);
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // Reserve & Rehash

    // basic exception safety
    template <class T>
    inline bool table<T>::reserve_for_insert(std::size_t size)
    {
        if(size >= max_load_) {
            if (!this->buckets_) {
                std::size_t old_bucket_count = this->bucket_count_;
                this->bucket_count_ = (std::max)(this->bucket_count_,
                    this->min_buckets_for_size(size));
                this->create_buckets();
                this->max_load_ = calculate_max_load();
                return old_bucket_count != this->bucket_count_;
            }
            else {
                std::size_t num_buckets
                    = this->min_buckets_for_size((std::max)(size,
                        this->size_ + (this->size_ >> 1)));
                if (num_buckets != this->bucket_count_) {
                    rehash_impl(num_buckets);
                    return true;
                }
            }
        }
        
        return false;
    }

    // if hash function throws, basic exception safety
    // strong otherwise.

    template <class T>
    void table<T>::rehash(std::size_t min_buckets)
    {
        using namespace std;

        if(!this->size_) {
            if(this->buckets_) this->delete_buckets();
            this->bucket_count_ = next_prime(min_buckets);
            this->max_load_ = 0;
        }
        else {
            // no throw:
            min_buckets = next_prime((std::max)(min_buckets,
                    double_to_size_t(floor(this->size_ / (double) mlf_)) + 1));
            if(min_buckets != this->bucket_count_) rehash_impl(min_buckets);
        }
    }

    // strong otherwise exception safety
    template <class T>
    void table<T>::rehash_impl(std::size_t num_buckets)
    {
        std::size_t size = this->size_;
        BOOST_ASSERT(size);

        buckets dst(this->node_alloc(), num_buckets);
        dst.create_buckets();
        
        bucket_ptr src_start = this->get_bucket(this->bucket_count_);
        bucket_ptr dst_start = dst.get_bucket(dst.bucket_count_);

        dst_start->next_ = src_start->next_;
        src_start->next_ = bucket_ptr();
        // No need to do this, since the following is 'no throw'.
        //this->size_ = 0;

        node_ptr prev = dst_start;
        while (BOOST_UNORDERED_BORLAND_BOOL(prev->next_))
            prev = dst.place_in_bucket(prev, node::next_group2(prev));

        // Swap the new nodes back into the container and setup the
        // variables.
        dst.swap(*this); // no throw
        this->size_ = size;
        this->max_load_ = calculate_max_load();
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    // types
    //
    // This is used to convieniently pass around a container's typedefs
    // without having 7 template parameters.

    template <class K, class V, class H, class P, class A, class E, bool Unique>
    struct types
    {
    public:
        typedef K key_type;
        typedef V value_type;
        typedef H hasher;
        typedef P key_equal;
        typedef A value_allocator;
        typedef E extractor;
        
        typedef ::boost::unordered::detail::node_constructor<value_allocator, Unique> node_constructor;
        typedef ::boost::unordered::detail::buckets<value_allocator, Unique> buckets;
        typedef ::boost::unordered::detail::buffered_functions<hasher, key_equal> buffered_functions;

        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef BOOST_DEDUCED_TYPENAME buckets::bucket bucket;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME buckets::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_allocator node_allocator;

        typedef std::pair<node_ptr, node_ptr> iterator_pair;
    };
}}}

namespace boost { namespace unordered { namespace iterator_detail {

    // Iterators
    //
    // all no throw

    template <class A, bool Unique> class iterator;
    template <class A, bool Unique> class c_iterator;
    template <class A, bool Unique> class l_iterator;
    template <class A, bool Unique> class cl_iterator;

    // Local Iterators
    //
    // all no throw

    template <class A, bool Unique>
    class l_iterator
        : public ::boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::pointer,
            BOOST_DEDUCED_TYPENAME A::reference>
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef cl_iterator<A, Unique> const_local_iterator;

        friend class cl_iterator<A, Unique>;
        node_ptr ptr_;
        std::size_t bucket_;
        std::size_t bucket_count_;

    public:
        l_iterator() : ptr_() {}
        l_iterator(node_ptr x, std::size_t b, std::size_t c)
            : ptr_(x), bucket_(b), bucket_count_(c) {}
        BOOST_DEDUCED_TYPENAME A::reference operator*() const {
            return node::get_value(ptr_);
        }
        value_type* operator->() const {
            return node::get_value_ptr(ptr_);
        }
        l_iterator& operator++() {
            ptr_ = ptr_->next_;
            if (ptr_ && node::get_hash(ptr_) % bucket_count_ != bucket_)
                ptr_ = node_ptr();
            return *this;
        }
        l_iterator operator++(int) {
            l_iterator tmp(*this);
            ptr_ = ptr_->next_;
            if (ptr_ && node::get_hash(ptr_) % bucket_count_ != bucket_)
                ptr_ = node_ptr();
            return tmp;
        }
        bool operator==(l_iterator x) const {
            return ptr_ == x.ptr_;
        }
        bool operator==(const_local_iterator x) const {
            return ptr_ == x.ptr_;
        }
        bool operator!=(l_iterator x) const {
            return ptr_ != x.ptr_;
        }
        bool operator!=(const_local_iterator x) const {
            return ptr_ != x.ptr_;
        }
    };

    template <class A, bool Unique>
    class cl_iterator
        : public ::boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::const_pointer,
            BOOST_DEDUCED_TYPENAME A::const_reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef l_iterator<A, Unique> local_iterator;
        friend class l_iterator<A, Unique>;

        node_ptr ptr_;
        std::size_t bucket_;
        std::size_t bucket_count_;

    public:
        cl_iterator() : ptr_() {}
        cl_iterator(node_ptr x, std::size_t b, std::size_t c)
            : ptr_(x), bucket_(b), bucket_count_(c) {}
        cl_iterator(local_iterator x)
            : ptr_(x.ptr_), bucket_(x.bucket_), bucket_count_(x.bucket_count_)
        {}
        BOOST_DEDUCED_TYPENAME A::const_reference
            operator*() const {
            return node::get_value(ptr_);
        }
        value_type const* operator->() const {
            return node::get_value_ptr(ptr_);
        }
        cl_iterator& operator++() {
            ptr_ = ptr_->next_;
            if (ptr_ && node::get_hash(ptr_) % bucket_count_ != bucket_)
                ptr_ = node_ptr();
            return *this;
        }
        cl_iterator operator++(int) {
            cl_iterator tmp(*this);
            ptr_ = ptr_->next_;
            if (ptr_ && node::get_hash(ptr_) % bucket_count_ != bucket_)
                ptr_ = node_ptr();
            return tmp;
        }
        bool operator==(local_iterator x) const {
            return ptr_ == x.ptr_;
        }
        bool operator==(cl_iterator x) const {
            return ptr_ == x.ptr_;
        }
        bool operator!=(local_iterator x) const {
            return ptr_ != x.ptr_;
        }
        bool operator!=(cl_iterator x) const {
            return ptr_ != x.ptr_;
        }
    };

    template <class A, bool Unique>
    class iterator
        : public ::boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::pointer,
            BOOST_DEDUCED_TYPENAME A::reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_ptr node_ptr;
        typedef c_iterator<A, Unique> const_iterator;
        friend class c_iterator<A, Unique>;
        node_ptr node_;

    public:

        iterator() : node_() {}
        explicit iterator(node_ptr const& x) : node_(x) {}
        BOOST_DEDUCED_TYPENAME A::reference operator*() const {
            return node::get_value(node_);
        }
        value_type* operator->() const {
            return &node::get_value(node_);
        }
        iterator& operator++() {
            node_ = node_->next_; return *this;
        }
        iterator operator++(int) {
            iterator tmp(node_); node_ = node_->next_; return tmp;
        }
        bool operator==(iterator const& x) const {
            return node_ == x.node_;
        }
        bool operator==(const_iterator const& x) const {
            return node_ == x.node_;
        }
        bool operator!=(iterator const& x) const {
            return node_ != x.node_;
        }
        bool operator!=(const_iterator const& x) const {
            return node_ != x.node_;
        }
    };

    template <class A, bool Unique>
    class c_iterator
        : public ::boost::iterator <
            std::forward_iterator_tag,
            BOOST_DEDUCED_TYPENAME A::value_type,
            std::ptrdiff_t,
            BOOST_DEDUCED_TYPENAME A::const_pointer,
            BOOST_DEDUCED_TYPENAME A::const_reference >
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef BOOST_DEDUCED_TYPENAME buckets::node node;
        typedef BOOST_DEDUCED_TYPENAME buckets::node_ptr node_ptr;
        typedef ::boost::unordered::iterator_detail::iterator<A, Unique>
            iterator;
        friend class ::boost::unordered::iterator_detail::iterator<A, Unique>;
        friend class ::boost::unordered::detail::iterator_access;
        node_ptr node_;

    public:

        c_iterator() : node_() {}
        explicit c_iterator(node_ptr const& x) : node_(x) {}
        c_iterator(iterator const& x) : node_(x.node_) {}
        BOOST_DEDUCED_TYPENAME A::const_reference operator*() const {
            return node::get_value(node_);
        }
        value_type const* operator->() const {
            return &node::get_value(node_);
        }
        c_iterator& operator++() {
            node_ = node_->next_; return *this;
        }
        c_iterator operator++(int) {
            c_iterator tmp(node_); node_ = node_->next_; return tmp;
        }
        bool operator==(iterator const& x) const {
            return node_ == x.node_;
        }
        bool operator==(c_iterator const& x) const {
            return node_ == x.node_;
        }
        bool operator!=(iterator const& x) const {
            return node_ != x.node_;
        }
        bool operator!=(c_iterator const& x) const {
            return node_ != x.node_;
        }
    };
}}}

#endif
