/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_HASHSET_HOOK_HPP
#define BOOST_INTRUSIVE_HASHSET_HOOK_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/utilities.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/slist_hook.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <stdexcept>

namespace boost {
namespace intrusive {

//! Derive a class from unordered_set_base_hook in order to store objects in 
//! in an unordered_set/unordered_multi_set. unordered_set_base_hook holds the data necessary to maintain 
//! the unordered_set/unordered_multi_set and provides an appropriate value_traits class for unordered_set/unordered_multi_set.
//! 
//! The first integer template argument defines a tag to identify the node. 
//! The same tag value can be used in different classes, but if a class is 
//! derived from more than one unordered_set_base_hook, then each unordered_set_base_hook needs its 
//! unique tag.
//!
//! The second boolean template parameter will specify the linking mode of the hook.
//!
//! The third argument is the pointer type that will be used internally in the hook
//! and the unordered_set/unordered_multi_set configured from this hook.
template< class Tag              //= tag
        , linking_policy Policy  //= safe_link
        , class VoidPointer      //= void *
        >
class unordered_set_base_hook
{
   /// @cond
   typedef slist_base_hook<Tag, Policy, VoidPointer> IsListHook;
   IsListHook m_slisthook;
   typedef IsListHook                                 implementation_defined;
   /// @endcond

   public:
   enum { linking_policy = Policy };
   typedef typename implementation_defined::node_traits  node_traits;
   typedef typename node_traits::node                    node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type                          node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type                    const_node_ptr;
   typedef unordered_set_base_hook
      <Tag, Policy, VoidPointer>                         this_type;
   typedef typename boost::pointer_to_other
      <VoidPointer, this_type>::type                     this_type_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const this_type>::type               const_this_type_ptr;

   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state.
   //! 
   //! <b>Throws</b>: Nothing.
   unordered_set_base_hook()
      :  m_slisthook()
   {}

   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using unordered_set_base_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook(const unordered_set_base_hook &other)
      :  m_slisthook(other.m_slisthook)
   {}

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Rationale</b>: Providing an assignment operator 
   //!   makes classes using unordered_set_base_hook STL-compliant without forcing the 
   //!   user to do some additional work. "swap" can be used to emulate
   //!   move-semantics.
   unordered_set_base_hook& operator=(const unordered_set_base_hook &other)
   {  return *this;  }

   //! <b>Effects</b>: If Policy is normal_link, the destructor does
   //!   nothing (ie. no code is generated). If Policy is safe_link and the
   //!   object is stored in an list an assertion is raised. If Policy is
   //!   auto_unlink and "is_linked()" is true, the node is unlinked.
   //! 
   //! <b>Throws</b>: Nothing.
   ~unordered_set_base_hook() 
   {} //m_slisthook's destructor does the job

   //! <b>Precondition</b>: Policy must be safe_link or auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether unordered_set/unordered_multiset::iterator_to 
   //!   will return a valid iterator. 
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const 
   {  return m_slisthook.is_linked(); }

   //! The value_traits class is used as the first template argument for unordered_set/unordered_multiset. 
   //! The template argument T defines the class type stored in unordered_set/unordered_multiset. Objects 
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
      return this_type_ptr((this_type*)detail::get_pointer(IsListHook::to_hook_ptr(p)));
   }

   //! <b>Effects</b>: Converts a const pointer to a node stored in a container into
   //!   a const pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing.
   static const_this_type_ptr to_hook_ptr(const_node_ptr p)
   {
      return const_this_type_ptr((const this_type*)detail::get_pointer(IsListHook::to_hook_ptr(p)));
   }

   //! <b>Effects</b>: Returns a pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing.
   node_ptr to_node_ptr()
   {  return m_slisthook.to_node_ptr();  }

