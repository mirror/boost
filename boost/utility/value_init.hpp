// (C) Copyright 2002-2007, Fernando Luis Cacciola Carballal.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// 21 Ago 2002 (Created) Fernando Cacciola
// 07 Set 2007 (Worked around MSVC++ bug) Fernando Cacciola, Niels Dekker
//
#ifndef BOOST_UTILITY_VALUE_INIT_21AGO2002_HPP
#define BOOST_UTILITY_VALUE_INIT_21AGO2002_HPP

#include <boost/detail/select_type.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500) )
// Microsoft Visual C++ does not correctly support value initialization, as reported by
// Pavel Kuznetsov (MetaCommunications Engineering), 7/28/2005, Feedback ID 100744,
// Feedback Title: Value-initialization in new-expression
// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100744
// The report was closed at 11/14/2006, and its status was set to "Closed (Won't Fix)".
// Luckily, even in the presence of this compiler bug, boost::value_initialized will still
// do its job correctly, when using the following workaround:
#define BOOST_UTILITY_VALUE_INIT_WORKAROUND
#endif

#ifdef BOOST_UTILITY_VALUE_INIT_WORKAROUND
#include <boost/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <cstring>
#include <new>

namespace boost {

namespace vinit_detail {

template<class T>
class const_T_base
{
  protected :

    const_T_base()
    {
      std::memset(&x, 0, sizeof(x));
      new (&x) T();
    }

    ~const_T_base() { get().T::~T(); }

    T & get() const
    {
      void const * ptr = &x;
      return *static_cast<T*>(ptr);
    }

  private :
    typename ::boost::aligned_storage<sizeof(T), ::boost::alignment_of<T>::value>::type x;
} ;

template<class T>
class non_const_T_base
{
  protected :

    non_const_T_base()
    {
      std::memset(&x, 0, sizeof(x));
      new (&x) T();
    }

    ~non_const_T_base() { get().T::~T(); }

    T & get() const
    { 
      void * ptr = &x;
      return *static_cast<T*>(ptr);
    }

  private :
    mutable typename ::boost::aligned_storage<sizeof(T), ::boost::alignment_of<T>::value>::type x;
} ;

#else

namespace boost {

namespace vinit_detail {

template<class T>
class const_T_base
{
  protected :

   const_T_base() : x() {}
   T & get() const { return x; }

  private :
   T x ;
} ;

template<class T>
class non_const_T_base
{
  protected :

   non_const_T_base() : x() {}
   T & get() const { return x; }

  private :
   mutable T x ;
} ;

#endif

template<class T>
struct select_base
{
  typedef
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
  typename
#endif 
    ::boost::detail::if_true< ::boost::is_const<T>::value >
      ::template then< const_T_base<T>, non_const_T_base<T> >::type type ;
} ;

} // namespace vinit_detail

template<class T>
class value_initialized : private vinit_detail::select_base<T>::type
{
  public :

    value_initialized() {}

    operator T&() const { return this->get(); }

    T& data() const { return this->get(); }

} ;

template<class T>
T const& get ( value_initialized<T> const& x )
{
  return x.data() ;
}
template<class T>
T& get ( value_initialized<T>& x )
{
  return x.data() ;
}

} // namespace boost


#endif

