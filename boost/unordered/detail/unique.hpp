
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_UNIQUE_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_UNIQUE_HPP_INCLUDED

#include <boost/unordered/detail/extract_key.hpp>

namespace boost { namespace unordered { namespace detail {

    template <class T>
    class unique_table : public T::table_base
    {
    public:
        typedef typename T::hasher hasher;
        typedef typename T::key_equal key_equal;
        typedef typename T::value_allocator value_allocator;
        typedef typename T::key_type key_type;
        typedef typename T::value_type value_type;
        typedef typename T::table_base table_base;
        typedef typename T::node_constructor node_constructor;
        typedef typename T::node_allocator node_allocator;

        typedef typename T::node node;
        typedef typename T::node_ptr node_ptr;
        typedef typename T::bucket_ptr bucket_ptr;
        typedef typename T::extractor extractor;
        
        typedef std::pair<node_ptr, bool> emplace_return;

        // Constructors

        unique_table(std::size_t n, hasher const& hf, key_equal const& eq,
            value_allocator const& a)
          : table_base(n, hf, eq, a) {}
        unique_table(unique_table const& x)
          : table_base(x,
                allocator_traits<node_allocator>::
                select_on_container_copy_construction(x.node_alloc())) {}
        unique_table(unique_table const& x, value_allocator const& a)
          : table_base(x, a) {}
        unique_table(unique_table& x, move_tag m)
          : table_base(x, m) {}
        unique_table(unique_table& x, value_allocator const& a,
            move_tag m)
          : table_base(x, a, m) {}
        ~unique_table() {}

        // equals

        bool equals(unique_table const& other) const
        {
            if(this->size_ != other.size_) return false;
            if(!this->size_) return true;
    
            for(node_ptr n1 = this->get_bucket(this->bucket_count_)->next_;
                n1; n1 = n1->next_)
            {
                node_ptr n2 = other.find_matching_node(n1);

#if !defined(BOOST_UNORDERED_DEPRECATED_EQUALITY)
                if(!n2 || node::get_value(n1) != node::get_value(n2))
                    return false;
#else
                if(!n2 || !extractor::compare_mapped(
                        node::get_value(n1), node::get_value(n2)))
                    return false;
#endif
            }
    
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        // A convenience method for adding nodes.

        node_ptr add_node(
                node_constructor& a,
                std::size_t bucket_index,
                std::size_t hash)        
        {
            bucket_ptr b = this->get_bucket(bucket_index);
            node_ptr n = a.release();
            node::set_hash(n, hash);
    
            if (!b->next_)
            {
                bucket_ptr start_node = this->get_bucket(this->bucket_count_);
                
                if (start_node->next_) {
                    this->buckets_[
                        node::get_hash(start_node->next_) % this->bucket_count_
                    ].next_ = n;
                }
    
                b->next_ = start_node;
                n->next_ = start_node->next_;
                start_node->next_ = n;
            }
            else
            {
                n->next_ = b->next_->next_;
                b->next_->next_ = n;
            }
    
            ++this->size_;
            return n;
        }

        ////////////////////////////////////////////////////////////////////////////
        // Insert methods

        // if hash function throws, basic exception safety
        // strong otherwise

        value_type& operator[](key_type const& k)
        {
            typedef typename value_type::second_type mapped_type;
    
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr pos = this->find_node(bucket_index, hash, k);
    
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                return node::get_value(pos);
            }
    
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct_pair(k, (mapped_type*) 0);
    
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(this->reserve_for_insert(this->size_ + 1))
                bucket_index = hash % this->bucket_count_;
    
            // Nothing after this point can throw.
    
            return node::get_value(add_node(a, bucket_index, hash));
        }

        emplace_return emplace_impl_with_node(node_constructor& a)
        {
            // No side effects in this initial code
            key_type const& k = this->get_key(a.value());
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr pos = this->find_node(bucket_index, hash, k);
            
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                // Found an existing key, return it (no throw).
                return emplace_return(pos, false);
            }
    
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(this->reserve_for_insert(this->size_ + 1))
                bucket_index = hash % this->bucket_count_;
    
