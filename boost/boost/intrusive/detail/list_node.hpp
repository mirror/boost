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

#ifndef BOOST_INTRUSIVE_LIST_NODE_HPP
#define BOOST_INTRUSIVE_LIST_NODE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <iterator>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#ifdef BOOST_INTRUSIVE_USE_ITERATOR_FACADE
#include <boost/iterator/iterator_facade.hpp>
#endif
#ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost {
namespace intrusive {
namespace detail {

// list_node_traits can be used with circular_list_algorithms and supplies
// a list_node holding the pointers needed for a double-linked list
// it is used by list_derived_node and list_member_node
template<class VoidPointer>
struct list_node_traits
{
   struct node;
   typedef typename boost::pointer_to_other
      <VoidPointer, node>::type          node_ptr;
   typedef typename boost::pointer_to_other
      <VoidPointer, const node>::type    const_node_ptr;

   struct node
   {
      node_ptr prev_, next_;
   };

   static node_ptr get_previous(const_node_ptr n)
   {  return n->prev_;  }

   static void set_previous(node_ptr n, node_ptr prev)
   {  n->prev_ = prev;  }

   static node_ptr get_next(const_node_ptr n)
   {  return n->next_;  }

   static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }
};

#ifdef BOOST_INTRUSIVE_USE_ITERATOR_FACADE

// list_iterator provides some basic functions for a 
// node oriented forward iterator:
template<class T, class ValueTraits>
class list_iterator
  : public boost::iterator_facade
         < list_iterator<T, ValueTraits>
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
   struct enabler{};

   public:
   typedef typename pointer_to_other<typename ValueTraits::node_ptr, T>::type pointer;
   typedef typename std::iterator_traits<node_ptr>::difference_type difference_type;

   list_iterator ()
      :  node_ (0)
   {}

   explicit list_iterator(node_ptr node)
      :  node_ (node)
   {}

   #ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
   template <class OtherValue>
   list_iterator(list_iterator<OtherValue, ValueTraits> const& other
                ,typename boost::enable_if<
                        boost::is_convertible<OtherValue*,T*>
                     , enabler
                     >::type = enabler()
                 )
      :  node_(other.pointed_node())
   {}
   #else
   template <class OtherValue>
   list_iterator(list_iterator<OtherValue, ValueTraits> const& other,
                  typename enable_if<
                        is_convertible<OtherValue*,T*>
                  >::type* = 0)
      :  node_(other.pointed_node())
   {}
   #endif

   const node_ptr &pointed_node() const
   { return node_; }

   private:
   friend class boost::iterator_core_access;
   template <class, class> friend class list_iterator;

   template <class OtherValue>
   bool equal(list_iterator<OtherValue, ValueTraits> const& other) const
   {  return other.pointed_node() == node_;  }

   void increment()
   {  node_ = node_traits::get_next(node_);   }

   void decrement()
   {  node_ = node_traits::get_previous(node_);   }

   T& dereference() const
   { return *ValueTraits::to_value_ptr(node_); }

   node_ptr node_;
};

#else //BOOST_INTRUSIVE_USE_ITERATOR_FACADE

// list_iterator provides some basic functions for a 
// node oriented bidirectional iterator:
template<class T, class ValueTraits>
class list_iterator
   :  public std::iterator<std::bidirectional_iterator_tag, T>
{
   struct enabler{};
   protected:
   typedef typename ValueTraits::node_traits    node_traits;
   typedef typename node_traits::node           node;
   typedef typename node_traits::node_ptr       node_ptr;
 
   public:
   typedef T & reference;
   typedef T * pointer;

   list_iterator()
      : node_ (0)
   {}

   explicit list_iterator(node_ptr node)
      : node_ (node)
   {}
   #ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
   template <class OtherValue>
   list_iterator(list_iterator<OtherValue, ValueTraits> const& other
                ,typename boost::enable_if<
                        boost::is_convertible<OtherValue*,T*>
                     , enabler
                     >::type = enabler()
                 )
      :  node_(other.pointed_node())
   {}
   #else
   template <class OtherValue>
   list_iterator(list_iterator<OtherValue, ValueTraits> const& other,
                  typename enable_if<
                        is_convertible<OtherValue*,T*>
                  >::type* = 0)
      :  node_(other.pointed_node())
   {}
   #endif

   const node_ptr &pointed_node() const
   { return node_; }

   list_iterator &operator=(const node_ptr &node)
   {  node_ = node;  return static_cast<list_iterator&>(*this);  }

   public:
   list_iterator& operator++() 
   { 
      node_ = node_traits::get_next(node_); 
      return static_cast<list_iterator&> (*this); 
   }
   
   list_iterator operator++(int)
   {
      list_iterator result (node_);
      node_ = node_traits::get_next(node_);
      return result;
   }

   list_iterator& operator--() 
   { 
      node_ = node_traits::get_previous(node_); 
      return static_cast<list_iterator&> (*this); 
   }
   
   list_iterator operator--(int)
   {
      list_iterator result (node_);
      node_ = node_traits::get_previous(node_);
      return result;
   }

   bool operator== (const list_iterator& i) const
   { return node_ == i.pointed_node(); }

   bool operator!= (const list_iterator& i) const
   { return !operator== (i); }

   T& operator*() const
   { return *ValueTraits::to_value_ptr(node_); }

   pointer operator->() const
   { return detail::get_pointer(ValueTraits::to_value_ptr(node_)); }

   private:
   node_ptr node_;
};

#endif

} //namespace detail 
} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_NODE_HPP
