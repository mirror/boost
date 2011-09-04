
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
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
    class table : public T::buckets, public T::functions
    {
        table(table const&);
        table& operator=(table const&);
    public:
        typedef typename T::hasher hasher;
        typedef typename T::key_equal key_equal;
        typedef typename T::value_allocator value_allocator;
        typedef typename T::key_type key_type;
        typedef typename T::value_type value_type;
        typedef typename T::functions functions;
        typedef typename T::buckets buckets;
        typedef typename T::extractor extractor;
        typedef typename T::node_constructor node_constructor;

        typedef typename T::node node;
        typedef typename T::bucket bucket;
        typedef typename T::node_ptr node_ptr;
        typedef typename T::bucket_ptr bucket_ptr;
        typedef typename T::node_allocator node_allocator;
        typedef typename T::iterator_pair iterator_pair;

        // Members
        
        float mlf_;
        std::size_t max_load_; // Only use if this->buckets_.

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
            return this->find_node_impl(hash % this->bucket_count_, hash, k, eq);
        }
        
        node_ptr find_node(
                std::size_t bucket_index,
                std::size_t hash,
                key_type const& k) const
        {
            if (!this->size_) return node_ptr();
            return this->find_node_impl(bucket_index, hash, k, this->key_eq());
        }

        node_ptr find_node(key_type const& k) const
        {
            if (!this->size_) return node_ptr();
            std::size_t hash = this->hash_function()(k);
            return this->find_node_impl(hash % this->bucket_count_, hash, k,
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
                    static_cast<double>(this->mlf_) *
                    static_cast<double>(this->max_bucket_count())
                )) - 1;
        }

        std::size_t calculate_max_load()
        {
            using namespace std;
    
            // From 6.3.1/13:
            // Only resize when size >= mlf_ * count
            return double_to_size_t(ceil(
                    static_cast<double>(this->mlf_) *
                    static_cast<double>(this->bucket_count_)
                ));

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
            return next_prime(double_to_size_t(floor(
                static_cast<double>(size) /
                static_cast<double>(mlf_))) + 1);
        }

        ////////////////////////////////////////////////////////////////////////
        // Constructors

        table(std::size_t num_buckets,
                hasher const& hf,
                key_equal const& eq,
                node_allocator const& a)
          : buckets(a, next_prime(num_buckets)),
            functions(hf, eq),
            mlf_(1.0f),
            max_load_(0)
        {
        }

        table(table const& x, node_allocator const& a)
          : buckets(a, x.min_buckets_for_size(x.size_)),
            functions(x),
            mlf_(x.mlf_),
            max_load_(0)
        {
            if(x.size_) {
                x.copy_buckets_to(*this);
                this->max_load_ = calculate_max_load();
            }
        }

        table(table& x, move_tag m)
          : buckets(x, m),
            functions(x),
            mlf_(x.mlf_),
            max_load_(calculate_max_load()) {}

        // TODO: Why do I use x's bucket count?
        table(table& x, node_allocator const& a, move_tag m)
          : buckets(a, x.bucket_count_),
            functions(x),
            mlf_(x.mlf_),
            max_load_(x.max_load_)
        {
            if(a == x.node_alloc()) {
                this->buckets::swap(x, false_type());
            }
            else if(x.size_) {
                // Use a temporary table because move_buckets_to leaves the
                // source container in a complete mess.
                buckets tmp(x, m);
                tmp.move_buckets_to(*this);
                this->max_load_ = calculate_max_load();
            }
        }

        ~table()
        {}

        // Iterators

        node_ptr begin() const {
            return !this->buckets_ ?
                node_ptr() : this->buckets_[this->bucket_count_].next_;
        }

        void assign(table const& x)
        {
            assign(x, integral_constant<bool,
                allocator_traits<node_allocator>::
                propagate_on_container_copy_assignment::value>());
        }

        void assign(table const& x, false_type)
        {
            table tmp(x, this->node_alloc());
            this->swap(tmp, false_type());
        }

        void assign(table const& x, true_type)
        {
            table tmp(x, x.node_alloc());
            // Need to delete before setting the allocator so that buckets
            // aren't deleted with the wrong allocator.
            if(this->buckets_) this->delete_buckets();
            // TODO: Can allocator assignment throw?
            this->allocators_.assign(x.allocators_);
            this->swap(tmp, false_type());
        }

        void move_assign(table& x)
        {
            move_assign(x, integral_constant<bool,
                allocator_traits<node_allocator>::
                propagate_on_container_move_assignment::value>());
        }
        
        void move_assign(table& x, true_type)
        {
            if(this->buckets_) this->delete_buckets();
            this->allocators_.move_assign(x.allocators_);
            move_assign_no_alloc(x);
        }

        void move_assign(table& x, false_type)
        {
            if(this->node_alloc() == x.node_alloc()) {
                if(this->buckets_) this->delete_buckets();
                move_assign_no_alloc(x);
            }
            else {
                set_hash_functions<hasher, key_equal> new_func_this(*this, x);

                if (x.size_) {
                    buckets b(this->node_alloc(), x.min_buckets_for_size(x.size_));
                    buckets tmp(x, move_tag());
                    tmp.move_buckets_to(b);
                    b.swap(*this);
                }
                else {
                    this->clear();
                }
                
                this->mlf_ = x.mlf_;
                if (this->buckets_) this->max_load_ = calculate_max_load();
                new_func_this.commit();
            }
        }
        
        void move_assign_no_alloc(table& x)
        {
            set_hash_functions<hasher, key_equal> new_func_this(*this, x);
            // No throw from here.
            this->move_buckets_from(x);
            this->mlf_ = x.mlf_;
            this->max_load_ = x.max_load_;
            new_func_this.commit();
        }

        ////////////////////////////////////////////////////////////////////////
        // Swap & Move

        void swap(table& x)
        {
            swap(x, integral_constant<bool,
                    allocator_traits<node_allocator>::
                    propagate_on_container_swap::value>());
        }

        // Only swaps the allocators if Propagate::value
        template <typename Propagate>
        void swap(table& x, Propagate p)
        {
            set_hash_functions<hasher, key_equal> op1(*this, x);
            set_hash_functions<hasher, key_equal> op2(x, *this);
            // I think swap can throw if Propagate::value,
            // since the allocators' swap can throw. Not sure though.
            this->buckets::swap(x, p);
            std::swap(this->mlf_, x.mlf_);
            std::swap(this->max_load_, x.max_load_);
            op1.commit();
            op2.commit();
        }

        // Swap everything but the allocators, and the functions objects.
        void swap_contents(table& x)
        {
            this->buckets::swap(x, false_type());
            std::swap(this->mlf_, x.mlf_);
            std::swap(this->max_load_, x.max_load_);
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
            return this->delete_nodes(pos, end);
        }

        // Reserve and rehash

        bool reserve_for_insert(std::size_t);
        void rehash(std::size_t);
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // Reserve & Rehash

    // basic exception safety
    template <class T>
    inline bool table<T>::reserve_for_insert(std::size_t size)
    {
        if (!this->buckets_) {
            std::size_t old_bucket_count = this->bucket_count_;
            this->bucket_count_ = (std::max)(this->bucket_count_,
                this->min_buckets_for_size(size));
            this->create_buckets();
            this->max_load_ = calculate_max_load();
            return old_bucket_count != this->bucket_count_;
        }
        else if(size >= max_load_) {
            std::size_t num_buckets
                = this->min_buckets_for_size((std::max)(size,
                    this->size_ + (this->size_ >> 1)));
            if (num_buckets != this->bucket_count_) {
                this->rehash_impl(num_buckets);
                this->max_load_ = calculate_max_load();
                return true;
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
        }
        else {
            // no throw:
            min_buckets = next_prime((std::max)(min_buckets,
                double_to_size_t(floor(
                    static_cast<double>(this->size_) /
                    static_cast<double>(mlf_))) + 1));
            if(min_buckets != this->bucket_count_) {
                this->rehash_impl(min_buckets);
                this->max_load_ = calculate_max_load();
            }
        }
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
        typedef ::boost::unordered::detail::functions<hasher, key_equal> functions;

        typedef typename buckets::node node;
        typedef typename buckets::bucket bucket;
        typedef typename buckets::node_ptr node_ptr;
        typedef typename buckets::bucket_ptr bucket_ptr;
        typedef typename buckets::node_allocator node_allocator;

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
            typename boost::unordered::detail::allocator_traits<A>::value_type,
            std::ptrdiff_t,
            typename boost::unordered::detail::allocator_traits<A>::pointer,
            typename boost::unordered::detail::allocator_traits<A>::value_type&>
    {
    public:
        typedef typename boost::unordered::detail::allocator_traits<A>::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef typename buckets::node_ptr node_ptr;
        typedef typename buckets::node node;
        typedef cl_iterator<A, Unique> const_local_iterator;

        friend class cl_iterator<A, Unique>;
        
        node_ptr ptr_;
        std::size_t bucket_;
        std::size_t bucket_count_;

    public:
        l_iterator() : ptr_() {}
        l_iterator(node_ptr x, std::size_t b, std::size_t c)
            : ptr_(x), bucket_(b), bucket_count_(c) {}
        typename boost::unordered::detail::allocator_traits<A>::value_type& operator*() const {
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
            typename boost::unordered::detail::allocator_traits<A>::value_type,
            std::ptrdiff_t,
            typename boost::unordered::detail::allocator_traits<A>::const_pointer,
            typename boost::unordered::detail::allocator_traits<A>::value_type const& >
    {
    public:
        typedef typename boost::unordered::detail::allocator_traits<A>::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef typename buckets::node_ptr node_ptr;
        typedef typename buckets::node node;
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
        typename boost::unordered::detail::allocator_traits<A>::value_type const&
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
            typename boost::unordered::detail::allocator_traits<A>::value_type,
            std::ptrdiff_t,
            typename boost::unordered::detail::allocator_traits<A>::pointer,
            typename boost::unordered::detail::allocator_traits<A>::value_type& >
    {
    public:
        typedef typename boost::unordered::detail::allocator_traits<A>::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef typename buckets::node node;
        typedef typename buckets::node_ptr node_ptr;
        typedef c_iterator<A, Unique> const_iterator;
        friend class c_iterator<A, Unique>;
        node_ptr node_;

    public:

        iterator() : node_() {}
        explicit iterator(node_ptr const& x) : node_(x) {}
        typename boost::unordered::detail::allocator_traits<A>::value_type& operator*() const {
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
            typename boost::unordered::detail::allocator_traits<A>::value_type,
            std::ptrdiff_t,
            typename boost::unordered::detail::allocator_traits<A>::const_pointer,
            typename boost::unordered::detail::allocator_traits<A>::value_type const& >
    {
    public:
        typedef typename boost::unordered::detail::allocator_traits<A>::value_type value_type;

    private:
        typedef ::boost::unordered::detail::buckets<A, Unique> buckets;
        typedef typename buckets::node node;
        typedef typename buckets::node_ptr node_ptr;
        typedef ::boost::unordered::iterator_detail::iterator<A, Unique>
            iterator;
        friend class ::boost::unordered::iterator_detail::iterator<A, Unique>;

#if !defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)
        template <class K, class T, class H, class P, class A2>
        friend class ::boost::unordered::unordered_map;
        template <class K, class T, class H, class P, class A2>
        friend class ::boost::unordered::unordered_multimap;
        template <class T, class H, class P, class A2>
        friend class ::boost::unordered::unordered_set;
        template <class T, class H, class P, class A2>
        friend class ::boost::unordered::unordered_multiset;
#else
    public:
#endif

        node_ptr node_;

    public:

        c_iterator() : node_() {}
        explicit c_iterator(node_ptr const& x) : node_(x) {}
        c_iterator(iterator const& x) : node_(x.node_) {}
        typename boost::unordered::detail::allocator_traits<A>::value_type const& operator*() const {
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
