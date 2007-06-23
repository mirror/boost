/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
// The internal implementation of red-black trees is based on that of SGI STL
// stl_tree.h file: 
//
// Copyright (c) 1996,1997
// Silicon Graphics Computer Systems, Inc.
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Silicon Graphics makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
//
//
// Copyright (c) 1994
// Hewlett-Packard Company
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Hewlett-Packard Company makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.

#ifndef BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <cstddef>
#include <boost/detail/no_exceptions_support.hpp>
#include <boost/intrusive/detail/utilities.hpp>


namespace boost {
namespace intrusive {

//! rbtree_algorithms provides basic algorithms to manipulate 
//! nodes forming a red-black tree. The insertion and deletion algorithms are 
//! based on those in Cormen, Leiserson, and Rivest, Introduction to Algorithms 
//! (MIT Press, 1990), except that
//! 
//! (1) the header node is maintained with links not only to the root
//! but also to the leftmost node of the tree, to enable constant time
//! begin(), and to the rightmost node of the tree, to enable linear time
//! performance when used with the generic set algorithms (set_union,
//! etc.);
//! 
//! (2) when a node being deleted has two children its successor node is
//! relinked into its place, rather than copied, so that the only
//! pointers invalidated are those referring to the deleted node.
//!
//! rbtree_algorithms is configured with a NodeTraits class, which capsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the circular list
//!
//! <tt>node_ptr</tt>: A pointer to a node
//!
//! <tt>const_node_ptr</tt>: A pointer to a const node
//!
//! <tt>color</tt>: The type that can store the color of a node
//!
//! <b>Static functions</b>:
//!
//! <tt>static node_ptr get_parent(const_node_ptr n);</tt>
//! 
//! <tt>static void set_parent(node_ptr n, node_ptr parent);</tt>
//!
//! <tt>static node_ptr get_left(const_node_ptr n);</tt>
//! 
//! <tt>static void set_left(node_ptr n, node_ptr left);</tt>
//!
//! <tt>static node_ptr get_right(const_node_ptr n);</tt>
//! 
//! <tt>static void set_right(node_ptr n, node_ptr right);</tt>
//! 
//! <tt>static color get_color(const_node_ptr n);</tt>
//! 
//! <tt>static void set_color(node_ptr n, color c);</tt>
//! 
//! <tt>static color black();</tt>
//! 
//! <tt>static color red();</tt>
template<class NodeTraits>
class rbtree_algorithms
{
   /// @cond
   private:
   typedef typename NodeTraits::node            node;
   /// @endcond

   public:
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef typename NodeTraits::color           color;

   /// @cond
   private:
   static node_ptr uncast(const_node_ptr ptr)
   {
      return node_ptr(const_cast<node*>(::boost::intrusive::detail::get_pointer(ptr)));
   }
   /// @endcond

   public:

   //! This type is the information that will be filled by insert_unique_check
   struct insert_commit_data
   {
      insert_commit_data()
         :  link_left(false)
         ,  node(0)
      {}
      bool     link_left;
      node_ptr node;
   };

   //! <b>Requires</b>: header1 and header2 must be the header nodes
   //!  of two trees.
   //! 
   //! <b>Effects</b>: Swaps two trees. After the function header1 will contain 
   //!   links to the second tree and header2 will have links to the first tree.
   //! 
   //! <b>Complexity</b>: Constant. 
   //! 
   //! <b>Throws</b>: Nothing.
   static void swap_tree(node_ptr header1, node_ptr header2)
   {
      if(header1 == header2)
         return;
   
      node_ptr tmp;

      //Parent swap
      tmp = NodeTraits::get_parent(header1);
      NodeTraits::set_parent(header1, NodeTraits::get_parent(header2));
      NodeTraits::set_parent(header2, tmp);
      //Left swap
      tmp = NodeTraits::get_left(header1);
      NodeTraits::set_left(header1, NodeTraits::get_left(header2));
      NodeTraits::set_left(header2, tmp);
      //Right swap
      tmp = NodeTraits::get_right(header1);
      NodeTraits::set_right(header1, NodeTraits::get_right(header2));
      NodeTraits::set_right(header2, tmp);

      //Now test parent
      node_ptr h1_parent(NodeTraits::get_parent(header1));
      if(h1_parent){
         NodeTraits::set_parent(h1_parent, header1);
      }
      else{
         NodeTraits::set_left(header1, header1);
         NodeTraits::set_right(header1, header1);
      }

      node_ptr h2_parent(NodeTraits::get_parent(header2));
      if(NodeTraits::get_parent(header2)){
         NodeTraits::set_parent(h2_parent, header2);
      }
      else{
         NodeTraits::set_left(header2, header2);
         NodeTraits::set_right(header2, header2);
      }
   }

