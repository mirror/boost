
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This contains the basic data structure, apart from the actual values. There's
// no construction or deconstruction here. So this only depends on the pointer
// type.

#ifndef BOOST_UNORDERED_DETAIL_NODE_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_NODE_HPP_INCLUDED

#include <boost/unordered/detail/util.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, <= 0X0582)
#define BOOST_UNORDERED_BORLAND_BOOL(x) (bool)(x)
#else
#define BOOST_UNORDERED_BORLAND_BOOL(x) x
#endif

namespace boost { namespace unordered { namespace detail {

    ////////////////////////////////////////////////////////////////////////////
    //
    // This section implements buckets and nodes. Here's a rough
    // inheritance diagram, to show how they pull together.
    //
    // For unordered_set/unordered_map:
    //
    //  bucket<A>              value_base<A::value_type>
    //     |                            |
    //     +--------------+-------------+
    //                    |
    //             ungrouped_node<A>
    //
    // For unordered_multiset/unordered_multimap:
    //
    //  bucket<A>              value_base<A::value_type>
    //     |                            |
    //     +--------------+-------------+
    //                    |
    //              grouped_node<A>

    // bucket
    //
    // bucket is used for both the buckets and as a base class for
    // nodes. By using 'bucket_ptr' for 'node_ptr', 'next_' can point
    // to either a bucket or a node. This is used later to implement a
    // sentinel at the end of the bucket array.
    
    template <class A>
    class bucket
    {
        bucket& operator=(bucket const&);
    public:
        typedef BOOST_DEDUCED_TYPENAME
            ::boost::unordered::detail::rebind_wrap<A, bucket>::type
            bucket_allocator;
        typedef BOOST_DEDUCED_TYPENAME bucket_allocator::pointer bucket_ptr;
        typedef bucket_ptr node_ptr;
    
        node_ptr next_;

        bucket() : next_() {}
    };

    // The space used to store values in a node.

    template <class ValueType>
    struct value_base
    {
        typedef ValueType value_type;
        BOOST_DEDUCED_TYPENAME ::boost::aligned_storage<
            sizeof(value_type),
            ::boost::alignment_of<value_type>::value>::type data_;

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

    // In containers with equivalent keys (unordered_multimap and
    // unordered_multiset) equivalent nodes are grouped together, in
    // containers with unique keys (unordered_map and unordered_set)
    // individual nodes are treated as groups of one. The following two
    // classes implement the data structure.

    // This is used for containers with unique keys. There are no groups
    // so it doesn't add any extra members, and just treats individual
    // nodes as groups of one.

    template <class A>
    struct ungrouped_node
      : ::boost::unordered::detail::bucket<A>,
        value_base<BOOST_DEDUCED_TYPENAME A::value_type>
    {
        typedef ::boost::unordered::detail::bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME bucket::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

        std::size_t hash_;

        ungrouped_node() : bucket() {}

        void init(node_ptr) {}

        static node_ptr next_group(node_ptr ptr)
        {
            return ptr->next_;
        }

        static node_ptr next_group2(node_ptr ptr)
        {
            return ptr->next_;
        }

        static std::size_t group_count(node_ptr n)
        {
            return !n ? 0 : 1;
        }

        static void add_after_node(node_ptr n, node_ptr position)
        {
            n->next_ = position->next_;
            position->next_ = position;            
        }

        static node_ptr unlink_node(bucket& b, node_ptr n)
        {
            return unlink_nodes(b, n, n->next_);
        }

        static node_ptr unlink_nodes(bucket& b, node_ptr begin, node_ptr end)
        {
            node_ptr prev = b.next_;
            while(prev->next_ != begin) prev = prev->next_;
            prev->next_ = end;
            return prev;
        }
        
        static std::size_t get_hash(node_ptr p)
        {
            return static_cast<ungrouped_node&>(*p).hash_;
        }

        static void set_hash(node_ptr p, std::size_t hash)
        {
            static_cast<ungrouped_node&>(*p).hash_ = hash;
        }

        static value_type& get_value(node_ptr p)
        {
            return static_cast<ungrouped_node&>(*p).value();
        }

        static value_type* get_value_ptr(node_ptr p)
        {
            return static_cast<ungrouped_node&>(*p).value_ptr();
        }
    };

    // This is used for containers with equivalent keys. It implements a
    // circular list running in the opposite direction to the linked
    // list through the nodes.

