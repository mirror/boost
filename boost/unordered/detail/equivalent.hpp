
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_EQUIVALENT_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_EQUIVALENT_HPP_INCLUDED

#include <boost/unordered/detail/extract_key.hpp>

namespace boost { namespace unordered { namespace detail {

    template <class T>
    class equivalent_table : public T::table
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

        // Constructors

        equivalent_table(std::size_t n,
            hasher const& hf, key_equal const& eq, value_allocator const& a)
          : table(n, hf, eq, a) {}
        equivalent_table(equivalent_table const& x)
          : table(x, x.node_alloc()) {}
        equivalent_table(equivalent_table const& x,
            value_allocator const& a)
          : table(x, a) {}
        equivalent_table(equivalent_table& x, move_tag m)
          : table(x, m) {}
        equivalent_table(equivalent_table& x,
            value_allocator const& a, move_tag m)
          : table(x, a, m) {}
        ~equivalent_table() {}

        // Equality

        bool equals(equivalent_table const& other) const
        {
            if(this->size_ != other.size_) return false;
            if(!this->size_) return true;
    
            for(node_ptr n1 = this->buckets_[this->bucket_count_].next_; n1;)
            {
                node_ptr n2 = other.find_matching_node(n1);
                if(!n2) return false;
    
                node_ptr end1 = node::next_group(n1);
                node_ptr end2 = node::next_group(n2);
    
                do {
                    if(!extractor::compare_mapped(
                        node::get_value(n1), node::get_value(n2)))
                        return false;
                    n1 = n1->next_;
                    n2 = n2->next_;
                } while(n1 != end1 && n2 != end2);
                if(n1 != end1 || n2 != end2) return false;
            }
    
            return true;
        }

        ////////////////////////////////////////////////////////////////////////
        // A convenience method for adding nodes.

        inline node_ptr add_node(
                node_constructor& a,
                std::size_t bucket_index,
                std::size_t hash,
                node_ptr pos)
        {
            node_ptr n = a.release();
            node::set_hash(n, hash);
    
            if(BOOST_UNORDERED_BORLAND_BOOL(pos)) {
                node::add_after_node(n, pos);
                if (n->next_) {
                    std::size_t next_bucket =
                        node::get_hash(n->next_) % this->bucket_count_;
                    if (next_bucket != bucket_index) {
                        this->buckets_[next_bucket].next_ = n;
                    }
                }
            }
            else {
                bucket_ptr b = this->get_bucket(bucket_index);
    
                if (!b->next_)
                {
                    bucket_ptr start_node =
                        this->get_bucket(this->bucket_count_);
                    
                    if (BOOST_UNORDERED_BORLAND_BOOL(start_node->next_)) {
                        this->buckets_[
                            node::get_hash(start_node->next_) %
                                this->bucket_count_].next_ = n;
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
            }
            ++this->size_;
            return n;
        }

        ////////////////////////////////////////////////////////////////////////
        // Insert methods

        node_ptr emplace_impl(node_constructor& a)
        {
            key_type const& k = this->get_key(a.value());
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            node_ptr position = this->find_node(bucket_index, hash, k);
    
            // reserve has basic exception safety if the hash function
            // throws, strong otherwise.
            if(this->reserve_for_insert(this->size_ + 1)) {
                bucket_index = hash % this->bucket_count_;
            }
    
            return add_node(a, bucket_index, hash, position);
        }

        void emplace_impl_no_rehash(node_constructor& a)
        {
            key_type const& k = this->get_key(a.value());
            std::size_t hash = this->hash_function()(k);
            std::size_t bucket_index = hash % this->bucket_count_;
            add_node(a, bucket_index, hash,
                this->find_node(bucket_index, hash, k));
        }

#if defined(BOOST_UNORDERED_STD_FORWARD)

        template <class... Args>
        node_ptr emplace(Args&&... args)
        {
            // Create the node before rehashing in case it throws an
            // exception (need strong safety in such a case).
            node_constructor a(*this);
            a.construct(std::forward<Args>(args)...);
    
            return emplace_impl(a);
        }

#else

#define BOOST_UNORDERED_INSERT_IMPL(z, num_params, _)                       \
        template <BOOST_UNORDERED_TEMPLATE_ARGS(z, num_params)>             \
        node_ptr emplace(BOOST_UNORDERED_FUNCTION_PARAMS(z, num_params))    \
        {                                                                   \
            node_constructor a(*this);                                      \
            a.construct(BOOST_UNORDERED_CALL_PARAMS(z, num_params));        \
            return emplace_impl(a);                                         \
        }

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_UNORDERED_EMPLACE_LIMIT,
            BOOST_UNORDERED_INSERT_IMPL, _)

#undef BOOST_UNORDERED_INSERT_IMPL
#endif

        ////////////////////////////////////////////////////////////////////////
        // Insert range methods

        // if hash function throws, or inserting > 1 element, basic exception
        // safety. Strong otherwise
        template <class I>
        void insert_for_range(I i, I j, forward_traversal_tag)
        {
            if(i == j) return;
            std::size_t distance = ::boost::unordered::detail::distance(i, j);
            if(distance == 1) {
                emplace(*i);
            }
            else {
                // Only require basic exception safety here
                this->reserve_for_insert(this->size_ + distance);

                node_constructor a(*this);    
                for (; i != j; ++i) {
                    a.construct(*i);
                    emplace_impl_no_rehash(a);
                }
            }
        }

        template <class I>
        void insert_for_range(I i, I j, ::boost::incrementable_traversal_tag)
        {
            node_constructor a(*this);
            for (; i != j; ++i) {
                a.construct(*i);
                emplace_impl(a);
            }
        }

        // If hash function throws, or inserting > 1 element, basic exception
        // safety. Strong otherwise
        template <class I>
        void insert_range(I i, I j)
        {
            BOOST_DEDUCED_TYPENAME ::boost::iterator_traversal<I>::type
                iterator_traversal_tag;
            insert_for_range(i, j, iterator_traversal_tag);
        }

    };

    template <class H, class P, class A>
    struct multiset : public types<
        BOOST_DEDUCED_TYPENAME A::value_type,
        BOOST_DEDUCED_TYPENAME A::value_type,
        H, P, A,
        set_extractor<BOOST_DEDUCED_TYPENAME A::value_type>,
        false>
    {
        typedef equivalent_table<multiset<H, P, A> > impl;
        typedef table<multiset<H, P, A> > table;
    };

    template <class K, class H, class P, class A>
    struct multimap : public types<
        K, BOOST_DEDUCED_TYPENAME A::value_type,
        H, P, A,
        map_extractor<K, BOOST_DEDUCED_TYPENAME A::value_type>,
        false>
    {
        typedef equivalent_table<multimap<K, H, P, A> > impl;
        typedef table<multimap<K, H, P, A> > table;
    };
}}}

#endif
