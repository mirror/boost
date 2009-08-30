
// Copyright (C) 2003-2004 Jeremy B. Maitin-Shepard.
// Copyright (C) 2005-2009 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This contains the basic data structure, apart from the actual values. There's
// no construction or deconstruction here. So this only depends on the pointer
// type.

#ifndef BOOST_UNORDERED_DETAIL_NODE_HPP_INCLUDED
#define BOOST_UNORDERED_DETAIL_NODE_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/unordered/detail/fwd.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, <= 0X0582)
#define BOOST_UNORDERED_BORLAND_BOOL(x) (bool)(x)
#else
#define BOOST_UNORDERED_BORLAND_BOOL(x) x
#endif

namespace boost { namespace unordered_detail {

    template <class BucketPtr>
    static inline BucketPtr& next_node(BucketPtr ptr)
    {
        return ptr->next_;
    }

    template <class BucketPtr>
    static inline std::size_t node_count(BucketPtr ptr, BucketPtr end)
    {
        std::size_t count = 0;
        while(ptr != end) {
            ++count;
            ptr = next_node(ptr);
        }
        return count;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // ungrouped node implementation
    
    template <class A>
    inline BOOST_DEDUCED_TYPENAME ungrouped_node_base<A>::node_ptr&
        ungrouped_node_base<A>::next_group(node_ptr ptr)
    {
        return next_node(ptr);
    }

    template <class A>
    inline std::size_t ungrouped_node_base<A>::group_count(node_ptr)
    {
        return 1;
    }

    template <class A>
    inline void ungrouped_node_base<A>::add_to_bucket(node_ptr n, bucket& b)
    {
        next_node(n) = b.next_;
        b.next_ = n;
    }

    template <class A>
    inline void ungrouped_node_base<A>::add_group_to_bucket(node_ptr n, bucket& b)
    {
        next_node(n) = b.next_;
        b.next_ = n;
    }

    template <class A>
    inline void ungrouped_node_base<A>::add_after_node(node_ptr n, node_ptr position)
    {
        next_node(n) = next_node(position);
        next_node(position) = position;
    }
    
    template <class A>
    void ungrouped_node_base<A>::unlink_node(bucket& b, node_ptr node)
    {
        unlink_nodes(b, node, next_node(node));
    }

    template <class A>
    void ungrouped_node_base<A>::unlink_nodes(bucket& b, node_ptr begin, node_ptr end)
    {
        node_ptr* pos = &b.next_;
        while(*pos != begin) pos = &next_node(*pos);
        *pos = end;
    }

    template <class A>
    void ungrouped_node_base<A>::unlink_nodes(bucket& b, node_ptr end)
    {
        b.next_ = end;
    }

    template <class A>
    inline void ungrouped_node_base<A>::unlink_group(node_ptr* b)
    {
        *b = next_node(*b);
    }

    ////////////////////////////////////////////////////////////////////////////
    // grouped node implementation
    
    template <class A>
    inline BOOST_DEDUCED_TYPENAME grouped_node_base<A>::node_ptr&
        grouped_node_base<A>::group_prev(node_ptr ptr)
    {
        return get(ptr).group_prev_;
    }

    template <class A>
    inline BOOST_DEDUCED_TYPENAME grouped_node_base<A>::node_ptr&
        grouped_node_base<A>::next_group(node_ptr ptr)
    {
        return next_node(group_prev(ptr));
    }

    template <class A>
    inline std::size_t grouped_node_base<A>::group_count(node_ptr ptr)
    {
        node_ptr start = ptr;
        std::size_t size = 0;
        do {
            ++size;
            ptr = group_prev(ptr);
        } while(ptr != start);
        return size;
    }

    template <class A>
    inline void grouped_node_base<A>::add_to_bucket(node_ptr n, bucket& b)
    {
        next_node(n) = b.next_;
        group_prev(n) = n;
        b.next_ = n;
    }

    template <class A>
    inline void grouped_node_base<A>::add_group_to_bucket(node_ptr n, bucket& b)
    {
        next_group(n) = b.next_;
        b.next_ = n;
    }

    template <class A>
    inline void grouped_node_base<A>::add_after_node(node_ptr n, node_ptr position)
    {
        next_node(n) = next_group(position);
        group_prev(n) = group_prev(position);
        next_group(position) = n;
        group_prev(position) = n;
    }

    // Break a ciruclar list into two, with split as the beginning
    // of the second group (if split is at the beginning then don't
    // split).
    template <class A>
    inline BOOST_DEDUCED_TYPENAME grouped_node_base<A>::node_ptr
        grouped_node_base<A>::split_group(node_ptr split)
    {
        // If split is at the beginning of the group then there's
        // nothing to split.
        if(next_node(group_prev(split)) != split)
            return split;

        // Find the start of the group.
        node_ptr start = split;
        do {
            start = group_prev(start);
        } while(next_node(group_prev(start)) == start);

        node_ptr last = group_prev(start);
        group_prev(start) = group_prev(split);
        group_prev(split) = last;

        return start;
    }

    template <class A>
    void grouped_node_base<A>::unlink_node(bucket& b, node_ptr node)
    {
        node_ptr next = next_node(node);
        node_ptr* pos = &next_node(group_prev(node));

        if(*pos != node) {
            // The node is at the beginning of a group.

            // Find the previous node pointer:
            pos = &b.next_;
            while(*pos != node) pos = &next_group(*pos);

            // Remove from group
            if(BOOST_UNORDERED_BORLAND_BOOL(next) && group_prev(next) == node)
                group_prev(next) = group_prev(node);
        }
        else if(BOOST_UNORDERED_BORLAND_BOOL(next) && group_prev(next) == node) {
            // The deleted node is not at the end of the group, so
            // change the link from the next node.
            group_prev(next) = group_prev(node);
        }
        else {
            // The deleted node is at the end of the group, so the
            // first node in the group is pointing to it.
            // Find that to change its pointer.
            node_ptr x = group_prev(node);
            while(group_prev(x) != node) {
                x = group_prev(x);
            }
            group_prev(x) = group_prev(node);
        }
        *pos = next;
    }

    template <class A>
    void grouped_node_base<A>::unlink_nodes(bucket& b, node_ptr begin, node_ptr end)
    {
        node_ptr* pos = &next_node(group_prev(begin));

        if(*pos != begin) {
            // The node is at the beginning of a group.

            // Find the previous node pointer:
            pos = &b.next_;
            while(*pos != begin) pos = &next_group(*pos);

            // Remove from group
            if(BOOST_UNORDERED_BORLAND_BOOL(end)) split_group(end);
        }
        else {
            node_ptr group1 = split_group(begin);
            if(BOOST_UNORDERED_BORLAND_BOOL(end)) {
                node_ptr group2 = split_group(end);

                if(begin == group2) {
                    node_ptr end1 = group_prev(group1);
                    node_ptr end2 = group_prev(group2);
                    group_prev(group1) = end2;
                    group_prev(group2) = end1;
                }
            }
        }
        *pos = end;
    }

    template <class A>
    void grouped_node_base<A>::unlink_nodes(bucket& b, node_ptr end)
    {
        split_group(end);
        b.next_ = end;
    }

    template <class A>
    inline void grouped_node_base<A>::unlink_group(node_ptr* b)
    {
        *b = next_group(*b);
    }    
}}

#endif
