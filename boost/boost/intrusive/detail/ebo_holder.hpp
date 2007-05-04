/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Joaquín M López Muñoz  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP

#include <boost/type_traits/is_empty.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<typename T, bool IsEmpty = false>
class ebo_holder_impl
{
   public:
   ebo_holder_impl(){}
   ebo_holder_impl(const T& t):t(t){}

   T&       get(){return t;}
   const T& get()const{return t;}

   private:
   T t;
};

template<typename T>
class ebo_holder_impl<T, true>
   :  private T
{
   public:
   ebo_holder_impl(){}
   ebo_holder_impl(const T& t):T(t){}

   T&       get(){return *this;}
   const T& get()const{return *this;}
};

template<typename T>
class ebo_holder
   :  public ebo_holder_impl<T,boost::is_empty<T>::value>
{
   private:
   typedef ebo_holder_impl<T,boost::is_empty<T>::value> super;

   public:
   ebo_holder(){}
   ebo_holder(const T& t):super(t){}

   ebo_holder& operator=(const ebo_holder& x)
   {
      this->get()=x.get();
      return *this;
   }
};


}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_EBO_HOLDER_HPP
