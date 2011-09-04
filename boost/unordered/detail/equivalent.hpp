
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2011 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_UNORDERED_DETAIL_EQUIVALENT_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_EQUIVALENT_HPP_INCLUDED

#include <boost/unordered/detail/extract_key.hpp>

namespace boost { namespace unordered { namespace detail {

    template <class T>
    class equivalent_table : public T::table_base
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

        // Constructors

        equivalent_table(std::size_t n,
            hasher const& hf, key_equal const& eq, value_allocator const& a)
          : table_base(n, hf, eq, a) {}
        equivalent_table(equivalent_table const& x)
          : table_base(x,
                allocator_traits<node_allocator>::
                select_on_container_copy_construction(x.node_alloc())) {}
        equivalent_table(equivalent_table const& x,
            value_allocator const& a)
          : table_base(x, a) {}
        equivalent_table(equivalent_table& x, move_tag m)
          : table_base(x, m) {}
        equivalent_table(equivalent_table& x,
            value_allocator const& a, move_tag m)
          : table_base(x, a, m) {}
        ~equivalent_table() {}

        // Equality

        bool equals(equivalent_table const& other) const
        {
            if(this->size_ != other.size_) return false;
            if(!this->size_) return true;
    
            for(node_ptr n1 = this->buckets_[this->bucket_count_].next_; n1;)
            {
                node_ptr n2 = other.find_matching_node(n1);
                if (!n2) return false;
                node_ptr end1 = node::next_group(n1);
                node_ptr end2 = node::next_group(n2);
                if (!group_equals(n1, end1, n2, end2)) return false;
                n1 = end1;    
            }
    
            return true;
        }

#if !defined(BOOST_UNORDERED_DEPRECATED_EQUALITY)

        static bool group_equals(node_ptr n1, node_ptr end1,
                node_ptr n2, node_ptr end2)
        {
            for(;;)
            {
                if (node::get_value(n1) != node::get_value(n2))
                    break;

                n1 = n1->next_;
                n2 = n2->next_;
            
                if (n1 == end1) return n2 == end2;
                if (n2 == end2) return false;
            }
            
            for(node_ptr n1a = n1, n2a = n2;;)
            {
                n1a = n1a->next_;
                n2a = n2a->next_;

                if (n1a == end1)
                {
                    if (n2a == end2) break;
                    else return false;
                }
                if (n2a == end2) return false;
            }

            node_ptr start = n1;
            for(;n1 != end2; n1 = n1->next_)
            {
                value_type const& v = node::get_value(n1);
                if (find(start, n1, v)) continue;
                std::size_t matches = count_equal(n2, end2, v);
                if (!matches || matches != 1 + count_equal(n1->next_, end1, v))
                    return false;
            }
            
            return true;
        }

#else

        static bool group_equals(node_ptr n1, node_ptr end1,
                node_ptr n2, node_ptr end2)
        {
            for(;;)
            {
                if(!extractor::compare_mapped(
                    node::get_value(n1), node::get_value(n2)))
                    return false;

                n1 = n1->next_;
                n2 = n2->next_;

                if (n1 == end1) return n2 == end2;
                if (n2 == end2) return false;
            }
        }

#endif

        static bool find(node_ptr n, node_ptr end, value_type const& v)
        {
            for(;n != end; n = n->next_)
                if (node::get_value(n) == v)
                    return true;
            return false;
        }
        
        static std::size_t count_equal(node_ptr n, node_ptr end, value_type const& v)
        {
            std::size_t count = 0;
            for(;n != end; n = n->next_)
                if (node::get_value(n) == v) ++count;
            return count;
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

#if defined(BOOST_NO_RVALUE_REFERENCES)
        node_ptr emplace(please_ignore_this_overload const&)
        {
            BOOST_ASSERT(false);
            return this->begin();
        }
#endif

#if defined(BOOST_UNORDERED_STD_FORWARD_MOVE)

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
            insert_for_range(i, j,
                BOOST_DEDUCED_TYPENAME ::boost::iterator_traversal<I>::type());
        }

    };

    template <class H, class P, class A>
    struct multiset : public types<
        typename allocator_traits<A>::value_type,
        typename allocator_traits<A>::value_type,
        H, P, A,
        set_extractor<typename allocator_traits<A>::value_type>,
        false>
    {
        typedef equivalent_table<multiset<H, P, A> > impl;
        typedef table<multiset<H, P, A> > table_base;
    };

    template <class K, class H, class P, class A>
    struct multimap : public types<
        K, typename allocator_traits<A>::value_type,
        H, P, A,
        map_extractor<K, typename allocator_traits<A>::value_type>,
        false>
    {
        typedef equivalent_table<multimap<K, H, P, A> > impl;
        typedef table<multimap<K, H, P, A> > table_base;
    };
}}}

#endif
