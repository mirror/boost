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

#ifndef BOOST_INTRUSIVE_SLIST_HPP
#define BOOST_INTRUSIVE_SLIST_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/slist_hook.hpp>
#include <boost/intrusive/circular_slist_algorithms.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <functional>
#include <cstddef>

namespace boost {
namespace intrusive {

//! The class template slist is an intrusive container, that encapsulates 
//! a singly-linked list. You can use such a list to squeeze the last bit 
//! of performance from your application. Unfortunately, the little gains 
//! come with some huge drawbacks. A lot of member functions can't be 
//! implemented as efficiently as for standard containers. To overcome 
//! this limitation some other member functions with rather unusual semantics 
//! have to be introduced.
//!
//! The template parameter ValueTraits is called "value traits". It stores
//! information and operations about the type to be stored in the container.
//!
//! If the user specifies ConstantTimeSize as "true", a member of type SizeType
//! will be embedded in the class, that will keep track of the number of stored objects.
//! This will allow constant-time O(1) size() member, instead of default O(N) size.
//! 
//! The iterators of slist are forward iterators. slist provides a static 
//! function called "previous" to compute the previous iterator of a given iterator. 
//! This function has linear complexity. To improve the usability esp. with 
//! the '*_after' functions, ++end() == begin() and previous(begin()) == end() 
//! are defined. In addition, whenever you have an end iterator, 'after this 
//! iterator' means 'at the beginning of the list'. To improve the self-documentation
//! a "before_begin()" function is defined, returning the end() iterator.
template < class ValueTraits
         , bool ConstantTimeSize //= true
         , class SizeType        //= std::size_t
         >
class slist
   :  private detail::size_holder<ConstantTimeSize, SizeType>
   ,  private ValueTraits::node_traits::node
{
   /// @cond
   private:
   typedef slist<ValueTraits, ConstantTimeSize, SizeType>  this_type; 
   typedef typename ValueTraits::node_traits                node_traits;
   typedef detail::size_holder<ConstantTimeSize, SizeType>  size_traits;

   //! This class is
   //! non-copyable
   slist (const slist&);

   //! This class is
   //! non-asignable
   slist &operator =(const slist&);
   /// @endcond

   //Public typedefs
   public:
   typedef ValueTraits                                               value_traits;
   typedef typename ValueTraits::value_type                          value_type;
   typedef typename ValueTraits::pointer                             pointer;
   typedef typename ValueTraits::const_pointer                       const_pointer;
   typedef typename std::iterator_traits<pointer>::reference         reference;
   typedef typename std::iterator_traits<const_pointer>::reference   const_reference;
   typedef typename std::iterator_traits<pointer>::difference_type   difference_type;
   typedef SizeType                                                  size_type;
   typedef detail::slist_iterator<value_type, ValueTraits>           iterator;
   typedef detail::slist_iterator<const value_type, ValueTraits>     const_iterator;

   /// @cond
   private:
   typedef typename node_traits::node              node;
   typedef typename boost::pointer_to_other
      <pointer, node>::type                        node_ptr;
   typedef typename boost::pointer_to_other
      <pointer, const node>::type                  const_node_ptr;
   typedef circular_slist_algorithms<node_traits>  node_algorithms;
   enum { safemode_or_autounlink  = 
            (int)ValueTraits::linking_policy == (int)auto_unlink   ||
            (int)ValueTraits::linking_policy == (int)safe_link     };

   //Constant-time size is incompatible with auto-unlink hooks!
   BOOST_STATIC_ASSERT(!(ConstantTimeSize && ((int)ValueTraits::linking_policy == (int)auto_unlink)));

   node_ptr get_root_node()
   {  return node_ptr(&static_cast<node&>(*this));  }

   const_node_ptr get_root_node() const
   {  return const_node_ptr(&static_cast<const node&>(*this));  }

   static node_ptr uncast(const_node_ptr ptr)
   {
      return node_ptr(const_cast<node*>(detail::get_pointer(ptr)));
   }

   static iterator previous_node(iterator beg, iterator i)
   {
      return iterator
         (node_algorithms::get_previous_node(beg.pointed_node(), i.pointed_node()));
   }

   static const_iterator previous_node(const_iterator beg, const_iterator i)
   {
      return const_iterator
         (node_algorithms::get_previous_node(beg.pointed_node(), i.pointed_node()));
   }
   /// @endcond

   public:
   //! <b>Effects</b>: constructs an empty list. 
   //! 
   //! <b>Complexity</b>: Constant 
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   slist()
   {
      size_traits::set_size(size_type(0));
      node_algorithms::init(this->get_root_node()); 
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Constructs a list equal to [first,last).
   //! 
   //! <b>Complexity</b>: Linear in std::distance(b, e). No copy constructors are called.  
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   template<class Iterator>
   slist(Iterator b, Iterator e)
   {
      size_traits::set_size(size_type(0));
      node_algorithms::init(this->get_root_node());
      insert_after(before_begin(), b, e);
   }

   //! <b>Effects</b>: If it's a safe-mode
   //!   or auto-unlink value, the destructor does nothing
   //!   (ie. no code is generated). Otherwise it detaches all elements from this. 
   //!   In this case the objects in the list are not deleted (i.e. no destructors 
   //!   are called), but the hooks according to the ValueTraits template parameter
   //!   are set to their default value.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the list, if 
   //!   it's a safe-mode or auto-unlink value. Otherwise constant.
   ~slist()
   {  this->clear(); }

   //! <b>Effects</b>: Erases all the elements of the container.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements of the list.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased elements.
   void clear()
   {
      if(safemode_or_autounlink){
         this->erase_after(this->before_begin(), this->end()); 
      }
      else{
         node_algorithms::init(this->get_root_node());
         size_traits::set_size(size_type(0));
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements of the container
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements of the list.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased elements.
   template <class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  this->erase_after_and_dispose(this->before_begin(), this->end(), disposer);   }

   //! <b>Requires</b>: value must be an lvalue.
   //! 
   //! <b>Effects</b>: Inserts the value in the front of the list.
   //!   No copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void push_front(reference value) 
   {
      node_ptr to_insert = ValueTraits::to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_MODE_CONTAINER_INSERTION_ASSERT(node_algorithms::unique(to_insert));
      node_algorithms::link_after(this->get_root_node(), to_insert); 
      size_traits::increment();
   }

   //! <b>Effects</b>: Erases the first element of the list.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased element.
   void pop_front() 
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      node_algorithms::unlink_after(this->get_root_node());
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the first element of the list.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   void pop_front_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      this->pop_front();
      disposer(ValueTraits::to_value_ptr(to_erase));
   }

   //! <b>Effects</b>: Returns a reference to the first element of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   reference front()
   { return *ValueTraits::to_value_ptr(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the first element of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reference front() const
   { return *ValueTraits::to_value_ptr(uncast(node_traits::get_next(this->get_root_node()))); }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   iterator begin() 
   { return iterator (node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const 
   { return const_iterator (node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const 
   { return const_iterator (node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   iterator end() 
   { return iterator (this->get_root_node()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator end() const 
   { return const_iterator (uncast(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const 
   { return const_iterator (uncast(this->get_root_node())); }

   //! <b>Effects</b>: Returns an iterator that points to a position
   //!   before the first element. Equivalent to "end()"
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   iterator before_begin() 
   { return end(); }

   //! <b>Effects</b>: Returns an iterator that points to a position
   //!   before the first element. Equivalent to "end()"
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator before_begin() const 
   { return end(); }

   //! <b>Effects</b>: Returns an iterator that points to a position
   //!   before the first element. Equivalent to "end()"
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator cbefore_begin() const 
   { return end(); }

   //! <b>Precondition</b>: end_iterator must be a valid end iterator
   //!   of slist.
   //! 
   //! <b>Effects</b>: Returns a const reference to the slist associated to the end iterator
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   static slist &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<slist&>(*end_iterator.pointed_node());  }

   //! <b>Precondition</b>: end_iterator must be a valid end const_iterator
   //!   of slist.
   //! 
   //! <b>Effects</b>: Returns a const reference to the slist associated to the end iterator
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   static const slist &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const slist&>(*end_iterator.pointed_node());  }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements contained in the list.
   //!   if ConstantTimeSize is false. Constant time otherwise.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   size_type size() const
   {
      if(ConstantTimeSize)
         return size_traits::get_size();
      else
         return node_algorithms::count(this->get_root_node()) - 1; 
   }

   //! <b>Effects</b>: Returns true if the list contains no elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   bool empty() const
   { return node_algorithms::unique(this->get_root_node()); }

   //! <b>Effects</b>: Swaps the elements of x and *this.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements of both lists.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void swap(slist& other)
   {
      node_algorithms::swap_nodes(this->get_root_node(), other.get_root_node());
      if(ConstantTimeSize){
         size_type backup = size_traits::get_size();
         size_traits::set_size(other.get_size());
         other.set_size(backup);
      }
   }

   //! <b>Effects</b>: Moves backwards all the elements, so that the first
   //!   element becomes the second, the second becomes the third...
   //!   the last element becomes the first one.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements plus the number shifts.
   //! 
   //! <b>Note</b>: Iterators Does not affect the validity of iterators and references.
   void shift_backwards(size_type n = 1)
   {
      //Null shift, nothing to do
      if(!n) return;
      node_ptr root = this->get_root_node();
      node_ptr first  = node_traits::get_next(root);

      //size() == 0 or 1, nothing to do
      if(node_traits::get_next(first) == root) return;

      //Iterate until the root node is found to know where the current last node is.
      //If the shift count is less than the size of the list, we can also obtain
      //the position of the new last node after the shift.
      node_ptr old_last(first), next_to_it, new_last(root);
      size_type distance = 1;
      while(root != (next_to_it = node_traits::get_next(old_last))){
         if(++distance > n)
            new_last = node_traits::get_next(new_last);
         old_last = next_to_it;
      }
      //If the shift was bigger or equal than the size, obtain the equivalent
      //forward shifts and find the new last node.
      if(distance <= n){
         //Now find the equivalent forward shifts.
         //Shorcut the shift with the modulo of the size of the list
         size_type new_before_last_pos = (distance - (n % distance))% distance;
         //If the shift is a multiple of the size there is nothing to do
         if(!new_before_last_pos)   return;
         
         for( new_last = root
            ; new_before_last_pos--
            ; new_last = node_traits::get_next(new_last)){
            //empty
         }
      }

      //Now unlink the root node and link it after the new last node
      node_algorithms::unlink_after(old_last);
      node_algorithms::link_after(new_last, root);
   }

   //! <b>Effects</b>: Moves forward all the elements, so that the second
   //!   element becomes the first, the third becomes the second...
   //!   the first element becomes the last one.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements plus the number shifts.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void shift_forward(size_type n = 1)
   {
      //Null shift, nothing to do
      if(!n) return;
      node_ptr root = this->get_root_node();
      node_ptr first  = node_traits::get_next(root);

      //size() == 0 or 1, nothing to do
      if(node_traits::get_next(first) == root) return;

      bool end_found = false;
      node_ptr new_last;

      //Now find the new last node according to the shift count.
      //If we find the root node before finding the new last node
      //unlink the root, shortcut the search now that we know the size of the list
      //and continue.
      for(size_type i = 1; i <= n; ++i){
         new_last = first;
         first = node_traits::get_next(first);
         if(first == root){
            //Shorcut the shift with the modulo of the size of the list
            n %= i;
            i = 0;
            //Unlink the root node and continue the new first node search
            first = node_traits::get_next(first);
            node_algorithms::unlink_after(new_last);
            end_found = true;
         }
      }

      //If the root node has not been found in the previous loop, find it
      //starting in the new first node and unlink it
      if(!end_found){
         node_algorithms::unlink_after(node_algorithms::get_previous_node(first, root));
      }

      //Now link the root node after the new last node
      node_algorithms::link_after(new_last, root);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the 
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!   
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //! 
   //! <b>Throws</b>: If cloner throws.
   template <class Cloner, class Disposer>
   void clone_from(const slist &src, Cloner cloner, Disposer disposer)
   {  
      this->clear_and_dispose(disposer);
      try{
         iterator prev = this->before_begin();
         const_iterator b(src.begin()), e(src.end());
         for(; b != e; ++b, ++prev){
            this->insert_after(prev, *cloner(*b));
         }
      }
      catch(...){
         clear_and_dispose(disposer);
         throw;
      }
   }

   //! <b>Requires</b>: value must be an lvalue and prev_p must point to an element
   //!   contained by the list or to end().
   //!
   //! <b>Effects</b>: Inserts the value after the position pointed by prev_p.
   //!    No copy constructor is called.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   iterator insert_after(iterator prev_p, reference value)
   {
      node_ptr n = ValueTraits::to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_MODE_CONTAINER_INSERTION_ASSERT(node_algorithms::unique(n));
      node_algorithms::link_after(prev_p.pointed_node(), n);
      size_traits::increment();
      return iterator (n);
   }

   //! <b>Requires</b>: Dereferencing iterator must yield 
   //!   an lvalue of type value_type and prev_p must point to an element
   //!   contained by the list or to the end node.
   //! 
   //! <b>Effects</b>: Inserts the [first, last)
   //!   after the position prev_p.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements inserted.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   template<class Iterator>
   void insert_after(iterator prev_p, Iterator first, Iterator last)
   {
      for (; first != last; ++first)
         prev_p = insert_after(prev_p, *first);
   }

   //! <b>Requires</b>: value must be an lvalue and p must point to an element
   //!   contained by the list or to end().
   //!
   //! <b>Effects</b>: Inserts the value before the position pointed by p.
   //!   No copy constructor is called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements before p. 
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   iterator insert(iterator p, reference value)
   {  return insert_after(this->previous(p), value);  }

   //! <b>Requires</b>: Dereferencing iterator must yield 
   //!   an lvalue of type value_type and p must point to an element 
   //!   contained by the list or to the end node.
   //! 
   //! <b>Effects</b>: Inserts the pointed by b and e
   //!   before the position p. No copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements inserted plus linear
   //!   to the elements before b.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   template<class Iterator>
   void insert(iterator p, Iterator b, Iterator e)
   {  return insert_after(this->previous(p), b, e);  }

   //! <b>Effects</b>: Erases the element after the element pointed by prev of 
   //!   the list. No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   iterator erase_after(iterator prev)
   {
      iterator it(prev); ++it;
      node_ptr to_erase(it.pointed_node());
      node_algorithms::unlink_after(prev.pointed_node());
      size_traits::decrement();
      iterator ret(++prev);
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      return ret;
   }

   //! <b>Effects</b>: Erases the range (before_first, last) from
   //!   the list. No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Lineal to the elements (last - before_first).
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   iterator erase_after(iterator before_first, iterator last)
   {
      iterator first;
      while(++(first = before_first) != last){
         this->erase_after(before_first);
      }
      return last;
   }

   //! <b>Effects</b>: Erases the element pointed by i of the list. 
   //!   No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed element,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the elements before i.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   iterator erase(iterator i)
   {  return this->erase_after(this->previous(i));  }

   //! <b>Requires</b>: first and last must be valid iterator to elements in *this.
   //! 
   //! <b>Effects</b>: Erases the range pointed by b and e.
   //!   No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements erased plus linear
   //!   to the elements before first.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased elements.
   iterator erase(iterator first, iterator last)
   {  return erase_after(this->previous(first), last);  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element after the element pointed by prev of 
   //!   the list.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   iterator erase_after_and_dispose(iterator prev, Disposer disposer)
   {
      iterator it(prev); ++it;
      node_ptr to_erase(it.pointed_node());
      iterator ret(this->erase_after(prev));
      disposer(ValueTraits::to_value_ptr(to_erase));
      return ret;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range (before_first, last) from
   //!   the list.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Lineal to the elements (last - before_first).
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   iterator erase_after_and_dispose(iterator before_first, iterator last, Disposer disposer)
   {
      iterator first;
      while(++(first = before_first) != last){
         this->erase_after_and_dispose(before_first, disposer);
      }
      return last;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed by i of the list. 
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed element,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the elements before i.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   template<class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer)
   {  return this->erase_after_and_dispose(this->previous(i), disposer);  }

   //! <b>Requires</b>: first and last must be valid iterator to elements in *this.
   //!                  Disposer::operator()(pointer) shouldn't throw.
   //! 
   //! <b>Effects</b>: Erases the range pointed by b and e.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements erased plus linear
   //!   to the elements before first.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased elements.
   template<class Disposer>
   iterator erase_and_dispose(iterator first, iterator last, Disposer disposer)
   {  return erase_after_and_dispose(this->previous(first), last, disposer);  }

   //! <b>Requires</b>: Dereferencing iterator must yield 
   //!   an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Clears the list and inserts the range pointed by b and e.
   //!   No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements inserted plus
   //!   linear to the elements contained in the list if it's a safe-mode
   //!   or auto-unlink value.
   //!   Linear to the number of elements inserted in the list otherwise.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!   to the erased elements.
   template<class Iterator>
   void assign(Iterator b, Iterator e)
   {
      this->clear();
      this->insert_after(before_begin(), b, e);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Requires</b>: Dereferencing iterator must yield 
   //!   an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Clears the list and inserts the range pointed by b and e.
   //!   No destructors or copy constructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements inserted plus
   //!   linear to the elements contained in the list.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!   to the erased elements.
   template<class Iterator, class Disposer>
   void dispose_and_assign(Disposer disposer, Iterator b, Iterator e)
   {
      this->clear_and_dispose(disposer);
      this->insert_after_and_dispose(before_begin(), b, e, disposer);
   }

   //! <b>Requires</b>: prev is an iterator to an element or x.end()/x.before_begin() in x.
   //! 
   //! <b>Effects</b>: Transfers all the elements of list x to this list, after the
   //! the element pointed by prev. No destructors or copy constructors are called.
   //! 
   //! <b>Returns</b>: The last element inserted of x or prev if x is empty.
   //!   This iterator can be used as new "prev" iterator for a new splice_after call.
   //!   that will splice new values after the previously spliced values.
   //! 
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements contained in x
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //! list. Iterators of this list and all the references are not invalidated.
   iterator splice_after(iterator prev, slist &x)
   {
      if (!x.empty()){
         iterator last_x(x.previous(x.end()));
         node_algorithms::transfer_after
            ( prev.pointed_node()
            , x.end().pointed_node()
            , last_x.pointed_node());
         size_traits::set_size(size_traits::get_size() + x.get_size());
         x.set_size(size_type(0));
         return last_x;
      }
      else{
         return prev;
      }
   }

   //! <b>Requires</b>: prev must point to an element contained by this list or
   //!   to the before_begin() element. prev_ele must point to an element contained in list
   //!   x or must be x.before_begin().
   //! 
   //! <b>Effects</b>: Transfers the element after prev_ele, from list x to this list, 
   //!   after the element pointed by prev. No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //! list. Iterators of this list and all the references are not invalidated.
   void splice_after(iterator prev, slist &x, iterator prev_ele)
   {
      iterator nxt = prev_ele;
      ++nxt;
      if (nxt != prev && prev_ele != prev){
         node_algorithms::transfer_after
            (prev.pointed_node(), prev_ele.pointed_node(), nxt.pointed_node());
         size_traits::increment();
         x.decrement();
      }
   }

   //! <b>Requires</b>: prev_pos must be a dereferenceable iterator in *this or be
   //!   before_begin(), and before_first and before_last belong to x and
   //!   ++before_first != x.end() && before_last != x.end(). 
   //! 
   //! <b>Effects</b>: Transfers the range (before_first, before_last] from list x to this
   //!   list, after the element pointed by prev_pos.
   //!   No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements transferred
   //!   if ConstantTimeSize is true. Constant-time otherwise.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(iterator prev_pos, slist &x, iterator before_first, iterator before_last)
   {
      if (before_first != before_last){
         if(ConstantTimeSize){
            size_type increment = std::distance(before_first, before_last);
            node_algorithms::transfer_after
               (prev_pos.pointed_node(), before_first.pointed_node(), before_last.pointed_node());
            size_traits::set_size(size_traits::get_size() + increment);
            x.set_size(x.get_size() - increment);
         }
         else{
            node_algorithms::transfer_after
               (prev_pos.pointed_node(), before_first.pointed_node(), before_last.pointed_node());
         }
      }
   }

   //! <b>Requires</b>: prev_pos must be a dereferenceable iterator in *this or be
   //!   before_begin(), and before_first and before_last belong to x and
   //!   ++before_first != x.end() && before_last != x.end() and
   //!   n == std::distance(before_first, before_last).
   //! 
   //! <b>Effects</b>: Transfers the range (before_first, before_last] from list x to this
   //!   list, after the element pointed by p. No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant time.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(iterator prev_pos, slist &x, iterator before_first, iterator before_last, difference_type n)
   {
      if(n){
         if(ConstantTimeSize){
            BOOST_INTRUSIVE_INVARIANT_ASSERT(std::distance(before_first, before_last) == n);
            node_algorithms::transfer_after
               (prev_pos.pointed_node(), before_first.pointed_node(), before_last.pointed_node());
            size_traits::set_size(size_traits::get_size() + n);
            x.set_size(x.get_size() - n);
         }
         else{
            node_algorithms::transfer_after
               (prev_pos.pointed_node(), before_first.pointed_node(), before_last.pointed_node());
         }
      }
   }

   //! <b>Requires</b>: it is an iterator to an element in x.
   //! 
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //! the element pointed by it. No destructors or copy constructors are called.
   //! 
   //! <b>Returns</b>: The last element inserted of x or the previous element
   //!   of it if x is empty.
   //!   This iterator can be used as new "prev" iterator for a new splice call.
   //!   that will splice new values after the previously spliced values.
   //! 
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements contained in x plus linear to
   //!   the elements before it.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //! list. Iterators of this list and all the references are not invalidated.
   iterator splice(iterator it, slist &x)
   {  return splice_after(this->previous(it), x);   }

   //! <b>Requires</b>: it p must be a valid iterator of *this.
   //!   elem must point to an element contained in list
   //!   x.
   //! 
   //! <b>Effects</b>: Transfers the element elem, from list x to this list, 
   //!   before the element pointed by pos. No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the elements before pos and before elem.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //! list. Iterators of this list and all the references are not invalidated.
   void splice(iterator pos, slist &x, iterator elem)
   {  return splice_after(this->previous(pos), x, this->previous(elem));  }

   //! <b>Requires</b>: pos must be a dereferenceable iterator in *this
   //!   and first and last belong to x and first and last a valid range on x. 
   //! 
   //! <b>Effects</b>: Transfers the range [first, last) from list x to this
   //!   list, before the element pointed by pos.
   //!   No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the sum of elements before pos, first, and last.
   //!   Plus linear to the number of elements transferred if ConstantTimeSize is true.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(iterator pos, slist &x, iterator first, iterator last)
   {  return splice_after(this->previous(pos), x, this->previous(first), this->previous(last));  }

   //! <b>Requires</b>: pos must be a dereferenceable iterator in *this
   //!   and first and last belong to x and first and last a valid range on x. 
   //!   n == std::distance(first, last).
   //! 
   //! <b>Effects</b>: Transfers the range [first, last) from list x to this
   //!   list, before the element pointed by pos.
   //!   No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the sum of elements before pos, first, and last.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(iterator pos, slist &x, iterator first, iterator last, difference_type n)
   {  return splice_after(this->previous(pos), x, this->previous(first), this->previous(last), n);  }

   //! <b>Effects</b>: This function sorts the list *this according to std::less<value_type>. 
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the predicate throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated
   template<class Predicate>
   void sort(Predicate p)
   {
      if (node_traits::get_next(node_traits::get_next(this->get_root_node()))
               != this->get_root_node()) {
         slist carry;
         slist counter[64];
         int fill = 0;
         iterator last_inserted;
         while(!this->empty()){
            last_inserted = this->begin();
            carry.splice_after(carry.before_begin(), *this, this->before_begin());
            int i = 0;
            while(i < fill && !counter[i].empty()) {
               last_inserted = carry.merge(counter[i++], p);
            }
            BOOST_INTRUSIVE_INVARIANT_ASSERT(counter[i].empty());

            iterator last_element(previous_node(last_inserted, carry.end()));
            if(ConstantTimeSize){
               counter[i].splice_after( counter[i].end(), carry
                                      , carry.before_begin(), last_element
                                      , carry.size());
            }
            else{
               counter[i].splice_after( counter[i].end(), carry
                                      , carry.before_begin(), last_element);
            }
            //counter[i].splice_after(counter[i].end(), carry, carry.end(), previous_node(last_inserted, carry.end()));
            //carry.swap(counter[i]);
            if(i == fill)
               ++fill;
         }

         for (int i = 1; i < fill; ++i)
            last_inserted = counter[i].merge(counter[i-1], p);
         //this->swap(counter[fill-1]);
         BOOST_INTRUSIVE_INVARIANT_ASSERT(this->empty());

         iterator last_element(previous_node(last_inserted, counter[--fill].end()));
         if(ConstantTimeSize){
            this->splice_after( end(), counter[fill], counter[fill].before_begin()
                              , last_element, counter[fill].size());
         }
         else{
            this->splice_after( end(), counter[fill], counter[fill].before_begin()
                              , last_element);
         }
      }
   }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct. 
   //! 
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is 
   //!   equivalent to one from x, then the element from *this will precede the one from x. 
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or std::less<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated.
   void sort()
   { this->sort(std::less<value_type>()); }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct. 
   //! 
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is 
   //!   equivalent to one from x, then the element from *this will precede the one from x. 
   //! 
   //! <b>Returns</b>: An iterator to the last transferred value, end() is x is empty.
   //! 
   //! <b>Throws</b>: If the predicate throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated.
   template<class Predicate>
   iterator merge(slist& x, Predicate p) 
   {
      iterator a(before_begin()), e(end()), ax(x.before_begin());
      iterator last_inserted(e);
      iterator a_next;
      while(++(a_next = a) != e && !x.empty()) {
         iterator ix(ax);
         iterator cx;
         size_type n(0);
         while(++(cx = ix) != ax && p(*cx, *a_next)){
            ++ix; ++n;
         }
         if(ax != ix){
            this->splice_after(a, x, ax, ix, n);
            last_inserted = ix;
         }
         a = a_next;
      }  
      if (!x.empty()){
         last_inserted = this->splice_after(a, x);
      }
      return last_inserted;
   }

   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this according to std::less<value_type>. The merge is stable; 
   //!   that is, if an element from *this is equivalent to one from x, then the element 
   //!   from *this will precede the one from x. 
   //! 
   //! <b>Throws</b>: if std::less<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated
   void merge(slist& x)
   { this->merge(x, std::less<value_type>()); }

   //! <b>Effects</b>: Reverses the order of elements in the list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: This function is linear to the contained elements.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated
   void reverse() 
   {  node_algorithms::reverse(this->get_root_node());  }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid. This function is 
   //!   linear time: it performs exactly size() comparisons for equality.
   void remove(const_reference value)
   {  remove_if(detail::equal_to_value<const_reference>(value));  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void remove_and_dispose(const_reference value, Disposer disposer)
   {  remove_and_dispose_if(detail::equal_to_value<const_reference>(value), disposer);  }

   //! <b>Effects</b>: Removes all the elements for which a specified
   //!   predicate is satisfied. No destructors are called.
   //! 
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time. It performs exactly size() calls to the predicate.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Pred>
   void remove_if(Pred pred)
   {  remove_and_dispose_if(pred, detail::null_disposer());   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes all the elements for which a specified
   //!   predicate is satisfied.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Pred, class Disposer>
   void remove_and_dispose_if(Pred pred, Disposer disposer)
   {
      iterator bcur(this->before_begin()), cur, e(this->end());
      
      while(++(cur = bcur) != e){
         if (pred(*cur)){
            pointer p = cur.operator->();
            this->erase_after(bcur);
            disposer(p);
         }
         else{
            ++bcur;
         }
      }
   }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that are equal from the list. No destructors are called.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons calls to pred()).
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void unique()
   {  unique_and_dispose(std::equal_to<value_type>(), detail::null_disposer());  }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that satisfy some binary predicate from the list.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: If the predicate throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate>
   void unique(BinaryPredicate pred)
   {  unique_and_dispose(pred, detail::null_disposer());  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that satisfy some binary predicate from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void unique_and_dispose(Disposer disposer)
   {  unique(std::equal_to<value_type>(), disposer);  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that satisfy some binary predicate from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //! 
   //! <b>Throws</b>: If the predicate throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate, class Disposer>
   void unique_and_dispose(BinaryPredicate pred, Disposer disposer)
   {
      iterator end_n(end());
      iterator cur(begin());
      iterator cur_next;

      if (cur != end_n) {
         while(++(cur_next = cur) != end_n) {
            if (pred(*cur, *cur_next)){
               pointer p = cur_next.operator->();
               this->erase_after(cur);
               disposer(p);
            }
            else{
               ++cur;
            }
         }
      }
   }

   //! <b>Requires</b>: value must be a reference to a value inserted in a list.
   //! 
   //! <b>Effects</b>: This function returns a const_iterator pointing to the element
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant time.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated.
   static iterator iterator_to(reference value) 
   { 
      BOOST_INTRUSIVE_INVARIANT_ASSERT (!node_algorithms::unique(ValueTraits::to_node_ptr(value)));
      return iterator (ValueTraits::to_node_ptr(value)); 
   }

   //! <b>Requires</b>: value must be a const reference to a value inserted in a list.
   //! 
   //! <b>Effects</b>: This function returns an iterator pointing to the element.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant time.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated.
   static const_iterator iterator_to(const_reference value) 
   { 
      BOOST_INTRUSIVE_INVARIANT_ASSERT (!node_algorithms::unique(ValueTraits::to_node_ptr(const_cast<reference> (value))));
      return const_iterator (ValueTraits::to_node_ptr(const_cast<reference> (value))); 
   }

   //! <b>Returns</b>: The iterator to the element before i in the list. 
   //!   Returns the end-iterator, if either i is the begin-iterator or the 
   //!   list is empty. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements before i. 
   iterator previous(iterator i)
   {
      return iterator
         (node_algorithms::get_previous_node
            (before_begin().pointed_node(), i.pointed_node()));
   }

   //! <b>Returns</b>: The const_iterator to the element before i in the list. 
   //!   Returns the end-const_iterator, if either i is the begin-const_iterator or 
   //!   the list is empty. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements before i. 
   const_iterator previous(const_iterator i) const
   {
      return const_iterator
         (node_algorithms::get_previous_node
            (before_begin().pointed_node(), i.pointed_node()));
   }
};

template <class V, bool C, class S>
inline bool operator==(const slist<V, C, S>& x, const slist<V, C, S>& y)
{
   if(C && x.size() != y.size()){
      return false;
   }
   typedef typename slist<V, C, S>::const_iterator const_iterator;
   const_iterator end1 = x.end();

   const_iterator i1 = x.begin();
   const_iterator i2 = y.begin();
   if(C){
      while (i1 != end1 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1;
   }
   else{
      const_iterator end2 = y.end();
      while (i1 != end1 && i2 != end2 && *i1 == *i2) {
         ++i1;
         ++i2;
      }
      return i1 == end1 && i2 == end2;
   }
}

template <class V, bool C, class S>
inline bool operator<(const slist<V, C, S>& x,
                      const slist<V, C, S>& y)
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template <class V, bool C, class S>
inline bool operator!=(const slist<V, C, S>& x, const slist<V, C, S>& y) 
{  return !(x == y); }

template <class V, bool C, class S>
inline bool operator>(const slist<V, C, S>& x, const slist<V, C, S>& y) 
{  return y < x;  }

template <class V, bool C, class S>
inline bool operator<=(const slist<V, C, S>& x, const slist<V, C, S>& y) 
{  return !(y < x);  }

template <class V, bool C, class S>
inline bool operator>=(const slist<V, C, S>& x, const slist<V, C, S>& y) 
{  return !(x < y);  }

template <class V, bool C, class S>
inline void swap(slist<V, C, S>& x, slist<V, C, S>& y)
{  x.swap(y);  }

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SLIST_HPP
