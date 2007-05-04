/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP
#define BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/pointer_type.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/detail/parent_from_member.hpp>
#include <boost/intrusive/detail/ebo_holder.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <boost/get_pointer.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {

//This functor compares a stored value
//and the one passed as an argument
template<class ConstReference>
class equal_to_value
{
   ConstReference t_;

   public:
   equal_to_value(ConstReference t)
      :  t_(t)
   {}

   bool operator()(ConstReference t)const
   {  return t_ == t;   }
};

class null_destroyer
{
   public:
   template <class Pointer>
   void operator()(Pointer)
   {}
};

template<bool ConstantSize, class SizeType>
struct size_holder
{
   enum {   constant_time_size = ConstantSize  };
   typedef SizeType  size_type;

   SizeType get_size() const
   {  return size_;  }

   void set_size(SizeType size)
   {  size_ = size; }

   void decrement()
   {  --size_; }

   void increment()
   {  ++size_; }

   SizeType size_;
};

template<class SizeType>
struct size_holder<false, SizeType>
{
   enum {   constant_time_size = false  };
   typedef SizeType  size_type;

   size_type get_size() const
   {  return 0;  }

   void set_size(size_type)
   {}

   void decrement()
   {}

   void increment()
   {}
};

template<class T, class DerivationHookType, typename Tag>
struct derivation_value_traits
{
   public:
   typedef typename DerivationHookType::node_traits                  node_traits;
   typedef T                                                         value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename boost::pointer_to_other<node_ptr, T>::type       pointer;
   typedef typename boost::pointer_to_other<node_ptr, const T>::type const_pointer;
   typedef typename std::iterator_traits<pointer>::reference         reference;
   typedef typename std::iterator_traits<const_pointer>::reference   const_reference;
   enum { linking_policy = DerivationHookType::linking_policy };

   static node_ptr to_node_ptr(reference value)
   { return static_cast<DerivationHookType &>(value).to_node_ptr(); }

   static const_node_ptr to_node_ptr(const_reference value)
   { return static_cast<const DerivationHookType &>(value).to_node_ptr(); }

   static pointer to_value_ptr(node_ptr n) 
   { 
      using boost::get_pointer;
      return static_cast<T*>(get_pointer(DerivationHookType::to_hook_ptr(n))); 
   }

   static const_pointer to_value_ptr(const_node_ptr n)
   { 
      using boost::get_pointer;
      return static_cast<const T*>(get_pointer(DerivationHookType::to_hook_ptr(n))); 
   }
};


template<class T, class MemberHookType, MemberHookType T::* P>
struct member_value_traits
{
   public:
   typedef typename MemberHookType::node_traits                      node_traits;
   typedef T                                                         value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename boost::pointer_to_other<node_ptr, T>::type       pointer;
   typedef typename boost::pointer_to_other<node_ptr, const T>::type const_pointer;
   typedef typename std::iterator_traits<pointer>::reference         reference;
   typedef typename std::iterator_traits<const_pointer>::reference   const_reference;
   enum { linking_policy = MemberHookType::linking_policy };

   public:
   static node_ptr to_node_ptr(reference value)
   {
      MemberHookType* result = &(value.*P);
      return result->to_node_ptr();
   }

   static const_node_ptr to_node_ptr(const_reference value)
   {
      const MemberHookType* result = &(value.*P);
      return result->to_node_ptr();
   }

   //Now let's be nasty. A pointer to member is usually implemented
   //as an offset from the start of the class.
   //get the offset in bytes and go
   //backwards from n to the value subtracting
   //the needed bytes.
   static pointer to_value_ptr(node_ptr n)
   {
      using boost::get_pointer;
      return pointer(parent_from_member((MemberHookType*)get_pointer(n), P));
   }

   static const_pointer to_value_ptr(const_node_ptr n)
   {
      using boost::get_pointer;
      const_pointer(parent_from_member<value_type>((const MemberHookType*)get_pointer(n), P));
   }

   private:
   //This function converts a pointer to data member into an offset.
   //This function is not standard and it's compiler-dependent.
   static std::size_t value_to_node_offset()
   {
      const MemberHookType T::* const p = P;
      return *(const std::size_t*)(const void *)(&p);
//      using boost::get_pointer;
//      const typename node_traits::node *np =
//         get_pointer((((const value_type *)get_pointer(n))->*P).to_node_ptr());
//      return ((const char*)np - (const char*)(const value_type *)get_pointer(n));
   }
};

template<class KeyValueCompare, class ValueTraits>
struct key_node_ptr_compare
   :  private detail::ebo_holder<KeyValueCompare>
{
   typedef typename ValueTraits::node_ptr node_ptr;
   typedef detail::ebo_holder<KeyValueCompare> base_t;
   key_node_ptr_compare(KeyValueCompare kcomp)
      :  base_t(kcomp)
   {}

   template<class KeyType>
   bool operator()(node_ptr node, const KeyType &key) const
   {  return base_t::get()(*ValueTraits::to_value_ptr(node), key); }

   template<class KeyType>
   bool operator()(const KeyType &key, node_ptr node) const
   {  return base_t::get()(key, *ValueTraits::to_value_ptr(node)); }

   bool operator()(node_ptr node1, node_ptr node2) const
   {
      return base_t::get()
         (*ValueTraits::to_value_ptr(node1), *ValueTraits::to_value_ptr(node2)); 
   }
};


template<class F, class ValueTraits>
struct value_to_node_cloner
   :  private detail::ebo_holder<F>
{
   typedef typename ValueTraits::node_ptr node_ptr;
   typedef detail::ebo_holder<F> base_t;

   value_to_node_cloner(F f)
      :  base_t(f)
   {}
   
   node_ptr operator()(node_ptr p)
   {  return ValueTraits::to_node_ptr(*base_t::get()(*ValueTraits::to_value_ptr(p))); }
};

template<class F, class ValueTraits>
struct value_to_node_destroyer
   :  private detail::ebo_holder<F>
{
   typedef typename ValueTraits::node_ptr node_ptr;
   typedef detail::ebo_holder<F> base_t;
   value_to_node_destroyer(F f)
      :  base_t(f)
   {}

   void operator()(node_ptr p)
   {  base_t::get()(ValueTraits::to_value_ptr(p));   }
};

template <linking_policy Policy>
struct dispatcher
{};

template<class Container>
void destructor_impl(Container &cont, dispatcher<safe_link>)
{  BOOST_ASSERT(!cont.is_linked());  }

template<class Container>
void destructor_impl(Container &cont, dispatcher<auto_unlink>)
{  cont.unlink();  }

template<class Container>
void destructor_impl(Container &cont, dispatcher<normal_link>)
{}

template<class Node, class MaybeClass>
struct node_plus_pred
   :  public ebo_holder<MaybeClass>
   ,  public Node
{
   node_plus_pred()
      {}

   node_plus_pred(const Node &x, const MaybeClass &y)
      : Node(x), ebo_holder<MaybeClass>(y) {}

   node_plus_pred(const MaybeClass &y)
      : ebo_holder<MaybeClass>(y) {}

   Node &first()          
      {  return *this;  }
   const Node &first() const 
      {  return *this;  }
   MaybeClass &second()        
      {  return ebo_holder<MaybeClass>::get();  }
   const MaybeClass &second() const  
      {  return ebo_holder<MaybeClass>::get();  }

   static node_plus_pred *this_from_node(Node *n)
   {  return static_cast<node_plus_pred*>(n);   }

   static node_plus_pred *this_from_node(const Node *n)
   {  return static_cast<const node_plus_pred*>(n);   }
};


} //namespace detail 
} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP
