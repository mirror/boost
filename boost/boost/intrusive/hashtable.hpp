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
//boost
#include <boost/utility.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/functional/hash.hpp>
//General intrusive utilities
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/detail/hashtable_node.hpp>
#include <boost/intrusive/linking_policy.hpp>
//Implementation utilities
#include <boost/intrusive/unordered_set_hook.hpp>
#include <boost/intrusive/slist.hpp>
#include <cstddef>

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
   boost::compressed_pair
      <boost::compressed_pair<bucket_info_t, Hash>
      ,Equal> members_;

   const Equal &priv_equal() const
   {  return members_.second();  }

   Equal &priv_equal()
   {  return members_.second();  }

   const_bucket_info_ptr priv_bucket_info() const
   {  return &members_.first().first();  }

   bucket_info_ptr priv_bucket_info()
   {  return &members_.first().first();  }

   const Hash &priv_hasher() const
   {  return members_.first().second();  }

   Hash &priv_hasher()
   {  return members_.first().second();  }

   const bucket_ptr &priv_buckets() const
   {  return members_.first().first().buckets_;  }

   bucket_ptr &priv_buckets()
   {  return members_.first().first().buckets_;  }

   const size_type &priv_buckets_len() const
   {  return members_.first().first().buckets_len_;  }

   size_type &priv_buckets_len()
   {  return members_.first().first().buckets_len_;  }

   static node_ptr uncast(const_node_ptr ptr)
   {
      return node_ptr(const_cast<node*>(detail::get_pointer(ptr)));
   }

   static bucket_info_ptr uncast(const_bucket_info_ptr ptr)
   {
      return bucket_info_ptr(const_cast<bucket_info_t*>(detail::get_pointer(ptr)));
   }

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

   hashtable( bucket_ptr buckets
             , size_type buckets_len
             , const Hash & hasher = Hash()
             , const Equal &equal = Equal()) 
      :  members_(boost::compressed_pair<bucket_info_t, Hash>(hasher), equal)
   {
      
      BOOST_ASSERT(buckets_len != 0);
      priv_buckets()       = buckets;
      priv_buckets_len()   = buckets_len;
      priv_clear_buckets();
      size_traits::set_size(size_type(0));
   }

   ~hashtable() 
   {  this->clear(); }

   iterator begin()
   {
      size_type bucket_num;
      local_iterator local_it = priv_begin(bucket_num);
      return iterator( local_it, this->priv_bucket_info());
   }

   const_iterator begin() const
   {  return cbegin();  }

   const_iterator cbegin() const
   {
      size_type bucket_num;
      local_iterator local_it = priv_begin(bucket_num);
      return const_iterator( local_it, this->priv_bucket_info());
   }

   iterator end()
   {
      bucket_info_t *info = detail::get_pointer(this->priv_bucket_info());
      return iterator(invalid_local_it(*info), 0);
   }

   const_iterator end() const
   {  return cend(); }

   const_iterator cend() const
   {  
      const bucket_info_t *info = detail::get_pointer(this->priv_bucket_info());
      return const_iterator(invalid_local_it(*info), 0);
   }

   hasher hash_function() const
   {  return this->priv_hasher();  }

   key_equal key_eq() const
   {  return this->priv_equal();   }

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

   template <class Cloner, class Destroyer>
   void clone_from(const hashtable &src, Cloner cloner, Destroyer destroyer)
   {
      this->clear_and_destroy(destroyer);
      if(!ConstantTimeSize || !src.empty()){
         const size_type src_bucket_count = src.bucket_count();
         const size_type dst_bucket_count = this->bucket_count();

         //If src bucket count is bigger or equal, structural copy is possible
         if(src_bucket_count >= dst_bucket_count){
            //First clone the first ones
            const bucket_ptr src_buckets = src.priv_buckets();
            const bucket_ptr dst_buckets = this->priv_buckets();
            size_type constructed;
            try{
               for( constructed = 0
                  ; constructed < dst_bucket_count
                  ; ++constructed){
                  dst_buckets[constructed].clone_from(src_buckets[constructed], cloner, destroyer);
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
            }
            catch(...){
               while(constructed--){
                  dst_buckets[constructed].clear_and_destroy(destroyer);
               }
               throw;
            }
            size_traits::set_size(src.get_size());
         }
         else{
            //Unlike previous cloning algorithm, this can throw
            //if cloner, the hasher or comparison functor throw
            const_iterator b(src.begin()), e(src.end());
            try{
               for(; b != e; ++b){
                  this->insert_equal(*cloner(*b));
               }
            }
            catch(...){
               this->clear_and_destroy(destroyer);
               throw;
            }
         }
      }
   }

   iterator insert_equal(reference value)
   {
      size_type bucket_num, hash;
      local_iterator it = priv_find(value, this->priv_hasher(), this->priv_equal(), bucket_num, hash);
      bucket_type &b = this->priv_buckets()[bucket_num];
      if(it == invalid_local_it(*this->priv_bucket_info())){
         it = b.before_begin();
      }
      size_traits::increment();
      return iterator(b.insert_after(it, value), this->priv_bucket_info());
   }

   template<class Iterator>
   void insert_equal(Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert_equal(*b);
   }

   std::pair<iterator, bool> insert_unique(reference value)
   {
      insert_commit_data commit_data;
      std::pair<iterator, bool> ret = insert_unique_check(value, commit_data);
      if(!ret.second)
         return ret;
      return std::pair<iterator, bool> (insert_unique_commit(value, commit_data), true);
   }

   template<class Iterator>
   void insert_unique(Iterator b, Iterator e)
   {
      for (; b != e; ++b)
         this->insert_unique(*b);
   }

   std::pair<iterator, bool> insert_unique_check
      (const_reference value, insert_commit_data &commit_data)
   {  return insert_unique_check(value, this->priv_hasher(), this->priv_equal(), commit_data); }

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
      bool success = prev_pos == invalid_local_it(*this->priv_bucket_info());
      if(success){
         prev_pos = this->priv_buckets()[bucket_num].before_begin();
      }
      return std::pair<iterator, bool>
         (iterator(prev_pos, this->priv_bucket_info())
         ,success);
   }

   iterator insert_unique_commit(reference value, const insert_commit_data &commit_data)
   {
      size_type bucket_num = commit_data.hash % this->priv_buckets_len();
      bucket_type &b = this->priv_buckets()[bucket_num];
      size_traits::increment();
      return iterator( b.insert_after(b.before_begin(), value)
                     , this->priv_bucket_info());
   }

   void erase(const_iterator i)
   {  erase_and_destroy(i, detail::null_destroyer());  }

   void erase(const_iterator b, const_iterator e)
   {  erase_and_destroy(b, e, detail::null_destroyer());  }

   size_type erase(const_reference value)
   {  return this->erase(value, this->priv_hasher(), this->priv_equal());  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type erase(const KeyType& key, KeyHasher hasher, KeyValueEqual equal)
   {  return erase_and_destroy(key, hasher, equal, detail::null_destroyer()); }

   template<class Destroyer>
   void erase_and_destroy(const_iterator i, Destroyer destroyer)
   {
      local_iterator to_erase(i.local());
      bucket_ptr f(priv_buckets()), l(f + priv_buckets_len());
      bucket_type &b = this->priv_buckets()[bucket_type::get_bucket_num(to_erase, *f, *l)];
      b.erase_after_and_destroy(b.previous(to_erase), destroyer);
      size_traits::decrement();
   }

   template<class Destroyer>
   void erase_and_destroy(const_iterator b, const_iterator e, Destroyer destroyer)
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
            nxt = first_b.erase_after_and_destroy(before_first_local_it, destroyer);
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
            nxt = b.erase_after_and_destroy(b_begin, destroyer);
            size_traits::decrement();
         }
      }

      //Now erase nodes from the last bucket
      {
         bucket_type &last_b = buckets[last_bucket_num];
         local_iterator b_begin(last_b.before_begin());
         local_iterator nxt(b_begin); ++nxt;
         while(nxt != last_local_it){
            nxt = last_b.erase_after_and_destroy(b_begin, destroyer);
            size_traits::decrement();
         }
      }
   }

   template<class Destroyer>
   size_type erase_and_destroy(const_reference value, Destroyer destroyer)
   {  return erase_and_destroy(value, priv_hasher(), priv_equal(), destroyer);   }

   template<class KeyType, class KeyHasher, class KeyValueEqual, class Destroyer>
   size_type erase_and_destroy(const KeyType& key, KeyHasher hasher
                  ,KeyValueEqual equal, Destroyer destroyer)
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
         it = b.erase_after_and_destroy(prev, destroyer);
         size_traits::decrement();
      }
      return count;
   }

   void clear()
   {
      if(safemode_or_autounlink){
         priv_clear_buckets();
      }
      size_traits::set_size(size_type(0));
   }

   template<class Destroyer>
   void clear_and_destroy(Destroyer destroyer)
   {
      if(!ConstantTimeSize || !this->empty()){
         size_type num_buckets = this->bucket_count();
         bucket_ptr b = this->priv_buckets();
         for(; num_buckets--; ++b){
            b->clear_and_destroy(destroyer);
         }
         size_traits::set_size(size_type(0));
      }
   }

   size_type count(const_reference value) const
   {  return this->count(value, this->priv_hasher(), this->priv_equal());  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   size_type count(const KeyType &key, const KeyHasher &hasher, const KeyValueEqual &equal) const
   {
      size_type bucket_n1, bucket_n2, count;
      priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      return count;
   }

   iterator find(const_reference value)
   {  return find(value, this->priv_hasher(), this->priv_equal());   }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   iterator find(const KeyType &key, KeyHasher hasher, KeyValueEqual equal)
   {
      size_type bucket_n, hash;
      local_iterator local_it = priv_find(key, hasher, equal, bucket_n, hash);
      return iterator( local_it
                      , this->priv_bucket_info());
   }

   const_iterator find(const_reference value) const
   {  return find(value, this->priv_hasher(), this->priv_equal());   }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   const_iterator find
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal) const
   {
      size_type bucket_n, hash;
      local_iterator local_it = priv_find(key, hasher, equal, bucket_n, hash);
      return const_iterator( local_it
                           , uncast(this->priv_bucket_info()));
   }

   std::pair<iterator,iterator> equal_range(const_reference value)
   {  return this->equal_range(value, this->priv_hasher(), this->priv_equal());  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<iterator,iterator> equal_range
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal)
   {
      size_type bucket_n1, bucket_n2, count;
      std::pair<local_iterator, local_iterator> ret
         = priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      return std::pair<iterator, iterator>
         (  iterator( ret.first, this->priv_bucket_info() )
         ,  iterator( ret.second, this->priv_bucket_info()) );
   }

   std::pair<const_iterator, const_iterator>
      equal_range(const_reference value) const
   {  return this->equal_range(value, this->priv_hasher(), this->priv_equal());  }

   template<class KeyType, class KeyHasher, class KeyValueEqual>
   std::pair<const_iterator,const_iterator> equal_range
      (const KeyType &key, KeyHasher hasher, KeyValueEqual equal) const
   {
      size_type bucket_n1, bucket_n2, count;
      std::pair<local_iterator, local_iterator> ret
         = priv_equal_range(key, hasher, equal, bucket_n1, bucket_n2, count);
      return std::pair<const_iterator, const_iterator>
         (  const_iterator( ret.first, uncast(this->priv_bucket_info()) )
         ,  const_iterator( ret.second, uncast(this->priv_bucket_info()) )  );
   }

   size_type bucket_count() const
   {  return this->priv_buckets_len();   }

   size_type bucket_size(size_type n) const
   {  return this->priv_buckets()[n].size();   }

   size_type bucket(const key_type& k)  const
   {  return this->bucket(k, this->priv_hasher());   }

   template<class KeyType, class KeyHasher>
   size_type bucket(const KeyType& k, const KeyHasher &hasher)  const
   {  return hasher(k) % this->priv_buckets_len();   }

   bucket_ptr bucket_pointer() const
   {  return this->priv_buckets();   }

   local_iterator begin(size_type n)
   {  return this->priv_buckets()[n].begin();  }

   const_local_iterator begin(size_type n) const
   {  return this->cbegin(n);  }

   const_local_iterator cbegin(size_type n) const
   {  return const_cast<const bucket_type&>(this->priv_buckets()[n]).begin();  }

   local_iterator end(size_type n)
   {  return this->priv_buckets()[n].end();  }

   const_local_iterator end(size_type n) const
   {  return this->cend(n);  }

   const_local_iterator cend(size_type n) const
   {  return const_cast<const bucket_type&>(this->priv_buckets()[n]).end();  }

   void rehash(bucket_ptr new_buckets, size_type new_buckets_len)
   {
      bucket_ptr old_buckets     = this->priv_buckets();
      size_type  old_buckets_len = this->priv_buckets_len();

      try{
         size_type n = 0;
         bool same_buffer = old_buckets == new_buckets;
         //If we are shrinking the bucket array, just rehash the last nodes
         if(same_buffer && (old_buckets_len > new_buckets_len)){
            n = new_buckets_len;
         }

         //Iterate through nodes
         for(; n < old_buckets_len; ++n){
            bucket_type &old_bucket = old_buckets[n];
            local_iterator before_i(old_bucket.before_begin());
            local_iterator end(old_bucket.end());
            local_iterator i(old_bucket.begin());
            for(;i != end; ++i){
               size_type new_n = this->priv_hasher()(*i) % new_buckets_len;
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

         this->priv_buckets()      = new_buckets;
         this->priv_buckets_len()  = new_buckets_len;
      }
      catch(...){
         for(size_type n = 0; n < new_buckets_len; ++n){
            new_buckets[n].clear();
            old_buckets[n].clear();
         }
         size_traits::set_size(size_type(0));
         throw;
      }
   }

   iterator iterator_to(reference value)
   {
      return iterator( bucket_type::iterator_to(value)
                     , this->priv_bucket_info());
   }

   const_iterator iterator_to(const_reference value) const
   {
      return const_iterator( bucket_type::iterator_to(const_cast<reference>(value))
                     , uncast(this->priv_bucket_info()));
   }

   static local_iterator local_iterator_to(reference value)
   {  return bucket_type::iterator_to(value);  }

   static const_local_iterator local_iterator_to(const_reference value)
   {  return bucket_type::iterator_to(value);  }

   // no throw
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

   // no throw
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
      return invalid_local_it(*this->priv_bucket_info());
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
      , KeyValueEqual equal, size_type &bucket_number, size_type &hash) const
   {
      size_type b_len(this->priv_buckets_len());
      hash = hasher(key);
      bucket_number = hash % b_len;

      if(ConstantTimeSize && this->empty()){
         return invalid_local_it(*this->priv_bucket_info());
      }
      
      bucket_type &b = this->priv_buckets()[bucket_number];
      local_iterator it = b.begin();

      while(it != b.end()){
         if(equal(key, *it)){
            return it;
         }
         ++it;
      }

      return invalid_local_it(*this->priv_bucket_info());
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
      size_type hash;
      count = 0;
      //Let's see if the element is present
      std::pair<local_iterator, local_iterator> to_return
         ( priv_find(key, hasher, equal, bucket_number_first, hash)
         , invalid_local_it(*this->priv_bucket_info()));
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
      to_return.second = invalid_local_it(*this->priv_bucket_info());
      return to_return;
   }
   /// @endcond
};

} //namespace intrusive 
} //namespace boost 

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_HASHTABLE_HPP
