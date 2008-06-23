/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_ITESTVALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_ITESTVALUE_HPP

#include <iostream>
#include <boost/intrusive/set_hook.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <boost/intrusive/slist_hook.hpp>
#include <boost/intrusive/unordered_set_hook.hpp>
#include <boost/intrusive/splay_set_hook.hpp>
#include <boost/intrusive/avl_set_hook.hpp>
#include <boost/intrusive/bs_set_hook.hpp>
#include <boost/intrusive/options.hpp>
#include <boost/functional/hash.hpp>
#include "smart_ptr.hpp"

namespace boost{
namespace intrusive{

struct my_tag;

template<class VoidPointer>
struct set_base_hook_type
{  typedef set_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct set_auto_base_hook_type
{  typedef set_base_hook<link_mode<auto_unlink>, void_pointer<VoidPointer>, tag<my_tag>, optimize_size<true> > type;  };

template<class VoidPointer>
struct set_member_hook_type
{  typedef set_member_hook<void_pointer<VoidPointer>, optimize_size<true> > type;  };

template<class VoidPointer>
struct set_auto_member_hook_type
{  typedef set_member_hook<link_mode<auto_unlink>, void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct splay_set_base_hook_type
{  typedef splay_set_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct splay_set_auto_base_hook_type
{  typedef splay_set_base_hook<link_mode<auto_unlink>, void_pointer<VoidPointer>, tag<my_tag> > type;  };

template<class VoidPointer>
struct splay_set_member_hook_type
{  typedef splay_set_member_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct splay_set_auto_member_hook_type
{  typedef splay_set_member_hook<link_mode<auto_unlink>, void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct bs_set_base_hook_type
{  typedef bs_set_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct bs_set_member_hook_type
{  typedef bs_set_member_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct avl_set_base_hook_type
{  typedef avl_set_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct avl_set_auto_base_hook_type
{  typedef avl_set_base_hook<link_mode<auto_unlink>, void_pointer<VoidPointer>, tag<my_tag>, optimize_size<true> > type;  };

template<class VoidPointer>
struct avl_set_member_hook_type
{  typedef avl_set_member_hook<void_pointer<VoidPointer>, optimize_size<true> > type;  };

template<class VoidPointer>
struct avl_set_auto_member_hook_type
{  typedef avl_set_member_hook<link_mode<auto_unlink>, void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct list_base_hook_type
{  typedef list_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct list_auto_base_hook_type
{  typedef list_base_hook<link_mode<auto_unlink>, void_pointer<VoidPointer>, tag<my_tag> > type;  };

template<class VoidPointer>
struct list_member_hook_type
{  typedef list_member_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct list_auto_member_hook_type
{  typedef list_member_hook<link_mode<auto_unlink>, void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct slist_base_hook_type
{  typedef slist_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct slist_auto_base_hook_type
{  typedef slist_base_hook<link_mode<auto_unlink>, void_pointer<VoidPointer>, tag<my_tag> > type;  };

template<class VoidPointer>
struct slist_member_hook_type
{  typedef slist_member_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct slist_auto_member_hook_type
{  typedef slist_member_hook<link_mode<auto_unlink>, void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct uset_base_hook_type
{  typedef unordered_set_base_hook<void_pointer<VoidPointer> > type;  };

template<class VoidPointer>
struct uset_auto_base_hook_type
{
   typedef unordered_set_base_hook
      < link_mode<auto_unlink>
      , void_pointer<VoidPointer>
      , tag<my_tag>
      , store_hash<true>
      > type;
};

template<class VoidPointer>
struct uset_member_hook_type
{
   typedef unordered_set_member_hook
      < void_pointer<VoidPointer>
      , optimize_multikey<true>
      > type;
};

template<class VoidPointer>
struct uset_auto_member_hook_type
{
   typedef unordered_set_member_hook
      < link_mode<auto_unlink>, void_pointer<VoidPointer>
      , store_hash<true>
      , optimize_multikey<true>
      > type;
};

template<class VoidPointer, bool ConstantTimeSize>
struct testvalue
   :  set_base_hook_type<VoidPointer>::type
   ,  set_auto_base_hook_type<VoidPointer>::type
   ,  splay_set_base_hook_type<VoidPointer>::type
   ,  splay_set_auto_base_hook_type<VoidPointer>::type
   ,  bs_set_base_hook_type<VoidPointer>::type
   ,  avl_set_base_hook_type<VoidPointer>::type
   ,  avl_set_auto_base_hook_type<VoidPointer>::type
   ,  list_base_hook_type<VoidPointer>::type
   ,  list_auto_base_hook_type<VoidPointer>::type
   ,  slist_base_hook_type<VoidPointer>::type
   ,  slist_auto_base_hook_type<VoidPointer>::type
   ,  uset_base_hook_type<VoidPointer>::type
   ,  uset_auto_base_hook_type<VoidPointer>::type
{
   typedef typename set_auto_base_hook_type<VoidPointer>::type          set_auto_base_hook_t;
   typedef typename set_base_hook_type<VoidPointer>::type               set_base_hook_t;
   typedef typename set_auto_member_hook_type<VoidPointer>::type        set_auto_member_hook_t;
   typedef typename set_member_hook_type<VoidPointer>::type             set_member_hook_t;

   typedef typename splay_set_auto_base_hook_type<VoidPointer>::type    splay_set_auto_base_hook_t;
   typedef typename splay_set_base_hook_type<VoidPointer>::type         splay_set_base_hook_t;
   typedef typename splay_set_auto_member_hook_type<VoidPointer>::type  splay_set_auto_member_hook_t;
   typedef typename splay_set_member_hook_type<VoidPointer>::type       splay_set_member_hook_t;

   typedef typename bs_set_base_hook_type<VoidPointer>::type            bs_set_base_hook_t;
   typedef typename bs_set_member_hook_type<VoidPointer>::type          bs_set_member_hook_t;

   typedef typename avl_set_auto_base_hook_type<VoidPointer>::type      avl_set_auto_base_hook_t;
   typedef typename avl_set_base_hook_type<VoidPointer>::type           avl_set_base_hook_t;
   typedef typename avl_set_auto_member_hook_type<VoidPointer>::type    avl_set_auto_member_hook_t;
   typedef typename avl_set_member_hook_type<VoidPointer>::type         avl_set_member_hook_t;

   typedef typename uset_auto_base_hook_type<VoidPointer>::type         unordered_set_auto_base_hook_t;
   typedef typename uset_base_hook_type<VoidPointer>::type              unordered_set_base_hook_t;
   typedef typename uset_auto_member_hook_type<VoidPointer>::type       unordered_set_auto_member_hook_t;
   typedef typename uset_member_hook_type<VoidPointer>::type            unordered_set_member_hook_t;

   typedef typename list_auto_base_hook_type<VoidPointer>::type         list_auto_base_hook_t;
   typedef typename list_base_hook_type<VoidPointer>::type              list_base_hook_t;
   typedef typename list_auto_member_hook_type<VoidPointer>::type       list_auto_member_hook_t;
   typedef typename list_member_hook_type<VoidPointer>::type            list_member_hook_t;

   typedef typename slist_auto_base_hook_type<VoidPointer>::type        slist_auto_base_hook_t;
   typedef typename slist_base_hook_type<VoidPointer>::type             slist_base_hook_t;
   typedef typename slist_auto_member_hook_type<VoidPointer>::type      slist_auto_member_hook_t;
   typedef typename slist_member_hook_type<VoidPointer>::type           slist_member_hook_t;

   //Set members
   set_member_hook_t       set_node_;
   set_auto_member_hook_t  set_auto_node_;

   //SplaySet members
   splay_set_member_hook_t       splay_set_node_;
   splay_set_auto_member_hook_t  splay_set_auto_node_;

   //ScapegoatSet members
   bs_set_member_hook_t       sg_set_node_;

   //AvlSet members
   avl_set_member_hook_t       avl_set_node_;
   avl_set_auto_member_hook_t  avl_set_auto_node_;

   //Unordered set members
   unordered_set_member_hook_t      unordered_set_node_;
   unordered_set_auto_member_hook_t unordered_set_auto_node_;

   //List members
   list_member_hook_t         list_node_;
   list_auto_member_hook_t    list_auto_node_;

   //Slist members
   slist_member_hook_t        slist_node_;
   slist_auto_member_hook_t   slist_auto_node_;

   int value_;

   static const bool constant_time_size = ConstantTimeSize;

   testvalue()
   {}

   testvalue(int i)
      :  value_(i)
   {}

   testvalue (const testvalue& src)
      :  value_ (src.value_)
   {}

   // testvalue is used in std::vector and thus prev and next
   // have to be handled appropriately when copied:

   testvalue & operator= (const testvalue& src)
   {/*
      set_base_hook_t::operator=(src);
      set_auto_base_hook_t::operator=(src);
      this->set_node_ = src.set_node_;
      this->set_auto_node_ = src.set_auto_node_;

      splay_set_base_hook_t::operator=(src);
      splay_set_auto_base_hook_t::operator=(src);
      this->splay_set_node_ = src.splay_set_node_;
      this->splay_set_auto_node_ = src.splay_set_auto_node_;

      bs_set_base_hook_t::operator=(src);
      this->sg_set_node_ = src.sg_set_node_;

      avl_set_base_hook_t::operator=(src);
      avl_set_auto_base_hook_t::operator=(src);
      this->avl_set_node_ = src.avl_set_node_;
      this->avl_set_auto_node_ = src.avl_set_auto_node_;

      unordered_set_base_hook_t::operator=(src);
      unordered_set_auto_base_hook_t::operator=(src);
      this->unordered_set_node_ = src.unordered_set_node_;
      this->unordered_set_auto_node_ = src.unordered_set_auto_node_;

      list_base_hook_t::operator=(src);
      list_auto_base_hook_t::operator=(src);
      this->list_node_ = src.list_node_;
      this->list_auto_node_ = src.list_auto_node_;

      slist_base_hook_t::operator=(src);
      slist_auto_base_hook_t::operator=(src);
      this->slist_node_ = src.slist_node_;
      this->slist_auto_node_ = src.slist_auto_node_;
*/
      value_ = src.value_;
      return *this;
   }

   void swap_nodes(testvalue &other)
   {
      //Set 
      set_base_hook_t::swap_nodes(other);
      set_auto_base_hook_t::swap_nodes(other);
      set_node_.swap_nodes(other.set_node_);
      set_auto_node_.swap_nodes(other.set_auto_node_);

      //SplaySet 
      splay_set_base_hook_t::swap_nodes(other);
      splay_set_auto_base_hook_t::swap_nodes(other);
      splay_set_node_.swap_nodes(other.splay_set_node_);
      splay_set_auto_node_.swap_nodes(other.splay_set_auto_node_);

      //ScapeoatSet 
      bs_set_base_hook_t::swap_nodes(other);
      sg_set_node_.swap_nodes(other.sg_set_node_);

      //AvlSet 
      avl_set_base_hook_t::swap_nodes(other);
      avl_set_auto_base_hook_t::swap_nodes(other);
      avl_set_node_.swap_nodes(other.avl_set_node_);
      avl_set_auto_node_.swap_nodes(other.avl_set_auto_node_);

      //Unordered set 
      unordered_set_base_hook_t::swap_nodes(other);
      unordered_set_auto_base_hook_t::swap_nodes(other);
      unordered_set_node_.swap_nodes(other.unordered_set_node_);
      unordered_set_auto_node_.swap_nodes(other.unordered_set_auto_node_);

      //List
      list_base_hook_t::swap_nodes(other);
      list_auto_base_hook_t::swap_nodes(other);
      list_node_.swap_nodes(other.list_node_);
      list_auto_node_.swap_nodes(other.list_auto_node_);

      //Slist
      slist_base_hook_t::swap_nodes(other);
      slist_auto_base_hook_t::swap_nodes(other);
      slist_node_.swap_nodes(other.slist_node_);
      slist_auto_node_.swap_nodes(other.slist_auto_node_);
   }

   bool is_linked() const
   {
      //Set 
      return set_base_hook_t::is_linked() ||
      set_auto_base_hook_t::is_linked() ||
      set_node_.is_linked() ||
      set_auto_node_.is_linked() ||

      //SplaySet 
      splay_set_base_hook_t::is_linked() ||
      splay_set_auto_base_hook_t::is_linked() ||
      splay_set_node_.is_linked() ||
      splay_set_auto_node_.is_linked() ||

      //ScapeoatSet 
      bs_set_base_hook_t::is_linked() ||
      sg_set_node_.is_linked() ||

      //AvlSet 
      avl_set_base_hook_t::is_linked() ||
      avl_set_auto_base_hook_t::is_linked() ||
      avl_set_node_.is_linked() ||
      avl_set_auto_node_.is_linked() ||

      //Unordered set 
      unordered_set_base_hook_t::is_linked() ||
      unordered_set_auto_base_hook_t::is_linked() ||
      unordered_set_node_.is_linked() ||
      unordered_set_auto_node_.is_linked() ||

      //List
      list_base_hook_t::is_linked() ||
      list_auto_base_hook_t::is_linked() ||
      list_node_.is_linked() ||
      list_auto_node_.is_linked() ||

      //Slist
      slist_base_hook_t::is_linked() ||
      slist_auto_base_hook_t::is_linked() ||
      slist_node_.is_linked() ||
      slist_auto_node_.is_linked();
   }

   ~testvalue()
   {}

   bool operator< (const testvalue &other) const
   {  return value_ < other.value_;  }

   bool operator==(const testvalue &other) const
   {  return value_ == other.value_;  }

   friend bool operator< (int other1, const testvalue &other2)
   {  return other1 < other2.value_;  }

   friend bool operator< (const testvalue &other1, int other2)
   {  return other1.value_ < other2;  }

   friend bool operator== (int other1, const testvalue &other2)
   {  return other1 == other2.value_;  }

   friend bool operator== (const testvalue &other1, int other2)
   {  return other1.value_ == other2;  }
};

template<class VoidPointer, bool ConstantTimeSize>
std::size_t hash_value(const testvalue<VoidPointer, ConstantTimeSize> &t)
{
   boost::hash<int> hasher;
   return hasher(t.value_);
}

template<class VoidPointer, bool constant_time_size>
std::ostream& operator<<
   (std::ostream& s, const testvalue<VoidPointer, constant_time_size>& t)
{  return s << t.value_;   }

struct even_odd
{
   template<class VoidPointer, bool constant_time_size>
   bool operator()
      (const testvalue<VoidPointer, constant_time_size>& v1
      ,const testvalue<VoidPointer, constant_time_size>& v2) const
   {
      if ((v1.value_ & 1) == (v2.value_ & 1))
         return v1.value_ < v2.value_;
      else
         return v2.value_ & 1;
   }  
};

struct is_even
{
   template<class VoidPointer, bool constant_time_size>
   bool operator()
      (const testvalue<VoidPointer, constant_time_size>& v1) const
   {  return (v1.value_ & 1) == 0;  }  
};

}  //namespace boost{
}  //namespace intrusive{

#endif