   //! <b>Requires</b>: node is a tree node but not the header.
   //! 
   //! <b>Effects</b>: Unlinks the node and rebalances the tree.
   //! 
   //! <b>Complexity</b>: Average complexity is constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static void unlink_and_rebalance(node_ptr node)
   {
      if(NodeTraits::get_parent(node)){
         node_ptr x = NodeTraits::get_parent(node);
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node);
      }
   }

   //! <b>Requires</b>: header is the header of a tree.
   //! 
   //! <b>Effects</b>: Unlinks the leftmost node from the tree, and
   //!   updates the header link to the new leftmost node.
   //! 
   //! <b>Complexity</b>: Average complexity is constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Notes</b>: This function breaks the tree and the tree can
   //!   only be used for more unlink_leftmost_without_rebalance calls.
   //!   This function is normally used to achieve a step by step
   //!   controlled destruction of the tree.
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header)
   {
      node_ptr leftmost = NodeTraits::get_left(header);
      if (leftmost == header)
         return 0;
      node_ptr leftmost_parent(NodeTraits::get_parent(leftmost));
      node_ptr leftmost_right (NodeTraits::get_right(leftmost));
      bool is_root = leftmost_parent == header;

      if (leftmost_right){
         NodeTraits::set_parent(leftmost_right, leftmost_parent);
         NodeTraits::set_left(header, minimum(leftmost_right));

         if (is_root)
            NodeTraits::set_parent(header, leftmost_right);
         else
            NodeTraits::set_left(NodeTraits::get_parent(header), leftmost_right);
      }
      else if (is_root){
         NodeTraits::set_parent(header, 0);
         NodeTraits::set_left(header,  header);
         NodeTraits::set_right(header, header);
      }
      else{
         NodeTraits::set_left(leftmost_parent, 0);
         NodeTraits::set_left(header, leftmost_parent);
      }
      return leftmost;
   }

   //! <b>Requires</b>: node is a node of the tree or an node initialized
   //!   by init(...).
   //! 
   //! <b>Effects</b>: Returns true if the node is initialized by init().
   //! 
   //! <b>Complexity</b>: Constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static bool unique(const_node_ptr node)
   { return NodeTraits::get_parent(node) == 0; }

   //! <b>Requires</b>: node is a node of the tree but it's not the header.
   //! 
   //! <b>Effects</b>: Returns the number of nodes of the subtree.
   //! 
   //! <b>Complexity</b>: Constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static std::size_t count(const_node_ptr node)
   {
      std::size_t result = 1;
      if(NodeTraits::get_left(node))
         result += count(NodeTraits::get_left(node));
      if(NodeTraits::get_right(node))
         result += count(NodeTraits::get_right(node));
      return result;
   }

   //! <b>Requires</b>: p is a node from the tree except the header.
   //! 
   //! <b>Effects</b>: Returns the next node of the tree.
   //! 
   //! <b>Complexity</b>: Average constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static node_ptr next_node(node_ptr p)
   {
      node_ptr p_right(NodeTraits::get_right(p));
      if(p_right){
         return minimum(p_right);
      }
      else {
         node_ptr x = NodeTraits::get_parent(p);
         while(p == NodeTraits::get_right(x)){
            p = x;
            x = NodeTraits::get_parent(x);
         }
         return NodeTraits::get_right(p) != x ? x : uncast(p);
      }
   }

   //! <b>Requires</b>: p is a node from the tree except the leftmost node.
   //! 
   //! <b>Effects</b>: Returns the previous node of the tree.
   //! 
   //! <b>Complexity</b>: Average constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static node_ptr prev_node(node_ptr p)
   {
      if(is_header(p)){
         return NodeTraits::get_right(p); // p is header, return rightmost
      }
      else if(NodeTraits::get_left(p)){
         return maximum(NodeTraits::get_left(p));
      }
      else {
         node_ptr x = NodeTraits::get_parent(p);
         while(p == NodeTraits::get_left(x)){
            p = x;
            x = NodeTraits::get_parent(x);
         }
         return x;
      }
   }

   //! <b>Requires</b>: node must not be part of any tree.
   //!
   //! <b>Effects</b>: After the function unique(node) == true.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Nodes</b>: If node is inserted in a tree, this function corrupts the tree.
   static void init(node_ptr node)
   {
      NodeTraits::set_parent(node, 0);
      NodeTraits::set_left(node, 0);
      NodeTraits::set_right(node, 0); 
      NodeTraits::set_color(node, NodeTraits::black());
   };

