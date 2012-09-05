//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
// Stable vector.
//
// Copyright 2008 Joaquin M Lopez Munoz.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_STABLE_VECTOR_HPP

#if (defined _MSC_VER) && (_MSC_VER >= 1200)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/container/detail/version_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/utilities.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/algorithms.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/aligned_storage.hpp>
#include <algorithm> //max
#include <stdexcept>
#include <memory>
#include <new> //placement new

///@cond

#include <boost/container/vector.hpp>

//#define STABLE_VECTOR_ENABLE_INVARIANT_CHECKING

#if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)
#include <boost/assert.hpp>
#endif

///@endcond

namespace boost {
namespace container {

///@cond

namespace stable_vector_detail{

template<class SmartPtr>
struct smart_ptr_type
{
   typedef typename SmartPtr::value_type value_type;
   typedef value_type *pointer;
   static pointer get (const SmartPtr &smartptr)
   {  return smartptr.get();}
};

template<class T>
struct smart_ptr_type<T*>
{
   typedef T value_type;
   typedef value_type *pointer;
   static pointer get (pointer ptr)
   {  return ptr;}
};

template <class C>
class clear_on_destroy
{
   public:
   clear_on_destroy(C &c)
      :  c_(c), do_clear_(true)
   {}

   void release()
   {  do_clear_ = false; }

   ~clear_on_destroy()
   {
      if(do_clear_){
         c_.clear();
         c_.priv_clear_pool(); 
      }
   }

   private:
   clear_on_destroy(const clear_on_destroy &);
   clear_on_destroy &operator=(const clear_on_destroy &);
   C &c_;
   bool do_clear_;
};

template<typename VoidPointer, typename T>
struct node;

template<class NodePtr>
struct node_base
{
   private:
   typedef NodePtr                              node_ptr;
   typedef typename boost::intrusive::
      pointer_traits<node_ptr>                  node_ptr_traits;
   typedef typename node_ptr_traits::
      template rebind_pointer
         <node_base>::type                      node_base_ptr;
   typedef typename node_ptr_traits::
      template rebind_pointer
         <node_ptr>::type                       node_ptr_ptr;

   public:
   node_base(const node_ptr_ptr &n)
      : up(n)
   {}

   node_base()
      : up()
   {}

