/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_ITERATOR_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_ITERATOR_HPP_INCLUDED

#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/view/ext_/detail/next_impl.hpp>
#include <boost/fusion/view/ext_/detail/deref_impl.hpp>
#include <boost/fusion/view/ext_/detail/equal_to_impl.hpp>
#include <boost/fusion/view/ext_/segmented_begin.hpp>
#include <boost/fusion/view/ext_/segmented_end.hpp>

namespace boost { namespace fusion
{
    struct segmented_iterator_tag {};
    
    // A segmented iterator is a stack of segment nodes.
    // Note: push_front/pop_front create views. That should
    // be good enough.
    template<typename Nodes>
    struct segmented_iterator
      : fusion::iterator_base<segmented_iterator<Nodes> >
    {
        typedef forward_traversal_tag category;
        typedef segmented_iterator_tag fusion_tag;

        explicit segmented_iterator(Nodes const &ns)
          : nodes(ns)
        {}

        typedef Nodes nodes_type;
        nodes_type nodes;
    };

}}

#endif
