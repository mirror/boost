/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztañaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_LIST_HOOK_HPP
#define BOOST_INTRUSIVE_LIST_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/utilities.hpp>
#include <boost/intrusive/detail/pointer_type.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/detail/list_node.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <boost/intrusive/tag.hpp>
#include <boost/get_pointer.hpp>
#include <boost/static_assert.hpp>
#include <stdexcept>

namespace boost {
namespace intrusive {

//! Derive a class from list_base_hook in order to store objects in 
//! in an list. list_base_hook holds the data necessary to maintain the 
//! list and provides an appropriate value_traits class for list.
//! 
//! The first integer template argument defines a tag to identify the node. 
//! The same tag value can be used in different classes, but if a class is 
//! derived from more than one list_base_hook, then each list_base_hook needs its 
//! unique tag.
//!
//! The second boolean template parameter will specify the linking mode of the hook.
//!
//! The third argument is the pointer type that will be used internally in the hook
//! and the list configured from this hook.
template< class Tag              //= tag
        , linking_policy Policy  //= safe_link
        , class VoidPointer      //= void *
        >
class list_base_hook
   :  private detail::list_node_traits<VoidPointer>::node
{
   public:
   typedef detail::list_node_traits<VoidPointer>      node_traits;
   enum {   linking_policy = Policy   };

   /// @cond
   private:
   typedef circular_list_algorithms<node_traits>               node_algorithms;

   public:
   typedef typename node_traits::node                 node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type                       node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type                 const_node_ptr;
   typedef list_base_hook
      <Tag, Policy, VoidPointer>                      this_type;

   typedef typename boost::pointer_to_other
      <VoidPointer, this_type>::type                  this_type_ptr;

   typedef typename boost::pointer_to_other
      <VoidPointer, const this_type>::type            const_this_type_ptr;

   private:
   node_ptr this_as_node()
   {  return node_ptr(static_cast<node *const>(this)); }

   const_node_ptr this_as_node() const
   {  return const_node_ptr(static_cast<const node *const>(this)); }
   /// @endcond

   public:
   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state.
   //! 
   //! <b>Throws</b>: Nothing. 
   list_base_hook()
      :  node()
   {
      if(Policy == safe_link || Policy == auto_unlink){
         node_algorithms::init(this_as_node());
      }
   }

   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using list_base_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   list_base_hook(const list_base_hook& ) 
      :  node()
   {
      if(Policy == safe_link || Policy == auto_unlink){
         node_algorithms::init(this_as_node());
      }
   }

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing an assignment operator 
   //!   makes classes using list_base_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   list_base_hook& operator=(const list_base_hook& ) 
   {  return *this;  }

   //! <b>Effects</b>: If Policy is normal_link, the destructor does
   //!   nothing (ie. no code is generated). If Policy is safe_link and the
   //!   object is stored in an list an assertion is raised. If Policy is
   //!   auto_unlink and "is_linked()" is true, the node is unlinked.
   //! 
   //! <b>Throws</b>: Nothing. 
   ~list_base_hook()
   {  detail::destructor_impl(*this, detail::dispatcher<Policy>());  }

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements 
   //!   related to those nodes in one or two containers. That is, if the node 
   //!   this is part of the element e1, the node x is part of the element e2 
   //!   and both elements are included in the containers s1 and s2, then after 
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1 
   //!   at the position of e1. If one element is not in a container, then 
   //!   after the swap-operation the other element is not in a container. 
   //!   Iterators to e1 and e2 related to those nodes are invalidated. 
   //!
   //! <b>Complexity</b>: Constant 
   //!
   //! <b>Throws</b>: Nothing. 
   void swap_nodes(list_base_hook &other) 
   { node_algorithms::swap_nodes(this_as_node(), other.this_as_node()); }

   //! <b>Precondition</b>: Policy must be safe_link or auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether list::iterator_to 
   //!   will return a valid iterator. 
   //!
   //! <b>Complexity</b>: Constant 
   bool is_linked() const 
   {
      //is_linked() can be only used in safe-mode or auto-unlink
      BOOST_STATIC_ASSERT((Policy == safe_link || Policy == auto_unlink));
      return !node_algorithms::unique(this_as_node()); 
   }

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if Policy is auto_unlink.
   //! 
   //! <b>Throws</b>: Nothing. 
   void unlink()
   {
      BOOST_STATIC_ASSERT((Policy == auto_unlink));
      node_algorithms::unlink(this_as_node());
      node_algorithms::init(this_as_node());
   }

   //! The value_traits class is used as the first template argument for list. 
   //! The template argument T defines the class type stored in list. Objects 
   //! of type T and of types derived from T can be stored. T doesn't need to be 
   //! copy-constructible or assignable.
   template<class T>
   struct value_traits
      : detail::derivation_value_traits<T, this_type, Tag>
   {};

   //! <b>Effects</b>: Converts a pointer to a node into
   //!   a pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static this_type_ptr to_hook_ptr(node_ptr p)
   {
      using boost::get_pointer;
      return this_type_ptr(static_cast<list_base_hook*> (get_pointer(p))); 
   }

   //! <b>Effects</b>: Converts a const pointer to a node stored in a container into
   //!   a const pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static const_this_type_ptr to_hook_ptr(const_node_ptr p)
   {
      using boost::get_pointer;
      return const_this_type_ptr(static_cast<const list_base_hook*> (get_pointer(p))); 
   }

   //! <b>Effects</b>: Returns a pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   node_ptr to_node_ptr()
   { return this_as_node(); }

   //! <b>Effects</b>: Returns a const pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   const_node_ptr to_node_ptr() const
   { return this_as_node(); }
};

//! Put a public data member list_member_hook in order to store objects of this class in
//! an list. list_member_hook holds the data necessary for maintaining the list and 
//! provides an appropriate value_traits class for list.
//! 
//! The first boolean template parameter will specify the linking mode of the hook.
//!
//! The second argument is the pointer type that will be used internally in the hook
//! and the list configured from this hook.
template< linking_policy Policy  //= safe_link
        , class VoidPointer      //= void *
        >
class list_member_hook
   :  private detail::list_node_traits<VoidPointer>::node
{
   public:
   typedef detail::list_node_traits<VoidPointer>      node_traits;
   enum { linking_policy = Policy };

   /// @cond
   private:
   typedef circular_list_algorithms<node_traits>               node_algorithms;
   /// @endcond

   public:
   typedef typename node_traits::node                 node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type                       node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type                 const_node_ptr;
   typedef list_member_hook
      <Policy, VoidPointer>                           this_type;

   typedef typename boost::pointer_to_other
      <VoidPointer, this_type >::type                 this_type_ptr;

   typedef typename boost::pointer_to_other
      <VoidPointer, const this_type >::type           const_this_type_ptr;

   /// @cond
   private:
   node_ptr this_as_node()
   {  return node_ptr(static_cast<node *const>(this)); }

   const_node_ptr this_as_node() const
   {  return const_node_ptr(static_cast<const node *const>(this)); }
   /// @endcond

   public:
   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state.
   //! 
   //! <b>Throws</b>: Nothing. 
   list_member_hook()
      :  node()
   {
      if(Policy == safe_link || Policy == auto_unlink){
         node_algorithms::init(this_as_node());
      }
   }

   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using list_member_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   list_member_hook(const list_member_hook& ) 
      :  node()
   {
      if(Policy == safe_link || Policy == auto_unlink){
         node_algorithms::init(this_as_node());
      }
   }

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing an assignment operator 
   //!   makes classes using list_member_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   list_member_hook& operator=(const list_member_hook& )
   {  return *this;  }

   //! <b>Effects</b>: If Policy is normal_link, the destructor does
   //!   nothing (ie. no code is generated). If Policy is safe_link and the
   //!   object is stored in an list an assertion is raised. If Policy is
   //!   auto_unlink and "is_linked()" is true, the node is unlinked.
   //! 
   //! <b>Throws</b>: Nothing. 
   ~list_member_hook()
   {  detail::destructor_impl(*this, detail::dispatcher<Policy>());  }

   //! <b>Effects</b>: Swapping two nodes swaps the position of the elements 
   //!   related to those nodes in one or two containers. That is, if the node 
   //!   this is part of the element e1, the node x is part of the element e2 
   //!   and both elements are included in the containers s1 and s2, then after 
   //!   the swap-operation e1 is in s2 at the position of e2 and e2 is in s1 
   //!   at the position of e1. If one element is not in a container, then 
   //!   after the swap-operation the other element is not in a container. 
   //!   Iterators to e1 and e2 related to those nodes are invalidated. 
   //!
   //! <b>Complexity</b>: Constant 
   //!
   //! <b>Throws</b>: Nothing.
   void swap_nodes(list_member_hook& other) 
   { node_algorithms::swap_nodes(this_as_node(), other.this_as_node()); }

   //! <b>Precondition</b>: Policy must be safe_link or auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether list::iterator_to 
   //!   will return a valid iterator. 
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const 
   {
      //is_linked() can be only used in safe-mode or auto-unlink
      BOOST_STATIC_ASSERT((Policy == safe_link || Policy == auto_unlink));
      return !node_algorithms::unique(this_as_node()); 
   }

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if Policy is auto_unlink.
   //! 
   //! <b>Throws</b>: Nothing. 
   void unlink()
   {
      BOOST_STATIC_ASSERT((Policy == auto_unlink));
      node_algorithms::unlink(this_as_node());
      node_algorithms::init(this_as_node());
   }

   //! The value_traits class is used as the first template argument for list. 
   //! The template argument is a pointer to member pointing to the node in 
   //! the class. Objects of type T and of types derived from T can be stored. 
   //! T doesn't need to be copy-constructible or assignable.
   template<class T, this_type T::* M>
   struct value_traits
      : detail::member_value_traits<T, this_type, M>
   {};

   //! <b>Effects</b>: Converts a pointer to a node into
   //!   a pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static this_type_ptr to_hook_ptr(node_ptr p)
   {
      using boost::get_pointer;
      return this_type_ptr(static_cast<this_type*> (get_pointer(p))); 
   }

   //! <b>Effects</b>: Converts a const pointer to a node stored in a container into
   //!   a const pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static const_this_type_ptr to_hook_ptr(const_node_ptr p)
   {
      using boost::get_pointer;
      return const_this_type_ptr(static_cast<const this_type*> (get_pointer(p))); 
   }

   //! <b>Effects</b>: Returns a pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   node_ptr to_node_ptr()
   { return this_as_node(); }

   //! <b>Effects</b>: Returns a const pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   const_node_ptr to_node_ptr() const
   { return this_as_node(); }
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_HOOK_HPP