   node_ptr_ptr up;
};

template<typename VoidPointer, typename T>
struct node
   : public node_base
   <typename boost::intrusive::
         pointer_traits<VoidPointer>::template
            rebind_pointer< node<VoidPointer, T> >::type>
{
   private:
   node();

   public:
   T value;
};

template<typename T, typename Reference, typename Pointer>
class iterator
   : public std::iterator< std::random_access_iterator_tag
                         , T
                         , typename boost::intrusive::
                              pointer_traits<Pointer>::difference_type
                         , Pointer
                         , Reference>
{
   typedef boost::intrusive::
      pointer_traits<Pointer>                   ptr_traits;
   typedef typename ptr_traits::template
         rebind_pointer<void>::type             void_ptr;
   typedef node<void_ptr, T>                    node_type;
   typedef typename ptr_traits::template
         rebind_pointer<node_type>::type        node_ptr;
   typedef typename ptr_traits::template
         rebind_pointer<node_ptr>::type         node_ptr_ptr;
   typedef typename ptr_traits::template
      rebind_pointer<T>::type                   friend_iterator_pointer;

   friend class iterator<T, const T, friend_iterator_pointer>;

   public:
   typedef std::random_access_iterator_tag      iterator_category;
   typedef T                                    value_type;
   typedef typename ptr_traits::difference_type difference_type;
   typedef Pointer                              pointer;
   typedef Reference                            reference;

   iterator()
   {}

   explicit iterator(node_ptr p)
      : pn(p)
   {}

   iterator(const iterator<T, T&, friend_iterator_pointer>& x)
      : pn(x.pn)
   {}

   public:
   //Pointer like operators
   reference operator*()  const
   {  return  pn->value;  }

   pointer   operator->() const
   {  return  ptr_traits::pointer_to(*this);  }

   //Increment / Decrement
   iterator& operator++() 
   {
      if(node_ptr_ptr p = this->pn->up){
         ++p;
         this->pn = *p;
      }
      return *this;
   }

   iterator operator++(int)
   {  iterator tmp(*this);  ++*this; return iterator(tmp); }

   iterator& operator--()
   {
      if(node_ptr_ptr p = this->pn->up){
         --p;
         this->pn = *p;
      }
      return *this;
   }

   iterator operator--(int)
   {  iterator tmp(*this);  --*this; return iterator(tmp);  }

   reference operator[](difference_type off) const
   {
      iterator tmp(*this);
      tmp += off;
      return *tmp;
   }

   iterator& operator+=(difference_type off)
   {
      if(node_ptr_ptr p = this->pn->up){
         p += off;
         this->pn = *p;
      }
      return *this;
   }

   friend iterator operator+(const iterator &left, difference_type off)
   {
      iterator tmp(left);
      tmp += off;
      return tmp;
   }

   friend iterator operator+(difference_type off, const iterator& right)
   {
      iterator tmp(right);
      tmp += off;
      return tmp;
   }

   iterator& operator-=(difference_type off)
   {  *this += -off; return *this;   }

   friend iterator operator-(const iterator &left, difference_type off)
   {
      iterator tmp(left);
      tmp -= off;
      return tmp;
   }

   friend difference_type operator-(const iterator& left, const iterator& right)
   {
      return left.pn->up - right.pn->up;
   }

   //Comparison operators
   friend bool operator==   (const iterator& l, const iterator& r)
   {  return l.pn == r.pn;  }

   friend bool operator!=   (const iterator& l, const iterator& r)
   {  return l.pn != r.pn;  }

   friend bool operator<    (const iterator& l, const iterator& r)
   {  return l.pn->up < r.pn->up;  }

   friend bool operator<=   (const iterator& l, const iterator& r)
   {  return l.pn->up <= r.pn->up;  }

   friend bool operator>    (const iterator& l, const iterator& r)
   {  return l.pn->up > r.pn->up;  }

   friend bool operator>=   (const iterator& l, const iterator& r)
   {  return l.pn->up >= r.pn->up;  }

   node_ptr pn;
};

template<class A, unsigned int Version>
struct select_multiallocation_chain
{
   typedef typename A::multiallocation_chain type;
};

template<class A>
struct select_multiallocation_chain<A, 1>
{
   typedef typename boost::intrusive::pointer_traits
      <typename allocator_traits<A>::pointer>::
         template rebind_pointer<void>::type                void_ptr;
   typedef container_detail::basic_multiallocation_chain
      <void_ptr>                                            multialloc_cached_counted;
   typedef boost::container::container_detail::
      transform_multiallocation_chain
         < multialloc_cached_counted
         , typename allocator_traits<A>::value_type>        type;
};

} //namespace stable_vector_detail

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

#if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)

#define STABLE_VECTOR_CHECK_INVARIANT \
invariant_checker BOOST_JOIN(check_invariant_,__LINE__)(*this); \
BOOST_JOIN(check_invariant_,__LINE__).touch();
#else

#define STABLE_VECTOR_CHECK_INVARIANT

#endif   //#if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)

#endif   //#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

/// @endcond

//! Originally developed by Joaquin M. Lopez Munoz, stable_vector is std::vector
//! drop-in replacement implemented as a node container, offering iterator and reference
//! stability.
//!
//! More details taken the author's blog:
//! (<a href="http://bannalia.blogspot.com/2008/09/introducing-stablevector.html" >
//! Introducing stable_vector</a>)
//!
//! We present stable_vector, a fully STL-compliant stable container that provides
//! most of the features of std::vector except element contiguity.
//!
//! General properties: stable_vector satisfies all the requirements of a container,
//! a reversible container and a sequence and provides all the optional operations
//! present in std::vector. Like std::vector,  iterators are random access.
//! stable_vector does not provide element contiguity; in exchange for this absence,
//! the container is stable, i.e. references and iterators to an element of a stable_vector
//! remain valid as long as the element is not erased, and an iterator that has been
//! assigned the return value of end() always remain valid until the destruction of
//! the associated  stable_vector.
//!
//! Operation complexity: The big-O complexities of stable_vector operations match
//! exactly those of std::vector. In general, insertion/deletion is constant time at
//! the end of the sequence and linear elsewhere. Unlike std::vector, stable_vector
//! does not internally perform any value_type destruction, copy or assignment
//! operations other than those exactly corresponding to the insertion of new
//! elements or deletion of stored elements, which can sometimes compensate in terms
//! of performance for the extra burden of doing more pointer manipulation and an
//! additional allocation per element.
//!
//! Exception safety: As stable_vector does not internally copy elements around, some
//! operations provide stronger exception safety guarantees than in std::vector:
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class T, class A = std::allocator<T> >
#else
template <class T, class A>
#endif
class stable_vector
{
   ///@cond
   typedef allocator_traits<A>                        allocator_traits_type;
   typedef typename container_detail::
      move_const_ref_type<T>::type                    insert_const_ref_type;
   typedef boost::intrusive::
      pointer_traits
         <typename allocator_traits_type::pointer>    ptr_traits;
   typedef typename boost::intrusive::pointer_traits
      <typename allocator_traits_type::pointer>::
         template rebind_pointer<void>::type          void_ptr;
   typedef stable_vector_detail::node<void_ptr, T>    node_type;
   typedef typename ptr_traits::template
      rebind_pointer<node_type>::type                 node_ptr;
   typedef typename ptr_traits::template
         rebind_pointer<node_ptr>::type               node_ptr_ptr;
   typedef stable_vector_detail::
      node_base<node_ptr>                             node_base_type;
   typedef typename ptr_traits::template
         rebind_pointer<node_base_type>::type         node_base_ptr;
   typedef boost::intrusive::
      pointer_traits<node_base_ptr>                   node_base_ptr_traits;
   typedef boost::intrusive::
      pointer_traits<node_ptr>                        node_ptr_traits;
   typedef boost::intrusive::
      pointer_traits<node_ptr_ptr>                    node_ptr_ptr_traits;
   typedef ::boost::container::vector<node_ptr,
      typename allocator_traits_type::
         template portable_rebind_alloc
            <node_ptr>::type>                         impl_type;
   typedef typename impl_type::iterator               impl_iterator;

   typedef ::boost::container::container_detail::
      integral_constant<unsigned, 1>                  allocator_v1;
   typedef ::boost::container::container_detail::
      integral_constant<unsigned, 2>                  allocator_v2;
   typedef ::boost::container::container_detail::integral_constant
      <unsigned, boost::container::container_detail::
      version<A>::value>                              alloc_version;
   typedef typename allocator_traits_type::
      template portable_rebind_alloc
         <node_type>::type                            node_allocator_type;

   node_ptr allocate_one()
   {  return this->allocate_one(alloc_version());   }

