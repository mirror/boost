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
#ifndef BOOST_INTRUSIVE_HASHSET_HPP
#define BOOST_INTRUSIVE_HASHSET_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/hashtable.hpp>
#include <iterator>

namespace boost {
namespace intrusive {

//! The class template unordered_set is an intrusive container, that mimics most of 
//! the interface of std::tr1::unordered_set as described in the C++ TR1.
//!
//! unordered_set is a pseudo-intrusive container: each object to be stored in the
//! container must contain a proper hook, but the container also needs
//! additional auxiliary memory to work: unordered_set needs a pointer to an array
//! of type `bucket_type` to be passed in the constructor. This bucket array must
//! have at least the same lifetime as the container. This makes the use of
//! unordered_set more complicated than purely intrusive containers.
//! `bucket_type` is default-constructible, copyable and assignable
//!
//! The template parameter ValueTraits is called "value traits". It stores
//! information and operations about the type to be stored in the container.
//!
//! The template parameter Hash is a unary function object that take an argument
//!   of type ValueTraits::value_type and returns a value of type std::size_t.
//!
//! The template parameter Equal is a binary predicate that takes two arguments of
//!   type ValueTraits::value_type. Equal is an equivalence relation.
//!
//! If the user specifies ConstantTimeSize as "true", a member of type SizeType
//! will be embedded in the class, that will keep track of the number of stored objects.
//! This will allow constant-time O(1) size() member, instead of default O(N) size.
//!
//! unordered_set only provides forward iterators but it provides 4 iterator types:
//! iterator and const_iterator to navigate through the whole container and
//! local_iterator and const_local_iterator to navigate through the values
//! stored in a single bucket. Local iterators are faster and smaller.
//!
//! It's not recommended to use non ConstantTimeSize unordered_sets because several
//! key functions, like "empty()", become non-constant time functions. Non
//! ConstantTimeSize unordered_sets are mainly provided to support auto-unlink hooks.
//!
//! unordered_set, unlike std::unordered_set, does not make automatic rehashings nor
//! offers functions related to a load factor. Rehashing can be explicitly requested
//! and the user must provide a new bucket array that will be used from that moment.
//!
//! Since no automatic rehashing is done, iterators are never invalidated when
//! inserting or erasing elements. Iterators are only invalidated when rehasing.
template< class ValueTraits
        , class Hash             //= boost::hash<typename ValueTraits::value_type>
        , class Equal            //= std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize //= true
        , class SizeType         //= std::size_t
        >
class unordered_set
{
   /// @cond
   private:
   typedef hashtable<ValueTraits, Hash, Equal, ConstantTimeSize, SizeType> table_type;

   //! This class is
   //! non-copyable
   unordered_set (const unordered_set&);

   //! This class is
   //! non-assignable
   unordered_set &operator =(const unordered_set&);

   typedef table_type implementation_defined;
   /// @endcond

   public:
   typedef ValueTraits                                                  value_traits;
   typedef typename ValueTraits::value_type                             value_type;
   typedef typename ValueTraits::pointer                                pointer;
   typedef typename ValueTraits::const_pointer                          const_pointer;
   typedef typename std::iterator_traits<pointer>::reference            reference;
   typedef typename std::iterator_traits<const_pointer>::reference      const_reference;
   typedef typename std::iterator_traits<pointer>::difference_type      difference_type;
   typedef SizeType                                                     size_type;
   typedef value_type                                                   key_type;
   typedef Equal                                                        key_equal;
   typedef Hash                                                         hasher;
   typedef typename implementation_defined::bucket_type                 bucket_type;
   typedef typename boost::pointer_to_other<pointer, bucket_type>::type bucket_ptr;
   typedef typename implementation_defined::iterator                    iterator;
   typedef typename implementation_defined::const_iterator              const_iterator;
   typedef typename implementation_defined::insert_commit_data          insert_commit_data;
   typedef typename implementation_defined::local_iterator              local_iterator;
   typedef typename implementation_defined::const_local_iterator        const_local_iterator;

   /// @cond
   private:
   table_type table_;
   /// @endcond

   public:

   //! <b>Requires</b>: buckets must not be being used by any other resource.
   //!
   //! <b>Effects</b>: Constructs an empty unordered_set, storing a reference
   //!   to the bucket array and copies of the hasher and equal functors.
   //!   
   //! <b>Complexity</b>: Constant. 
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor or invocation of Hash or Equal throws. 
   //!
   //! <b>Notes</b>: buckets array must be destroyed only after
   //!   *this is destroyed. 
   unordered_set( bucket_ptr buckets
           , size_type buckets_len
           , const Hash & hasher = Hash()
           , const Equal &equal = Equal()) 
      :  table_(buckets, buckets_len, hasher, equal)
   {}

