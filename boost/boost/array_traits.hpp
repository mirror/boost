// -*-C++-*- array.hpp
// <!!----------------------------------------------------------------------> 
// <!! Copyright (C) 1998 Dietmar Kuehl, Claas Solutions GmbH > 
// <!!> 
// <!! Permission to use, copy, modify, distribute and sell this > 
// <!! software for any purpose is hereby granted without fee, provided > 
// <!! that the above copyright notice appears in all copies and that > 
// <!! both that copyright notice and this permission notice appear in > 
// <!! supporting documentation. Dietmar Kuehl and Claas Solutions make no > 
// <!! representations about the suitability of this software for any > 
// <!! purpose. It is provided "as is" without express or implied warranty. > 
// <!!----------------------------------------------------------------------> 

// Author: Dietmar Kuehl dietmar.kuehl@claas-solutions.de 
// Title:  STL container support, including support for built-in arrays
// Version: $Id$

// -------------------------------------------------------------------------- 

#if !defined(BOOST_ARRAY_HPP)
#define BOOST_ARRAY_HPP 1

// -------------------------------------------------------------------------- 

#include <cstddef>

// -------------------------------------------------------------------------- 

namespace boost
{

  // --- a general version of container traits ------------------------------ 

  template <typename Cont>
    struct array_traits
    {
      typedef typename Cont::iterator  iter_type;
      typedef typename Cont::size_type size_type;
      static iter_type begin(Cont &cont) { return cont.begin(); }
      static iter_type end(Cont &cont) { return cont.end(); }
      static size_type size(Cont &cont) { return cont.size(); }
    };

  // --- a version of container traits for constant constainer --------------

  template <typename Cont>
    struct array_traits<Cont const>
    {
      typedef typename Cont::const_iterator  iter_type;
      typedef typename Cont::size_type       size_type;
      static iter_type begin(Cont const &cont) { return cont.begin(); }
      static iter_type end(Cont const &cont) { return cont.end(); }
      static size_type size(Cont const &cont) { return cont.size(); }
    };

  // --- a special version for non-const built-in arrays -------------------- 

  template <typename T, size_t sz>
    struct array_traits<T[sz]>
    {
      typedef T*     iter_type;
      typedef size_t size_type;
      static iter_type begin(T (&array)[sz]) { return array; }
      static iter_type end(T (&array)[sz]) { return array + sz; }
      static size_type size(T (&)[sz]) { return sz; }
    };
  
  // --- a special version for const built-in arrays ------------------------ 

  template <typename T, size_t sz>
    struct array_traits<T const[sz]>
    {
      typedef T const*     iter_type;
      typedef size_t size_type;
      static iter_type begin(T const (&array)[sz]) { return array; }
      static iter_type end(T const (&array)[sz]) { return array + sz; }
      static size_type size(T const (&array)[sz]) { return sz; }
    };

  template <typename T, int sz>
  inline char (&sizer(T (&)[sz]))[sz];
  
  // --- general version of the global accessor functions --------------------- 

  template <typename Cont>
    inline typename array_traits<Cont>::iter_type
    begin(Cont &cont) { return array_traits<Cont>::begin(cont); }

  template <typename Cont>
    inline typename array_traits<Cont>::iter_type
    end(Cont &cont) { return array_traits<Cont>::end(cont); }

  template <typename Cont>
    inline typename array_traits<Cont>::size_type
    size(Cont &cont) { return array_traits<Cont>::size(cont); }

  // --- Actually the above should be sufficient but compilers seem -----------
  // --- to welcome some help. So here we go:

  template <typename T, size_t sz>
    inline typename array_traits<T[sz]>::iter_type
    begin(T (&a)[sz]) { return array_traits<T[sz]>::begin(a); }
  
  template <typename T, size_t sz>
    inline typename array_traits<T[sz]>::iter_type
    end(T (&a)[sz]) { return array_traits<T[sz]>::end(a); }
  
  template <typename T, size_t sz>
    inline typename array_traits<T[sz]>::size_type
    size(T (&a)[sz]) { return array_traits<T[sz]>::size(a); }
  
  // --- Apparently the compilers also need some specific help, ---------------

  // --- EDG-2.39 wants to pass around pointers in some contexts --------------
#ifdef __EDG__
  template <typename T>
    struct array_traits<T*>
    {
      typedef T*     iter_type;
      typedef size_t size_type;
    };
#endif

  // --- egcs-1998-11-22 apparently likes an extra const version: -------------
#ifdef __GNUG__
  template <typename T, size_t sz>
    inline typename array_traits<T const[sz]>::iter_type
    begin(T const(&a)[sz]) { return array_traits<T const[sz]>::begin(a); }
  
  template <typename T, size_t sz>
    inline typename array_traits<T const[sz]>::iter_type
    end(T const(&a)[sz]) { return array_traits<T const[sz]>::end(a); }
  
  template <typename T, size_t sz>
    inline typename array_traits<T const[sz]>::size_type
    size(T const (&a)[sz]) { return array_traits<T const[sz]>::size(a); }
#endif
  
}

// -----------------------------------------------------------------------------

#endif /* BOOST_ARRAY_HPP */
