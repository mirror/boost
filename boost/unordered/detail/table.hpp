
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_ALL_HPP_INCLUDED

#include <boost/unordered/detail/buckets.hpp>
#include <boost/unordered/detail/util.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <cmath>

namespace boost { namespace unordered { namespace detail {

    ////////////////////////////////////////////////////////////////////////////
    // convert double to std::size_t

    inline std::size_t double_to_size(double f)
    {
        return f >= static_cast<double>(
            (std::numeric_limits<std::size_t>::max)()) ?
            (std::numeric_limits<std::size_t>::max)() :
            static_cast<std::size_t>(f);
    }

    // The space used to store values in a node.

    template <typename ValueType>
    struct value_base
    {
        typedef ValueType value_type;

        typename boost::aligned_storage<
            sizeof(value_type),
            boost::alignment_of<value_type>::value>::type data_;

        void* address() {
            return this;
        }

        value_type& value() {
            return *(ValueType*) this;
        }

        value_type* value_ptr() {
            return (ValueType*) this;
        }

    private:

        value_base& operator=(value_base const&);
    };

    template <typename NodeAlloc>
    struct copy_nodes
    {
        typedef boost::unordered::detail::allocator_traits<NodeAlloc>
            node_allocator_traits;

        node_constructor<NodeAlloc> constructor;

        explicit copy_nodes(NodeAlloc& a) : constructor(a) {}

        typename node_allocator_traits::pointer create(
                typename node_allocator_traits::value_type::value_type const& v)
        {
            constructor.construct_with_value2(v);
            return constructor.release();
        }
    };

    template <typename NodeAlloc>
    struct move_nodes
    {
        typedef boost::unordered::detail::allocator_traits<NodeAlloc>
            node_allocator_traits;

        node_constructor<NodeAlloc> constructor;

        explicit move_nodes(NodeAlloc& a) : constructor(a) {}

        typename node_allocator_traits::pointer create(
                typename node_allocator_traits::value_type::value_type& v)
        {
            constructor.construct_with_value2(boost::move(v));
            return constructor.release();
        }
    };

    template <typename Buckets>
    struct assign_nodes
    {
        node_holder<typename Buckets::node_allocator> holder;

        explicit assign_nodes(Buckets& b) : holder(b) {}

        typename Buckets::node_pointer create(
                typename Buckets::value_type const& v)
        {
            return holder.copy_of(v);
        }
    };

    template <typename Buckets>
    struct move_assign_nodes
    {
        node_holder<typename Buckets::node_allocator> holder;

        explicit move_assign_nodes(Buckets& b) : holder(b) {}

        typename Buckets::node_pointer create(
                typename Buckets::value_type& v)
        {
            return holder.move_copy_of(v);
        }
    };