   //! <b>Effects</b>: Returns a const pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing.
   const_node_ptr to_node_ptr() const
   {  return m_slisthook.to_node_ptr();  }
};

//! Put a public data member unordered_set_member_hook in order to store objects of this class in
//! an unordered_set/unordered_multi_set. unordered_set_member_hook holds the data necessary for maintaining the
//! unordered_set/unordered_multi_set and provides an appropriate value_traits class for unordered_set/unordered_multi_set.
//! 
//! The first boolean template parameter will specify the linking mode of the hook.
//!
//! The second argument is the pointer type that will be used internally in the hook
//! and the unordered_set/unordered_multi_set configured from this hook.
template< linking_policy Policy  //= safe_link
        , class VoidPointer      //= void *
        >
class unordered_set_member_hook
{
   /// @cond
   typedef slist_member_hook<Policy, VoidPointer>  IsListHook;
   IsListHook m_slisthook;
   typedef IsListHook                                 implementation_defined;
   /// @endcond

   public:
   enum { linking_policy = Policy };
   typedef typename implementation_defined::node_traits  node_traits;
   typedef typename node_traits::node                    node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type                          node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type                    const_node_ptr;
   typedef unordered_set_member_hook
      <Policy, VoidPointer>                              this_type;
   typedef typename boost::pointer_to_other
      <VoidPointer, this_type>::type                     this_type_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const this_type>::type               const_this_type_ptr;

   public:
   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state.
   //! 
   //! <b>Throws</b>: Nothing. 
   unordered_set_member_hook()
      :  m_slisthook()
   {}

   //! <b>Effects</b>: If Policy is auto_unlink or safe_mode_linnk
   //!   initializes the node to an unlinked state. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using unordered_set_member_hook STL-compliant without forcing the 
   //!   user to do some additional work.
   unordered_set_member_hook(const unordered_set_member_hook &other)
      :  m_slisthook(other.m_slisthook)
   {}

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //! 
   //! <b>Throws</b>: Nothing. 
   //! 
   //! <b>Rationale</b>: Providing an assignment operator 
   //!   makes classes using unordered_set_member_hook STL-compliant without forcing the 
   //!   user to do some additional work.
   unordered_set_member_hook& operator=(const unordered_set_member_hook &other) 
   {  return *this;  }

   //! <b>Effects</b>: If Policy is normal_link, the destructor does
   //!   nothing (ie. no code is generated). If Policy is safe_link and the
   //!   object is stored in an list an assertion is raised. If Policy is
   //!   auto_unlink and "is_linked()" is true, the node is unlinked.
   //! 
   //! <b>Throws</b>: Nothing. 
   ~unordered_set_member_hook() 
   {} //m_slisthook's destructor does the job

   //! <b>Precondition</b>: Policy must be safe_link or auto_unlink.
   //!
   //! <b>Complexity</b>: Constant 
   bool is_linked() const 
   {  return m_slisthook.is_linked();  }

   //! The value_traits class is used as the first template argument for unordered_set/unordered_multiset. 
   //! The template argument is a pointer to member pointing to the node in 
   //! the class. Objects of type T and of types derived from T can be stored. 
   //! T doesn't need to be copy-constructible or assignable.
   template<class T, this_type T::* M>
   struct value_traits
      : detail::member_value_traits<T, this_type, M>
   {};

   //! <b>Effects</b>: Removes the node if it's inserted in a container.
   //!   This function is only allowed if Policy is auto_unlink.
   //! 
   //! <b>Throws</b>: Nothing. 
   void unlink()
   {  m_slisthook.unlink();   }

   //! <b>Effects</b>: Converts a pointer to a node into
   //!   a pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static this_type_ptr to_hook_ptr(node_ptr p)
   {
      return this_type_ptr((this_type*)detail::get_pointer(IsListHook::to_hook_ptr(p)));
   }

   //! <b>Effects</b>: Converts a const pointer to a node stored in a container into
   //!   a const pointer to the hook that holds that node.
   //! 
   //! <b>Throws</b>: Nothing. 
   static const_this_type_ptr to_hook_ptr(const_node_ptr p)
   {
      return const_this_type_ptr((const this_type*)detail::get_pointer(IsListHook::to_hook_ptr(p)));
   }

   //! <b>Effects</b>: Returns a pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   node_ptr to_node_ptr()
   {  return m_slisthook.to_node_ptr();  }

   //! <b>Effects</b>: Returns a const pointer to the node that this hook holds.
   //! 
   //! <b>Throws</b>: Nothing. 
   const_node_ptr to_node_ptr() const
   {  return m_slisthook.to_node_ptr();  }
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_HASHSET_HOOK_HPP