   //! <b>Requires</b>: buckets must not be being used by any other resource
   //!   and Dereferencing iterator must yield an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Constructs an empty unordered_set and inserts elements from 
   //!   [b, e).
   //!   
   //! <b>Complexity</b>: If N is std::distance(b, e): Average case is O(N)
   //!   (with a good hash function and with buckets_len >= N),worst case O(N2).
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor or invocation of Hash or Equal throws. 
   //!
   //! <b>Notes</b>: buckets array must be destroyed only after
   //!   *this is destroyed. 
   template<class Iterator>
   unordered_set( bucket_ptr buckets
           , size_type buckets_len
           , Iterator b
           , Iterator e
           , const Hash & hasher = Hash()
           , const Equal &equal = Equal()) 
      :  table_(buckets, buckets_len, hasher, equal)
   {  table_.insert_unique(b, e);  }

   //! <b>Effects</b>: Detaches all elements from this. The objects in the unordered_set 
   //!   are not deleted (i.e. no destructors are called).
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the unordered_set, if 
   //!   it's a safe-mode or auto-unlink value. Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   ~unordered_set() 
   {}

   //! <b>Effects</b>: Returns an iterator pointing to the beginning of the unordered_set.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   iterator begin()
   { return table_.begin();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_set.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator begin() const
   { return table_.begin();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_set.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cbegin() const
   { return table_.cbegin();  }

   //! <b>Effects</b>: Returns an iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   iterator end()
   { return table_.end();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator end() const
   { return table_.end();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cend() const
   { return table_.cend();  }

   //! <b>Effects</b>: Returns the hasher object used by the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If hasher copy-constructor throws.
   hasher hash_function() const
   { return table_.hash_function(); }

   //! <b>Effects</b>: Returns the key_equal object used by the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If key_equal copy-constructor throws.
   key_equal key_eq() const
   { return table_.key_eq(); }

   //! <b>Effects</b>: Returns true is the container is empty.
   //! 
   //! <b>Complexity</b>: if ConstantTimeSize is false, average constant time
   //!   (worst case, with empty() == true): O(this->bucket_count()).
   //!   Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bool empty() const
   { return table_.empty(); }

   //! <b>Effects</b>: Returns the number of elements stored in the unordered_set.
   //! 
   //! <b>Complexity</b>: Linear to elements contained in *this if
   //!   ConstantTimeSize is false. Constant-time otherwise.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type size() const
   { return table_.size(); }

   //! <b>Requires</b>: the hasher and the equality function unqualified swap
   //!   call should not throw.
   //! 
   //! <b>Effects</b>: Swaps the contents of two unordered_sets.
   //!   Swaps also the contained bucket array and equality and hasher functors.
   //! 
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If the swap() call for the comparison or hash functors
   //!   found using ADL throw. Basic guarantee.
   void swap(unordered_set& other)
   { table_.swap(other.table_); }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Destroyer::operator()(pointer), clones all the 
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this.
   //!
   //!   If cloner throws, all cloned elements are unlinked and destroyed
   //!   calling Destroyer::operator()(pointer).
   //!   
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //! 
   //! <b>Throws</b>: If cloner throws. Basic guarantee.
   template <class Cloner, class Destroyer>
   void clone_from(const unordered_set &src, Cloner cloner, Destroyer destroyer)
   {  table_.clone_from(src.table_, cloner, destroyer);  }

   //! <b>Requires</b>: value must be an lvalue
   //! 
   //! <b>Effects</b>: Tries to inserts value into the unordered_set.
   //!
   //! <b>Returns</b>: If the value
   //!   is not already present inserts it and returns a pair containing the
   //!   iterator to the new value and true. If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Strong guarantee.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   std::pair<iterator, bool> insert(reference value)
   {  return table_.insert_unique(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //! 
   //! <b>Effects</b>: Checks if a value can be inserted in the unordered_set, using
   //!   a user provided key instead of the value itself.
   //!
   //! <b>Returns</b>: If there is an equivalent value
   //!   returns a pair containing an iterator to the already present value
   //!   and false. If the value can be inserted returns true in the returned
   //!   pair boolean and fills "commit_data" that is meant to be used with
   //!   the "insert_commit" function.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //!
   //! <b>Throws</b>: If hasher or key_value_equal throw. Strong guarantee.
   //! 
   //! <b>Notes</b>: This function is used to improve performance when constructing
   //!   a value_type is expensive: if there is an equivalent value
   //!   the constructed object must be discarded. Many times, the part of the
   //!   node that is used to impose the hash or the equality is much cheaper to
   //!   construct than the value_type and this function offers the possibility to
   //!   use that the part to check if the insertion will be successful.
   //!
   //!   If the check is successful, the user can construct the value_type and use
   //!   "insert_commit" to insert the object in constant-time.
   //!
   //!   "commit_data" remains valid for a subsequent "insert_commit" only if no more
   //!   objects are inserted or erased from the unordered_set.
   //!
   //!   After a successful rehashing insert_commit_data remains valid.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<iterator, bool> insert_check
      (const KeyType &key, KeyHasher hasher, KeyValueEqual key_value_equal, insert_commit_data &commit_data)
   {  return table_.insert_unique_check(key, hasher, key_value_equal, commit_data); }

   //! <b>Requires</b>: value must be an lvalue of type value_type. commit_data
   //!   must have been obtained from a previous call to "insert_check".
   //!   No objects should have been inserted or erased from the unordered_set between
   //!   the "insert_check" that filled "commit_data" and the call to "insert_commit".
   //! 
   //! <b>Effects</b>: Inserts the value in the unordered_set using the information obtained
   //!   from the "commit_data" that a previous "insert_check" filled.
   //!
   //! <b>Returns</b>: An iterator to the newly inserted object.
   //! 
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Notes</b>: This function has only sense if a "insert_check" has been
   //!   previously executed to fill "commit_data". No value should be inserted or
   //!   erased between the "insert_check" and "insert_commit" calls.
   //!
   //!   After a successful rehashing insert_commit_data remains valid.
   iterator insert_commit(reference value, const insert_commit_data &commit_data)
   {  return table_.insert_unique_commit(value, commit_data); }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue 
   //!   of type value_type.
   //! 
   //! <b>Effects</b>: Equivalent to this->insert(t) for each element in [b, e).
   //! 
   //! <b>Complexity</b>: Average case O(N), where N is std::distance(b, e).
   //!   Worst case O(N*this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  table_.insert_unique(b, e);  }

   //! <b>Effects</b>: Erases the element pointed to by i. 
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased element. No destructors are called.
   void erase(const_iterator i)
   {  table_.erase(i);  }

   //! <b>Effects</b>: Erases the range pointed to by b end e. 
   //! 
   //! <b>Complexity</b>: Average case O(std::distance(b, e)),
   //!   worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void erase(const_iterator b, const_iterator e)
   {  table_.erase(b, e);  }

   //! <b>Effects</b>: Erases all the elements with the given value.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.  Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   size_type erase(const_reference value)
   {  return table_.erase(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Erases all the elements that have the same hash and
   //!   compare equal with the given key.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or equal throw. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type erase(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.erase(key, hasher, equal);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed to by i. 
   //!   Destroyer::operator()(pointer) is called for the removed element.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators 
   //!    to the erased elements.
   template<class Destroyer>
   iterator erase_and_destroy(const_iterator i, Destroyer destroyer)
   {  return table_.erase_and_destroy(i, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Complexity</b>: Average case O(std::distance(b, e)),
   //!   worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Destroyer>
   iterator erase_and_destroy(const_iterator b, const_iterator e, Destroyer destroyer)
   {  return table_.erase_and_destroy(b, e, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given value.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Destroyer>
   size_type erase_and_destroy(const_reference value, Destroyer destroyer)
   {  return table_.erase_and_destroy(value, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "equal".
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or key_value_equal throw. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class KeyType, class KeyHasher, class KeyValueEqual, class Destroyer>
   size_type erase_and_destroy(const KeyType& key, KeyHasher hasher, KeyValueEqual equal, Destroyer destroyer)
   {  return table_.erase_and_destroy(key, hasher, equal, destroyer);  }

   //! <b>Effects</b>: Erases all of the elements. 
   //! 
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void clear()
   {  return table_.clear();  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //! 
   //! <b>Effects</b>: Erases all of the elements. 
   //! 
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Destroyer>
   void clear_and_destroy(Destroyer destroyer)
   {  return table_.clear_and_destroy(destroyer);  }

   //! <b>Effects</b>: Returns the number of contained elements with the given value
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   size_type count(const_reference value) const
   {  return table_.find(value) != end();  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns the number of contained elements with the given key
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or equal throw.
   template<class KeyType, class KeyHasher, class KeyValueEqual, class Destroyer>
   size_type count(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.find(key, hasher, equal) != end();  }

   //! <b>Effects</b>: Finds an iterator to the first element is equal to
   //!   "value" or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   iterator find(const_reference value)
   {  return table_.find(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Finds an iterator to the first element whose key is 
   //!   "key" according to the given hasher and equality functor or end() if
   //!   that element does not exist.
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or equal throw.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   iterator find(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.find(key, hasher, equal);  }

   //! <b>Effects</b>: Finds a const_iterator to the first element whose key is 
   //!   "key" or end() if that element does not exist.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   const_iterator find(const_reference value) const
   {  return table_.find(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Finds an iterator to the first element whose key is 
   //!   "key" according to the given hasher and equality functor or end() if
   //!   that element does not exist.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or equal throw.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   const_iterator find(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.find(key, equal);  }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<iterator,iterator> equal_range(const_reference value)
   {  return table_.equal_range(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns a range containing all elements with equivalent
   //!   keys. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(key, hasher, equal)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or the equal throw.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.equal_range(key, hasher, equal);  }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<const_iterator, const_iterator>
      equal_range(const_reference value) const
   {  return table_.equal_range(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns a range containing all elements with equivalent
   //!   keys. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(key, hasher, equal)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the hasher or equal throw.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.equal_range(key, equal);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid iterator i belonging to the unordered_set
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the internal hash function throws.
   iterator iterator_to(reference value)
   {  return table_.iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_iterator i belonging to the
   //!   unordered_set that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the internal hash function throws.
   const_iterator iterator_to(const_reference value) const
   {  return table_.iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid local_iterator i belonging to the unordered_set
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static local_iterator local_iterator_to(reference value)
   {  return table_type::local_iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_local_iterator i belonging to
   //!   the unordered_set that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static const_local_iterator local_iterator_to(const_reference value)
   {  return table_type::local_iterator_to(value);  }

   //! <b>Effects</b>: Returns the number of buckets passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_count() const
   {  return table_.bucket_count();   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns the number of elements in the nth bucket.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_size(size_type n) const
   {  return table_.bucket_size(n);   }

   //! <b>Effects</b>: Returns the index of the bucket in which elements
   //!   with keys equivalent to k would be found, if any such element existed.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash functor throws.
   //!
   //! <b>Note</b>: the return value is in the range [0, this->bucket_count()).
   size_type bucket(const key_type& k) const
   {  return table_.bucket(k);   }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //! <b>Effects</b>: Returns the index of the bucket in which elements
   //!   with keys equivalent to k would be found, if any such element existed.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If hasher throws.
   //!
   //! <b>Note</b>: the return value is in the range [0, this->bucket_count()).
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k,  KeyHasher hasher) const
   {  return table_.bucket(k, hasher);   }

   //! <b>Effects</b>: Returns the bucket array pointer passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bucket_ptr bucket_pointer() const
   {  return table_.bucket_pointer();   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   local_iterator begin(size_type n)
   {  return table_.begin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator begin(size_type n) const
   {  return table_.begin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator cbegin(size_type n) const
   {  return table_.cbegin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   local_iterator end(size_type n)
   {  return table_.end(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator end(size_type n) const
   {  return table_.end(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator cend(size_type n) const
   {  return table_.cend(n);   }

   //! <b>Requires</b>: new_buckets must be a pointer to a new bucket array
   //!   or the same as the old bucket array. new_size is the length of the
   //!   the array pointed by new_buckets. If new_buckets == this->bucket_pointer()
   //!   n can be bigger or smaller than this->bucket_count().
   //!
   //! <b>Effects</b>: Updates the internal reference with the new bucket erases
   //!   the values from the old bucket and inserts then in the new one. 
   //! 
   //! <b>Complexity</b>: Average case linear in this->size(), worst case quadratic.
   //! 
   //! <b>Throws</b>: If the hasher functor throws. Basic guarantee.
   void rehash(bucket_ptr new_buckets, size_type new_size)
   {  table_.rehash(new_buckets, new_size); }

   //! <b>Effects</b>: Returns the nearest new bucket count optimized for
   //!   the container that is bigger than n. This suggestion can be used
   //!   to create bucket arrays with a size that will usually improve
   //!   container's performance. If such value does not exist, the 
   //!   higher possible value is returned.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static size_type suggested_upper_bucket_count(size_type n)
   {  return table_type::suggested_upper_bucket_count(n);  }

   //! <b>Effects</b>: Returns the nearest new bucket count optimized for
   //!   the container that is smaller than n. This suggestion can be used
   //!   to create bucket arrays with a size that will usually improve
   //!   container's performance. If such value does not exist, the 
   //!   lower possible value is returned.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static size_type suggested_lower_bucket_count(size_type n)
   {  return table_type::suggested_lower_bucket_count(n);  }
};

//! The class template unordered_multiset is an intrusive container, that mimics most of 
//! the interface of std::tr1::unordered_multiset as described in the C++ TR1.
//!
//! unordered_multiset is a pseudo-intrusive container: each object to be stored in the
//! container must contain a proper hook, but the container also needs
//! additional auxiliary memory to work: unordered_multiset needs a pointer to an array
//! of type `bucket_type` to be passed in the constructor. This bucket array must
//! have at least the same lifetime as the container. This makes the use of
//! unordered_multiset more complicated than purely intrusive containers.
//! `bucket_type` is default-constructible, copyable and assignable
//!
//! The template parameter ValueTraits is called "value traits". It stores
//! information and operations about the type to be stored in the container.
//!
//! The template parameter Hash is a unary function object that take an argument
//!   of type ValueTraits::value_type and returns a value of type std::size_t.
//!
//! The template parameter Equal is a binary predicate that takes two arguments of
//!   type ValueTraits::value_type. Equal is an equivalence relation.
//!
//! If the user specifies ConstantTimeSize as "true", a member of type SizeType
//! will be embedded in the class, that will keep track of the number of stored objects.
//! This will allow constant-time O(1) size() member, instead of default O(N) size.
//!
//! unordered_multiset only provides forward iterators but it provides 4 iterator types:
//! iterator and const_iterator to navigate through the whole container and
//! local_iterator and const_local_iterator to navigate through the values
//! stored in a single bucket. Local iterators are faster and smaller.
//!
//! It's not recommended to use non ConstantTimeSize unordered_multisets because several
//! key functions, like "empty()", become non-constant time functions. Non
//! ConstantTimeSize unordered_multisets are mainly provided to support auto-unlink hooks.
//!
//! unordered_multiset, unlike std::unordered_set, does not make automatic rehashings nor
//! offers functions related to a load factor. Rehashing can be explicitly requested
//! and the user must provide a new bucket array that will be used from that moment.
//!
//! Since no automatic rehashing is done, iterators are never invalidated when
//! inserting or erasing elements. Iterators are only invalidated when rehasing.
template< class ValueTraits
        , class Hash             //= boost::hash<typename ValueTraits::value_type>
        , class Equal            //= std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize //= true
        , class SizeType         //= std::size_t
        >
class unordered_multiset
{
   /// @cond
   private:
   typedef hashtable<ValueTraits, Hash, Equal, ConstantTimeSize, SizeType> table_type;
   /// @endcond

   //! This class is
   //! non-copyable
   unordered_multiset (const unordered_multiset&);

   //! This class is
   //! non-assignable
   unordered_multiset &operator =(const unordered_multiset&);

   typedef table_type implementation_defined;

   public:
   typedef ValueTraits                                                  value_traits;
   typedef typename ValueTraits::value_type                             value_type;
   typedef typename ValueTraits::pointer                                pointer;
   typedef typename ValueTraits::const_pointer                          const_pointer;
   typedef typename std::iterator_traits<pointer>::reference            reference;
   typedef typename std::iterator_traits<const_pointer>::reference      const_reference;
   typedef typename std::iterator_traits<pointer>::difference_type      difference_type;
   typedef SizeType                                                     size_type;
   typedef value_type                                                   key_type;
   typedef Equal                                                        key_equal;
   typedef Hash                                                         hasher;
   typedef typename implementation_defined::bucket_type                 bucket_type;
   typedef typename boost::pointer_to_other<pointer, bucket_type>::type bucket_ptr;
   typedef typename implementation_defined::iterator                    iterator;
   typedef typename implementation_defined::const_iterator              const_iterator;
   typedef typename implementation_defined::insert_commit_data          insert_commit_data;
   typedef typename implementation_defined::local_iterator              local_iterator;
   typedef typename implementation_defined::const_local_iterator        const_local_iterator;

   /// @cond
   private:
   table_type table_;
   /// @endcond

   public:

   //! <b>Requires</b>: buckets must not be being used by any other resource.
   //!
   //! <b>Effects</b>: Constructs an empty unordered_multiset, storing a reference
   //!   to the bucket array and copies of the hasher and equal functors.
   //!   
   //! <b>Complexity</b>: Constant. 
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor or invocation of Hash or Equal throws. 
   //!
   //! <b>Notes</b>: buckets array must be destroyed only after
   //!   *this is destroyed. 
   unordered_multiset  ( bucket_ptr buckets
                  , size_type buckets_len
                  , const Hash & hasher = Hash()
                  , const Equal &equal = Equal()) 
      :  table_(buckets, buckets_len, hasher, equal)
   {}

   //! <b>Requires</b>: buckets must not be being used by any other resource
   //!   and Dereferencing iterator must yield an lvalue of type value_type.
   //! 
   //! <b>Effects</b>: Constructs an empty unordered_multiset and inserts elements from 
   //!   [b, e).
   //!   
   //! <b>Complexity</b>: If N is std::distance(b, e): Average case is O(N)
   //!   (with a good hash function and with buckets_len >= N),worst case O(N2).
   //! 
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the copy constructor or invocation of Hash or Equal throws. 
   //!
   //! <b>Notes</b>: buckets array must be destroyed only after
   //!   *this is destroyed.
   template<class Iterator>
   unordered_multiset  ( bucket_ptr buckets
                  , size_type buckets_len
                  , Iterator b
                  , Iterator e
                  , const Hash & hasher = Hash()
                  , const Equal &equal = Equal()) 
      :  table_(buckets, buckets_len, hasher, equal)
   {  table_.insert_equal(b, e);  }

   //! <b>Effects</b>: Detaches all elements from this. The objects in the unordered_multiset 
   //!   are not deleted (i.e. no destructors are called).
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the unordered_multiset, if 
   //!   it's a safe-mode or auto-unlink value. Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   ~unordered_multiset() 
   {}

   //! <b>Effects</b>: Returns an iterator pointing to the beginning of the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_multiset): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   iterator begin()
   { return table_.begin();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_multiset.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_multiset): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator begin() const
   { return table_.begin();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_multiset.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_multiset): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cbegin() const
   { return table_.cbegin();  }

   //! <b>Effects</b>: Returns an iterator pointing to the end of the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   iterator end()
   { return table_.end();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator end() const
   { return table_.end();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cend() const
   { return table_.cend();  }

   //! <b>Effects</b>: Returns the hasher object used by the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If hasher copy-constructor throws.
   hasher hash_function() const
   { return table_.hash_function(); }

   //! <b>Effects</b>: Returns the key_equal object used by the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If key_equal copy-constructor throws.
   key_equal key_eq() const
   { return table_.key_eq(); }

   //! <b>Effects</b>: Returns true is the container is empty.
   //! 
   //! <b>Complexity</b>: if ConstantTimeSize is false, average constant time
   //!   (worst case, with empty() == true): O(this->bucket_count()).
   //!   Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bool empty() const
   { return table_.empty(); }

   //! <b>Effects</b>: Returns the number of elements stored in the unordered_multiset.
   //! 
   //! <b>Complexity</b>: Linear to elements contained in *this if
   //!   ConstantTimeSize is false. Constant-time otherwise.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type size() const
   { return table_.size(); }

   //! <b>Requires</b>: the hasher and the equality function unqualified swap
   //!   call should not throw.
   //! 
   //! <b>Effects</b>: Swaps the contents of two unordered_multisets.
   //!   Swaps also the contained bucket array and equality and hasher functors.
   //!
   //! 
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If the swap() call for the comparison or hash functors
   //!   found using ADL throw. Basic guarantee.
   void swap(unordered_multiset& other)
   { table_.swap(other.table_); }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Destroyer::operator()(pointer), clones all the 
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this.
   //!
   //!   If cloner throws, all cloned elements are unlinked and destroyed
   //!   calling Destroyer::operator()(pointer).
   //!   
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //! 
   //! <b>Throws</b>: If cloner throws.
   template <class Cloner, class Destroyer>
   void clone_from(const unordered_multiset &src, Cloner cloner, Destroyer destroyer)
   {  table_.clone_from(src.table_, cloner, destroyer);  }

   //! <b>Requires</b>: value must be an lvalue
   //! 
   //! <b>Effects</b>: Inserts value into the unordered_multiset.
   //!
   //! <b>Returns</b>: An iterator to the new inserted value.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Strong guarantee.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   iterator insert(reference value)
   {  return table_.insert_equal(value);  }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue 
   //!   of type value_type.
   //! 
   //! <b>Effects</b>: Equivalent to this->insert(t) for each element in [b, e).
   //! 
   //! <b>Complexity</b>: Insert range is in general O(N * log(N)), where N is the 
   //!   size of the range. However, it is linear in N if the range is already sorted 
   //!   by value_comp().
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   //!   No copy-constructors are called.
   template<class Iterator>
   void insert(Iterator b, Iterator e)
   {  table_.insert_equal(b, e);  }

   //! <b>Effects</b>: Erases the element pointed to by i. 
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased element. No destructors are called.
   void erase(const_iterator i)
   {  table_.erase(i);  }

   //! <b>Effects</b>: Erases the range pointed to by b end e. 
   //! 
   //! <b>Complexity</b>: Average case O(std::distance(b, e)),
   //!   worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void erase(const_iterator b, const_iterator e)
   {  table_.erase(b, e);  }

   //! <b>Effects</b>: Erases all the elements with the given value.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   size_type erase(const_reference value)
   {  return table_.erase(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Erases all the elements that have the same hash and
   //!   compare equal with the given key.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the hasher or the equal functors throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type erase(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.erase(key, hasher, equal);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed to by i. 
   //!   Destroyer::operator()(pointer) is called for the removed element.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators 
   //!    to the erased elements.
   template<class Destroyer>
   void erase_and_destroy(const_iterator i, Destroyer destroyer)
   {  table_.erase_and_destroy(i, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Complexity</b>: Average case O(std::distance(b, e)),
   //!   worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Destroyer>
   void erase_and_destroy(const_iterator b, const_iterator e, Destroyer destroyer)
   {  table_.erase_and_destroy(b, e, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given value.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Destroyer>
   size_type erase_and_destroy(const_reference value, Destroyer destroyer)
   {  return table_.erase_and_destroy(value, destroyer);  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "equal".
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: The number of erased elements.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)).
   //!   Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If hasher or equal throw. Basic guarantee.
   //! 
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class KeyType, class KeyHasher, class KeyValueEqual, class Destroyer>
   size_type erase_and_destroy(const KeyType& key, KeyHasher hasher, KeyValueEqual equal, Destroyer destroyer)
   {  return table_.erase_and_destroy(key, hasher, equal, destroyer);  }

   //! <b>Effects</b>: Erases all the elements of the container.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   void clear()
   {  return table_.clear();  }

   //! <b>Requires</b>: Destroyer::operator()(pointer) shouldn't throw.
   //! 
   //! <b>Effects</b>: Erases all the elements of the container.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   Destroyer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Destroyer>
   void clear_and_destroy(Destroyer destroyer)
   {  return table_.clear_and_destroy(destroyer);  }

   //! <b>Effects</b>: Returns the number of contained elements with the given key
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   size_type count(const_reference value) const
   {  return table_.count(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns the number of contained elements with the given key
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   template<class KeyType, class KeyHasher, class KeyValueEqual, class Destroyer>
   size_type count(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.count(key, hasher, equal);  }

   //! <b>Effects</b>: Finds an iterator to the first element whose value is 
   //!   "value" or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   iterator find(const_reference value)
   {  return table_.find(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Finds an iterator to the first element whose key is 
   //!   "key" according to the given hasher and equality functor or end() if
   //!   that element does not exist.
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   iterator find(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.find(key, hasher, equal);  }

   //! <b>Effects</b>: Finds a const_iterator to the first element whose key is 
   //!   "key" or end() if that element does not exist.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   const_iterator find(const_reference value) const
   {  return table_.find(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Finds an iterator to the first element whose key is 
   //!   "key" according to the given hasher and equality functor or end() if
   //!   that element does not exist.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   const_iterator find(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.find(key, equal);  }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<iterator,iterator> equal_range(const_reference value)
   {  return table_.equal_range(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns a range containing all elements with equivalent
   //!   keys. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(key, hasher, equal)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<iterator,iterator> equal_range(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return table_.equal_range(key, hasher, equal);  }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<const_iterator, const_iterator>
      equal_range(const_reference value) const
   {  return table_.equal_range(value);  }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //!   "key_value_equal" must be a equality function that induces 
   //!   the same equality as key_equal. The difference is that
   //!   "key_value_equal" compares an arbitrary key with the contained values.
   //!
   //! <b>Effects</b>: Returns a range containing all elements with equivalent
   //!   keys. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(key, hasher, equal)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   //!
   //! <b>Note</b>: This function is used when constructing a value_type
   //!   is expensive and the value_type can be compared with a cheaper
   //!   key type. Usually this key is part of the value_type.
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<const_iterator, const_iterator>
      equal_range(const KeyType& key, KeyHasher hasher, KeyValueEqual equal) const
   {  return table_.equal_range(key, equal);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_multiset of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid iterator i belonging to the unordered_multiset
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash function throws.
   iterator iterator_to(reference value)
   {  return table_.iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_multiset of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_iterator i belonging to the
   //!   unordered_multiset that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash function throws.
   const_iterator iterator_to(const_reference value) const
   {  return table_.iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_multiset of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid local_iterator i belonging to the unordered_multiset
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static local_iterator local_iterator_to(reference value)
   {  return table_type::local_iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_multiset of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_local_iterator i belonging to
   //!   the unordered_multiset that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static const_local_iterator local_iterator_to(const_reference value)
   {  return table_type::local_iterator_to(value);  }

   //! <b>Effects</b>: Returns the number of buckets passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_count() const
   {  return table_.bucket_count();   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns the number of elements in the nth bucket.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_size(size_type n) const
   {  return table_.bucket_size(n);   }

   //! <b>Effects</b>: Returns the index of the bucket in which elements
   //!   with keys equivalent to k would be found, if any such element existed.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash functor throws.
   //!
   //! <b>Note</b>: the return value is in the range [0, this->bucket_count()).
   size_type bucket(const key_type& k) const
   {  return table_.bucket(k);   }

   //! <b>Requires</b>: "hasher" must be a hash function that induces 
   //!   the same hash values as the stored hasher. The difference is that
   //!   "hasher" hashes the given key instead of the value_type.
   //!
   //! <b>Effects</b>: Returns the index of the bucket in which elements
   //!   with keys equivalent to k would be found, if any such element existed.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash functor throws.
   //!
   //! <b>Note</b>: the return value is in the range [0, this->bucket_count()).
   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k, const KeyHasher &hasher) const
   {  return table_.bucket(k, hasher);   }

   //! <b>Effects</b>: Returns the bucket array pointer passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bucket_ptr bucket_pointer() const
   {  return table_.bucket_pointer();   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   local_iterator begin(size_type n)
   {  return table_.begin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator begin(size_type n) const
   {  return table_.begin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the beginning
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator cbegin(size_type n) const
   {  return table_.cbegin(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   local_iterator end(size_type n)
   {  return table_.end(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator end(size_type n) const
   {  return table_.end(n);   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns a const_local_iterator pointing to the end
   //!   of the sequence stored in the bucket n.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>:  [this->begin(n), this->end(n)) is a valid range
   //!   containing all of the elements in the nth bucket. 
   const_local_iterator cend(size_type n) const
   {  return table_.cend(n);   }

   //! <b>Requires</b>: new_buckets must be a pointer to a new bucket array
   //!   or the same as the old bucket array. new_size is the length of the
   //!   the array pointed by new_buckets. If new_buckets == this->bucket_pointer()
   //!   n can be bigger or smaller than this->bucket_count().
   //!
   //! <b>Effects</b>: Updates the internal reference with the new bucket erases
   //!   the values from the old bucket and inserts then in the new one. 
   //! 
   //! <b>Complexity</b>: Average case linear in this->size(), worst case quadratic.
   //! 
   //! <b>Throws</b>: If the hasher functor throws.
   void rehash(bucket_ptr new_buckets, size_type new_size)
   {  table_.rehash(new_buckets, new_size); }

   //! <b>Effects</b>: Returns the nearest new bucket count optimized for
   //!   the container that is bigger than n. This suggestion can be used
   //!   to create bucket arrays with a size that will usually improve
   //!   container's performance. If such value does not exist, the 
   //!   higher possible value is returned.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static size_type suggested_upper_bucket_count(size_type n)
   {  return table_type::suggested_upper_bucket_count(n);  }

   //! <b>Effects</b>: Returns the nearest new bucket count optimized for
   //!   the container that is smaller than n. This suggestion can be used
   //!   to create bucket arrays with a size that will usually improve
   //!   container's performance. If such value does not exist, the 
   //!   lower possible value is returned.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //! 
   //! <b>Throws</b>: Nothing.
   static size_type suggested_lower_bucket_count(size_type n)
   {  return table_type::suggested_lower_bucket_count(n);  }
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_HASHSET_HPP