   //! <b>Requires</b>: node must not be part of any tree.
   //!
   //! <b>Effects</b>: Initializes the header to represent an empty tree.
   //!   unique(header) == true.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Nodes</b>: If node is inserted in a tree, this function corrupts the tree.
   static void init_header(node_ptr header)
   {
      NodeTraits::set_parent(header, 0);
      NodeTraits::set_left(header, header);
      NodeTraits::set_right(header, header); 
      NodeTraits::set_color(header, NodeTraits::red()); 
   };

   //! <b>Requires</b>: header must be the header of a tree, z a node
   //!    of that tree and z != header.
   //!
   //! <b>Effects</b>: Erases node "z" from the tree with header "header".
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static node_ptr erase(node_ptr header, node_ptr z)
   {
      node_ptr y(z);
      node_ptr x(0);
      node_ptr x_parent(0);
      node_ptr y_left(NodeTraits::get_left(y));
      node_ptr y_right(NodeTraits::get_right(y));
      if(!y_left){
         x = y_right;    // x might be null.
      }
      else if(!y_right){ // z has exactly one non-null child. y == z.
         x = y_left;       // x is not null.
      }
      else{
         y = minimum (y_right);
         x = NodeTraits::get_right(y);     // x might be null.
      }

      if(y != z){
         // relink y in place of z.  y is z's successor
         NodeTraits::set_parent(NodeTraits::get_left(z), y);
         NodeTraits::set_left(y, NodeTraits::get_left(z));
         if(y != NodeTraits::get_right(z)){
            x_parent = NodeTraits::get_parent(y);
            if(x)
               NodeTraits::set_parent(x, NodeTraits::get_parent(y));
            NodeTraits::set_left(NodeTraits::get_parent(y), x);   // y must be a child of left_
            NodeTraits::set_right(y, NodeTraits::get_right(z));
            NodeTraits::set_parent(NodeTraits::get_right(z), y);
         }
         else
            x_parent = y;
         replace_own (z, y, header);
         NodeTraits::set_parent(y, NodeTraits::get_parent(z));
         color tmp(NodeTraits::get_color(y));
         tmp = NodeTraits::get_color(y);
         NodeTraits::set_color(y, NodeTraits::get_color(z));
         NodeTraits::set_color(z, tmp);
//         std::swap(NodeTraits::get_color(y), NodeTraits::get_color(z));
         y = z;
         // y now points to node to be actually deleted
      }
      else {                        // y == z
         x_parent = NodeTraits::get_parent(y);
         if(x)
            NodeTraits::set_parent(x, NodeTraits::get_parent(y));
         replace_own (z, x, header);
         if(NodeTraits::get_left(header) == z){
            NodeTraits::set_left(header, NodeTraits::get_right(z) == 0 ?        // z->get_left() must be null also
               NodeTraits::get_parent(z) :  // makes leftmost == header if z == root
               minimum (x));
         }
         if(NodeTraits::get_right(header) == z){
            NodeTraits::set_right(header, NodeTraits::get_left(z) == 0 ?        // z->get_right() must be null also
                              NodeTraits::get_parent(z) :  // makes rightmost == header if z == root
                              maximum(x));
         }
      }
      if(NodeTraits::get_color(y) != NodeTraits::red()){
         while(x != NodeTraits::get_parent(header) && (x == 0 || NodeTraits::get_color(x) == NodeTraits::black())){
            if(x == NodeTraits::get_left(x_parent)){
               node_ptr w = NodeTraits::get_right(x_parent);
               if(NodeTraits::get_color(w) == NodeTraits::red()){
                  NodeTraits::set_color(w, NodeTraits::black());
                  NodeTraits::set_color(x_parent, NodeTraits::red());
                  rotate_left(x_parent, header);
                  w = NodeTraits::get_right(x_parent);
               }
               if((NodeTraits::get_left(w) == 0 || NodeTraits::get_color(NodeTraits::get_left(w))  == NodeTraits::black()) &&
                  (NodeTraits::get_right(w) == 0 || NodeTraits::get_color(NodeTraits::get_right(w)) == NodeTraits::black())){
                  NodeTraits::set_color(w, NodeTraits::red());
                  x = x_parent;
                  x_parent = NodeTraits::get_parent(x_parent);
               } 
               else {
                  if(NodeTraits::get_right(w) == 0 || NodeTraits::get_color(NodeTraits::get_right(w)) == NodeTraits::black()){
                     NodeTraits::set_color(NodeTraits::get_left(w), NodeTraits::black());
                     NodeTraits::set_color(w, NodeTraits::red());
                     rotate_right(w, header);
                     w = NodeTraits::get_right(x_parent);
                  }
                  NodeTraits::set_color(w, NodeTraits::get_color(x_parent));
                  NodeTraits::set_color(x_parent, NodeTraits::black());
                  if(NodeTraits::get_right(w))
                     NodeTraits::set_color(NodeTraits::get_right(w), NodeTraits::black());
                  rotate_left(x_parent, header);
                  break;
               }
            }
            else {
               // same as above, with right_ <-> left_.
               node_ptr w = NodeTraits::get_left(x_parent);
               if(NodeTraits::get_color(w) == NodeTraits::red()){
                  NodeTraits::set_color(w, NodeTraits::black());
                  NodeTraits::set_color(x_parent, NodeTraits::red());
                  rotate_right(x_parent, header);
                  w = NodeTraits::get_left(x_parent);
               }
               if((NodeTraits::get_right(w) == 0 || NodeTraits::get_color(NodeTraits::get_right(w)) == NodeTraits::black()) &&
                  (NodeTraits::get_left(w) == 0 || NodeTraits::get_color(NodeTraits::get_left(w)) == NodeTraits::black())){
                  NodeTraits::set_color(w, NodeTraits::red());
                  x = x_parent;
                  x_parent = NodeTraits::get_parent(x_parent);
               }
               else {
                  if(NodeTraits::get_left(w) == 0 || NodeTraits::get_color(NodeTraits::get_left(w)) == NodeTraits::black()){
                     NodeTraits::set_color(NodeTraits::get_right(w), NodeTraits::black());
                     NodeTraits::set_color(w, NodeTraits::red());
                     rotate_left(w, header);
                     w = NodeTraits::get_left(x_parent);
                  }
                  NodeTraits::set_color(w, NodeTraits::get_color(x_parent));
                  NodeTraits::set_color(x_parent, NodeTraits::black());
                  if(NodeTraits::get_left(w))
                     NodeTraits::set_color(NodeTraits::get_left(w), NodeTraits::black());
                  rotate_right(x_parent, header);
                  break;
               }
            }
         }
         if(x)
            NodeTraits::set_color(x, NodeTraits::black());
      }
      return y;
   }

