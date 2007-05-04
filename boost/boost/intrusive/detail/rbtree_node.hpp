/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztañaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_RBTREE_NODE_HPP
#define BOOST_INTRUSIVE_RBTREE_NODE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/intrusive/detail/pointer_type.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/get_pointer.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <cstddef>
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/intrusive/pointer_plus_bit.hpp>

namespace boost {
namespace intrusive {

namespace detail {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                Generic node_traits for any pointer type                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//This is the compact representation: 3 pointers
template<class VoidPointer>
struct compact_rbtree_node
{
   typedef typename pointer_to_other
      <VoidPointer
      ,compact_rbtree_node<VoidPointer> >::type node_ptr;
   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
};

//This is the normal representation: 3 pointers + enum
template<class VoidPointer>
struct rbtree_node
{
   typedef typename pointer_to_other
      <VoidPointer
      ,rbtree_node<VoidPointer> >::type   node_ptr;

   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
   color color_;
};

//This is the default node traits implementation
//using a node with 3 generic pointers plus an enum
template<class VoidPointer>
struct default_rbtree_node_traits_impl
{
   typedef rbtree_node<VoidPointer> node;

   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type          node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type    const_node_ptr;

   typedef typename node::color color;

   static node_ptr get_parent(const_node_ptr n)
   {  return n->parent_;  }

   static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   static color get_color(const_node_ptr n)
   {  return n->color_;  }

   static void set_color(node_ptr n, color c)
   {  n->color_ = c;  }

   static color black()
   {  return node::black_t;  }

   static color red()
   {  return node::red_t;  }
};

//This is the compact node traits implementation
//using a node with 3 generic pointers
template<class VoidPointer>
struct compact_rbtree_node_traits_impl
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type          node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type    const_node_ptr;

   typedef pointer_plus_bit<node_ptr> ptr_bit;

   typedef typename node::color color;

   static node_ptr get_parent(const_node_ptr n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

   static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   static color get_color(const_node_ptr n)
   {  return (color)ptr_bit::get_bit(n->parent_);  }

   static void set_color(node_ptr n, color c)
   {  ptr_bit::set_bit(n->parent_, c != 0);  }

   static color black()
   {  return node::black_t;  }

   static color red()
   {  return node::red_t;  }
};

//Dispatches the implementation based on the boolean
template<class VoidPointer, bool compact>
struct rbtree_node_traits_dispatch
   :  public default_rbtree_node_traits_impl<VoidPointer>
{};

template<class VoidPointer>
struct rbtree_node_traits_dispatch<VoidPointer, true>
   :  public compact_rbtree_node_traits_impl<VoidPointer>
{};

//Inherit from the dispatcher depending on the embedding capabilities
template<class VoidPointer>
struct rbtree_node_traits
   :  public rbtree_node_traits_dispatch
         <VoidPointer
         ,has_pointer_plus_bit
            < typename pointer_to_other
               <VoidPointer
               , compact_rbtree_node<VoidPointer>
               >::type
            >::value
         >
{};

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                   Implementation of the rbtree iterator                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

template<class T, class ValueTraits>
class rbtree_iterator
  : public boost::iterator_facade
         < rbtree_iterator<T, ValueTraits>
         , T
         , boost::bidirectional_traversal_tag
         , T&
         , typename std::iterator_traits<typename ValueTraits::node_ptr>::difference_type
         >
{
   typedef typename ValueTraits::node_traits    node_traits;
   typedef typename node_traits::node           node;
   typedef typename node_traits::node_ptr       node_ptr;
   typedef typename node_traits::const_node_ptr const_node_ptr;
   typedef rbtree_algorithms<node_traits>       node_algorithms;
   struct enabler{};

   public:
   typedef typename pointer_to_other<typename ValueTraits::node_ptr, T>::type pointer;
   typedef typename std::iterator_traits<node_ptr>::difference_type difference_type;

   rbtree_iterator ()
      :  node_ (0)
   {}

   explicit rbtree_iterator(node_ptr node)
      :  node_ (node)
   {}

   template <class OtherValue>
   rbtree_iterator(rbtree_iterator<OtherValue, ValueTraits> const& other
                ,typename boost::enable_if<
                        boost::is_convertible<OtherValue*,T*>
                     , enabler
                     >::type = enabler()
                 )
      :  node_(other.pointed_node())
   {}

   const node_ptr &pointed_node() const
   { return node_; }

   private:
   friend class boost::iterator_core_access;
   template <class, class> friend class rbtree_iterator;

   template <class OtherValue>
   bool equal(rbtree_iterator<OtherValue, ValueTraits> const& other) const
   {  return other.pointed_node() == node_;  }

   void increment()
   {  node_ = node_algorithms::next_node(node_);   }

   void decrement()
   {  node_ = node_algorithms::prev_node(node_);   }

   T& dereference() const
   { return *ValueTraits::to_value_ptr(node_); }

   node_ptr node_;
};

} //namespace detail 
} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_NODE_HPP