            // Nothing after this point can throw.
    
            return emplace_return(add_node(a, bucket_index, hash), true);
        }

        emplace_return insert(value_type const& v)
        {
            key_type const& k = extractor::extract(v);
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr pos = this->find_node(bucket_index, hash, k);
    
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                // Found an existing key, return it (no throw).
                return emplace_return(pos, false);
            }
    
            // Isn't in table, add to bucket.
    
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct(v);
    
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(this->reserve_for_insert(this->size_ + 1))
                bucket_index = hash % this->bucket_count_;
    
            // Nothing after this point can throw.
    
            return emplace_return(add_node(a, bucket_index, hash), true);
        }


#if defined(BOOST_NO_RVALUE_REFERENCES)
        emplace_return emplace(please_ignore_this_overload const&)
        {
            BOOST_ASSERT(false);
            return emplace_return(this->begin(), false);
        }
#endif

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)

        template<class... Args>
        emplace_return emplace(Args&&... args)
        {
            return emplace_impl(
                    extractor::extract(std::forward<Args>(args)...),
                    std::forward<Args>(args)...);
        }

        template<class... Args>
        emplace_return emplace_impl(key_type const& k, Args&&... args)
        {
            // No side effects in this initial code
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr pos = this->find_node(bucket_index, hash, k);
    
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                // Found an existing key, return it (no throw).
                return emplace_return(pos, false);
            }
    
            // Doesn't already exist, add to bucket.
            // Side effects only in this block.
    
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);
    
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(this->reserve_for_insert(this->size_ + 1))
                bucket_index = hash % this->bucket_count_;
    
            // Nothing after this point can throw.
    
            return emplace_return(add_node(a, bucket_index, hash), true);
        }

        template<class... Args>
        emplace_return emplace_impl(no_key, Args&&... args)
        {
            // Construct the node regardless - in order to get the key.
            // It will be discarded if it isn't used
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);
            return emplace_impl_with_node(a);
        }
#else

        template <class Arg0>
        emplace_return emplace(BOOST_FWD_REF(Arg0) arg0)
        {
            return emplace_impl(
                extractor::extract(boost::forward<Arg0>(arg0)),
                boost::forward<Arg0>(arg0));
        }

#define BOOST_UNORDERED_INSERT1_IMPL(z, n, _)                               \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                      \
        emplace_return emplace(                                             \
            BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                          \
        {                                                                   \
            return emplace_impl(extractor::extract(arg0, arg1),             \
                    BOOST_UNORDERED_CALL_PARAMS(z, n));                     \
        }

#define BOOST_UNORDERED_INSERT2_IMPL(z, n, _)                               \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                      \
        emplace_return emplace_impl(key_type const& k,                      \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                           \
        {                                                                   \
            std::size_t hash = this->hash_function()(k);                    \
            std::size_t bucket_index = hash % this->bucket_count_;          \
            node_ptr pos = this->find_node(bucket_index, hash, k);          \
                                                                            \
            if (BOOST_UNORDERED_BORLAND_BOOL(pos)) {                        \
                return emplace_return(pos, false);                          \
            } else {                                                        \
                node_constructor a(*this);                                  \
                a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));             \
                                                                            \
                if(this->reserve_for_insert(this->size_ + 1))               \
                    bucket_index = hash % this->bucket_count_;              \
                                                                            \
                return emplace_return(                                      \
                    add_node(a, bucket_index, hash),                        \
                    true);                                                  \
            }                                                               \
        }                                                                   \
                                                                            \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, n)>                      \
        emplace_return emplace_impl(no_key,                                 \
           BOOST_UNORDERED_FUNCTION_PARAMS(z, n))                           \
        {                                                                   \
            node_constructor a(*this);                                      \
            a.construct(BOOST_UNORDERED_CALL_PARAMS(z, n));                 \
            return emplace_impl_with_node(a);                               \
        }

        BOOST_PP_REPEAT_FROM_TO(2, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_INSERT1_IMPL, _)
        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_INSERT2_IMPL, _)