   template<class AllocatorVersion>
   node_ptr allocate_one(AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {  return this->priv_node_alloc().allocate(1);   }

   template<class AllocatorVersion>
   node_ptr allocate_one(AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <!boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {  return this->priv_node_alloc().allocate_one();   }

   void deallocate_one(node_ptr p)
   {  return this->deallocate_one(p, alloc_version());   }

   template<class AllocatorVersion>
   void deallocate_one(node_ptr p, AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {  this->priv_node_alloc().deallocate(p, 1);   }

   template<class AllocatorVersion>
   void deallocate_one(node_ptr p, AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <!boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {  this->priv_node_alloc().deallocate_one(p);   }

   friend class stable_vector_detail::clear_on_destroy<stable_vector>;
   ///@endcond
   public:


   // types:

   typedef typename allocator_traits_type::reference              reference;
   typedef typename allocator_traits_type::const_reference        const_reference;
   typedef typename allocator_traits_type::pointer                pointer;
   typedef typename allocator_traits_type::const_pointer          const_pointer;
   typedef stable_vector_detail::iterator
      <T,T&, pointer>                                 iterator;
   typedef stable_vector_detail::iterator
      <T,const T&, const_pointer>                     const_iterator;
   typedef typename impl_type::size_type              size_type;
   typedef typename iterator::difference_type         difference_type;
   typedef T                                          value_type;
   typedef A                                          allocator_type;
   typedef std::reverse_iterator<iterator>            reverse_iterator;
   typedef std::reverse_iterator<const_iterator>      const_reverse_iterator;
   typedef node_allocator_type                        stored_allocator_type;

   ///@cond
   private:
   BOOST_COPYABLE_AND_MOVABLE(stable_vector)
   static const size_type ExtraPointers = 3;
   //This container stores metadata at the end of the node_ptr vector with additional 3 pointers:
   //    back() is this->impl.back() - ExtraPointers;
   //    end node index is    *(this->impl.end() -3)
   //    Node cache first is  *(this->impl.end() - 2);
   //    Node cache last is   this->impl.back();

   typedef typename stable_vector_detail::
      select_multiallocation_chain
      < node_allocator_type
      , alloc_version::value
      >::type                                         multiallocation_chain;
   ///@endcond
   public:

   //! <b>Effects</b>: Default constructs a stable_vector.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   stable_vector()
      : internal_data(), impl()
   {
      STABLE_VECTOR_CHECK_INVARIANT;
   }

   //! <b>Effects</b>: Constructs a stable_vector taking the allocator as parameter.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   explicit stable_vector(const allocator_type& al)
      : internal_data(al), impl(al)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts n default contructed values.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor or copy constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit stable_vector(size_type n)
      : internal_data(), impl()
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->resize(n);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor or copy constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   stable_vector(size_type n, const T& t, const allocator_type& al = allocator_type())
      : internal_data(al), impl(al)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), n, t);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts a copy of the range [first, last) in the stable_vector.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor or copy constructor
   //!   throws or T's constructor taking an dereferenced InIt throws.
   //!
   //! <b>Complexity</b>: Linear to the range [first, last).
   template <class InputIterator>
   stable_vector(InputIterator first,InputIterator last, const allocator_type& al = allocator_type())
      : internal_data(al), impl(al)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), first, last);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Copy constructs a stable_vector.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   stable_vector(const stable_vector& x)
      : internal_data(allocator_traits<node_allocator_type>::
         select_on_container_copy_construction(x.priv_node_alloc()))
      , impl(allocator_traits<allocator_type>::
         select_on_container_copy_construction(x.impl.get_stored_allocator()))
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), x.begin(), x.end());
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Move constructor. Moves mx's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   stable_vector(BOOST_RV_REF(stable_vector) x)
      : internal_data(boost::move(x.priv_node_alloc())), impl(boost::move(x.impl))
   {
      this->priv_swap_members(x);
   }

