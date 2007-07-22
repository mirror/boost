/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_HASHTABLE_HPP
#define BOOST_INTRUSIVE_HASHTABLE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
//std C++
#include <functional>
#include <utility>
#include <algorithm>
#include <cstddef>
//boost
#include <boost/intrusive/detail/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/functional/hash.hpp>
#ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
#include <boost/detail/no_exceptions_support.hpp>
#endif
//General intrusive utilities
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/detail/hashtable_node.hpp>
#include <boost/intrusive/linking_policy.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
//Implementation utilities
#include <boost/intrusive/unordered_set_hook.hpp>
#include <boost/intrusive/slist.hpp>

namespace boost {
namespace intrusive {

//! The class template hashtable is an intrusive hash table container, that
//! is used to construct intrusive unordered_set and unordered_multiset containers. The
//! no-throw guarantee holds only, if the Equal object and Hasher don't throw.
template< class ValueTraits
        , class Hash             //= boost::hash<typename ValueTraits::value_type>
        , class Equal            //= std::equal_to<typename ValueTraits::value_type>
        , bool  ConstantTimeSize //= true
        , class SizeType         //= std::size_t
        >
class hashtable
   :  private detail::size_holder<ConstantTimeSize, SizeType>
{
   /// @cond
   private:
   typedef slist<ValueTraits, false, SizeType> slist_impl;
   typedef hashtable<ValueTraits, Hash, Equal
                     ,ConstantTimeSize, SizeType>           this_type; 
   typedef typename ValueTraits::node_traits                node_traits;
   typedef detail::size_holder<ConstantTimeSize, SizeType>  size_traits;

   //noncopyable
   hashtable (const hashtable&);
   hashtable operator =(const hashtable&);
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
   typedef Hash                                                         hasher;
   typedef Equal                                                        key_equal;
   typedef detail::bucket_type_impl<slist_impl>                         bucket_type;
   typedef typename boost::pointer_to_other
      <pointer, bucket_type>::type                                      bucket_ptr;
   typedef typename slist_impl::iterator                                local_iterator;
   typedef typename slist_impl::const_iterator                          const_local_iterator;

   typedef detail::hashtable_iterator<value_type, slist_impl>           iterator;
   typedef detail::hashtable_iterator<value_type, slist_impl>           const_iterator;

   /// @cond
   private:
   typedef typename node_traits::node                                   node;
   typedef typename boost::pointer_to_other
      <pointer, node>::type                                             node_ptr;
   typedef typename boost::pointer_to_other
      <node_ptr, const node>::type                                      const_node_ptr;

   enum { safemode_or_autounlink  = 
            (int)ValueTraits::linking_policy == (int)auto_unlink   ||
            (int)ValueTraits::linking_policy == (int)safe_link     };

   //Constant-time size is incompatible with auto-unlink hooks!
   BOOST_STATIC_ASSERT(!(ConstantTimeSize && ((int)ValueTraits::linking_policy == (int)auto_unlink)));

   typedef detail::bucket_info_impl<slist_impl>    bucket_info_t;
   typedef typename boost::pointer_to_other
      <pointer, bucket_info_t>::type               bucket_info_ptr;
   typedef typename boost::pointer_to_other
      <pointer, const bucket_info_t>::type         const_bucket_info_ptr;

   //User scattered boost::compressed pair to get EBO all compilers
//   boost::compressed_pair
//      <boost::compressed_pair<bucket_info_t, Hash>
//      ,Equal> members_;
   struct bucket_hash_t
      :  public detail::ebo_functor_holder<Hash>
   {
      bucket_hash_t(const Hash & h)
         :  detail::ebo_functor_holder<Hash>(h)
      {}
      bucket_info_t bucket_info;
   };

   struct bucket_hash_equal_t
      :  public detail::ebo_functor_holder<Equal>
   {
      bucket_hash_equal_t(const Hash & h, const Equal &e)
         :  detail::ebo_functor_holder<Equal>(e), bucket_hash(h)
      {}
      bucket_hash_t bucket_hash;
   } bucket_hash_equal_;

   const Equal &priv_equal() const
   {  return static_cast<const Equal&>(bucket_hash_equal_.get());  }

   Equal &priv_equal()
   {  return static_cast<Equal&>(bucket_hash_equal_.get());  }

   const bucket_info_t &priv_bucket_info() const
   {  return bucket_hash_equal_.bucket_hash.bucket_info;  }

   bucket_info_t &priv_bucket_info()
   {  return bucket_hash_equal_.bucket_hash.bucket_info;  }

   const Hash &priv_hasher() const
   {  return static_cast<const Hash&>(bucket_hash_equal_.bucket_hash.get());  }

   Hash &priv_hasher()
   {  return static_cast<Hash&>(bucket_hash_equal_.bucket_hash.get());  }

   const bucket_ptr &priv_buckets() const
   {  return priv_bucket_info().buckets_;  }

   bucket_ptr &priv_buckets()
   {  return priv_bucket_info().buckets_;  }

   const size_type &priv_buckets_len() const
   {  return priv_bucket_info().buckets_len_;  }

   size_type &priv_buckets_len()
   {  return priv_bucket_info().buckets_len_;  }

   static node_ptr uncast(const_node_ptr ptr)
   {
      return node_ptr(const_cast<node*>(detail::get_pointer(ptr)));
   }

//   static bucket_info_ptr uncast(const_bucket_info_ptr ptr)
//   {
//      return bucket_info_ptr(const_cast<bucket_info_t*>(detail::get_pointer(ptr)));
//   }

   static slist_impl &bucket_to_slist(bucket_type &b)
   {  return static_cast<slist_impl &>(b);  }

   static const slist_impl &bucket_to_slist(const bucket_type &b)
   {  return static_cast<const slist_impl &>(b);  }

   struct insert_commit_data_impl
   {
      size_type hash;
   };
   /// @endcond

   public:
   typedef insert_commit_data_impl insert_commit_data;

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
   //! <b>Notes</b>: buckets array must be disposed only after
   //!   *this is disposed. 
   hashtable( bucket_ptr buckets
             , size_type buckets_len
             , const Hash & hasher = Hash()
             , const Equal &equal = Equal()) 
      :  bucket_hash_equal_(hasher, equal)
   {
      
      BOOST_INTRUSIVE_INVARIANT_ASSERT(buckets_len != 0);
      priv_buckets()       = buckets;
      priv_buckets_len()   = buckets_len;
      priv_clear_buckets();
      size_traits::set_size(size_type(0));
   }

   //! <b>Effects</b>: Detaches all elements from this. The objects in the unordered_set 
   //!   are not deleted (i.e. no destructors are called).
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the unordered_set, if 
   //!   it's a safe-mode or auto-unlink value. Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   ~hashtable() 
   {  this->clear(); }

   //! <b>Effects</b>: Returns an iterator pointing to the beginning of the unordered_set.
   //! 
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   iterator begin()
   {
      size_type bucket_num;
      local_iterator local_it = priv_begin(bucket_num);
      return iterator(local_it, const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_set.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator begin() const
   {  return cbegin();  }

   //! <b>Effects</b>: Returns a const_iterator pointing to the beginning
   //!   of the unordered_set.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!   Worst case (empty unordered_set): O(this->bucket_count())
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cbegin() const
   {
      size_type bucket_num;
      local_iterator local_it = priv_begin(bucket_num);
      return const_iterator( local_it, const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Effects</b>: Returns an iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   iterator end()
   {  return iterator(invalid_local_it(this->priv_bucket_info()), 0);   }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator end() const
   {  return cend(); }

   //! <b>Effects</b>: Returns a const_iterator pointing to the end of the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   const_iterator cend() const
   {  return const_iterator(invalid_local_it(this->priv_bucket_info()), 0);  }

   //! <b>Effects</b>: Returns the hasher object used by the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If hasher copy-constructor throws.
   hasher hash_function() const
   {  return this->priv_hasher();  }

   //! <b>Effects</b>: Returns the key_equal object used by the unordered_set.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If key_equal copy-constructor throws.
   key_equal key_eq() const
   {  return this->priv_equal();   }

   //! <b>Effects</b>: Returns true is the container is empty.
   //! 
   //! <b>Complexity</b>: if ConstantTimeSize is false, average constant time
   //!   (worst case, with empty() == true): O(this->bucket_count()).
   //!   Otherwise constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bool empty() const
   {
      if(ConstantTimeSize){
         return !size();
      }
      else{
         size_type buckets_len = this->priv_buckets_len();
         const bucket_type *b = detail::get_pointer(this->priv_buckets());
         for (size_type n = 0; n < buckets_len; ++n, ++b){
            if(!b->empty()){
               return false;
            }
         }
         return true;
      }
   }

   //! <b>Effects</b>: Returns the number of elements stored in the unordered_set.
   //! 
   //! <b>Complexity</b>: Linear to elements contained in *this if
   //!   ConstantTimeSize is false. Constant-time otherwise.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type size() const
   {
      if(ConstantTimeSize)
         return size_traits::get_size();
      else{
         size_type len = 0;
         size_type buckets_len = this->priv_buckets_len();
         const bucket_type *b = detail::get_pointer(this->priv_buckets());
         for (size_type n = 0; n < buckets_len; ++n, ++b){
            len += b->size();
         }
         return len;
      }
   }

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
   void swap(hashtable& other)
   {
      using std::swap;
      //These can throw
      swap(this->priv_equal(), other.priv_equal());
      swap(this->priv_hasher(), other.priv_hasher());
      //These can't throw
      swap(this->priv_buckets(), other.priv_buckets());
      swap(this->priv_buckets_len(), other.priv_buckets_len());
      if(ConstantTimeSize){
         size_type backup = size_traits::get_size();
         size_traits::set_size(other.get_size());
         other.set_size(backup);
      }
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
   //! <b>Throws</b>: If cloner throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(const hashtable &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      if(!ConstantTimeSize || !src.empty()){
         const size_type src_bucket_count = src.bucket_count();
         const size_type dst_bucket_count = this->bucket_count();

         //If src bucket count is bigger or equal, structural copy is possible
         if(src_bucket_count >= dst_bucket_count){
            //First clone the first ones
            const bucket_ptr src_buckets = src.priv_buckets();
            const bucket_ptr dst_buckets = this->priv_buckets();
            size_type constructed;
            #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
            BOOST_TRY{
            #endif
               for( constructed = 0
                  ; constructed < dst_bucket_count
                  ; ++constructed){
                  dst_buckets[constructed].clone_from(src_buckets[constructed], cloner, disposer);
               }
               if(src_bucket_count != dst_bucket_count){
                  //Now insert the remaining ones using the modulo trick
                  for(//"constructed" comes from the previous loop
                     ; constructed < src_bucket_count
                     ; ++constructed){
                     bucket_type &dst_b = dst_buckets[constructed % dst_bucket_count];
                     bucket_type &src_b = src_buckets[constructed];
                     for( local_iterator b(src_b.begin()), e(src_b.end())
                        ; b != e
                        ; ++b){
                        dst_b.push_front(*cloner(*b));
                     }
                  }
               }
            #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
            }
            BOOST_CATCH(...){
               while(constructed--){
                  dst_buckets[constructed].clear_and_dispose(disposer);
               }
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            #endif
            size_traits::set_size(src.get_size());
         }
         else{
            //Unlike previous cloning algorithm, this can throw
            //if cloner, the hasher or comparison functor throw
            const_iterator b(src.begin()), e(src.end());
            #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
            BOOST_TRY{
            #endif
               for(; b != e; ++b){
                  this->insert_equal(*cloner(*b));
               }
            #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
            }
            BOOST_CATCH(...){
               this->clear_and_dispose(disposer);
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            #endif
         }
      }
   }

   iterator insert_equal(reference value)
   {
      size_type bucket_num, hash;
      local_iterator it = priv_find(value, this->priv_hasher(), this->priv_equal(), bucket_num, hash);
      bucket_type &b = this->priv_buckets()[bucket_num];
      if(it == invalid_local_it(this->priv_bucket_info())){
         it = b.before_begin();
      }
      size_traits::increment();
      return iterator(b.insert_after(it, value), const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert_equal(*b);
   }

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
   std::pair<iterator, bool> insert_unique(reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = insert_unique_check(value, this->priv_hasher(), this->priv_equal(), commit_data);
      if(!ret.second)
         return ret;
      return std::pair<iterator, bool> (insert_unique_commit(value, commit_data), true);
   }

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
   void insert_unique(Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert_unique(*b);
   }

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
   std::pair<iterator, bool> insert_unique_check
      ( const KeyType &key
      , KeyHasher hasher
      , KeyValueEqual key_value_eq
      , insert_commit_data &commit_data)
   {
      size_type bucket_num;
      local_iterator prev_pos =
         priv_find(key, hasher, key_value_eq, bucket_num, commit_data.hash);
      bool success = prev_pos == invalid_local_it(this->priv_bucket_info());
      if(success){
         prev_pos = this->priv_buckets()[bucket_num].before_begin();
      }
      return std::pair<iterator, bool>
         (iterator(prev_pos, const_bucket_info_ptr(&this->priv_bucket_info()))
         ,success);
   }

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
   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data)
   {
      size_type bucket_num = commit_data.hash % this->priv_buckets_len();
      bucket_type &b = this->priv_buckets()[bucket_num];
      size_traits::increment();
      return iterator( b.insert_after(b.before_begin(), value)
                     , const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Effects</b>: Erases the element pointed to by i. 
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased element. No destructors are called.
   void erase(const_iterator i)
   {  erase_and_dispose(i, detail::null_disposer());  }

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
   {  erase_and_dispose(b, e, detail::null_disposer());  }

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
   {  return this->erase(value, this->priv_hasher(), this->priv_equal());  }

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
   {  return erase_and_dispose(key, hasher, equal, detail::null_disposer()); }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed to by i. 
   //!   Disposer::operator()(pointer) is called for the removed element.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators 
   //!    to the erased elements.
   template<class Disposer>
   void erase_and_dispose(const_iterator i, Disposer disposer)
   {
      local_iterator to_erase(i.local());
      bucket_ptr f(priv_buckets()), l(f + priv_buckets_len());
      bucket_type &b = this->priv_buckets()[bucket_type::get_bucket_num(to_erase, *f, *l)];
      b.erase_after_and_dispose(b.previous(to_erase), disposer);
      size_traits::decrement();
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the range pointed to by b end e.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Complexity</b>: Average case O(std::distance(b, e)),
   //!   worst case O(this->size()).
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators
   //!    to the erased elements.
   template<class Disposer>
   void erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {
      if(b == e)  return;

      //Get the bucket number and local iterator for both iterators
      bucket_ptr f(priv_buckets()), l(f + priv_buckets_len());
      size_type first_bucket_num = bucket_type::get_bucket_num(b.local(), *f, *l);

      local_iterator before_first_local_it
         = priv_buckets()[first_bucket_num].previous(b.local());
      size_type last_bucket_num;
      local_iterator last_local_it;

      //For the end iterator, we will assign the end iterator
      //of the last bucket
      if(e == end()){
         last_bucket_num   = this->bucket_count() - 1;
         last_local_it     = priv_buckets()[last_bucket_num].end();
      }
      else{
         last_local_it     = e.local();
         last_bucket_num  = bucket_type::get_bucket_num(last_local_it, *f, *l);
      }

      const bucket_ptr buckets = priv_buckets();
      //First erase the nodes of the first bucket
      {
         bucket_type &first_b = buckets[first_bucket_num];
         local_iterator nxt(before_first_local_it); ++nxt;
         local_iterator end = first_b.end();
         while(nxt != end){
            nxt = first_b.erase_after_and_dispose(before_first_local_it, disposer);
            size_traits::decrement();
         }
      }

      //Now fully clear the intermediate buckets
      for(size_type i = first_bucket_num+1; i < last_bucket_num; ++i){
         bucket_type &b = buckets[i];
         if(b.empty())
            continue;
         local_iterator b_begin(b.before_begin());
         local_iterator nxt(b_begin); ++nxt;
         local_iterator end = b.end();
         while(nxt != end){
            nxt = b.erase_after_and_dispose(b_begin, disposer);
            size_traits::decrement();
         }
      }

      //Now erase nodes from the last bucket
      {
         bucket_type &last_b = buckets[last_bucket_num];
         local_iterator b_begin(last_b.before_begin());
         local_iterator nxt(b_begin); ++nxt;
         while(nxt != last_local_it){
            nxt = last_b.erase_after_and_dispose(b_begin, disposer);
            size_traits::decrement();
         }
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given value.
   //!   Disposer::operator()(pointer) is called for the removed elements.
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
   template<class Disposer>
   size_type erase_and_dispose(const_reference value, Disposer disposer)
   {  return erase_and_dispose(value, priv_hasher(), priv_equal(), disposer);   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements with the given key.
   //!   according to the comparison functor "equal".
   //!   Disposer::operator()(pointer) is called for the removed elements.
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
   template<class KeyType, class KeyHasher, class KeyValueEqual, class Disposer>
   size_type erase_and_dispose(const KeyType& key, KeyHasher hasher
                  ,KeyValueEqual equal, Disposer disposer)
   {
      size_type count(0);

      if(ConstantTimeSize && this->empty()){
         return 0;
      }

      bucket_type &b = this->priv_buckets()[hasher(key) % this->priv_buckets_len()];
      local_iterator it    = b.begin();
      local_iterator prev  = b.before_begin();

      bool found = false;
      //Find equal value
      while(it != b.end()){
         if(equal(key, *it)){
            found = true;
            break;
         }
         ++prev;
         ++it;
      }
   
      if(!found)
         return 0;

      //If found erase all equal values
      for(local_iterator end = b.end(); it != end && equal(key, *it); ++count){
         it = b.erase_after_and_dispose(prev, disposer);
         size_traits::decrement();
      }
      return count;
   }

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
   {
      if(safemode_or_autounlink){
         priv_clear_buckets();
      }
      size_traits::set_size(size_type(0));
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //! 
   //! <b>Effects</b>: Erases all of the elements. 
   //! 
   //! <b>Complexity</b>: Linear to the number of elements on the container.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //! 
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!    to the erased elements. No destructors are called.
   template<class Disposer>
   void clear_and_dispose(Disposer disposer)
   {
      if(!ConstantTimeSize || !this->empty()){
         size_type num_buckets = this->bucket_count();
         bucket_ptr b = this->priv_buckets();
         for(; num_buckets--; ++b){
            b->clear_and_dispose(disposer);
         }
         size_traits::set_size(size_type(0));
      }
   }

   //! <b>Effects</b>: Returns the number of contained elements with the given value
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   size_type count(const_reference value) const
   {  return this->count(value, this->priv_hasher(), this->priv_equal());  }

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
   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type count(const KeyType &key, const KeyHasher &hasher, const KeyValueEqual &equal) const
   {
      size_type bucket_n1, bucket_n2, count;
      priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      return count;
   }

   //! <b>Effects</b>: Finds an iterator to the first element is equal to
   //!   "value" or end() if that element does not exist.
   //!
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   iterator find(const_reference value)
   {  return find(value, this->priv_hasher(), this->priv_equal());   }

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
   iterator find(const KeyType &key, KeyHasher hasher, KeyValueEqual equal)
   {
      size_type bucket_n, hash;
      local_iterator local_it = priv_find(key, hasher, equal, bucket_n, hash);
      return iterator( local_it
                      , const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Effects</b>: Finds a const_iterator to the first element whose key is 
   //!   "key" or end() if that element does not exist.
   //! 
   //! <b>Complexity</b>: Average case O(1), worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   const_iterator find(const_reference value) const
   {  return find(value, this->priv_hasher(), this->priv_equal());   }

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
   const_iterator find
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal) const
   {
      size_type bucket_n, hash;
      local_iterator local_it = priv_find(key, hasher, equal, bucket_n, hash);
      return const_iterator( local_it
                           , const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<iterator,iterator> equal_range(const_reference value)
   {  return this->equal_range(value, this->priv_hasher(), this->priv_equal());  }

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
   std::pair<iterator,iterator> equal_range
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal)
   {
      size_type bucket_n1, bucket_n2, count;
      std::pair<local_iterator, local_iterator> ret
         = priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      const_bucket_info_ptr info_ptr (&this->priv_bucket_info());
      return std::pair<iterator, iterator>
         (  iterator( ret.first, info_ptr)
         ,  iterator( ret.second, info_ptr) );
   }

   //! <b>Effects</b>: Returns a range containing all elements with values equivalent
   //!   to value. Returns std::make_pair(this->end(), this->end()) if no such 
   //!   elements exist.
   //! 
   //! <b>Complexity</b>: Average case O(this->count(value)). Worst case O(this->size()).
   //! 
   //! <b>Throws</b>: If the internal hasher or the equality functor throws.
   std::pair<const_iterator, const_iterator>
      equal_range(const_reference value) const
   {  return this->equal_range(value, this->priv_hasher(), this->priv_equal());  }

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
   std::pair<const_iterator,const_iterator> equal_range
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal) const
   {
      size_type bucket_n1, bucket_n2, count;
      std::pair<local_iterator, local_iterator> ret
         = priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      const_bucket_info_ptr info_ptr (&this->priv_bucket_info());
      return std::pair<const_iterator, const_iterator>
         ( const_iterator( ret.first, info_ptr)
         , const_iterator( ret.second, info_ptr) );
   }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid iterator belonging to the unordered_set
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the internal hash function throws.
   iterator iterator_to(reference value)
   {
      return iterator( bucket_type::iterator_to(value)
                     , const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_iterator belonging to the
   //!   unordered_set that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the internal hash function throws.
   const_iterator iterator_to(const_reference value) const
   {
      return const_iterator( bucket_type::iterator_to(const_cast<reference>(value))
                           , const_bucket_info_ptr(&this->priv_bucket_info()));
   }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid local_iterator belonging to the unordered_set
   //!   that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static local_iterator local_iterator_to(reference value)
   {  return bucket_type::iterator_to(value);  }

   //! <b>Requires</b>: value must be an lvalue and shall be in a unordered_set of
   //!   appropriate type. Otherwise the behavior is undefined.
   //! 
   //! <b>Effects</b>: Returns: a valid const_local_iterator belonging to
   //!   the unordered_set that points to the value
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   static const_local_iterator local_iterator_to(const_reference value)
   {  return bucket_type::iterator_to(value);  }

   //! <b>Effects</b>: Returns the number of buckets passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_count() const
   {  return this->priv_buckets_len();   }

   //! <b>Requires</b>: n is in the range [0, this->bucket_count()).
   //!
   //! <b>Effects</b>: Returns the number of elements in the nth bucket.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   size_type bucket_size(size_type n) const
   {  return this->priv_buckets()[n].size();   }

   //! <b>Effects</b>: Returns the index of the bucket in which elements
   //!   with keys equivalent to k would be found, if any such element existed.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: If the hash functor throws.
   //!
   //! <b>Note</b>: the return value is in the range [0, this->bucket_count()).
   size_type bucket(const key_type& k)  const
   {  return this->bucket(k, this->priv_hasher());   }

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
   size_type bucket(const KeyType& k, const KeyHasher &hasher)  const
   {  return hasher(k) % this->priv_buckets_len();   }

   //! <b>Effects</b>: Returns the bucket array pointer passed in the constructor
   //!   or the last rehash function.
   //! 
   //! <b>Complexity</b>: Constant.
   //! 
   //! <b>Throws</b>: Nothing.
   bucket_ptr bucket_pointer() const
   {  return this->priv_buckets();   }

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
   {  return this->priv_buckets()[n].begin();  }

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
   {  return this->cbegin(n);  }

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
   {  return const_cast<const bucket_type&>(this->priv_buckets()[n]).begin();  }

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
   {  return this->priv_buckets()[n].end();  }

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
   {  return this->cend(n);  }

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
   {  return const_cast<const bucket_type&>(this->priv_buckets()[n]).end();  }

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
   void rehash(bucket_ptr new_buckets, size_type new_buckets_len)
   {
      bucket_ptr old_buckets     = this->priv_buckets();
      size_type  old_buckets_len = this->priv_buckets_len();
      #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
      BOOST_TRY{
      #endif
         size_type n = 0;
         const bool same_buffer = old_buckets == new_buckets;
         //If the new bucket length is a common factor
         //of the old one we can avoid hash calculations.
         const bool fast_shrink = (old_buckets_len > new_buckets_len) && 
                                  (old_buckets_len % new_buckets_len) == 0;
         //If we are shrinking the same bucket array and it's
         //is a fast shrink, just rehash the last nodes
         if(same_buffer && fast_shrink){
            n = new_buckets_len;
         }

         //Iterate through nodes
         for(; n < old_buckets_len; ++n){
            bucket_type &old_bucket = old_buckets[n];

            if(!fast_shrink){
               local_iterator before_i(old_bucket.before_begin());
               local_iterator end(old_bucket.end());
               local_iterator i(old_bucket.begin());
               for(;i != end; ++i){
                  const size_type new_n = (this->priv_hasher()(*i) % new_buckets_len);
                  //If this is a buffer expansion don't move if it's not necessary
                  if(same_buffer && new_n == n){
                     ++before_i;
                  }
                  else{
                     bucket_type &new_b = new_buckets[new_n];
                     new_b.splice_after(new_b.before_begin(), old_bucket, before_i);
                     i = before_i;
                  }
               }
            }
            else{
               const size_type new_n = n % new_buckets_len;
               bucket_type &new_b = new_buckets[new_n];
               new_b.splice_after(new_b.before_begin(), old_bucket);
            }
         }

         this->priv_buckets()      = new_buckets;
         this->priv_buckets_len()  = new_buckets_len;
      #ifndef BOOST_INTRUSIVE_DISABLE_EXCEPTION_HANDLING
      }
      BOOST_CATCH(...){
         for(size_type n = 0; n < new_buckets_len; ++n){
            new_buckets[n].clear();
            old_buckets[n].clear();
         }
         size_traits::set_size(size_type(0));
         BOOST_RETHROW;
      }
      BOOST_CATCH_END
      #endif
   }

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
   {
      const std::size_t *primes     = &detail::prime_list_holder<0>::prime_list[0];
      const std::size_t *primes_end = primes + detail::prime_list_holder<0>::prime_list_size;
      size_type const* bound =
            std::lower_bound(primes, primes_end, n);
      if(bound == primes_end)
            bound--;
      return size_type(*bound);
   }

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
   {
      const std::size_t *primes     = &detail::prime_list_holder<0>::prime_list[0];
      const std::size_t *primes_end = primes + detail::prime_list_holder<0>::prime_list_size;
      size_type const* bound =
            std::upper_bound(primes, primes_end, n);
      if(bound != primes_end)
            bound--;
      return size_type(*bound);
   }

   /// @cond
   private:
   static local_iterator invalid_local_it(const bucket_info_t &b)
   {  return b.buckets_->end();  }

   local_iterator priv_begin(size_type &bucket_num) const
   {
      size_type buckets_len = this->priv_buckets_len();
      for (bucket_num = 0; bucket_num < buckets_len; ++bucket_num){
         bucket_type &b = this->priv_buckets()[bucket_num];
         if(!b.empty())
            return b.begin();
      }
      return invalid_local_it(this->priv_bucket_info());
   }

   void priv_clear_buckets()
   {  priv_clear_buckets(this->priv_buckets(), this->priv_buckets_len());  }

   static void priv_clear_buckets(bucket_ptr buckets_ptr, size_type buckets_len)
   {
      for(; buckets_len--; ++buckets_ptr){
         buckets_ptr->clear();
      }
   }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   local_iterator priv_find
      ( const KeyType &key,  KeyHasher hasher
      , KeyValueEqual equal, size_type &bucket_number, size_type &h) const
   {
      size_type b_len(this->priv_buckets_len());
      h = hasher(key);
      bucket_number = h % b_len;

      if(ConstantTimeSize && this->empty()){
         return invalid_local_it(this->priv_bucket_info());
      }
      
      bucket_type &b = this->priv_buckets()[bucket_number];
      local_iterator it = b.begin();

      while(it != b.end()){
         if(equal(key, *it)){
            return it;
         }
         ++it;
      }

      return invalid_local_it(this->priv_bucket_info());
   }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<local_iterator, local_iterator> priv_equal_range
      ( const KeyType &key
      , KeyHasher hasher
      , KeyValueEqual equal
      , size_type &bucket_number_first
      , size_type &bucket_number_second
      , size_type &count) const
   {
      size_type h;
      count = 0;
      //Let's see if the element is present
      std::pair<local_iterator, local_iterator> to_return
         ( priv_find(key, hasher, equal, bucket_number_first, h)
         , invalid_local_it(this->priv_bucket_info()));
      if(to_return.first == to_return.second){
         bucket_number_second = bucket_number_first;
         return to_return;
      }
      ++count;
      //If it's present, find the first that it's not equal in
      //the same bucket
      bucket_type &b = this->priv_buckets()[bucket_number_first];
      local_iterator it = to_return.first;
      ++it;

      while(it != b.end()){
         if(!equal(key, *it)){
            to_return.second = it;
            bucket_number_second = bucket_number_first;
            return to_return;
         }
         ++it;
         ++count;
      }
   
      //If we reached the end, find the first, non-empty bucket
      for(bucket_number_second = bucket_number_first+1
         ; bucket_number_second != this->priv_buckets_len()
         ; ++bucket_number_second){
         bucket_type &b = this->priv_buckets()[bucket_number_second];
         if(!b.empty()){
            to_return.second = b.begin();
            return to_return;
         }
      }

      //Otherwise, return the end node
      to_return.second = invalid_local_it(this->priv_bucket_info());
      return to_return;
   }
   /// @endcond
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_HASHTABLE_HPP