#undef BOOST_UNORDERED_INSERT1_IMPL
#undef BOOST_UNORDERED_INSERT2_IMPL

#endif

        ////////////////////////////////////////////////////////////////////////
        // Insert range methods
        //
        // if hash function throws, or inserting > 1 element, basic exception
        // safety strong otherwise

        template <class InputIt>
        void insert_range(InputIt i, InputIt j)
        {
            if(i != j)
                return insert_range_impl(extractor::extract(*i), i, j);
        }

        template <class InputIt>
        void insert_range_impl(key_type const&, InputIt i, InputIt j)
        {
            node_constructor a(*this);

            // Special case for empty buckets so that we can use
            // max_load_ (which isn't valid when buckets_ is null).
            if (!this->buckets_) {
                insert_range_empty(a, extractor::extract(*i), i, j);
                if (++i == j) return;
            }

            do {
                // Note: can't use get_key as '*i' might not be value_type - it
                // could be a pair with first_types as key_type without const or a
                // different second_type.
                //
                // TODO: Might be worth storing the value_type instead of the key
                // here. Could be more efficient if '*i' is expensive. Could be
                // less efficient if copying the full value_type is expensive.
                insert_range_impl2(a, extractor::extract(*i), i, j);
            } while(++i != j);
        }

        template <class InputIt>
        void insert_range_empty(node_constructor& a, key_type const& k,
            InputIt i, InputIt j)
        {
            std::size_t hash = this->hash_function()(k);
            a.construct(*i);
            this->reserve_for_insert(this->size_ + insert_size(i, j));
            add_node(a, hash % this->bucket_count_, hash);
        }

        template <class InputIt>
        void insert_range_impl2(node_constructor& a, key_type const& k,
            InputIt i, InputIt j)
        {
            // No side effects in this initial code
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr pos = this->find_node(bucket_index, hash, k);
    
            if (!BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                // Doesn't already exist, add to bucket.
                // Side effects only in this block.
    
                // Create the node before rehashing in case it throws an
                // exception (need strong safety in such a case).
                a.construct(*i);
    
                // reserve has basic exception safety if the hash function
                // throws, strong otherwise.
                if(this->size_ + 1 >= this->max_load_) {
                    this->reserve_for_insert(this->size_ + insert_size(i, j));
                    bucket_index = hash % this->bucket_count_;
                }
    
                // Nothing after this point can throw.
                add_node(a, bucket_index, hash);
            }
        }

        template <class InputIt>
        void insert_range_impl(no_key, InputIt i, InputIt j)
        {
            node_constructor a(*this);

            do {
                // No side effects in this initial code
                a.construct(*i);
                emplace_impl_with_node(a);
            } while(++i != j);
        }
    };

    template <class H, class P, class A>
    struct set : public types<
        typename allocator_traits<A>::value_type,
        typename allocator_traits<A>::value_type,
        H, P, A,
        set_extractor<typename allocator_traits<A>::value_type>,
        true>
    {        
        typedef ::boost::unordered::detail::unique_table<set<H, P, A> > impl;
        typedef ::boost::unordered::detail::table<set<H, P, A> > table_base;
    };

    template <class K, class H, class P, class A>
    struct map : public types<
        K, typename allocator_traits<A>::value_type,
        H, P, A,
        map_extractor<K, typename allocator_traits<A>::value_type>,
        true>
    {
        typedef ::boost::unordered::detail::unique_table<map<K, H, P, A> > impl;
        typedef ::boost::unordered::detail::table<map<K, H, P, A> > table_base;
    };
}}}

#endif