   //! <b>Requires</b>: "cloner" must be a function
   //!   object taking a node_ptr and returning a new cloned node of it. "disposer" must
   //!   take a node_ptr and shouldn't throw.
   //!
   //! <b>Effects</b>: First empties target tree calling 
   //!   <tt>void disposer::operator()(node_ptr)</tt> for every node of the tree
   //!    except the header.
   //!    
   //!   Then, duplicates the entire tree pointed by "source_header" cloning each
   //!   source node with <tt>node_ptr Cloner::operator()(node_ptr)</tt> to obtain 
   //!   the nodes of the target tree. If "cloner" throws, the cloned target nodes
   //!   are disposed using <tt>void disposer(node_ptr)</tt>.
   //! 
   //! <b>Complexity</b>: Linear to the number of element of the source tree plus the.
   //!   number of elements of tree target tree when calling this function.
   //! 
   //! <b>Throws</b>: If cloner functor throws. If this happens target nodes are disposed.
   template <class Cloner, class Disposer>
   static void clone_tree
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer)
   {
      if(!unique(target_header)){
         node_ptr p;
         while((p = unlink_leftmost_without_rebalance(target_header))){
            disposer(p);
         }
      }

      node_ptr source_root = NodeTraits::get_parent(source_header);
      if(!source_root)
         return;

      NodeTraits::set_parent
         ( target_header
         , deep_clone_node(source_root, target_header, cloner, disposer));
      NodeTraits::set_left(target_header, minimum(NodeTraits::get_parent(target_header)));
      NodeTraits::set_right(target_header, maximum(NodeTraits::get_parent(target_header)));
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. KeyNodePtrCompare can compare KeyType with tree's node_ptrs.
   //!
   //! <b>Effects</b>: Returns an node_ptr to the first element that is
   //!   not less than "key" according to "comp" or "header" if that element does
   //!   not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      node_ptr y = uncast(header);
      node_ptr x = NodeTraits::get_parent(header);
      while(x){
         if(comp(x, key)){
            x = NodeTraits::get_right(x);
         }
         else {
            y = x;
            x = NodeTraits::get_left(x);
         }
      }
      return y;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. KeyNodePtrCompare can compare KeyType with tree's node_ptrs.
   //!
   //! <b>Effects</b>: Returns an node_ptr to the first element that is greater
   //!   than "key" according to "comp" or "header" if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      node_ptr y = uncast(header);
      node_ptr x = NodeTraits::get_parent(header);
      while(x){
         if(comp(key, x)){
            y = x;
            x = NodeTraits::get_left(x);
         }
         else {
            x = NodeTraits::get_right(x);
         }
      }
      return y;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. KeyNodePtrCompare can compare KeyType with tree's node_ptrs.
   //!
   //! <b>Effects</b>: Returns an node_ptr to the element that is equivalent to
   //!   "key" according to "comp" or "header" if that element does not exist.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      node_ptr end = uncast(header);
      node_ptr y = lower_bound(header, key, comp);
      return (y == end || comp(key, y)) ? end : y;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. KeyNodePtrCompare can compare KeyType with tree's node_ptrs.
   //!
   //! <b>Effects</b>: Returns an a pair of node_ptr delimiting a range containing
   //!   all elements that are equivalent to "key" according to "comp" or an
   //!   empty range that indicates the position where those elements would be
   //!   if they there are no equivalent elements.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      node_ptr y = uncast(header);
      node_ptr x = NodeTraits::get_parent(header);

      while(x){
         if(comp(x, key)){
            x = NodeTraits::get_right(x);
         }
         else if(comp(key, x)){
            y = x;
            x = NodeTraits::get_left(x);
         }
         else{
            node_ptr xu(x), yu(y);
            y = x, x = NodeTraits::get_left(x);
            xu = NodeTraits::get_right(xu);

            while(x){
               if(comp(x, key)){
                  x = NodeTraits::get_right(x);
               }
               else {
                  y = x;
                  x = NodeTraits::get_left(x);
               }
            }

            while(xu){
               if(comp(key, xu)){
                  yu = xu;
                  xu = NodeTraits::get_left(xu);
               }
               else {
                  xu = NodeTraits::get_right(xu);
               }
            }
            return std::pair<node_ptr,node_ptr>(y, yu);
         }
      }
      return std::pair<node_ptr,node_ptr>(y, y);
   }

   //! <b>Requires</b>: "h" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree before the upper bound
   //!   according to "comp".
   //! 
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class NodePtrCompare>
   static node_ptr insert_equal_upper_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp)
   {
      node_ptr y(h);
      node_ptr x(NodeTraits::get_parent(y));

      while(x){
         y = x;
         x = comp(new_node, x) ? 
               NodeTraits::get_left(x) : NodeTraits::get_right(x);
      }

      bool link_left = (y == h) || 
                        comp(new_node, y);
      link_and_balance(new_node, y, link_left, h);
      return new_node;
   }

   //! <b>Requires</b>: "h" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs.
   //!
   //! <b>Effects</b>: Inserts new_node into the tree before the lower bound
   //!   according to "comp".
   //! 
   //! <b>Complexity</b>: Average complexity for insert element is at
   //!   most logarithmic.
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class NodePtrCompare>
   static node_ptr insert_equal_lower_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp)
   {
      node_ptr y(h);
      node_ptr x(NodeTraits::get_parent(y));

      while(x){
         y = x;
         x = !comp(x, new_node) ? 
               NodeTraits::get_left(x) : NodeTraits::get_right(x);
      }

      bool link_left = (y == h) || 
                        !comp(y, new_node);
      link_and_balance(new_node, y, link_left, h);
      return new_node;
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   NodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares two node_ptrs. "hint" is node from
   //!   the "header"'s tree.
   //!   
   //! <b>Effects</b>: Inserts new_node into the tree, using "hint" as a hint to
   //!   where it will be inserted. If "hint" is the upper_bound
   //!   the insertion takes constant time (two comparisons in the worst case).
   //!
   //! <b>Complexity</b>: Logarithmic in general, but it is amortized
   //!   constant time if new_node is inserted immediately before "hint".
   //! 
   //! <b>Throws</b>: If "comp" throws.
   template<class NodePtrCompare>
   static node_ptr insert_equal
      (node_ptr header, node_ptr hint, node_ptr new_node, NodePtrCompare comp)
   {
      if(hint == header || !comp(hint, new_node)){
         node_ptr prev(hint);
         if(hint == NodeTraits::get_left(header) || 
            !comp(new_node, (prev = prev_node(hint)))){
            bool link_left = unique(header) || !NodeTraits::get_left(hint);
            link_and_balance(new_node, link_left ? hint : prev, link_left, header);
            return new_node;
         }
         else{
            return insert_equal_upper_bound(header, new_node, comp);
         }
      }
      else{
         return insert_equal_lower_bound(header, new_node, comp);
      }
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares KeyType with a node_ptr.
   //! 
   //! <b>Effects</b>: Checks if there is an equivalent node to "key" in the
   //!   tree according to "comp" and obtains the needed information to realize
   //!   a constant-time node insertion if there is no equivalent node.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing a node_ptr to the already present node
   //!   and false. If there is not equivalent key can be inserted returns true
   //!   in the returned pair's boolean and fills "commit_data" that is meant to
   //!   be used with the "insert_commit" function to achieve a constant-time
   //!   insertion function.
   //! 
   //! <b>Complexity</b>: Average complexity is at most logarithmic.
   //!
   //! <b>Throws</b>: If "comp" throws.
   //! 
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a node is expensive and the user does not want to have two equivalent nodes
   //!   in the tree: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the node and this function offers the possibility to use that part
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the node and use
   //!   "insert_commit" to insert the node in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_unique_commit" only
   //!   if no more objects are inserted or erased from the set.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      node_ptr h(uncast(header));
      node_ptr y(h);
      node_ptr x(NodeTraits::get_parent(y));
      node_ptr prev(0);

      //Find the upper bound, cache the previous value and if we should
      //store it in the left or right node
      bool left_child = true;
      while(x){
         y = x;
         x = (left_child = comp(key, x)) ? 
               NodeTraits::get_left(x) : (prev = y, NodeTraits::get_right(x));
      }

      //Since we've found the upper bound there is no other value with the same key if:
      //    - There is no previous node
      //    - The previous node is less than the key
      if(!prev || comp(prev, key)){
         commit_data.link_left = left_child;
         commit_data.node      = y;
         return std::pair<node_ptr, bool>(node_ptr(), true);
      }
      //If the previous value was not less than key, it means that it's equal
      //(because we've checked the upper bound)
      else{
         return std::pair<node_ptr, bool>(prev, false);
      }
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   KeyNodePtrCompare is a function object that induces a strict weak
   //!   ordering compatible with the strict weak ordering used to create the
   //!   the tree. NodePtrCompare compares KeyType with a node_ptr.
   //!   "hint" is node from the "header"'s tree.
   //! 
   //! <b>Effects</b>: Checks if there is an equivalent node to "key" in the
   //!   tree according to "comp" using "hint" as a hint to where it should be
   //!   inserted and obtains the needed information to realize
   //!   a constant-time node insertion if there is no equivalent node. 
   //!   If "hint" is the upper_bound the function has constant time 
   //!   complexity (two comparisons in the worst case).
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing a node_ptr to the already present node
   //!   and false. If there is not equivalent key can be inserted returns true
   //!   in the returned pair's boolean and fills "commit_data" that is meant to
   //!   be used with the "insert_commit" function to achieve a constant-time
   //!   insertion function.
   //! 
   //! <b>Complexity</b>: Average complexity is at most logarithmic, but it is
   //!   amortized constant time if new_node should be inserted immediately before "hint".
   //!
   //! <b>Throws</b>: If "comp" throws.
   //! 
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a node is expensive and the user does not want to have two equivalent nodes
   //!   in the tree: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the order is much cheaper to construct
   //!   than the node and this function offers the possibility to use that part
   //!   to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the node and use
   //!   "insert_commit" to insert the node in constant-time. This gives a total
   //!   logarithmic complexity to the insertion: check(O(log(N)) + commit(O(1)).
   //!
   //!   "commit_data" remains valid for a subsequent "insert_unique_commit" only
   //!   if no more objects are inserted or erased from the set.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      //hint must be bigger than the key
      if(hint == header || comp(key, hint)){
         node_ptr prev = hint;
         //The previous value should be less than the key
         if(prev == NodeTraits::get_left(header) || comp((prev = prev_node(hint)), key)){
            commit_data.link_left = unique(header) || !NodeTraits::get_left(hint);
            commit_data.node      = commit_data.link_left ? hint : prev;
            return std::pair<node_ptr, bool>(node_ptr(), true);
         }
         else{
            return insert_unique_check(header, key, comp, commit_data);
            //return std::pair<node_ptr, bool>(prev, false);
         }
      }
      //The hint was wrong, use hintless insert
      else{
         return insert_unique_check(header, key, comp, commit_data);
      }
   }

   //! <b>Requires</b>: "header" must be the header node of a tree.
   //!   "commit_data" must have been obtained from a previous call to
   //!   "insert_unique_check". No objects should have been inserted or erased
   //!   from the set between the "insert_unique_check" that filled "commit_data"
   //!   and the call to "insert_commit". 
   //! 
   //! 
   //! <b>Effects</b>: Inserts new_node in the set using the information obtained
   //!   from the "commit_data" that a previous "insert_check" filled.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Notes</b>: This function has only sense if a "insert_unique_check" has been
   //!   previously executed to fill "commit_data". No value should be inserted or
   //!   erased between the "insert_check" and "insert_commit" calls.
   static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data)
   {
      //Check if commit_data has not been initialized by a insert_unique_check call.
      BOOST_INTRUSIVE_INVARIANT_ASSERT(commit_data.node != 0);
      link_and_balance(new_value, commit_data.node, commit_data.link_left, header);
   }

   /// @cond

   //! <b>Requires</b>: z is the node to be inserted, par is its parent,
   //!   left, indicates if z should be a left node of par and header is the header
   //!   of the tree.
   //! 
   //! <b>Effects</b>: If left is true links z as a left child of par or as a right
   //!    child otherwise. After that rebalances the tree.
   //! 
   //! <b>Complexity</b>: Average constant time.???
   //! 
   //! <b>Throws</b>: Nothing.
   static void link_and_balance (node_ptr z, node_ptr par, bool left, node_ptr header)
   {
      if(par == header){
         NodeTraits::set_parent(header, z);
         NodeTraits::set_right(header, z);
         NodeTraits::set_left(header, z);
      }
      else if(left){
         NodeTraits::set_left(par, z);
         if(par == NodeTraits::get_left(header))
             NodeTraits::set_left(header, z);
      }
      else{
         NodeTraits::set_right(par, z);
         if(par == NodeTraits::get_right(header))
             NodeTraits::set_right(header, z);
      }
      NodeTraits::set_parent(z, par);
      NodeTraits::set_right(z, 0);
      NodeTraits::set_left(z, 0);
      rebalance(z, header);
   }

   //! <b>Requires</b>: p is a node of a tree but not the header.
   //! 
   //! <b>Effects</b>: Returns the minimum node of the subtree starting at p.
   //! 
   //! <b>Complexity</b>: Logarithmic to the size of the subtree.
   //! 
   //! <b>Throws</b>: Nothing.
   static node_ptr minimum (node_ptr p)
   {
      for(node_ptr p_left = NodeTraits::get_left(p)
         ;p_left
         ;p_left = NodeTraits::get_left(p)){
         p = p_left;
      }
      return p;
   }

   //! <b>Requires</b>: p is a node of a tree but not the header.
   //! 
   //! <b>Effects</b>: Returns the maximum node of the subtree starting at p.
   //! 
   //! <b>Complexity</b>: Logarithmic to the size of the subtree.
   //! 
   //! <b>Throws</b>: Nothing.
   static node_ptr maximum(node_ptr p)
   {
      for(node_ptr p_right = NodeTraits::get_right(p)
         ;p_right
         ;p_right = NodeTraits::get_right(p)){
         p = p_right;
      }
      return p;
   }

   //! <b>Requires</b>: p is a node of a tree.
   //! 
   //! <b>Effects</b>: Returns true if p is the header of the tree.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static bool is_header(const_node_ptr p)
   {
      return NodeTraits::get_color(p) == NodeTraits::red() && 
             NodeTraits::get_parent(NodeTraits::get_parent(p)) == p;
   }

   //! <b>Requires</b>: p is a node of a tree.
   //! 
   //! <b>Effects</b>: Returns true if p is a left child.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static bool is_left_child(node_ptr p)
   {  return NodeTraits::get_left(NodeTraits::get_parent(p)) == p;  }

   //! <b>Requires</b>: p is a node of a tree.
   //! 
   //! <b>Effects</b>: Returns true if p is a right child.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static bool is_right_child (node_ptr p)
   {  return NodeTraits::get_right(NodeTraits::get_parent(p)) == p;  }

   static void replace_own (node_ptr own, node_ptr x, node_ptr header)
   {
      if(NodeTraits::get_parent(header) == own)
         NodeTraits::set_parent(header, x);
      else if(is_left_child(own))
         NodeTraits::set_left(NodeTraits::get_parent(own), x);
      else
         NodeTraits::set_right(NodeTraits::get_parent(own), x);
   }

   static void rotate_left(node_ptr p, node_ptr header)
   {
      node_ptr x = NodeTraits::get_right(p);
      NodeTraits::set_right(p, NodeTraits::get_left(x));
      if(NodeTraits::get_left(x) != 0)
         NodeTraits::set_parent(NodeTraits::get_left(x), p);
      NodeTraits::set_parent(x, NodeTraits::get_parent(p));
      replace_own (p, x, header);
      NodeTraits::set_left(x, p);
      NodeTraits::set_parent(p, x);
   }

   static void rotate_right(node_ptr p, node_ptr header)
   {
      node_ptr x(NodeTraits::get_left(p));
      node_ptr x_right(NodeTraits::get_right(x));
      NodeTraits::set_left(p, x_right);
      if(x_right)
         NodeTraits::set_parent(x_right, p);
      NodeTraits::set_parent(x, NodeTraits::get_parent(p));
      replace_own (p, x, header);
      NodeTraits::set_right(x, p);
      NodeTraits::set_parent(p, x);
   }

   static void rebalance(node_ptr p, node_ptr header)
   {
      NodeTraits::set_color(p, NodeTraits::red());
      while(p != NodeTraits::get_parent(header) && NodeTraits::get_color(NodeTraits::get_parent(p)) == NodeTraits::red()){
         node_ptr p_parent(NodeTraits::get_parent(p));
         node_ptr p_parent_parent(NodeTraits::get_parent(p_parent));
         if(is_left_child(p_parent)){
            node_ptr x = NodeTraits::get_right(p_parent_parent);
            if(x && NodeTraits::get_color(x) == NodeTraits::red()){
               NodeTraits::set_color(p_parent, NodeTraits::black());
               NodeTraits::set_color(p_parent_parent, NodeTraits::red());
               NodeTraits::set_color(x, NodeTraits::black());
               p = p_parent_parent;
            }
            else {
               if(!is_left_child(p)){
                  p = p_parent;
                  rotate_left(p, header);
               }
               node_ptr new_p_parent(NodeTraits::get_parent(p));
               node_ptr new_p_parent_parent(NodeTraits::get_parent(new_p_parent));
               NodeTraits::set_color(new_p_parent, NodeTraits::black());
               NodeTraits::set_color(new_p_parent_parent, NodeTraits::red());
               rotate_right(new_p_parent_parent, header);
            }
         }
         else{
            node_ptr x = NodeTraits::get_left(p_parent_parent);
            if(x && NodeTraits::get_color(x) == NodeTraits::red()){
               NodeTraits::set_color(p_parent, NodeTraits::black());
               NodeTraits::set_color(p_parent_parent, NodeTraits::red());
               NodeTraits::set_color(x, NodeTraits::black());
               p = p_parent_parent;
            }
            else{
               if(is_left_child(p)){
                  p = p_parent;
                  rotate_right(p, header);
               }
               node_ptr new_p_parent(NodeTraits::get_parent(p));
               node_ptr new_p_parent_parent(NodeTraits::get_parent(new_p_parent));
               NodeTraits::set_color(new_p_parent, NodeTraits::black());
               NodeTraits::set_color(new_p_parent_parent, NodeTraits::red());
               rotate_left(new_p_parent_parent, header);
            }
         }
      }
      NodeTraits::set_color(NodeTraits::get_parent(header), NodeTraits::black());
   }

   template <class Cloner, class Disposer>
   static node_ptr deep_clone_node
      (node_ptr source_root, node_ptr new_parent, Cloner cloner, Disposer disposer)
   {
      // structural copy.  source_root and new_parent must be non-null.
      node_ptr top = cloner(source_root);
      NodeTraits::set_parent(top, new_parent);
       
      BOOST_TRY {
         if(NodeTraits::get_right(source_root)){
            NodeTraits::set_right
               (top, deep_clone_node(NodeTraits::get_right(source_root), top
                                    ,cloner, disposer));
         }
         new_parent = top;
         source_root = NodeTraits::get_left(source_root);

         while(source_root){
            node_ptr y = cloner(source_root);
            NodeTraits::set_left(new_parent, y);
            NodeTraits::set_parent(y, new_parent);

            if(NodeTraits::get_right(source_root)){
               NodeTraits::set_right(y, deep_clone_node(NodeTraits::get_right(source_root), y
                                                    ,cloner, disposer));
            }
            new_parent = y;
            source_root = NodeTraits::get_left(source_root);
         }
      }
      BOOST_CATCH(...){
         deep_dispose_node(top, disposer);
         BOOST_RETHROW;
      }
      BOOST_CATCH_END
      return top;
   }

   template<class Disposer>
   static void deep_dispose_node(node_ptr x, Disposer disposer)
   {
      // erase without rebalancing
      while(x){
         deep_dispose_node(NodeTraits::get_right(x), disposer);
         node_ptr y = NodeTraits::get_left(x);
         disposer(x);
         x = y;
      }
   }
   /// @endcond
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP
