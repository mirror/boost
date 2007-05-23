/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_HASHTABLE_NODE_HPP
#define BOOST_INTRUSIVE_HASHTABLE_NODE_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#ifdef BOOST_INTRUSIVE_USE_ITERATOR_FACADE
#include <boost/iterator/iterator_facade.hpp>
#endif
#ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#endif
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {

template<int Dummy = 0>
struct prime_list_holder
{
   static const std::size_t prime_list[];
   static const std::size_t prime_list_size;
};

template<int Dummy>
const std::size_t prime_list_holder<Dummy>::prime_list[] = {
   53ul, 97ul, 193ul, 389ul, 769ul,
   1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
   49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
   1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
   50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
   1610612741ul, 3221225473ul, 4294967291ul };

template<int Dummy>
const std::size_t prime_list_holder<Dummy>::prime_list_size
   = sizeof(prime_list)/sizeof(std::size_t);

template <class SlistImpl>
struct bucket_type_impl
   :  public SlistImpl
{
   bucket_type_impl()
   {}

   bucket_type_impl(const bucket_type_impl &)
   {}

   bucket_type_impl &operator=(const bucket_type_impl&)
   {  SlistImpl::clear();   }

   static typename std::iterator_traits
      <typename SlistImpl::const_iterator>::difference_type
         get_bucket_num
      ( typename SlistImpl::const_iterator it
      , const bucket_type_impl<SlistImpl> &first_bucket
      , const bucket_type_impl<SlistImpl> &last_bucket)
   {
      typename SlistImpl::const_iterator
         first(first_bucket.cend()), last(last_bucket.cend());

      //The end node is embedded in the singly linked list:
      //iterate until we reach it.
      while(!(first.pointed_node() <= it.pointed_node() &&
              it.pointed_node() <= last.pointed_node())){
         ++it;
      }
      //Now get the bucket_type_impl from the iterator
      const bucket_type_impl &b = static_cast<const bucket_type_impl&>
         (SlistImpl::container_from_end_iterator(it));

      //Now just calculate the index b has in the bucket array
      return &b - &first_bucket;
   }

   static SlistImpl &bucket_to_slist(bucket_type_impl<SlistImpl> &b)
   {  return static_cast<SlistImpl &>(b);  }

   static const SlistImpl &bucket_to_slist(const bucket_type_impl<SlistImpl> &b)
   {  return static_cast<const SlistImpl &>(b);  }
};

template<class SlistImpl>
struct bucket_info_impl
{
   typedef typename boost::pointer_to_other
      < typename SlistImpl::pointer
      , bucket_type_impl<SlistImpl> >::type bucket_ptr;
   typedef typename SlistImpl::size_type size_type;
   bucket_ptr  buckets_;
   size_type   buckets_len_;
};

#ifdef BOOST_INTRUSIVE_USE_ITERATOR_FACADE

template<class Value, class SlistImpl>
class hashtable_iterator
  : public boost::iterator_facade
         < hashtable_iterator<Value, SlistImpl>
         , Value
         , boost::forward_traversal_tag
         , Value&
         , typename std::iterator_traits<typename SlistImpl::iterator>::difference_type
         >
{
   typedef typename SlistImpl::iterator                        local_iterator;
   typedef typename SlistImpl::const_iterator                  const_local_iterator;
   typedef typename SlistImpl::value_traits::node_ptr          node_ptr;
   typedef typename SlistImpl::value_traits::const_node_ptr    const_node_ptr;

   typedef bucket_type_impl<SlistImpl>                         bucket_type;
   typedef typename boost::pointer_to_other
      < typename SlistImpl::pointer, bucket_type>::type        bucket_ptr;
   typedef typename boost::pointer_to_other
      < typename SlistImpl::pointer, const bucket_type>::type  const_bucket_ptr;
   typedef detail::bucket_info_impl<SlistImpl>                 bucket_info_t;
   typedef typename boost::pointer_to_other
      <bucket_ptr, bucket_info_t>::type                        bucket_info_ptr;
   typedef typename boost::pointer_to_other
      <bucket_ptr, const bucket_info_t>::type                  const_bucket_info_ptr;
   typedef typename SlistImpl::size_type                       size_type;
   struct enabler {};

   public:
   hashtable_iterator ()
   {}

   explicit hashtable_iterator(local_iterator ptr, const_bucket_info_ptr bucket_info)
      :  local_it_ (ptr),   bucket_info_ (bucket_info)
   {}


   #ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
   template <class OtherValue>
   hashtable_iterator(hashtable_iterator<OtherValue, SlistImpl> const& other
                     ,typename boost::enable_if<
                              boost::is_convertible<OtherValue*,Value*>
                           , enabler
                           >::type = enabler()
                      )
      :  local_it_(other.local_it_), bucket_info_(other.bucket_info_)
   {}
   #else
   template <class OtherValue>
   hashtable_iterator(hashtable_iterator<OtherValue, SlistImpl> const& other,
                     typename enable_if<
                           is_convertible<OtherValue*,T*>
                     >::type* = 0)
      :  local_it_(other.local_it_), bucket_info_(other.bucket_info_)
   {}
   #endif

   const local_iterator &local() const
   { return local_it_; }

   const_node_ptr pointed_node() const
   { return local_it_.pointed_node(); }

   const const_bucket_info_ptr &bucket_info() const
   { return bucket_info_; }

   private:
   friend class boost::iterator_core_access;
   template <class, class> friend class hashtable_iterator;

   template <class OtherValue>
   bool equal(hashtable_iterator<OtherValue, SlistImpl> const& other) const
   {  return other.local() == local_it_;  }

   void increment()
   {
      size_type   buckets_len    = bucket_info_->buckets_len_;
      const_bucket_ptr  buckets  = bucket_info_->buckets_;
      const_local_iterator first = bucket_type::bucket_to_slist(buckets[0]).cend();
      const_local_iterator last  = bucket_type::bucket_to_slist(buckets[buckets_len]).cend();

      ++local_it_;
      if(first.pointed_node() <= local_it_.pointed_node() && 
         local_it_.pointed_node() <= last.pointed_node()){
         size_type n_bucket = (size_type)
               bucket_type::get_bucket_num(local_it_, buckets[0], buckets[buckets_len]);
         do{
            if (++n_bucket == buckets_len){
               local_it_ = bucket_info_->buckets_->end();
               break;
            }
            local_it_ = bucket_type::bucket_to_slist(bucket_info_->buckets_[n_bucket]).begin();
         }
         while (local_it_ == bucket_type::bucket_to_slist(bucket_info_->buckets_[n_bucket]).end());
      }
   }

   Value& dereference() const
   { return *local_it_; }

   local_iterator          local_it_;
   const_bucket_info_ptr   bucket_info_;
};

#else

template<class T, class SlistImpl>
class hashtable_iterator
  : public std::iterator<std::forward_iterator_tag, T>
{
   typedef typename SlistImpl::iterator                        local_iterator;
   typedef typename SlistImpl::const_iterator                  const_local_iterator;
   typedef typename SlistImpl::value_traits::node_ptr          node_ptr;
   typedef typename SlistImpl::value_traits::const_node_ptr    const_node_ptr;

   typedef bucket_type_impl<SlistImpl>                         bucket_type;
   typedef typename boost::pointer_to_other
      < typename SlistImpl::pointer, bucket_type>::type        bucket_ptr;
   typedef typename boost::pointer_to_other
      < typename SlistImpl::pointer, const bucket_type>::type  const_bucket_ptr;
   typedef detail::bucket_info_impl<SlistImpl>                 bucket_info_t;
   typedef typename boost::pointer_to_other
      <bucket_ptr, bucket_info_t>::type                        bucket_info_ptr;
   typedef typename boost::pointer_to_other
      <bucket_ptr, const bucket_info_t>::type                  const_bucket_info_ptr;
   typedef typename SlistImpl::size_type                       size_type;
   struct enabler {};

   public:
   typedef T & reference;
   typedef T * pointer;

   hashtable_iterator ()
   {}

   explicit hashtable_iterator(local_iterator ptr, const_bucket_info_ptr bucket_info)
      :  local_it_ (ptr),   bucket_info_ (bucket_info)
   {}


   #ifdef BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
   template <class OtherValue>
   hashtable_iterator(hashtable_iterator<OtherValue, SlistImpl> const& other
                     ,typename boost::enable_if<
                              boost::is_convertible<OtherValue*,T*>
                           , enabler
                           >::type = enabler()
                      )
      :  local_it_(other.local_it_), bucket_info_(other.bucket_info_)
   {}
   #else
   template <class OtherValue>
   hashtable_iterator(hashtable_iterator<OtherValue, SlistImpl> const& other,
                     typename enable_if<
                           is_convertible<OtherValue*,T*>
                     >::type* = 0)
      :  local_it_(other.local_it_), bucket_info_(other.bucket_info_)
   {}
   #endif

   const local_iterator &local() const
   { return local_it_; }

   const_node_ptr pointed_node() const
   { return local_it_.pointed_node(); }

   const const_bucket_info_ptr &bucket_info() const
   { return bucket_info_; }

   public:
   hashtable_iterator& operator++() 
   { increment();   return *this;   }
   
   hashtable_iterator operator++(int)
   {
      hashtable_iterator result (*this);
      increment();
      return result;
   }

   friend bool operator== (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return i.pointed_node() == i2.pointed_node(); }

   friend bool operator!= (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return !(i == i2); }

   T& operator*() const
   { return *local_it_; }

   pointer operator->() const
   { return &(*local_it_); }

   private:
   void increment()
   {
      size_type   buckets_len    = bucket_info_->buckets_len_;
      const_bucket_ptr  buckets  = bucket_info_->buckets_;
      const_local_iterator first = bucket_type::bucket_to_slist(buckets[0]).cend();
      const_local_iterator last  = bucket_type::bucket_to_slist(buckets[buckets_len]).cend();

      ++local_it_;
      if(first.pointed_node() <= local_it_.pointed_node() && 
         local_it_.pointed_node() <= last.pointed_node()){
         size_type n_bucket = (size_type)
               bucket_type::get_bucket_num(local_it_, buckets[0], buckets[buckets_len]);
         do{
            if (++n_bucket == buckets_len){
               local_it_ = bucket_info_->buckets_->end();
               break;
            }
            local_it_ = bucket_type::bucket_to_slist(bucket_info_->buckets_[n_bucket]).begin();
         }
         while (local_it_ == bucket_type::bucket_to_slist(bucket_info_->buckets_[n_bucket]).end());
      }
   }

   local_iterator          local_it_;
   const_bucket_info_ptr   bucket_info_;
};
#endif

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif
