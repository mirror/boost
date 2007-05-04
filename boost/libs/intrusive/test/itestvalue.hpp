/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztañaga  2006-2007.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_ITESTVALUE
#define BOOST_INTRUSIVE_ITESTVALUE

#ifdef _MSC_VER
//#pragma warning(disable : 4584)
#endif

#include <iostream>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/intrusive/unordered_set.hpp>
#include <boost/intrusive/detail/pointer_to_other.hpp>
#include <boost/functional/hash.hpp>
#include "smart_ptr.hpp"

namespace boost{
namespace intrusive{

template<class VoidPointer, bool ConstantTimeSize>
struct testvalue
   :  set_base_hook<tag, safe_link, VoidPointer>
   ,  set_base_hook<tag, auto_unlink, VoidPointer>
   ,  unordered_set_base_hook<tag, safe_link, VoidPointer>
   ,  unordered_set_base_hook<tag, auto_unlink, VoidPointer>
   ,  list_base_hook<tag, safe_link, VoidPointer>
   ,  list_base_hook<tag, auto_unlink, VoidPointer>
   ,  slist_base_hook<tag, safe_link, VoidPointer>
   ,  slist_base_hook<tag, auto_unlink, VoidPointer>
{
   typedef set_base_hook<tag, auto_unlink, VoidPointer>   set_auto_base_hook;
   typedef set_base_hook<tag, safe_link, VoidPointer>set_base_hook;
   typedef set_member_hook<auto_unlink, VoidPointer>              set_auto_member_hook;
   typedef set_member_hook<safe_link, VoidPointer>           set_member_hook;

   typedef unordered_set_base_hook<tag, auto_unlink, VoidPointer>     unordered_set_auto_base_hook;
   typedef unordered_set_base_hook<tag, safe_link, VoidPointer>  unordered_set_base_hook;
   typedef unordered_set_member_hook<auto_unlink, VoidPointer>                unordered_set_auto_member_hook;
   typedef unordered_set_member_hook<safe_link, VoidPointer>             unordered_set_member_hook;

   typedef list_base_hook<tag, auto_unlink, VoidPointer>     list_auto_base_hook;
   typedef list_base_hook<tag, safe_link, VoidPointer>  list_base_hook;
   typedef list_member_hook<auto_unlink, VoidPointer>                list_auto_member_hook;
   typedef list_member_hook<safe_link, VoidPointer>             list_member_hook;

   typedef slist_base_hook<tag, auto_unlink, VoidPointer>    slist_auto_base_hook;
   typedef slist_base_hook<tag, safe_link, VoidPointer> slist_base_hook;
   typedef slist_member_hook<auto_unlink, VoidPointer>               slist_auto_member_hook;
   typedef slist_member_hook<safe_link, VoidPointer>            slist_member_hook;

   typedef typename boost::pointer_to_other
      <VoidPointer, testvalue>::type pointer;

   //Set members
   //pointer set_parent_, set_left_, set_right_;
   //int set_color_;
   set_member_hook set_node_;
   set_auto_member_hook set_auto_node_;
   unordered_set_member_hook unordered_set_node_;
   unordered_set_auto_member_hook unordered_set_auto_node_;

   //List members
   //pointer list_next_, list_prev_;
   list_member_hook list_node_;
   list_auto_member_hook list_auto_node_;

   //Slist members
   //pointer slist_next_;
   slist_member_hook slist_node_;
   slist_auto_member_hook slist_auto_node_;

   int value_;

   enum{  constant_time_size = ConstantTimeSize  };

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
   {
      set_base_hook::operator=(src);
      this->set_node_ = src.set_node_;
      set_auto_base_hook::operator=(src);
      this->set_auto_node_ = src.set_auto_node_;

      unordered_set_base_hook::operator=(src);
      this->unordered_set_node_ = src.unordered_set_node_;
      unordered_set_auto_base_hook::operator=(src);
      this->unordered_set_auto_node_ = src.unordered_set_auto_node_;

      list_base_hook::operator=(src);
      this->list_node_ = src.list_node_;
      list_auto_base_hook::operator=(src);
      this->list_auto_node_ = src.list_auto_node_;

      slist_base_hook::operator=(src);
      this->slist_node_ = src.slist_node_;
      slist_auto_base_hook::operator=(src);
      this->slist_auto_node_ = src.slist_auto_node_;
      value_ = src.value_;
      return *this;
   }

   void swap_nodes(testvalue &other)
   {
      //Set has no swapping

      //...

      //List
      list_base_hook::swap_nodes(other);
      list_node_.swap_nodes(other.list_node_);
      list_auto_base_hook::swap_nodes(other);
      list_auto_node_.swap_nodes(other.list_auto_node_);

      //Slist
      slist_base_hook::swap_nodes(other);
      slist_node_.swap_nodes(other.slist_node_);
      slist_auto_base_hook::swap_nodes(other);
      slist_auto_node_.swap_nodes(other.slist_auto_node_);
   }

   ~testvalue()
   {}

   bool operator< (const testvalue &other) const
   {  return value_ < other.value_;  }

   bool operator==(const testvalue &other) const
   {  return value_ == other.value_;  }
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

typedef testvalue<void *, false>          value_r_f;
typedef testvalue<smart_ptr<void>, false> value_s_f;
typedef testvalue<void *, true>           value_r_t;
typedef testvalue<smart_ptr<void>, true>  value_s_t;

//Typedefs
typedef value_r_f::set_base_hook::
   value_traits<value_r_f >                                 set_base_raw;

typedef value_r_f::set_member_hook::
      value_traits<value_r_f, &value_r_f::set_node_>        set_member_raw;

typedef value_r_f::set_auto_base_hook::
   value_traits<value_r_f>                                  set_auto_base_raw;

typedef value_r_f::set_auto_member_hook::
   value_traits<value_r_f, &value_r_f::set_auto_node_>      set_auto_member_raw;


typedef value_s_f::set_base_hook::
   value_traits<value_s_f >                                 set_base_smart;

typedef value_s_f::set_member_hook::
      value_traits<value_s_f, &value_s_f::set_node_>        set_member_smart;

typedef value_s_f::set_auto_base_hook::
   value_traits<value_s_f>                                  set_auto_base_smart;

typedef value_s_f::set_auto_member_hook::
      value_traits<value_s_f, &value_s_f::set_auto_node_>   set_auto_member_smart;

typedef value_r_t::set_base_hook::
   value_traits<value_r_t >                                 set_base_raw_t;

typedef value_r_t::set_member_hook::
      value_traits<value_r_t, &value_r_t::set_node_>        set_member_raw_t;

typedef value_s_t::set_base_hook::
   value_traits<value_s_t >                                 set_base_smart_t;

typedef value_s_t::set_member_hook::
      value_traits<value_s_t, &value_s_t::set_node_>        set_member_smart_t;

//Typedefs
typedef value_r_f::unordered_set_base_hook::
   value_traits<value_r_f >                                 unordered_set_base_raw;

typedef value_r_f::unordered_set_member_hook::
      value_traits<value_r_f, &value_r_f::unordered_set_node_> unordered_set_member_raw;

typedef value_r_f::unordered_set_auto_base_hook::
   value_traits<value_r_f>               unordered_set_auto_base_raw;

typedef value_r_f::unordered_set_auto_member_hook::
   value_traits<value_r_f, &value_r_f::unordered_set_auto_node_>          unordered_set_auto_member_raw;

typedef value_s_f::unordered_set_base_hook::
   value_traits<value_s_f >                   unordered_set_base_smart;

typedef value_s_f::unordered_set_member_hook::
      value_traits<value_s_f, &value_s_f::unordered_set_node_>         unordered_set_member_smart;

typedef value_s_f::unordered_set_auto_base_hook::
   value_traits<value_s_f>               unordered_set_auto_base_smart;

typedef value_s_f::unordered_set_auto_member_hook::
      value_traits<value_s_f, &value_s_f::unordered_set_auto_node_>     unordered_set_auto_member_smart;

typedef value_r_t::unordered_set_base_hook::
   value_traits<value_r_t >                              unordered_set_base_raw_t;

typedef value_r_t::unordered_set_member_hook::
      value_traits<value_r_t, &value_r_t::unordered_set_node_>                    unordered_set_member_raw_t;

typedef value_s_t::unordered_set_base_hook::
   value_traits<value_s_t >                   unordered_set_base_smart_t;

typedef value_s_t::unordered_set_member_hook::
      value_traits<value_s_t, &value_s_t::unordered_set_node_>         unordered_set_member_smart_t;

//Explicit instantiations
typedef value_r_f::list_base_hook::
   value_traits<value_r_f>               list_base_raw;

typedef value_r_f::list_member_hook::
   value_traits<value_r_f, &value_r_f::list_node_>          list_member_raw;

typedef value_r_f::list_auto_base_hook::
   value_traits<value_r_f>               list_auto_base_raw;

typedef value_r_f::list_auto_member_hook::
   value_traits<value_r_f, &value_r_f::list_auto_node_>          list_auto_member_raw;

typedef value_s_f::list_base_hook::
   value_traits<value_s_f>               list_base_smart;

typedef value_s_f::list_member_hook::
      value_traits<value_s_f, &value_s_f::list_node_>                    list_member_smart;

typedef value_s_f::list_auto_base_hook::
   value_traits<value_s_f>               list_auto_base_smart;

typedef value_s_f::list_auto_member_hook::
      value_traits<value_s_f, &value_s_f::list_auto_node_>                    list_auto_member_smart;

typedef value_r_t::list_base_hook::
   value_traits<value_r_t>               list_base_raw_t;

typedef value_r_t::list_member_hook::
   value_traits<value_r_t, &value_r_t::list_node_>  list_member_raw_t;

typedef value_s_t::list_base_hook::
      value_traits<value_s_t>               list_base_smart_t;

typedef value_s_t::list_member_hook::
      value_traits<value_s_t, &value_s_t::list_node_>                    list_member_smart_t;

typedef value_r_f::slist_base_hook::
   value_traits<value_r_f>               slist_base_raw;

typedef value_r_f::slist_member_hook::
   value_traits<value_r_f, &value_r_f::slist_node_>          slist_member_raw;

typedef value_r_f::slist_auto_base_hook::
   value_traits<value_r_f>               slist_auto_base_raw;

typedef value_r_f::slist_auto_member_hook::
   value_traits<value_r_f, &value_r_f::slist_auto_node_>          slist_auto_member_raw;

typedef value_s_f::slist_base_hook::
   value_traits<value_s_f>               slist_base_smart;

typedef value_s_f::slist_member_hook::
      value_traits<value_s_f, &value_s_f::slist_node_>                    slist_member_smart;

typedef value_s_f::slist_auto_base_hook::
   value_traits<value_s_f>               slist_auto_base_smart;

typedef value_s_f::slist_auto_member_hook::
      value_traits<value_s_f, &value_s_f::slist_auto_node_>                    slist_auto_member_smart;

typedef value_r_t::slist_base_hook::
   value_traits<value_r_t>               slist_base_raw_t;

typedef value_r_t::slist_member_hook::
   value_traits<value_r_t, &value_r_t::slist_node_>          slist_member_raw_t;

typedef value_s_t::slist_base_hook::
      value_traits<value_s_t>               slist_base_smart_t;

typedef value_s_t::slist_member_hook::
      value_traits<value_s_t, &value_s_t::slist_node_>                    slist_member_smart_t;

}  //namespace boost{
}  //namespace intrusive{

#endif