    template <class A>
    struct grouped_node
      : ::boost::unordered::detail::bucket<A>,
        value_base<BOOST_DEDUCED_TYPENAME A::value_type>
    {
        typedef ::boost::unordered::detail::bucket<A> bucket;
        typedef BOOST_DEDUCED_TYPENAME bucket::bucket_ptr bucket_ptr;
        typedef BOOST_DEDUCED_TYPENAME bucket::node_ptr node_ptr;
        typedef BOOST_DEDUCED_TYPENAME A::value_type value_type;

        std::size_t hash_;
        node_ptr group_prev_;

        grouped_node() : bucket(), group_prev_() {}
        void init(node_ptr n)
        {
            group_prev_ = n;
        }

        static node_ptr next_group(node_ptr ptr)
        {
            return get(ptr).group_prev_->next_;
        }

        static node_ptr next_group2(node_ptr ptr)
        {
            return get(ptr->next_).group_prev_;
        }

        static std::size_t group_count(node_ptr ptr)
        {
            if (!ptr) return 0;

            node_ptr start = ptr;
            std::size_t size = 0;
            do {
                ++size;
                ptr = get(ptr).group_prev_;
            } while(ptr != start);
            return size;
        }

        static void add_after_node(node_ptr n, node_ptr pos)
        {
            n->next_ = get(pos).group_prev_->next_;
            get(n).group_prev_ = get(pos).group_prev_;
            get(pos).group_prev_->next_ = n;
            get(pos).group_prev_ = n;
        }

        static node_ptr unlink_node(bucket& b, node_ptr n)
        {
            node_ptr next = n->next_;
            node_ptr prev = get(n).group_prev_;
    
            if(prev->next_ != n) {
                // The node is at the beginning of a group.
    
                // Find the previous node pointer:
                prev = b.next_;
                while(prev->next_ != n) {
                    prev = next_group2(prev);
                }
    
                // Remove from group
                if(BOOST_UNORDERED_BORLAND_BOOL(next) &&
                    get(next).group_prev_ == n)
                {
                    get(next).group_prev_ = get(n).group_prev_;
                }
            }
            else if(BOOST_UNORDERED_BORLAND_BOOL(next) &&
                get(next).group_prev_ == n)
            {
                // The deleted node is not at the end of the group, so
                // change the link from the next node.
                get(next).group_prev_ = get(n).group_prev_;
            }
            else {
                // The deleted node is at the end of the group, so the
                // first node in the group is pointing to it.
                // Find that to change its pointer.
                node_ptr x = get(n).group_prev_;
                while(get(x).group_prev_ != n) {
                    x = get(x).group_prev_;
                }
                get(x).group_prev_ = get(n).group_prev_;
            }
            prev->next_ = next;
    
            return prev;
        }

        static node_ptr unlink_nodes(bucket& b, node_ptr begin, node_ptr end)
        {
            node_ptr prev = get(begin).group_prev_;
    
            if(prev->next_ != begin) {
                // The node is at the beginning of a group.
    
                // Find the previous node pointer:
                prev = b.next_;
                while(prev->next_ != begin) prev = next_group2(prev);
    
                if(BOOST_UNORDERED_BORLAND_BOOL(end)) split_group(end);
            }
            else {
                node_ptr group1 = split_group(begin);
                if(BOOST_UNORDERED_BORLAND_BOOL(end)) {
                    node_ptr group2 = split_group(end);
    
                    if(begin == group2) {
                        node_ptr end1 = get(group1).group_prev_;
                        node_ptr end2 = get(group2).group_prev_;
                        get(group1).group_prev_ = end2;
                        get(group2).group_prev_ = end1;
                    }
                }
            }
    
            prev->next_ = end;
    
            return prev;
        }

        // Break a ciruclar list into two, with split as the beginning
        // of the second group (if split is at the beginning then don't
        // split).
        static node_ptr split_group(node_ptr split)
        {
            // Find first node in group.
            node_ptr first = split;
            while(next_group(first) == first)
                first = get(first).group_prev_;

            if(first == split) return split;
    
            node_ptr last = get(first).group_prev_;
            get(first).group_prev_ = get(split).group_prev_;
            get(split).group_prev_ = last;
    
            return first;
        }

        static std::size_t get_hash(node_ptr p) {
            return static_cast<grouped_node&>(*p).hash_;
        }
        static void set_hash(node_ptr p, std::size_t hash) {
            static_cast<grouped_node&>(*p).hash_ = hash;
        }
        static value_type& get_value(node_ptr p) {
            return static_cast<grouped_node&>(*p).value();
        }
        static value_type* get_value_ptr(node_ptr p) {
            return static_cast<grouped_node&>(*p).value_ptr();
        }

        static grouped_node& get(node_ptr ptr) {
            return static_cast<grouped_node&>(*ptr);
        }
    };

    // These two classes implement an easy way to pass around the node
    // group policy classes without the messy template parameters.
    // Whenever you see the template parameter 'G' it's one of these.

    struct ungrouped
    {
        template <class A>
        struct node {
            typedef ungrouped_node<A> type;
        };
    };

    struct grouped
    {
        template <class A>
        struct node {
            typedef grouped_node<A> type;
        };
    };

}}}

#endif
