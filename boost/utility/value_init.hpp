// (C) Copyright 2002-2007, Fernando Luis Cacciola Carballal.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// 21 Ago 2002 (Created) Fernando Cacciola
// 07 Set 2007 (Worked around MSVC++ bug) Fernando Cacciola, Niels Dekker
// 16 Nov 2007 (Refactoring: removed private base classes) Fernando Cacciola, Niels Dekker
//
#ifndef BOOST_UTILITY_VALUE_INIT_21AGO2002_HPP
#define BOOST_UTILITY_VALUE_INIT_21AGO2002_HPP

#include <boost/detail/select_type.hpp>
#include <boost/type_traits/cv_traits.hpp>
#include <boost/detail/workaround.hpp>

// Microsoft Visual C++ does not correctly support value initialization, as reported by
// Pavel Kuznetsov (MetaCommunications Engineering), 7/28/2005, Feedback ID 100744,
// Feedback Title: Value-initialization in new-expression
// https://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=100744
// The report was closed at 11/14/2006, and its status was set to "Closed (Won't Fix)".
// Luckily, even in the presence of this compiler bug, boost::value_initialized will still
// do its job correctly, when using the following workaround:
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
#  define BOOST_UTILITY_VALUE_INIT_WORKAROUND
#endif

#ifdef BOOST_UTILITY_VALUE_INIT_WORKAROUND

#include <boost/aligned_storage.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <cstring>
#include <new>

#ifdef BOOST_MSVC
#pragma warning(push)
#if _MSC_VER >= 1310
// When using MSVC 7.1 or higher, placement new, "new (&x) T()", may trigger warning C4345:
// "behavior change: an object of POD type constructed with an initializer of the form ()
// will be default-initialized".  There is no need to worry about this, though.
#pragma warning(disable: 4345)
#endif
#endif

namespace boost {

template<class T>
class value_initialized
{
  private :
    mutable typename ::boost::aligned_storage<sizeof(T), ::boost::alignment_of<T>::value>::type x;

  public :

    value_initialized()
    {
      std::memset(&x, 0, sizeof(x));
      new (&x) T();
    }

    ~value_initialized()
    {
      void * ptr = &x; 
      static_cast<T*>(ptr)->T::~T(); 
    }

    T& data() const
    {
      void * ptr = &x;
      return *static_cast<T*>(ptr);
    }

    operator T&() const { return this->data(); }

} ;

#ifdef BOOST_MSVC
// Restores the state of warning C4345.
#pragma warning(pop)
#endif

#else

namespace boost {

template<class T>
class value_initialized
{
  public :

    value_initialized() : x() {}

    T& data() const { return x; }

    operator T&() const { return this->data(); }

    mutable
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
    typename 
#endif
    ::boost::remove_const<T>::type x ;

} ;
#endif



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