   //! <b>Effects</b>: Copy constructs a stable_vector using the specified allocator.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   stable_vector(const stable_vector& x, const allocator_type &a)
      : internal_data(a), impl(a)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), x.begin(), x.end());
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Move constructor using the specified allocator.
   //!                 Moves mx's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise
   stable_vector(BOOST_RV_REF(stable_vector) x, const allocator_type &a)
      : internal_data(a), impl(a)
   {
      if(this->priv_node_alloc() == x.priv_node_alloc()){
         this->priv_swap_members(x);
      }
      else{
         stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
         this->insert(this->cend(), x.begin(), x.end());
         STABLE_VECTOR_CHECK_INVARIANT;
         cod.release();
      }
   }

   //! <b>Effects</b>: Destroys the stable_vector. All stored values are destroyed
   //!   and used memory is deallocated.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements.
   ~stable_vector()
   {
      this->clear();
      priv_clear_pool(); 
   }

   //! <b>Effects</b>: Makes *this contain the same elements as x.
   //!
   //! <b>Postcondition</b>: this->size() == x.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in x.
   stable_vector& operator=(BOOST_COPY_ASSIGN_REF(stable_vector) x)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if (&x != this){
         node_allocator_type &this_alloc     = this->priv_node_alloc();
         const node_allocator_type &x_alloc  = x.priv_node_alloc();
         container_detail::bool_<allocator_traits_type::
            propagate_on_container_copy_assignment::value> flag;
         if(flag && this_alloc != x_alloc){
            this->clear();
            this->shrink_to_fit();
         }
         container_detail::assign_alloc(this->priv_node_alloc(), x.priv_node_alloc(), flag);
         container_detail::assign_alloc(this->impl.get_stored_allocator(), x.impl.get_stored_allocator(), flag);
         this->assign(x.begin(), x.end());
      }
      return *this;
   }

   //! <b>Effects</b>: Move assignment. All mx's values are transferred to *this.
   //!
   //! <b>Postcondition</b>: x.empty(). *this contains a the elements x had
   //!   before the function.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear.
   stable_vector& operator=(BOOST_RV_REF(stable_vector) x)
   {
      if (&x != this){
         node_allocator_type &this_alloc = this->priv_node_alloc();
         node_allocator_type &x_alloc    = x.priv_node_alloc();
         //If allocators are equal we can just swap pointers
         if(this_alloc == x_alloc){
            //Destroy objects but retain memory
            this->clear();
            this->impl = boost::move(x.impl);
            this->priv_swap_members(x);
            //Move allocator if needed
            container_detail::bool_<allocator_traits_type::
               propagate_on_container_move_assignment::value> flag;
            container_detail::move_alloc(this->priv_node_alloc(), x.priv_node_alloc(), flag);
         }
         //If unequal allocators, then do a one by one move
         else{
            this->assign( boost::make_move_iterator(x.begin())
                        , boost::make_move_iterator(x.end()));
         }
      }
      return *this;
   }

   //! <b>Effects</b>: Assigns the the range [first, last) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing InpIt throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   template<typename InputIterator>
   void assign(InputIterator first,InputIterator last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename container_detail::enable_if_c
         < !container_detail::is_convertible<InputIterator, size_type>::value
         >::type * = 0
      #endif
      )
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      iterator first1   = this->begin();
      iterator last1    = this->end();
      for ( ; first1 != last1 && first != last; ++first1, ++first)
         *first1 = *first;
      if (first == last){
         this->erase(first1, last1);
      }
      else{
         this->insert(last1, first, last);
      }
   }


   //! <b>Effects</b>: Assigns the n copies of val to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   void assign(size_type n,const T& t)
   {
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      this->assign(cvalue_iterator(t, n), cvalue_iterator());
   }

   //! <b>Effects</b>: Returns a copy of the internal allocator.
   //!
   //! <b>Throws</b>: If allocator's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   allocator_type get_allocator()const
   {  return this->priv_node_alloc();  }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   const stored_allocator_type &get_stored_allocator() const BOOST_CONTAINER_NOEXCEPT
   {  return this->priv_node_alloc(); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   stored_allocator_type &get_stored_allocator() BOOST_CONTAINER_NOEXCEPT
   {  return this->priv_node_alloc(); }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator  begin()
   {   return (this->impl.empty()) ? this->end(): iterator(this->impl.front()) ;   }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator  begin()const
   {   return (this->impl.empty()) ? this->cend() : const_iterator(this->impl.front()) ;   }

   //! <b>Effects</b>: Returns an iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator        end()                {return iterator(this->get_end_node());}

   //! <b>Effects</b>: Returns a const_iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator  end()const           {return const_iterator(this->get_end_node());}

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator       rbegin()      {return reverse_iterator(this->end());}

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin()const {return const_reverse_iterator(this->end());}

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator       rend()        {return reverse_iterator(this->begin());}

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend()const   {return const_reverse_iterator(this->begin());}

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator         cbegin()const {return this->begin();}

   //! <b>Effects</b>: Returns a const_iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator         cend()const   {return this->end();}

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin()const{return this->rbegin();}

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend()const  {return this->rend();}

   //! <b>Effects</b>: Returns the number of the elements contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const
   {  return this->impl.empty() ? 0 : (this->impl.size() - ExtraPointers);   }

   //! <b>Effects</b>: Returns the largest possible size of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type max_size() const
   {  return this->impl.max_size() - ExtraPointers;  }

   //! <b>Effects</b>: Number of elements for which memory has been allocated.
   //!   capacity() is always greater than or equal to size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type capacity() const
   {
      if(!this->impl.capacity()){
         return 0;
      }
      else{
         const size_type num_nodes = this->impl.size() + this->internal_data.pool_size;
         const size_type num_buck  = this->impl.capacity();
         return (num_nodes < num_buck) ? num_nodes : num_buck;
      }
   }

   //! <b>Effects</b>: Returns true if the stable_vector contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   bool empty() const
   {  return this->impl.empty() || this->impl.size() == ExtraPointers;  }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are copy constructed from x.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type n, const T& t)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->size())
         this->insert(this->cend(), n - this->size(), t);
      else if(n < this->size())
         this->erase(this->cbegin() + n, this->cend());
   }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are default constructed.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type n)
   {
      typedef default_construct_iterator<value_type, difference_type> default_iterator;
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->size())
         this->insert(this->cend(), default_iterator(n - this->size()), default_iterator());
      else if(n < this->size())
         this->erase(this->cbegin() + n, this->cend());
   }

   //! <b>Effects</b>: If n is less than or equal to capacity(), this call has no
   //!   effect. Otherwise, it is a request for allocation of additional memory.
   //!   If the request is successful, then capacity() is greater than or equal to
   //!   n; otherwise, capacity() is unchanged. In either case, size() is unchanged.
   //!
   //! <b>Throws</b>: If memory allocation allocation throws.
   void reserve(size_type n)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->max_size())
         throw std::bad_alloc();

      size_type size = this->size();  
      size_type old_capacity = this->capacity();
      if(n > old_capacity){
         this->initialize_end_node(n);
         const void * old_ptr = &impl[0];
         this->impl.reserve(n + ExtraPointers);
         bool realloced = &impl[0] != old_ptr;
         //Fix the pointers for the newly allocated buffer
         if(realloced){
            this->align_nodes(this->impl.begin(), this->impl.begin()+size+1);
         }
         //Now fill pool if data is not enough
         if((n - size) > this->internal_data.pool_size){
            this->priv_add_to_pool((n - size) - this->internal_data.pool_size);
         }
      }
   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference operator[](size_type n)
   {  return this->impl[n]->value;   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a const reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference operator[](size_type n)const
   {  return this->impl[n]->value;  }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: std::range_error if n >= size()
   //!
   //! <b>Complexity</b>: Constant.
   reference at(size_type n)
   {
      if(n>=this->size())
         throw std::out_of_range("invalid subscript at stable_vector::at");
      return operator[](n);
   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a const reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: std::range_error if n >= size()
   //!
   //! <b>Complexity</b>: Constant.
   const_reference at(size_type n)const
   {
      if(n>=this->size())
         throw std::out_of_range("invalid subscript at stable_vector::at");
      return operator[](n);
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the first
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference front()
   {  return this->impl.front()->value;   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the first
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference front()const
   {  return this->impl.front()->value;   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the last
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference back()
   {  return (*(&this->impl.back() - ExtraPointers))->value; }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the last
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference back()const
   {  return (*(&this->impl.back() - ExtraPointers))->value; }

   //! <b>Effects</b>: Inserts a copy of x at the end of the stable_vector.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(insert_const_ref_type x)
   {  return priv_push_back(x);  }

   #if defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   void push_back(T &x) { push_back(const_cast<const T &>(x)); }

   template<class U>
   void push_back(const U &u, typename container_detail::enable_if_c
                  <container_detail::is_same<T, U>::value && !::boost::has_move_emulation_enabled<U>::value >::type* =0)
   { return priv_push_back(u); }
   #endif

   //! <b>Effects</b>: Constructs a new element in the end of the stable_vector
   //!   and moves the resources of mx to this new element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(BOOST_RV_REF(T) t)
   {  this->insert(end(), boost::move(t));  }

   //! <b>Effects</b>: Removes the last element from the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   void pop_back()
   {  this->erase(this->end()-1);   }

   //! <b>Requires</b>: position must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of x before position.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws or x's copy constructor throws.
   //!
   //! <b>Complexity</b>: If position is end(), amortized constant time
   //!   Linear time otherwise.
   iterator insert(const_iterator position, insert_const_ref_type x)
   {  return this->priv_insert(position, x); }

   #if defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   iterator insert(const_iterator position, T &x) { return this->insert(position, const_cast<const T &>(x)); }

   template<class U>
   iterator insert(const_iterator position, const U &u, typename container_detail::enable_if_c
                  <container_detail::is_same<T, U>::value && !::boost::has_move_emulation_enabled<U>::value >::type* =0)
   {  return this->priv_insert(position, u); }
   #endif

   //! <b>Requires</b>: position must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a new element before position with mx's resources.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: If position is end(), amortized constant time
   //!   Linear time otherwise.
   iterator insert(const_iterator position, BOOST_RV_REF(T) x)
   {
      typedef repeat_iterator<T, difference_type>           repeat_it;
      typedef boost::move_iterator<repeat_it> repeat_move_it;
      //Just call more general insert(pos, size, value) and return iterator
      size_type pos_n = position - cbegin();
      this->insert(position
         ,repeat_move_it(repeat_it(x, 1))
         ,repeat_move_it(repeat_it()));
      return iterator(this->begin() + pos_n);
   }

   //! <b>Requires</b>: pos must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert n copies of x before position.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or position if n is 0.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   iterator insert(const_iterator position, size_type n, const T& t)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(position, cvalue_iterator(t, n), cvalue_iterator());
   }

   //! <b>Requires</b>: pos must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [first, last) range before pos.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or position if first == last.
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced InpIt throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to std::distance [first, last).
   template <class InputIterator>
   iterator insert(const_iterator position,InputIterator first, InputIterator last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename container_detail::enable_if_c
         < !container_detail::is_convertible<InputIterator, size_type>::value
            && container_detail::is_input_iterator<InputIterator>::value
         >::type * = 0
      #endif
      )
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      const size_type pos_n = position - this->cbegin();
      for(; first != last; ++first){
         this->emplace(position, *first);
      }
      return this->begin() + pos_n;
   }

   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   template <class FwdIt>
   iterator insert(const_iterator position, FwdIt first, FwdIt last
      , typename container_detail::enable_if_c
         < !container_detail::is_convertible<FwdIt, size_type>::value
            && !container_detail::is_input_iterator<FwdIt>::value
         >::type * = 0
      )
   {
      size_type       n = (size_type)std::distance(first,last);
      difference_type d = position - this->cbegin();
      if(n){
         this->insert_iter_prolog(n, d);
         const impl_iterator it(this->impl.begin() + d);
         this->priv_insert_iter_fwd(it, first, last, n);
         //Fix the pointers for the newly allocated buffer
         this->align_nodes(it + n, this->get_end_align());
      }
      return this->begin() + d;
   }
   #endif

   #if defined(BOOST_CONTAINER_PERFECT_FORWARDING) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the end of the stable_vector.
   //!
   //! <b>Throws</b>: If memory allocation throws or the in-place constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   template<class ...Args>
   void emplace_back(Args &&...args)
   {
      typedef emplace_functor<Args...>         EmplaceFunctor;
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type> EmplaceIterator;
      EmplaceFunctor &&ef = EmplaceFunctor(boost::forward<Args>(args)...);
      this->insert(this->cend(), EmplaceIterator(ef), EmplaceIterator());
   }

   //! <b>Requires</b>: position must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... before position
   //!
   //! <b>Throws</b>: If memory allocation throws or the in-place constructor throws.
   //!
   //! <b>Complexity</b>: If position is end(), amortized constant time
   //!   Linear time otherwise.
   template<class ...Args>
   iterator emplace(const_iterator position, Args && ...args)
   {
      //Just call more general insert(pos, size, value) and return iterator
      size_type pos_n = position - cbegin();
      typedef emplace_functor<Args...>         EmplaceFunctor;
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type> EmplaceIterator;
      EmplaceFunctor &&ef = EmplaceFunctor(boost::forward<Args>(args)...);
      this->insert(position, EmplaceIterator(ef), EmplaceIterator());
      return iterator(this->begin() + pos_n);
   }

   #else

   #define BOOST_PP_LOCAL_MACRO(n)                                                              \
   BOOST_PP_EXPR_IF(n, template<) BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_EXPR_IF(n, >)       \
   void emplace_back(BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_LIST, _))                        \
   {                                                                                            \
      typedef BOOST_PP_CAT(BOOST_PP_CAT(emplace_functor, n), arg)                               \
         BOOST_PP_EXPR_IF(n, <) BOOST_PP_ENUM_PARAMS(n, P) BOOST_PP_EXPR_IF(n, >)               \
            EmplaceFunctor;                                                                     \
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type>  EmplaceIterator;   \
      EmplaceFunctor ef BOOST_PP_LPAREN_IF(n)                                                   \
                        BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _)                   \
                        BOOST_PP_RPAREN_IF(n);                                                  \
      this->insert(this->cend() , EmplaceIterator(ef), EmplaceIterator());                      \
   }                                                                                            \
                                                                                                \
   BOOST_PP_EXPR_IF(n, template<) BOOST_PP_ENUM_PARAMS(n, class P) BOOST_PP_EXPR_IF(n, >)       \
   iterator emplace(const_iterator pos                                                          \
           BOOST_PP_ENUM_TRAILING(n, BOOST_CONTAINER_PP_PARAM_LIST, _))                         \
   {                                                                                            \
      typedef BOOST_PP_CAT(BOOST_PP_CAT(emplace_functor, n), arg)                               \
         BOOST_PP_EXPR_IF(n, <) BOOST_PP_ENUM_PARAMS(n, P) BOOST_PP_EXPR_IF(n, >)               \
            EmplaceFunctor;                                                                     \
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type>  EmplaceIterator;   \
      EmplaceFunctor ef BOOST_PP_LPAREN_IF(n)                                                   \
                        BOOST_PP_ENUM(n, BOOST_CONTAINER_PP_PARAM_FORWARD, _)                   \
                        BOOST_PP_RPAREN_IF(n);                                                  \
      size_type pos_n = pos - this->cbegin();                                                   \
      this->insert(pos, EmplaceIterator(ef), EmplaceIterator());                                \
      return iterator(this->begin() + pos_n);                                                   \
   }                                                                                            \
   //!
   #define BOOST_PP_LOCAL_LIMITS (0, BOOST_CONTAINER_MAX_CONSTRUCTOR_PARAMETERS)
   #include BOOST_PP_LOCAL_ITERATE()

   #endif   //#ifdef BOOST_CONTAINER_PERFECT_FORWARDING

   //! <b>Effects</b>: Erases the element at position pos.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements between pos and the
   //!   last element. Constant if pos is the last element.
   iterator erase(const_iterator position)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      difference_type d = position - this->cbegin();
      impl_iterator   it = this->impl.begin() + d;
      this->delete_node(*it);
      it = this->impl.erase(it);
      this->align_nodes(it, this->get_end_align());
      return this->begin()+d;
   }

   //! <b>Effects</b>: Erases the elements pointed by [first, last).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the distance between first and last
   //!   plus linear to the elements between pos and the last element.
   iterator erase(const_iterator first, const_iterator last)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      difference_type d1 = first - this->cbegin(), d2 = last - this->cbegin();
      if(d1 != d2){
         impl_iterator it1(this->impl.begin() + d1), it2(this->impl.begin() + d2);
         for(impl_iterator it = it1; it != it2; ++it)
            this->delete_node(*it);
         impl_iterator e = this->impl.erase(it1, it2);
         this->align_nodes(e, this->get_end_align());
      }
      return iterator(this->begin() + d1);
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(stable_vector & x)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      container_detail::bool_<allocator_traits_type::propagate_on_container_swap::value> flag;
      container_detail::swap_alloc(this->priv_node_alloc(), x.priv_node_alloc(), flag);
      //vector's allocator is swapped here
      this->impl.swap(x.impl);
      this->priv_swap_members(x);
   }

   //! <b>Effects</b>: Erases all the elements of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the stable_vector.
   void clear()
   {   this->erase(this->cbegin(),this->cend()); }

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //!   with previous allocations. The size of the stable_vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   void shrink_to_fit()
   {
      if(this->capacity()){
         //First empty allocated node pool
         this->priv_clear_pool();
         //If empty completely destroy the index, let's recover default-constructed state
         if(this->empty()){
            this->impl.clear();
            this->impl.shrink_to_fit();
            this->internal_data.end_node.up = node_ptr_ptr();
         }
         //Otherwise, try to shrink-to-fit the index and readjust pointers if necessary
         else{
            const size_type size = this->size();
            const void* old_ptr = &impl[0];
            this->impl.shrink_to_fit();
            bool realloced = &impl[0] != old_ptr;
            //Fix the pointers for the newly allocated buffer
            if(realloced){
               this->align_nodes(this->impl.begin(), this->impl.begin()+size+1);
            }
         }
      }
   }

   /// @cond

   iterator priv_insert(const_iterator position, const value_type &t)
   {
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(position, cvalue_iterator(t, 1), cvalue_iterator());
   }

   void priv_push_back(const value_type &t)
   {  this->insert(end(), t);  }

   template<class AllocatorVersion>
   void priv_clear_pool(AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {
      if(!this->impl.empty() && this->impl.back()){
         node_ptr &pool_first_ref = *(this->impl.end() - 2);
         node_ptr &pool_last_ref  = this->impl.back();

         multiallocation_chain holder;
         holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, this->internal_data.pool_size);
         while(!holder.empty()){
            node_ptr n = holder.front();
            holder.pop_front();
            this->deallocate_one(n);
         }
         pool_first_ref = pool_last_ref = 0;
         this->internal_data.pool_size = 0;
      }
   }

   template<class AllocatorVersion>
   void priv_clear_pool(AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <!boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {
      if(!this->impl.empty() && this->impl.back()){
         node_ptr &pool_first_ref = *(this->impl.end() - 2);
         node_ptr &pool_last_ref  = this->impl.back();
         multiallocation_chain holder;
         holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, internal_data.pool_size);
         this->priv_node_alloc().deallocate_individual(boost::move(holder));
         pool_first_ref = pool_last_ref = 0;
         this->internal_data.pool_size = 0;
      }
   }

   void priv_clear_pool()
   {
      this->priv_clear_pool(alloc_version());
   }

   void priv_add_to_pool(size_type n)
   {
      this->priv_add_to_pool(n, alloc_version());
   }

   template<class AllocatorVersion>
   void priv_add_to_pool(size_type n, AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {
      size_type remaining = n;
      while(remaining--){
         this->put_in_pool(this->allocate_one());
      }
   }

   template<class AllocatorVersion>
   void priv_add_to_pool(size_type n, AllocatorVersion,
      typename boost::container::container_detail::enable_if_c
         <!boost::container::container_detail::is_same<AllocatorVersion, allocator_v1>
            ::value>::type * = 0)
   {
      node_ptr &pool_first_ref = *(this->impl.end() - 2);
      node_ptr &pool_last_ref  = this->impl.back();
      multiallocation_chain holder;
      holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, internal_data.pool_size);
      //BOOST_STATIC_ASSERT((::boost::has_move_emulation_enabled<multiallocation_chain>::value == true));
      multiallocation_chain m (this->priv_node_alloc().allocate_individual(n));
      holder.splice_after(holder.before_begin(), m, m.before_begin(), m.last(), n);
      this->internal_data.pool_size += n;
      std::pair<node_ptr, node_ptr> data(holder.extract_data());
      pool_first_ref = data.first;
      pool_last_ref = data.second;
   }

   void put_in_pool(node_ptr p)
   {
      node_ptr &pool_first_ref = *(this->impl.end()-2);
      node_ptr &pool_last_ref  = this->impl.back();
      multiallocation_chain holder;
      holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, internal_data.pool_size);
      holder.push_front(p);
      ++this->internal_data.pool_size;
      std::pair<node_ptr, node_ptr> ret(holder.extract_data());
      pool_first_ref = ret.first;
      pool_last_ref = ret.second;
   }

   node_ptr priv_get_from_pool()
   {
      if(!this->impl.back()){
         return node_ptr(0);
      }
      else{
         node_ptr &pool_first_ref = *(this->impl.end() - 2);
         node_ptr &pool_last_ref  = this->impl.back();
         multiallocation_chain holder;
         holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, internal_data.pool_size);
         node_ptr ret = holder.front();
         holder.pop_front();
         --this->internal_data.pool_size;
         if(!internal_data.pool_size){
            pool_first_ref = pool_last_ref = node_ptr();
         }
         else{
            std::pair<node_ptr, node_ptr> data(holder.extract_data());
            pool_first_ref = data.first;
            pool_last_ref = data.second;
         }
         return ret;
      }
   }

   void insert_iter_prolog(size_type n, difference_type d)
   {
      initialize_end_node(n);
      const void* old_ptr = &impl[0];
      //size_type old_capacity = this->capacity();
      //size_type old_size = this->size();
      this->impl.insert(this->impl.begin()+d, n, 0);
      bool realloced = &impl[0] != old_ptr;
      //Fix the pointers for the newly allocated buffer
      if(realloced){
         align_nodes(this->impl.begin(), this->impl.begin()+d);
      }
   }

   impl_iterator get_end_align()
   {
      return this->impl.end() - (ExtraPointers - 1);
   }

   static node_ptr_ptr ptr_to_node_ptr(node_ptr &n)
   {  return node_ptr_ptr_traits::pointer_to(n);   }

   void initialize_end_node(const size_type impl_capacity = 0)
   {
      if(this->impl.empty()){
         this->impl.reserve(impl_capacity + ExtraPointers);
         this->impl.resize(ExtraPointers);
         node_ptr &end_node_ref = impl[0];
         end_node_ref = this->get_end_node();
         this->internal_data.end_node.up = stable_vector::ptr_to_node_ptr(end_node_ref);
      }
   }

   void readjust_end_node()
   {
      if(!this->impl.empty()){
         node_ptr &end_node_ref = *(this->get_end_align()-1);
         end_node_ref = this->get_end_node();
         this->internal_data.end_node.up = node_ptr_ptr_traits::pointer_to(end_node_ref);
      }
      else{
         this->internal_data.end_node.up = node_ptr_ptr();
      }
   }

   node_ptr get_end_node() const
   {
      return node_ptr_traits::static_cast_from
         (node_base_ptr_traits::pointer_to(const_cast<node_base_type&>(this->internal_data.end_node)));
   }

   template<class Iter>
   node_ptr new_node(const node_ptr_ptr &up, Iter it)
   {
      node_ptr p = this->allocate_one();
      try{
         boost::container::construct_in_place(this->priv_node_alloc(), container_detail::addressof(p->value), it);
         //This does not throw
         ::new(static_cast<node_base_type*>(container_detail::to_raw_pointer(p))) node_base_type;
         p->up = up;
      }
      catch(...){
         this->deallocate_one(p);
         throw;
      }
      return p;
   }

   void delete_node(const node_ptr &n)
   {
      allocator_traits<node_allocator_type>::
         destroy(this->priv_node_alloc(), container_detail::to_raw_pointer(n));
      static_cast<node_base_type*>(container_detail::to_raw_pointer(n))->~node_base_type();
      this->put_in_pool(n);
   }

   static void align_nodes(impl_iterator first, impl_iterator last)
   {
      while(first!=last){
         (*first)->up = stable_vector::ptr_to_node_ptr(*first);
         ++first;
      }
   }

   template <class FwdIterator>
   void priv_insert_iter_fwd_alloc(const impl_iterator it, FwdIterator first, FwdIterator last, difference_type n, allocator_v1)
   {
      size_type i=0;
      try{
         while(first!=last){
            it[i] = this->new_node(stable_vector::ptr_to_node_ptr(it[i]), first);
            ++first;
            ++i;
         }
      }
      catch(...){
         impl_iterator e = this->impl.erase(it + i, it + n);
         this->align_nodes(e, this->get_end_align());
         throw;
      }
   }

   template <class FwdIterator>
   void priv_insert_iter_fwd_alloc(const impl_iterator it, FwdIterator first, FwdIterator last, difference_type n, allocator_v2)
   {
      multiallocation_chain mem(this->priv_node_alloc().allocate_individual(n));

      size_type i = 0;
      node_ptr p = 0;
      try{
         while(first != last){
            p = mem.front();
            mem.pop_front();
            //This can throw
            boost::container::construct_in_place(this->priv_node_alloc(), container_detail::addressof(p->value), first);
            //This does not throw
            ::new(static_cast<node_base_type*>(container_detail::to_raw_pointer(p))) node_base_type;
            p->up = stable_vector::ptr_to_node_ptr(it[i]);
            ++first;
            it[i] = p;
            ++i;
         }
      }
      catch(...){
         this->priv_node_alloc().deallocate_one(p);
         this->priv_node_alloc().deallocate_many(boost::move(mem));
         impl_iterator e = this->impl.erase(it+i, it+n);
         this->align_nodes(e, this->get_end_align());
         throw;
      }
   }

   template <class FwdIterator>
   void priv_insert_iter_fwd(const impl_iterator it, FwdIterator first, FwdIterator last, difference_type n)
   {
      size_type i = 0;
      node_ptr p = 0;
      try{
         while(first != last){
            p = this->priv_get_from_pool();
            if(!p){
               this->priv_insert_iter_fwd_alloc(it+i, first, last, n-i, alloc_version());
               break;
            }
            //This can throw
            boost::container::construct_in_place(this->priv_node_alloc(), container_detail::addressof(p->value), first);
            //This does not throw
            ::new(static_cast<node_base_type*>(container_detail::to_raw_pointer(p))) node_base_type;
            p->up = stable_vector::ptr_to_node_ptr(it[i]);
            ++first;
            it[i]=p;
            ++i;
         }
      }
      catch(...){
         put_in_pool(p);
         impl_iterator e = this->impl.erase(it+i, it+n);
         this->align_nodes(e, this->get_end_align());
         throw;
      }
   }

   void priv_swap_members(stable_vector &x)
   {
      container_detail::do_swap(this->internal_data.pool_size, x.internal_data.pool_size);
      this->readjust_end_node();
      x.readjust_end_node();
   }

   #if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)
   bool priv_invariant()const
   {
      impl_type & impl_ref =  const_cast<impl_type&>(this->impl);

      if(impl_ref.empty())
         return !this->capacity() && !this->size();
      if(this->get_end_node() != *(impl_ref.end() - ExtraPointers)){
         return false;
      }
      for( impl_iterator it = impl_ref.begin()
         , it_end = const_cast<stable_vector&>(*this).get_end_align()
         ; it != it_end
         ; ++it){
         if((*it)->up != stable_vector::ptr_to_node_ptr(*it)){
            return false;
         }
      }

      size_type n = this->capacity() - this->size();
      node_ptr &pool_first_ref = *(impl_ref.end() - 2);
      node_ptr &pool_last_ref  = impl_ref.back();
      multiallocation_chain holder;
      holder.incorporate_after(holder.before_begin(), pool_first_ref, pool_last_ref, internal_data.pool_size);
      multiallocation_chain::iterator beg(holder.begin()), end(holder.end());
      size_type num_pool = 0;
      while(beg != end){
         ++num_pool;
         ++beg;
      }
      return n >= num_pool;
   }

   class invariant_checker
   {
      invariant_checker(const invariant_checker &);
      invariant_checker & operator=(const invariant_checker &);
      const stable_vector* p;

      public:
      invariant_checker(const stable_vector& v):p(&v){}
      ~invariant_checker(){BOOST_ASSERT(p->priv_invariant());}
      void touch(){}
   };
   #endif

   class ebo_holder
      : public node_allocator_type
   {
      private:
      BOOST_MOVABLE_BUT_NOT_COPYABLE(ebo_holder)

      public:
      template<class AllocatorRLValue>
      explicit ebo_holder(BOOST_FWD_REF(AllocatorRLValue) a)
         : node_allocator_type(boost::forward<AllocatorRLValue>(a))
         , pool_size(0)
         , end_node()
      {}

      ebo_holder()
         : node_allocator_type()
         , pool_size(0)
         , end_node()
      {}

      size_type pool_size;
      node_base_type end_node;
   } internal_data;

   node_allocator_type &priv_node_alloc()              { return internal_data;  }
   const node_allocator_type &priv_node_alloc() const  { return internal_data;  }

   impl_type                           impl;
   /// @endcond
};

template <typename T,typename A>
bool operator==(const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return x.size()==y.size()&&std::equal(x.begin(),x.end(),y.begin());
}

template <typename T,typename A>
bool operator< (const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template <typename T,typename A>
bool operator!=(const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return !(x==y);
}

template <typename T,typename A>
bool operator> (const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return y<x;
}

template <typename T,typename A>
bool operator>=(const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return !(x<y);
}

template <typename T,typename A>
bool operator<=(const stable_vector<T,A>& x,const stable_vector<T,A>& y)
{
   return !(x>y);
}

// specialized algorithms:

template <typename T, typename A>
void swap(stable_vector<T,A>& x,stable_vector<T,A>& y)
{
   x.swap(y);
}

/// @cond

#undef STABLE_VECTOR_CHECK_INVARIANT

/// @endcond

}}

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_STABLE_VECTOR_HPP





