    template <typename Types>
    struct table :
        boost::unordered::detail::buckets<
            typename Types::allocator,
            typename Types::bucket,
            typename Types::node,
            typename Types::policy>,
        boost::unordered::detail::functions<
            typename Types::hasher,
            typename Types::key_equal>
    {
    private:
        table(table const&);
        table& operator=(table const&);
    public:
        typedef typename Types::hasher hasher;
        typedef typename Types::key_equal key_equal;
        typedef typename Types::key_type key_type;
        typedef typename Types::extractor extractor;
        typedef typename Types::value_type value_type;
        typedef typename Types::table table_impl;
        typedef typename Types::link_pointer link_pointer;
        typedef typename Types::policy policy;

        typedef boost::unordered::detail::functions<
            typename Types::hasher,
            typename Types::key_equal> functions;

        typedef boost::unordered::detail::buckets<
            typename Types::allocator,
            typename Types::bucket,
            typename Types::node,
            typename Types::policy> buckets;

        typedef typename buckets::node_allocator node_allocator;
        typedef typename buckets::node_allocator_traits node_allocator_traits;
        typedef typename buckets::node_pointer node_pointer;
        typedef typename buckets::const_node_pointer const_node_pointer;

        typedef typename table::iterator iterator;

        // Members

        float mlf_;
        std::size_t max_load_; // Only use if this->buckets_.

        ////////////////////////////////////////////////////////////////////////
        // Load methods

        std::size_t max_size() const
        {
            using namespace std;
    
            // size < mlf_ * count
            return boost::unordered::detail::double_to_size(ceil(
                    static_cast<double>(this->mlf_) *
                    static_cast<double>(this->max_bucket_count())
                )) - 1;
        }

        std::size_t calculate_max_load()
        {
            using namespace std;
    
            // From 6.3.1/13:
            // Only resize when size >= mlf_ * count
            return boost::unordered::detail::double_to_size(ceil(
                    static_cast<double>(this->mlf_) *
                    static_cast<double>(this->bucket_count_)
                ));

        }
        void max_load_factor(float z)
        {
            BOOST_ASSERT(z > 0);
            mlf_ = (std::max)(z, minimum_max_load_factor);
            if (this->buckets_)
                this->max_load_ = this->calculate_max_load();
        }

        std::size_t min_buckets_for_size(std::size_t size) const
        {
            BOOST_ASSERT(this->mlf_ >= minimum_max_load_factor);
    
            using namespace std;
    
            // From 6.3.1/13:
            // size < mlf_ * count
            // => count > size / mlf_
            //
            // Or from rehash post-condition:
            // count > size / mlf_

            return policy::new_bucket_count(
                boost::unordered::detail::double_to_size(floor(
                    static_cast<double>(size) /
                    static_cast<double>(mlf_))) + 1);
        }

        ////////////////////////////////////////////////////////////////////////
        // Constructors

        table(std::size_t num_buckets,
                hasher const& hf,
                key_equal const& eq,
                node_allocator const& a) :
            buckets(a, policy::new_bucket_count(num_buckets)),
            functions(hf, eq),
            mlf_(1.0f),
            max_load_(0)
        {}

        table(table const& x, node_allocator const& a) :
            buckets(a, x.min_buckets_for_size(x.size_)),
            functions(x),
            mlf_(x.mlf_),
            max_load_(0)
        {
            if(x.size_) {
                this->create_buckets(this->bucket_count_);
                copy_nodes<node_allocator> copy(this->node_alloc());
                table_impl::fill_buckets(x.get_start(), *this, copy);
                this->max_load_ = calculate_max_load();
            }
        }

        // TODO: Why calculate_max_load?
        table(table& x, boost::unordered::detail::move_tag m) :
            buckets(x, m),
            functions(x),
            mlf_(x.mlf_),
            max_load_(calculate_max_load())
        {}

        // TODO: Why not calculate_max_load?
        // TODO: Why do I use x's bucket count?
        table(table& x, node_allocator const& a,
                boost::unordered::detail::move_tag m) :
            buckets(a, x.bucket_count_),
            functions(x),
            mlf_(x.mlf_),
            max_load_(x.max_load_)
        {
            if(a == x.node_alloc()) {
                this->move_buckets_from(x);
            }
            else if(x.size_) {
                // Use a temporary table because moving the nodes leaves the
                // source container in a complete mess.

                buckets tmp(x, m);

                this->create_buckets(this->bucket_count_);
                move_nodes<node_allocator> move(this->node_alloc());
                table_impl::fill_buckets(tmp.get_start(), *this, move);

                this->max_load_ = calculate_max_load();
            }
        }

        // Iterators

        iterator begin() const {
            return !this->buckets_ ?
                iterator() : this->get_start();
        }

        // Assignment

        void assign(table const& x)
        {
            if (this != boost::addressof(x))
            {
                assign(x,
                    boost::unordered::detail::integral_constant<bool,
                        allocator_traits<node_allocator>::
                        propagate_on_container_copy_assignment::value>());
            }
        }

        void assign(table const& x, false_type)
        {
            // Strong exception safety.
            boost::unordered::detail::set_hash_functions<hasher, key_equal>
                new_func_this(*this, x);
            new_func_this.commit();
            mlf_ = x.mlf_;
            this->max_load_ = this->calculate_max_load();

            if (!this->size_ && !x.size_) return;

            if (!this->buckets_ || x.size_ >= this->max_load_) {
                this->create_buckets(min_buckets_for_size(x.size_));
                this->max_load_ = this->calculate_max_load();
            }
            else {
                this->clear_buckets();
            }

            // assign_nodes takes ownership of the container's elements,
            // assigning to them if possible, and deleting any that are
            // left over.
            assign_nodes<table> assign(*this);

            if (x.size_) {
                table_impl::fill_buckets(x.get_start(), *this, assign);
            }
        }

        void assign(table const& x, true_type)
        {
            if (this->node_alloc() == x.node_alloc()) {
                this->allocators_.assign(x.allocators_);
                this->assign(x, false_type());
            }
            else {
                boost::unordered::detail::set_hash_functions<hasher, key_equal>
                    new_func_this(*this, x);

                // Delete everything with current allocators before assigning
                // the new ones.
                if (this->buckets_) this->delete_buckets();
                this->allocators_.assign(x.allocators_);

                // Copy over other data, all no throw.
                new_func_this.commit();
                this->mlf_ = x.mlf_;
                this->bucket_count_ = this->min_buckets_for_size(x.size_);
                this->max_load_ = 0;

                // Finally copy the elements.
                if (x.size_) {
                    this->create_buckets(this->bucket_count_);
                    copy_nodes<node_allocator> copy(this->node_alloc());
                    table_impl::fill_buckets(x.get_start(), *this, copy);
                    this->max_load_ = this->calculate_max_load();
                }
            }
        }

        void move_assign(table& x)
        {
            if (this != boost::addressof(x))
            {
                move_assign(x,
                    boost::unordered::detail::integral_constant<bool,
                        allocator_traits<node_allocator>::
                        propagate_on_container_move_assignment::value>());
            }
        }

        void move_assign(table& x, true_type)
        {
            if(this->buckets_) this->delete_buckets();
            this->allocators_.move_assign(x.allocators_);
            move_assign_no_alloc(x);
        }

        void move_assign(table& x, false_type)
        {
            if (this->node_alloc() == x.node_alloc()) {
                if(this->buckets_) this->delete_buckets();
                move_assign_no_alloc(x);
            }
            else {
                boost::unordered::detail::set_hash_functions<hasher, key_equal>
                    new_func_this(*this, x);
                new_func_this.commit();
                mlf_ = x.mlf_;
                this->max_load_ = this->calculate_max_load();

                if (!this->size_ && !x.size_) return;

                if (!this->buckets_ || x.size_ >= max_load_) {
                    this->create_buckets(min_buckets_for_size(x.size_));
                    this->max_load_ = this->calculate_max_load();
                }
                else {
                    this->clear_buckets();
                }

                // move_assign_nodes takes ownership of the container's
                // elements, assigning to them if possible, and deleting
                // any that are left over.
                move_assign_nodes<table> assign(*this);

                if (x.size_) {
                    node_holder<node_allocator> nodes(x);
                    table_impl::fill_buckets(nodes.get_start(), *this, assign);
                }
            }
        }
        
        void move_assign_no_alloc(table& x)
        {
            boost::unordered::detail::set_hash_functions<hasher, key_equal>
                new_func_this(*this, x);
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
            swap(x,
                boost::unordered::detail::integral_constant<bool,
                    allocator_traits<node_allocator>::
                    propagate_on_container_swap::value>());
        }

        // Only swaps the allocators if Propagate::value
        template <typename Propagate>
        void swap(table& x, Propagate p)
        {
            // According to 23.2.1.8, if propagate_on_container_swap is
            // false the behaviour is undefined unless the allocators
            // are equal.
            BOOST_ASSERT(p.value || this->node_alloc() == x.node_alloc());

            boost::unordered::detail::set_hash_functions<hasher, key_equal>
                op1(*this, x);
            boost::unordered::detail::set_hash_functions<hasher, key_equal>
                op2(x, *this);
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

        // Accessors

        key_type const& get_key(value_type const& x) const
        {
            return extractor::extract(x);
        }

        std::size_t hash(key_type const& k) const
        {
            return policy::apply_hash(this->hash_function(), k);
        }

        // Find Node

        template <typename Key, typename Hash, typename Pred>
        iterator generic_find_node(
                Key const& k,
                Hash const& hf,
                Pred const& eq) const
        {
            if (!this->size_) return iterator();
            return static_cast<table_impl const*>(this)->
                find_node_impl(policy::apply_hash(hf, k), k, eq);
        }

        iterator find_node(
                std::size_t key_hash,
                key_type const& k) const
        {
            if (!this->size_) return iterator();
            return static_cast<table_impl const*>(this)->
                find_node_impl(key_hash, k, this->key_eq());
        }

        iterator find_node(key_type const& k) const
        {
            if (!this->size_) return iterator();
            return static_cast<table_impl const*>(this)->
                find_node_impl(this->hash(k), k, this->key_eq());
        }

        iterator find_matching_node(iterator n) const
        {
            // TODO: Does this apply to C++11?
            //
            // For some stupid reason, I decided to support equality comparison
            // when different hash functions are used. So I can't use the hash
            // value from the node here.
    
            return find_node(get_key(*n));
        }

        // Reserve and rehash

        void reserve_for_insert(std::size_t);
        void rehash(std::size_t);
        void reserve(std::size_t);
    };

    ////////////////////////////////////////////////////////////////////////////
    // Reserve & Rehash

    // basic exception safety
    template <typename Types>
    inline void table<Types>::reserve_for_insert(std::size_t size)
    {
        if (!this->buckets_) {
            this->create_buckets((std::max)(this->bucket_count_,
                this->min_buckets_for_size(size)));
            this->max_load_ = this->calculate_max_load();
        }
        // According to the standard this should be 'size >= max_load_',
        // but I think this is better, defect report filed.
        else if(size > max_load_) {
            std::size_t num_buckets
                = this->min_buckets_for_size((std::max)(size,
                    this->size_ + (this->size_ >> 1)));
            if (num_buckets != this->bucket_count_) {
                static_cast<table_impl*>(this)->rehash_impl(num_buckets);
                this->max_load_ = this->calculate_max_load();
            }
        }
    }

    // if hash function throws, basic exception safety
    // strong otherwise.

    template <typename Types>
    inline void table<Types>::rehash(std::size_t min_buckets)
    {
        using namespace std;

        if(!this->size_) {
            if(this->buckets_) this->delete_buckets();
            this->bucket_count_ = policy::new_bucket_count(min_buckets);
        }
        else {
            min_buckets = policy::new_bucket_count((std::max)(min_buckets,
                boost::unordered::detail::double_to_size(floor(
                    static_cast<double>(this->size_) /
                    static_cast<double>(mlf_))) + 1));

            if(min_buckets != this->bucket_count_) {
                static_cast<table_impl*>(this)->rehash_impl(min_buckets);
                this->max_load_ = this->calculate_max_load();
            }
        }
    }

    template <typename Types>
    inline void table<Types>::reserve(std::size_t num_elements)
    {
        rehash(static_cast<std::size_t>(
            std::ceil(static_cast<double>(num_elements) / this->mlf_)));
    }
}}}

#endif
