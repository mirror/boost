
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_UNIQUE_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_UNIQUE_HPP_INCLUDED

#include <boost/unordered/detail/extract_key.hpp>

namespace boost { namespace unordered { namespace detail {

    template <class T>
    class unique_table : public T::table
    {
    public:
        typedef BOOST_DEDUCED_TYPENAME T::hasher hasher;
        typedef BOOST_DEDUCED_TYPENAME T::key_equal key_equal;
        typedef BOOST_DEDUCED_TYPENAME T::value_allocator value_allocator;
        typedef BOOST_DEDUCED_TYPENAME T::key_type key_type;
        typedef BOOST_DEDUCED_TYPENAME T::value_type value_type;
        typedef BOOST_DEDUCED_TYPENAME T::table table;
        typedef BOOST_DEDUCED_TYPENAME T::node_constructor node_constructor;

        typedef BOOST_DEDUCED_TYPENAME T::node node;
        typedef BOOST_DEDUCED_TYPENAME T::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME T::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME T::extractor extractor;
        
        typedef std::pair<node_ptr, bool> emplace_return;

        // Constructors

        unique_table(std::size_t n, hasher const& hf, key_equal const& eq,
            value_allocator const& a)
          : table(n, hf, eq, a) {}
        unique_table(unique_table const& x)
          : table(x, x.node_alloc()) {}
        unique_table(unique_table const& x, value_allocator const& a)
          : table(x, a) {}
        unique_table(unique_table& x, move_tag m)
          : table(x, m) {}
        unique_table(unique_table& x, value_allocator const& a,
            move_tag m)
          : table(x, a, m) {}
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
                if(!BOOST_UNORDERED_BORLAND_BOOL(n2)) return false;
                if(!extractor::compare_mapped(
                    node::get_value(n1), node::get_value(n2)))
                    return false;
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
            typedef BOOST_DEDUCED_TYPENAME value_type::second_type mapped_type;
    
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


#if defined(BOOST_UNORDERED_STD_FORWARD)

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
        emplace_return emplace(Arg0 const& arg0)
        {
            return emplace_impl(extractor::extract(arg0), arg0);
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
        BOOST_DEDUCED_TYPENAME A::value_type,
        BOOST_DEDUCED_TYPENAME A::value_type,
        H, P, A,
        set_extractor<BOOST_DEDUCED_TYPENAME A::value_type>,
        true>
    {        
        typedef ::boost::unordered::detail::unique_table<set<H, P, A> > impl;
        typedef ::boost::unordered::detail::table<set<H, P, A> > table;
    };

    template <class K, class H, class P, class A>
    struct map : public types<
        K, BOOST_DEDUCED_TYPENAME A::value_type,
        H, P, A,
        map_extractor<K, BOOST_DEDUCED_TYPENAME A::value_type>,
        true>
    {
        typedef ::boost::unordered::detail::unique_table<map<K, H, P, A> > impl;
        typedef ::boost::unordered::detail::table<map<K, H, P, A> > table;
    };
}}}

#endif
