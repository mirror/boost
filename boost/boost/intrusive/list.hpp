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

#ifndef BOOST_INTRUSIVE_LIST_HPP
#define BOOST_INTRUSIVE_LIST_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <boost/static_assert.hpp>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cstddef>
#include <iterator>

namespace boost {
namespace intrusive {

//! The class template list is an intrusive container that mimics most of the 
//! interface of std::list as described in the C++ standard.
//!
//! The template parameter ValueTraits is called "value traits". It stores
//! information and operations about the type to be stored in the container.
//!
//! If the user specifies ConstantTimeSize as "true", a member of type SizeType
//! will be embedded in the class, that will keep track of the number of stored objects.
//! This will allow constant-time O(1) size() member, instead of default O(N) size.
template< class ValueTraits
        , bool  ConstantTimeSize //= true
        , class SizeType         //= std::size_t
        >
class list
   :  private detail::size_holder<ConstantTimeSize, SizeType>
   ,  private ValueTraits::node_traits::node
{
   /// @cond
   private:
   typedef list<ValueTraits, ConstantTimeSize, SizeType>   this_type; 
   typedef typename ValueTraits::node_traits                node_traits;
   typedef detail::size_holder<ConstantTimeSize, SizeType>  size_traits;

   //! This class is
   //! non-copyable
   list (const list&);

   //! This class is
   //! non-assignable
   list &operator =(const list&);
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
   typedef detail::list_iterator<value_type, ValueTraits>            iterator;
   typedef detail::list_iterator<const value_type, ValueTraits>      const_iterator;
   typedef std::reverse_iterator<iterator>                           reverse_iterator;
   typedef std::reverse_iterator<const_iterator>                     const_reverse_iterator;

   /// @cond
   private:
   typedef typename node_traits::node              node;
   typedef typename node_traits::node_ptr          node_ptr;
   typedef typename node_traits::const_node_ptr    const_node_ptr;
   typedef circular_list_algorithms<node_traits>            node_algorithms;
   enum { safemode_or_autounlink  = 
            (int)ValueTraits::linking_policy == (int)auto_unlink   ||
            (int)ValueTraits::linking_policy == (int)safe_link     };

   //Constant-time size is incompatible with auto-unlink hooks!
   BOOST_STATIC_ASSERT(!(ConstantTimeSize && ((int)ValueTraits::linking_policy == (int)auto_unlink)));

   //Const cast emulation for smart pointers
   static node_ptr uncast(const_node_ptr ptr)
   {
      //return node_ptr(detail::get_pointer(ptr)));
      return const_cast<node*>(detail::get_pointer(ptr));
   }

   node_ptr get_root_node()
   {  return node_ptr(&static_cast<node&>(*this));  }

   const_node_ptr get_root_node() const
   {  return const_node_ptr(&static_cast<const node&>(*this));  }
   /// @endcond

   public:
   //! <b>Effects</b>: constructs an empty list. 
   //! 
   //! <b>Complexity</b>: Constant 
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   list()
   {  
      size_traits::set_size(size_type(0));
      node_algorithms::init(this->get_root_node());  
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Constructs a list equal to the range [first,last).
   //! 
   //! <b>Complexity</b>: Linear in std::distance(b, e). No copy constructors are called.  
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   template<class Iterator>
   list(Iterator b, Iterator e)
   {
      size_traits::set_size(size_type(0));
      node_algorithms::init(this->get_root_node());
      this->insert(this->end(), b, e);
   }

   //! <b>Effects</b>: If it's not a safe-mode or an auto-unlink value_type 
   //!   the destructor does nothing
   //!   (ie. no code is generated). Otherwise it detaches all elements from this. 
   //!   In this case the objects in the list are not deleted (i.e. no destructors 
   //!   are called), but the hooks according to the ValueTraits template parameter
   //!   are set to their default value.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the list, if 
   //!   it's a safe-mode or auto-unlink value . Otherwise constant. 
   ~list() 
   {
      if(safemode_or_autounlink){
         this->clear(); 
      }
   }

   //! <b>Requires</b>: value must be an lvalue.
   //! 
   //! <b>Effects</b>: Inserts the value in the back of the list.
   //!   No copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void push_back(reference value) 
   {
      node_ptr to_insert = ValueTraits::to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_MODE_CONTAINER_INSERTION_ASSERT(node_algorithms::unique(to_insert));
      node_algorithms::link_before(this->get_root_node(), to_insert);
      size_traits::increment();
   }

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
      node_algorithms::link_before(node_traits::get_next(this->get_root_node()), to_insert); 
      size_traits::increment();
   }

   //! <b>Effects</b>: Erases the last element of the list.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased element.
   void pop_back() 
   {
      node_ptr to_erase = node_traits::get_previous(this->get_root_node());
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the last element of the list.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   void pop_back_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_previous(this->get_root_node());
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(ValueTraits::to_value_ptr(to_erase));
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
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the first element of the list.
   //!   No destructors are called.
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
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
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

   //! <b>Effects</b>: Returns a reference to the last element of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   reference back() 
   { return *ValueTraits::to_value_ptr(node_traits::get_previous(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the last element of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reference back() const 
   { return *ValueTraits::to_value_ptr(uncast(node_traits::get_previous(this->get_root_node()))); }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   iterator begin() 
   { return iterator(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const 
   { return cbegin(); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const 
   { return const_iterator(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   iterator end() 
   { return iterator(this->get_root_node()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator end() const 
   { return cend(); }

   //! <b>Effects</b>: Returns a constant iterator to the end of the list.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const
   { return const_iterator(uncast(this->get_root_node())); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning 
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin()
   { return reverse_iterator(end()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning 
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const 
   { return crbegin(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning 
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const 
   { return const_reverse_iterator(end()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend()   
   { return reverse_iterator(begin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const   
   { return crend(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const   
   { return const_reverse_iterator(begin()); }

   //! <b>Precondition</b>: end_iterator must be a valid end iterator
   //!   of list.
   //! 
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   static list &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<list&>(*end_iterator.pointed_node());  }

   //! <b>Precondition</b>: end_iterator must be a valid end const_iterator
   //!   of list.
   //! 
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   static const list &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const list&>(*end_iterator.pointed_node());  }

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
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void swap(list& other)
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
   //! <b>Complexity</b>: Linear to the number of shifts.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void shift_backwards(size_type n = 1)
   {
      //Null shift, nothing to do
      if(!n)   return;
      node_ptr root  = this->get_root_node();
      node_ptr last  = node_traits::get_previous(root);
      //size() == 0 or 1, nothing to do
      if(last == node_traits::get_next(root))   return;

      node_algorithms::unlink(root);
      //Now get the new last node
      while(n--){
         last = node_traits::get_previous(last);
      }
      node_algorithms::link_after(last, root);
   }

   //! <b>Effects</b>: Moves forward all the elements, so that the second
   //!   element becomes the first, the third becomes the second...
   //!   the first element becomes the last one.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of shifts.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void shift_forward(size_type n = 1)
   {
      //Null shift, nothing to do
      if(!n) return;
      node_ptr root  = this->get_root_node();
      node_ptr first  = node_traits::get_next(root);
      //size() == 0 or 1, nothing to do
      if(first == node_traits::get_previous(root)) return;
      node_algorithms::unlink(root);
      //Now get the new first node
      while(n--){
         first = node_traits::get_next(first);
      }
      node_algorithms::link_before(first, root);
   }

   //! <b>Effects</b>: Erases the element pointed by i of the list.
   //!   No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed element,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   iterator erase(iterator i)
   {
      iterator erase = i;
      ++i;
      node_ptr to_erase = erase.pointed_node();
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      return i;
   }

   //! <b>Requires</b>: first and last must be valid iterator to elements in *this.
   //!
   //! <b>Effects</b>: Erases the element range pointed by b and e
   //! No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements erased if it's a safe-mode
   //!   or auto-unlink value. Constant time otherwise.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the 
   //!   erased elements.
   iterator erase(iterator b, iterator e)
   {
      if(safemode_or_autounlink || ConstantTimeSize){
         while(b != e){
            b = this->erase(b);
         }
         return b;
      }
      else{
         node_algorithms::unlink(b.pointed_node(), e.pointed_node());
         return e;
      }
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
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template <class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer)
   {
      iterator erase = i;
      ++i;
      node_ptr to_erase = erase.pointed_node();
      node_algorithms::unlink(to_erase);
      size_traits::decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(ValueTraits::to_value_ptr(to_erase));
      return i;
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element range pointed by b and e
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements erased.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased elements.
   template <class Disposer>
   iterator erase_and_dispose(iterator b, iterator e, Disposer disposer)
   {
      while(b != e){
         b = this->erase_and_dispose(b, disposer);
      }
      return b;
   }

   //! <b>Effects</b>: Erases all the elements of the container.
   //!   No destructors are called.
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
         this->erase(this->begin(), this->end()); 
      }
      else{
         node_algorithms::init(this->get_root_node());
         size_traits::set_size(size_type(0));
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements of the container.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements of the list.
   //! 
   //! <b>Note</b>: Invalidates the iterators to the erased elements.
   template <class Disposer>
   void clear_and_dispose(Disposer disposer)
   {  this->erase_and_dispose(this->begin(), this->end(), disposer);   }

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
   //! <b>Throws</b>: If cloner throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(const list &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      try{
         const_iterator b(src.begin()), e(src.end());
         for(; b != e; ++b){
            this->push_back(*cloner(*b));
         }
      }
      catch(...){
         clear_and_dispose(disposer);
         throw;
      }
   }

   //! <b>Requires</b>: value must be an lvalue and p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts the value before the position pointed by p.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant time. No copy constructors are called.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   iterator insert(iterator p, reference value)
   {
      node_ptr to_insert = ValueTraits::to_node_ptr(value);
      if(safemode_or_autounlink)
         BOOST_INTRUSIVE_SAFE_MODE_CONTAINER_INSERTION_ASSERT(node_algorithms::unique(to_insert));
      node_algorithms::link_before(p.pointed_node(), to_insert);
      size_traits::increment();
      return iterator(to_insert);
   }

   //! <b>Requires</b>: Dereferencing iterator must yield 
   //!   an lvalue of type value_type and p must be a valid iterator of *this.
   //! 
   //! <b>Effects</b>: Inserts the range pointed by b and e before the position p.
   //!   No copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements inserted.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   template<class Iterator>
   void insert(iterator p, Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert(p, *b);
   }

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
      this->insert(this->end(), b, e);
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
      this->clear(disposer);
      this->insert(this->end(), b, e);
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(iterator p, list& x)
   {
      if(!x.empty()){
         node_algorithms::transfer
            (p.pointed_node(), x.begin().pointed_node(), x.end().pointed_node());
         size_traits::set_size(size_traits::get_size() + x.get_size());
         x.set_size(size_type(0));
      }
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   new_ele must point to an element contained in list x.
   //! 
   //! <b>Effects</b>: Transfers the value pointed by new_ele, from list x to this list, 
   //!   before the the element pointed by p. No destructors or copy constructors are called.
   //!   If p == new_ele or p == ++new_ele, this function is a null operation. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(iterator p, list&x, iterator new_ele)
   {
      node_algorithms::transfer(p.pointed_node(), new_ele.pointed_node());
      x.decrement();
      size_traits::increment();
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   start and end must point to elements contained in list x.
   //! 
   //! <b>Effects</b>: Transfers the range pointed by start and end from list x to this list, 
   //!   before the the element pointed by p. No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements transferred
   //!   if ConstantTimeSize is true. Constant-time otherwise.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(iterator p, list&x, iterator start, iterator end)
   {
      if(start != end){
         if(ConstantTimeSize){
            size_type increment = std::distance(start, end);
            node_algorithms::transfer(p.pointed_node(), start.pointed_node(), end.pointed_node());
            size_traits::set_size(size_traits::get_size() + increment);
            x.set_size(x.get_size() - increment);
         }
         else{
            node_algorithms::transfer(p.pointed_node(), start.pointed_node(), end.pointed_node());
         }
      }
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   start and end must point to elements contained in list x.
   //!   n == std::distance(start, end)
   //! 
   //! <b>Effects</b>: Transfers the range pointed by start and end from list x to this list, 
   //!   before the the element pointed by p. No destructors or copy constructors are called.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(iterator p, list&x, iterator start, iterator end, difference_type n)
   {
      if(n){
         if(ConstantTimeSize){
            BOOST_INTRUSIVE_INVARIANT_ASSERT(n == std::distance(start, end));
            node_algorithms::transfer(p.pointed_node(), start.pointed_node(), end.pointed_node());
            size_traits::set_size(size_traits::get_size() + n);
            x.set_size(x.get_size() - n);
         }
         else{
            node_algorithms::transfer(p.pointed_node(), start.pointed_node(), end.pointed_node());
         }
      }
   }

   //! <b>Effects</b>: This function sorts the list *this according to std::less<value_type>. 
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or std::less<value_type> throws. Basic guarantee.
   //!
   //! <b>Notes</b>: Iterators and references are not invalidated.
   //! 
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   void sort() 
   {  sort(std::less<value_type>());  }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak ordering
   //! 
   //! <b>Effects</b>: This function sorts the list *this according to p. The sort is 
   //!   stable, that is, the relative order of equivalent elements is preserved.
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the predicate throws. Basic guarantee.
   //!
   //! <b>Notes</b>: This won't throw if list_base_hook<>::value_traits or
   //!   list_member_hook::::value_traits are used as value traits.
   //!   Iterators and references are not invalidated.
   //! 
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   template<class Predicate>
   void sort(Predicate p)
   {
      if(node_traits::get_next(this->get_root_node()) 
         != node_traits::get_previous(this->get_root_node())){
         list carry;
         list counter[64];
         int fill = 0;
         while(!this->empty()){
            carry.splice(carry.begin(), *this, this->begin());
            int i = 0;
            while(i < fill && !counter[i].empty()) {
               carry.merge(counter[i++], p);
            }
            carry.swap(counter[i]);
            if(i == fill)
               ++fill;
         }
         for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i-1], p);
         this->swap(counter[fill-1]);
      }
   }

   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this according to std::less<value_type>. The merge is stable; 
   //!   that is, if an element from *this is equivalent to one from x, then the element 
   //!   from *this will precede the one from x. 
   //! 
   //! <b>Throws</b>: If std::less<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated
   void merge(list& x)
   { merge(x, std::less<value_type>()); }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct. 
   //! 
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is 
   //!   equivalent to one from x, then the element from *this will precede the one from x. 
   //! 
   //! <b>Throws</b>: If the predicate throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated.
   template<class Predicate>
   void merge(list& x, Predicate p)
   {
      iterator e = this->end();
      iterator bx = x.begin();
      iterator ex = x.end();

      for (iterator b = this->begin(); b != e; ++b) {
         size_type n(0);
         iterator ix(bx);
         while(ix != ex && p(*ix, *b)){
            ++ix; ++n;
         }
         this->splice(b, x, bx, ix, n);
         bx = ix;
      }
      //Now transfer the rest at the end of the container
      this->splice(e, x);
   }

   //! <b>Effects</b>: Reverses the order of elements in the list. 
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: This function is linear time.
   //! 
   //! <b>Note</b>: Iterators and references are not invalidated
   void reverse()
   {  node_algorithms::reverse(this->get_root_node());   }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
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
      iterator first = begin();
      iterator last = end();
      while(first != last) {
         iterator next = first;
         ++next;
         if(pred(*first)){
            pointer p = first.operator->();
            this->erase(first);
            disposer(p);
         }
         first = next;
      }
   }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that are equal from the list. No destructors are called.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1 comparisons calls to pred()).
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void unique()
   {  unique_and_dispose(std::equal_to<value_type>(), detail::null_disposer());  }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that satisfy some binary predicate from the list.
   //!   No destructors are called.
   //! 
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1 comparisons equality comparisons).
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate>
   void unique(BinaryPredicate pred)
   {  unique_and_dispose(pred, detail::null_disposer());  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that are equal from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //! 
   //! <b>Throws</b>: If std::equal_to<value_type throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void unique_and_dispose(Disposer disposer)
   {  unique_and_dispose(std::equal_to<value_type>(), disposer);  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent 
   //!   elements that satisfy some binary predicate from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //! 
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //! 
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //! 
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate, class Disposer>
   void unique_and_dispose(BinaryPredicate pred, Disposer disposer)
   {
      if(!this->empty()){
         iterator first = begin();
         iterator after = first;
         ++after;
         while(after != this->end()){
            if(pred(*first, *after)){
               pointer p = after.operator->();
               after = erase(after);
               disposer(p);
            }
            else{
               first = after++;
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
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::unique(ValueTraits::to_node_ptr(value)));
      return iterator(ValueTraits::to_node_ptr(value)); 
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
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::unique(ValueTraits::to_node_ptr(const_cast<reference> (value))));
      return const_iterator(ValueTraits::to_node_ptr(const_cast<reference> (value))); 
   }
};

template <class V, bool C, class S>
inline bool operator==(const list<V, C, S>& x, const list<V, C, S>& y)
{
   if(C && x.size() != y.size()){
      return false;
   }
   typedef typename list<V, C, S>::const_iterator const_iterator;
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
inline bool operator<(const list<V, C, S>& x,
                      const list<V, C, S>& y)
{  return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

template <class V, bool C, class S>
inline bool operator!=(const list<V, C, S>& x, const list<V, C, S>& y) 
{  return !(x == y); }

template <class V, bool C, class S>
inline bool operator>(const list<V, C, S>& x, const list<V, C, S>& y) 
{  return y < x;  }

template <class V, bool C, class S>
inline bool operator<=(const list<V, C, S>& x, const list<V, C, S>& y) 
{  return !(y < x);  }

template <class V, bool C, class S>
inline bool operator>=(const list<V, C, S>& x, const list<V, C, S>& y) 
{  return !(x < y);  }

template <class V, bool C, class S>
inline void swap(list<V, C, S>& x, list<V, C, S>& y)
{  x.swap(y);  }

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_HPP
