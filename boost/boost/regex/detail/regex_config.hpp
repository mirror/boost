/*
 *
 * Copyright (c) 1998-2000
 * Dr John Maddock
 *                                                          
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.  
 * It is provided "as is" without express or implied warranty.
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_config.hpp
  *   VERSION      3.11
  *   DESCRIPTION: auto-configure options for regular expression code.
  */

#ifndef BOOST_REGEX_CONFIG_HPP
#define BOOST_REGEX_CONFIG_HPP

/************************************************************************

The purpose of this header is to provide compiler and STL configuration
options.  Options fall into three categaries (namespaces, compiler and STL),
throughout, the defaults assume that the compiler and STL are fully C++ standard
compliant, features that are not supported on your system may be selectively
turned off by defining the appropriate macros.  Borland C++, Borland C++ Builder,
and Microsoft Visual C++ should be auto-recognised and configured. The HP aCC and 
SunPro C++ compiler should also be supported - but run configure for best results.
The SGI, HP, Microsoft and Rogue Wave STL's should be auto-recognised and configured.
Do not change this file unless you really really have to, add options to
<boost/regex/detail/regex_options.hpp> instead. See <regex_options.hpp> for a
full list of macros and their usage.

************************************************************************/

#include <boost/regex/detail/regex_options.hpp>

#ifdef __cplusplus
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <clocale>
#include <string>
#include <boost/smart_ptr.hpp>
#include <boost/cstdint.hpp>
#else
//
// C build,
// don't include <boost/config.hpp> because that may
// do C++ specific things in future...
//
#include <stdlib.h>
#ifdef _MSC_VER
#define BOOST_MSVC _MSC_VER
#endif
#endif

/* this will increase in future versions: */
#define BOOST_RE_VERSION 300

// fix:
#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#ifndef BOOST_RE_AUTO_CONFIGURE
#if (defined(__WIN32__) || defined(_WIN32) || defined(WIN32)) && !defined(__GNUC__)
   #define BOOST_RE_PLATFORM_W32
#endif

#ifdef __MWERKS__
// no std::maessages facet
#define BOOST_RE_NO_MESSAGES
#endif

#ifdef __BORLANDC__

   #if __BORLANDC__ < 0x500
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_BOOL
   #endif

   // versions prior to 0x530 not supported:
   #if __BORLANDC__ < 0x540
      // inline contructors exhibit strange behaviour
      // under Builder 3 and C++ 5.x when throwing exceptions
      #define INLINE_EXCEPTION_BUG
      #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
      #define BOOST_RE_NO_STRING_DEF_ARGS
      #define BOOST_RE_NO_TYPEINFO    // bad_cast etc not in namespace std.
   #endif

   #if (__BORLANDC__ == 0x550) || (__BORLANDC__ == 0x551)
      // problems with std::basic_string and dll RTL:
      #if defined(_RTLDLL) && defined(_RWSTD_COMPILE_INSTANTIATE)
         #ifdef BOOST_RE_BUILD_DLL
         #error _RWSTD_COMPILE_INSTANTIATE must not be defined when building regex++ as a DLL
         #else
         #pragma warn defining _RWSTD_COMPILE_INSTANTIATE when linking to the DLL version of the RTL may produce memory corruption problems in std::basic_string, as a result of separate versions of basic_string's static data in the RTL and you're exe/dll: be warned!!
         #endif
      #endif
      #ifndef _RTLDLL
         // this is harmless for a staic link:
         #define _RWSTD_COMPILE_INSTANTIATE
      #endif
   #endif

   #ifndef _CPPUNWIND
      #error exception handling support required
   #endif

   #ifndef __WIN32__
      #define BOOST_RE_CALL
      #define BOOST_RE_CCALL
   #else
      #ifndef BOOST_RE_CALL
         #define BOOST_RE_CALL __fastcall
      #endif
      #ifndef BOOST_RE_CCALL
         #define BOOST_RE_CCALL __stdcall
      #endif
   #endif

   #define BOOST_RE_NO_CAT
   // broken wide character support:
   #define BOOST_RE_NO_SWPRINTF

   #ifdef __MT__
      #define BOOST_RE_THREADS
   #endif

   //
   // VCL support:
   // if we're building a console app then there can't be any VCL (can there?)
   #if !defined(__CONSOLE__) && !defined(_NO_VCL)
      #define BOOST_RE_USE_VCL
   #endif
   //
   // import export options:
   #if defined(_RTLDLL) && !defined(BOOST_RE_NO_LIB)
      #ifdef BOOST_RE_BUILD_DLL
         #define BOOST_RE_IX_DECL __declspec( dllexport )
      #elif !defined(BOOST_REGEX_LIBRARY_INCLUDE_HPP) && !defined(BOOST_RE_NO_LIB)
         #define BOOST_RE_IX_DECL __declspec( dllimport )
      #endif
   #endif
   #ifndef BOOST_RE_NO_LIB
   #include <boost/regex/detail/regex_library_include.hpp>
   #endif

#include <cwchar>
#include <cwctype>

#endif

//
// only want "real" Visual C++ here:
#if defined(BOOST_MSVC) && !defined(__WATCOMC__) && !defined(__BORLANDC__) && !defined(__GNUC__) && !defined(__MWERKS__) && !defined (__ICL)
   #ifndef BOOST_RE_CALL
      #ifdef _DEBUG
         #define BOOST_RE_CALL __cdecl
      #else
         #define BOOST_RE_CALL __fastcall
      #endif
   #endif
   #ifndef BOOST_RE_CCALL
      #define BOOST_RE_CCALL __stdcall
   #endif

   #if BOOST_MSVC < 1100
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_DEFAULT_PARAM
      #define BOOST_RE_NO_BOOL
      #define BOOST_RE_NO_WCSTRING
      #define BOOST_RE_NO_LOCALE_H
      #define BOOST_RE_NO_TEMPLATE_RETURNS
   #endif

   #if BOOST_MSVC < 1200
      #define BOOST_RE_NO_STRING_DEF_ARGS
   #endif

   #if !defined(_CPPUNWIND) && defined(__cplusplus)
      #error exception handling support required
   #endif

   //
   // no support for nested template classes yet....
   // although this part of VC6 is badly documented
   #define BOOST_RE_NO_CAT
   #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
   #define BOOST_RE_NO_SWPRINTF

   #ifdef _MT
      #define BOOST_RE_THREADS
   #endif

#ifdef __cplusplus
#include <memory>
#include <utility>
#endif
#pragma warning(disable: 4786)
#pragma warning(disable: 4800)
#pragma warning(disable: 4200)
#pragma warning(disable: 4097)
#pragma warning(disable: 4127)

   //
   // import export options:
   #if defined(_DLL) && !defined(BOOST_RE_STATIC_LIB) && !defined(BOOST_RE_NO_LIB)
      #ifdef BOOST_RE_BUILD_DLL
         #define BOOST_RE_IX_DECL __declspec( dllexport )
      #elif !defined(BOOST_REGEX_LIBRARY_INCLUDE_HPP) && !defined(BOOST_RE_NO_LIB)
         #define BOOST_RE_IX_DECL __declspec( dllimport ) 
      #endif
   #endif
   #include <boost/regex/detail/regex_library_include.hpp>

#endif

#ifdef __GNUC__
   #if (__GNUC__ < 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ < 91))
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
   #endif

   #if defined(_WIN32) || defined(__CYGWIN__)
      /* there seems to be a problem with <windows.h> in gcc */
      #define BOOST_RE_LOCALE_C
      #define BOOST_RE_NO_W32
      #define BOOST_RE_NO_WCTYPE_H
      #define BOOST_RE_NO_TEMPLATE_SWITCH_MERGE
   #endif
   #define BOOST_RE_NO_CAT
   #define BOOST_RE_NO_SWPRINTF
   #include <string>
   #ifdef __BASTRING__
   	#define BOOST_RE_NO_WCSTRING
   #endif
   //
   // for now we'll always define these
   // unless we know that the platform can cope
   // with wide character strings:
   #if !defined(linux) || (defined(__GLIBCPP__) && !defined(_GLIBCPP_USE_WCHAR_T))
   	#define BOOST_RE_NO_WCTYPE_H
   	#define BOOST_RE_NO_WCSTRING
   #endif

#endif

#ifdef __MWERKS__
   #define BOOST_RE_NO_CAT
#endif

#ifdef __SUNPRO_CC
   #if (__SUNPRO_CC < 0x500)
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_OLD_IOSTREAM
   #endif
   #define BOOST_RE_NO_SWPRINTF
   #define BOOST_RE_NO_LOCALE_H
#endif

#if defined(__HP_aCC) || defined(__hpux)
   // putative HP aCC support, run configure for
   // support tailored to your system....
#   if (__HP_aCC < 31400)
   // non-conformant aCC:
   #define BOOST_RE_NO_NAMESPACES
   #define BOOST_RE_OLD_IOSTREAM
   #define BOOST_NO_STD_ALLOCATOR
#else
   #if !defined(_NAMESPACE_STD)
      #define BOOST_RE_OLD_IOSTREAM
   #endif
#endif
   #define BOOST_RE_NO_SWPRINTF
   #define BOOST_RE_NO_CAT
#endif

#ifdef __sgi // SGI IRIX C++
#define BOOST_RE_NO_SWPRINTF
// bring in stl version:
#include <memory> 
#if defined(__SGI_STL_PORT)
// STLPort on IRIX is misconfigured: <cwctype> does not compile
// as a temporary fix include <wctype.h> instead and prevent inclusion
// of STLPort version of <cwctype>
#include <wctype.h>
#define __STLPORT_CWCTYPE
#define BOOST_RE_NO_WCTYPE_H
#endif
#endif

#if defined __KCC
// Kai 3.4 appears to have no wide character string support:
#   if __KCC_VERSION <= 3499
#    define BOOST_RE_NO_WCSTRING
#   endif
#endif

#if (defined(_REENTRANT) || defined(_PTHREADS) || defined(__BEOS__)) && !defined(_NOTHREADS)
//
// Several compilers define _REENTRANT or 
// _PTHREADS when threading support is turned on:
//
#define BOOST_RE_THREADS
#endif

#endif  // BOOST_RE_AUTO_CONFIGURE

#ifdef __cplusplus
#ifndef BOOST_RE_NO_WCSTRING
#ifndef BOOST_RE_NO_WCTYPE_H
#include <cwctype>
#endif
#ifndef BOOST_RE_NO_WCHAR_H
#include <cwchar>
#endif
#endif
#endif

#ifdef BOOST_RE_NO_NAMESPACES
#define BOOST_RE_MAYBE_ACCESS_SPEC ::
#else
#define BOOST_RE_MAYBE_ACCESS_SPEC 
#endif

#ifndef BOOST_RE_IX_DECL
#define BOOST_RE_IX_DECL
#endif

#ifndef MB_CUR_MAX
// yuk!
// better make a conservative guess!
#define MB_CUR_MAX 10
#endif


/* everything else is C++: */

#ifdef __cplusplus

/* define macro's to make default parameter declaration easier: */

#ifdef BOOST_RE_NO_DEFAULT_PARAM
   #define BOOST_RE_DEFAULT_PARAM(x)
   #define BOOST_RE_TRICKY_DEFAULT_PARAM(x)
#elif defined(BOOST_RE_NO_TRICKY_DEFAULT_PARAM)
   #define BOOST_RE_DEFAULT_PARAM(x) = x
   #define BOOST_RE_TRICKY_DEFAULT_PARAM(x)
#else
   #define BOOST_RE_DEFAULT_PARAM(x) = x
   #define BOOST_RE_TRICKY_DEFAULT_PARAM(x) = x
#endif

/* STL configuration goes here: */

#ifndef BOOST_RE_AUTO_CONFIGURE

#include <stdexcept>

#ifndef BOOST_RE_NO_ITERATOR_H
   #include <iterator>

   #if defined(__SGI_STL_INTERNAL_ITERATOR_H) || defined(_STLP_INTERNAL_ITERATOR_H) || defined(__SGI_STL_ITERATOR_H) || defined(__SGI_STL_PORT)
               
      /* we are using SGI's STL
       some of these (std)
       may be guesswork: */

      # if (!defined (__SGI_STL_OWN_IOSTREAMS) && !defined(_STLP_OWN_IOSTREAMS) && !defined(__GLIBCPP__) && !defined(__STL_USE_NEW_IOSTREAMS)) || defined (__STL_HAS_NO_NEW_IOSTREAMS) || defined(_STLP_HAS_NO_NEW_IOSTREAMS) || defined (__STL_USE_NO_IOSTREAMS) || defined(__STLP_USE_NO_IOSTREAMS) || defined(__STL_NO_MBSTATE_T) || defined(__STLP_NO_MBSTATE_T)
         // Old IO streams:
         #define BOOST_RE_NO_LOCALE_H
         #define BOOST_RE_OLD_IOSTREAM
      #else
         #include <locale>
         #if defined( __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS) || defined(_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS)
            #define BOOST_RE_USE_FACET(l, m) (*std::_Use_facet<m >(l))
         #endif
      #endif
      #ifdef __BASTRING__
      	#define BOOST_RE_NO_WCSTRING
      #endif
      #if !(defined(__STL_MEMBER_TEMPLATE_CLASSES) || defined(__STLP_MEMBER_TEMPLATE_CLASSES)) || !(defined(__STL_MEMBER_TEMPLATES) || defined(__STLP_MEMBER_TEMPLATES))
         #define BOOST_NO_MEMBER_TEMPLATES
      #endif
      #define BOOST_RE_NO_TYPEINFO

      #if defined(__STL_NO_BOOL) || defined(__STLP_NO_BOOL)
         #define BOOST_RE_NO_BOOL
      #endif
      #if defined(__STL_LIMITED_DEFAULT_TEMPLATES) || defined(__STLP_LIMITED_DEFAULT_TEMPLATES)
         #define BOOST_RE_NO_TRICKY_DEFAULT_PARAM
         #define BOOST_RE_NO_STRING_DEF_ARGS  
      #endif

      #include <algorithm>
      #include <memory>

      #define BOOST_RE_ALGO_INCLUDED

      #if !(defined( __STL_CLASS_PARTIAL_SPECIALIZATION) || defined(__STLP_CLASS_PARTIAL_SPECIALIZATION)) || !defined(__SGI_STL_PORT)
         #define BOOST_NO_STD_DISTANCE
      #endif

      #if defined(__STL_USE_STD_ALLOCATORS) || (defined(__SGI_STL_PORT ) && !defined(__STL_MEMBER_TEMPLATE_CLASSES) && !defined(__STLP_MEMBER_TEMPLATE_CLASSES) && !defined(__STL_MEMBER_TEMPLATES) && !defined(__STLP_MEMBER_TEMPLATES))
         /* new style allocator's with nested template classes */
      #else  /* __STL_USE_STD_ALLOCATORS */
            #define BOOST_NO_STD_ALLOCATOR
      #endif /* __STL_USE_STD_ALLOCATORS */

      #define BOOST_RE_STL_DONE

   #elif defined(_RWSTD_VER) || defined(__STD_ITERATOR__)

      /* Rogue Wave STL */
      // Sometimes we have a four figure version number, sometimes a
      // six figure one (RW seems to omit trailing zeros from version number)
      #ifndef _RWSTD_VER
         #define BOOST_RWSTD_VER 0
      #else
         #if _RWSTD_VER < 0x10000
            #define BOOST_RWSTD_VER (_RWSTD_VER << 8)
         #else
            #define BOOST_RWSTD_VER _RWSTD_VER
         #endif
      #endif

      #if defined(RWSTD_NO_MEMBER_TEMPLATES) || defined(RWSTD_NO_MEM_CLASS_TEMPLATES)
         #define BOOST_NO_MEMBER_TEMPLATES
      #endif
      #ifdef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
         #define BOOST_RE_NO_TEMPLATE_RETURNS
      #endif

      #ifdef RWSTD_NO_EXCEPTIONS
         #error exception handling support required
      #endif

      #ifdef RWSTD_NO_DEFAULT_TEMPLATES
         #define BOOST_RE_NO_DEFAULT_PARAM
         #define BOOST_RE_NO_TRICKY_DEFAULT_PARAM
         #define BOOST_RE_NO_STRING_DEF_ARGS  
      #endif

      #ifdef _RWSTD_NO_COMPLEX_DEFAULT_TEMPLATES
         #define BOOST_RE_NO_TRICKY_DEFAULT_PARAM
         #define BOOST_RE_NO_STRING_DEF_ARGS  
      #endif

      #ifdef RWSTD_NO_BOOL
         #define BOOST_RE_NO_BOOL
      #endif

      #if (BOOST_RWSTD_VER < 0x020000) || defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
          #define BOOST_NO_STD_DISTANCE
      #endif

      #include <memory>

      #if !defined(_RWSTD_ALLOCATOR)
         /*
         // old style allocator
         // this varies a great deal between versions, and there is no way
         // that I can tell of differentiating between them, so use our
         // own default allocator...
         */
         #define BOOST_NO_STD_ALLOCATOR
      #endif

      #define BOOST_RE_STL_DONE
      #if BOOST_RWSTD_VER < 0x020100
         #define BOOST_RE_NO_OI_ASSIGN
      #endif

   #elif (defined(BOOST_MSVC) || defined(__ICL)) && (defined(_YVALS) || defined(_CPPLIB_VER))

      /* VC6 or Intel C++, with Dinkum STL */
      #define BOOST_RE_NO_OI_ASSIGN

      /* MS's allocators are rather ambiguous about their properties
      at least as far as MSDN is concerned, so play safe: */
      #define BOOST_NO_STD_ALLOCATOR

      #define BOOST_RE_STL_DONE
      #ifndef _CPPLIB_VER
         #define BOOST_RE_USE_FACET(l, type) std::use_facet(l, (type*)0, true)
         #define BOOST_RE_HAS_FACET(l, type) std::has_facet(l, (type*)0)
      #else
         #define BOOST_RE_USE_FACET(l, type) std::use_facet(l, (type*)0)
         #define BOOST_RE_HAS_FACET(l, type) std::has_facet(l, (type*)0)
      #endif


   #else

      /* unknown STL version
       try the defaults: */
    
   #endif  /* <iterator> config */

#endif

/* now do allocator if not already done */

#endif // BOOST_RE_AUTO_CONFIGURE



/* namespace configuration goes here: */
#define BOOST_RE_USING(x) using namespace x;


/* locale configuration goes here */
#if !defined(BOOST_RE_NO_LOCALE_H)
    #include <locale>
    #define LOCALE_INSTANCE(i) std::locale i;
    #define MAYBE_PASS_LOCALE(i) , i
    #ifndef BOOST_RE_NO_TEMPLATE_RETURNS
      #ifndef BOOST_RE_USE_FACET
         #define BOOST_RE_USE_FACET(l, type) std::use_facet< type >(l)
      #endif
      #ifndef BOOST_RE_HAS_FACET
         #define BOOST_RE_HAS_FACET(l, type) std::has_facet< type >(l)
      #endif
    #else
      #ifndef BOOST_RE_USE_FACET
         #define BOOST_RE_USE_FACET(l, type) std::use_facet(l, (type*)0)
      #endif
      #ifndef BOOST_RE_HAS_FACET
         #define BOOST_RE_HAS_FACET(l, type) std::has_facet(l, (type*)0)
      #endif
    #endif
#else
    #define LOCALE_INSTANCE(i)
    #define MAYBE_PASS_LOCALE(i)
#endif

/* compiler configuration goes here: */

#if defined( BOOST_RE_NO_BOOL) && !defined(bool)
   #define bool int
   #define true 1
   #define false 0
#endif

#ifndef BOOST_RE_CALL
#define BOOST_RE_CALL
#endif

#ifndef BOOST_RE_CCALL
#define BOOST_RE_CCALL
#endif

#ifndef BOOST_RE_DECL
#define BOOST_RE_DECL
#endif

#if defined(BOOST_RE_NO_DEFAULT_PARAM) || defined(BOOST_RE_NO_TRICKY_DEFAULT_PARAM)
#define BOOST_RE_NO_STRING_DEF_ARGS  
#endif

#if defined(BOOST_NO_MEMBER_TEMPLATES) && !defined(BOOST_NO_STD_ALLOCATOR)
#define BOOST_NO_STD_ALLOCATOR
#endif


/* add our class def's if they are needed: */

namespace boost{
   namespace re_detail{

#ifdef __BORLANDC__
   #pragma option push -a4 -b -Ve -pc
#endif

// add our destroy functions:

template <class T>
inline void BOOST_RE_CALL jm_destroy(T* t)
{
   t->~T();
   (void)t; // suppress incorrect MSVC compiler warning
}
#if 0
inline void BOOST_RE_CALL jm_destroy(char* t){}
inline void BOOST_RE_CALL jm_destroy(short* t){}
inline void BOOST_RE_CALL jm_destroy(unsigned short* t){}
inline void BOOST_RE_CALL jm_destroy(int* t){}
inline void BOOST_RE_CALL jm_destroy(unsigned int* t){}
inline void BOOST_RE_CALL jm_destroy(long* t){}
inline void BOOST_RE_CALL jm_destroy(unsigned long* t){}
#endif

template <class T>
inline void BOOST_RE_CALL jm_construct(void* p, const T& t)
{
   new (p) T(t);
}


template<class T, class Allocator>
class re_alloc_binder : public Allocator
{
public:
   typedef T         value_type;
   typedef T*        pointer;
   typedef const T*  const_pointer;
   typedef T&        reference;
   typedef const T&  const_reference;
   typedef std::size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   re_alloc_binder(const Allocator& i);
   re_alloc_binder(const re_alloc_binder& o) : Allocator(o) {}

   T* BOOST_RE_CALL allocate(std::size_t n, std::size_t /* hint */ = 0)
      { return 0 == n ? 0 : (T*) this->Allocator::allocate(n * sizeof(T)); }
   void BOOST_RE_CALL deallocate(T *p, std::size_t n)
             { if (0 != n) this->Allocator::deallocate((char*)p, n * sizeof (T)); }

   pointer BOOST_RE_CALL address(reference x) const { return &x; }
   const_pointer BOOST_RE_CALL address(const_reference x) const { return &x; }
   static size_type BOOST_RE_CALL max_size() { return (size_type)-1; }
   static void BOOST_RE_CALL construct(pointer p, const T& val) { jm_construct(p, val); }
   void BOOST_RE_CALL destroy(pointer p) { jm_destroy(p); }

   const Allocator& BOOST_RE_CALL instance()const { return *this; }

#ifndef BOOST_NO_MEMBER_TEMPLATES

   template <class U>
   struct rebind
   {
      typedef re_alloc_binder<U, Allocator> other;
   };
   
   template <class U>
   BOOST_RE_CALL re_alloc_binder(const re_alloc_binder<U, Allocator>& o) throw()
      : Allocator(o.instance())
   {
   }
#endif
};

template<class T, class Allocator>
inline re_alloc_binder<T, Allocator>::re_alloc_binder(const Allocator &i)
    : Allocator(i)
{}


//
// class jm_def_alloc
// basically a standard allocator that only allocates bytes...
// think of it as allocator<char>, with a non-standard 
// rebind::other typedef.
//
class jm_def_alloc
{
public:
   typedef char         value_type;
   typedef char*        pointer;
   typedef const char*  const_pointer;
   typedef char&        reference;
   typedef const char&  const_reference;
   typedef std::size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   pointer BOOST_RE_CALL address(reference x) const { return &x; }
   const_pointer BOOST_RE_CALL address(const_reference x) const { return &x; }
   static size_type BOOST_RE_CALL max_size() { return (size_type)-1; }
   static void BOOST_RE_CALL construct(pointer , const char& ) {  }
   void BOOST_RE_CALL destroy(pointer ) {  }
   static void * BOOST_RE_CALL allocate(std::size_t n, std::size_t /* hint */ = 0)
   {
      return ::operator new(n);
   }
   static void BOOST_RE_CALL deallocate(void *p, std::size_t /*n*/ )
   {
      ::operator delete(p);
   }

#ifndef BOOST_NO_MEMBER_TEMPLATES
   template <class U>
   struct rebind
   {
      typedef re_alloc_binder<U, jm_def_alloc> other;
   };

   template <class U>
   BOOST_RE_CALL jm_def_alloc(const re_alloc_binder<U, jm_def_alloc>& ) throw() { }
#endif
   jm_def_alloc(const jm_def_alloc&) {}
   jm_def_alloc() {}
};

template <class T>
struct dummy_iterator_base
{
   typedef T                       value_type;
   typedef std::ptrdiff_t    difference_type;
   typedef T*                      pointer;
   typedef T&                      reference;
   //typedef Category              iterator_category;
};

// we need to absolutely sure that int values are correctly
// translated to bool (true or false) values...
// note that the original HP STL redefines the bool type regardless
// of whether the compiler supports it.... yuk

#if defined(BOOST_RE_NO_BOOL) || defined(ITERATOR_H) || defined(bool)
#define BOOST_RE_MAKE_BOOL(x) boost::re_detail::boolify(x)

template <class I>
inline bool BOOST_RE_CALL boolify(I val)
{
   return val ? true : false;
}

#else
#define BOOST_RE_MAKE_BOOL(x) x
#endif


template <class T, class A>
struct rebind_allocator
{
#ifdef BOOST_NO_STD_ALLOCATOR
   typedef re_alloc_binder<T,A> type;
#else
   typedef typename A::template rebind<T> binder;
   typedef typename binder::other type;
#endif
};

#ifdef BOOST_NO_STD_DISTANCE
template <class T>
std::ptrdiff_t distance(const T& x, const T& y)
{ return y - x; }
#else
using std::distance;
#endif

#ifdef __BORLANDC__
  #pragma option pop
#endif
} // namespace re_detail

} // namespace boost

#ifdef BOOST_NO_STD_ALLOCATOR
#define BOOST_RE_DEF_ALLOC(T) boost::re_detail::jm_def_alloc
#define BOOST_RE_DEF_ALLOC_PARAM(T) BOOST_RE_DEFAULT_PARAM(boost::re_detail::jm_def_alloc)
#else
#include <memory>
#define BOOST_RE_DEF_ALLOC(T) std::allocator<T>
#define BOOST_RE_DEF_ALLOC_PARAM(T) BOOST_RE_TRICKY_DEFAULT_PARAM(std::allocator<T>)
#endif


#ifdef __GNUC__
#define INLINE_EXCEPTION_BUG
#endif

#if !defined(INLINE_EXCEPTION_BUG) || defined(BOOST_RE_NO_TEMPLATE_MERGE)
    #define CONSTRUCTOR_INLINE inline
#else
    #define CONSTRUCTOR_INLINE
#endif

#if defined(BOOST_RE_PLATFORM_W32) && !defined(BOOST_RE_LOCALE_W32) && !defined(BOOST_RE_LOCALE_C) && !defined(BOOST_RE_LOCALE_CPP) && !defined(BOOST_RE_NO_W32)
#define BOOST_RE_LOCALE_W32
#endif

#if !defined(BOOST_RE_LOCALE_W32) && !defined(BOOST_RE_LOCALE_C) && !defined(BOOST_RE_LOCALE_CPP)
#define BOOST_RE_LOCALE_C
#endif

#if defined(BOOST_RE_OLD_ALLOCATORS)
#define BOOST_RE_MAYBE_TYPENAME
#else
#define BOOST_RE_MAYBE_TYPENAME typename
#endif

#if defined(_WIN32) && !defined(BOOST_RE_NO_W32)
#include <windows.h>
#endif


/* now do debugging stuff: */

#ifdef BOOST_RE_DEBUG

#ifdef BOOST_RE_OLD_IOSTREAM
#include <iostream.h>
#else
#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::hex;
using std::dec;
#endif

   #ifndef jm_assert
      #define jm_assert(x) if((x) == 0){ cerr << "Assertion failed: " << #x << " in file " << __FILE__ << "and line " << __LINE__ << endl; exit(-1); }
   #endif
   #ifndef jm_trace
      #define jm_trace(x) cerr << x << endl;
   #endif
   #ifndef jm_instrument 
      #define jm_instrument jm_trace(__FILE__<<"#"<<__LINE__)
   #endif

namespace boost{
   namespace re_detail{
class debug_guard
{
public:
   char g1[32];
   const char* pc;
   char* pnc;
   const char* file;
   int line;
   char g2[32];
   debug_guard(const char* f, int l, const char* p1 = 0, char* p2 = 0);
   ~debug_guard();
};

#define BOOST_RE_GUARD_STACK boost::re_detail::debug_guard sg(__FILE__, __LINE__);
#define BOOST_RE_GUARD_GLOBAL(x) const char g1##x[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, }; char g2##x[32]; boost::debug_guard g3##x(__FILE__, __LINE__, g1##x, g2##x);

   } // namespace re_detail
} // namespace boost

   #ifdef __BORLANDC__
      #pragma message "macro allocator: " BOOST_RE_DEF_ALLOC_PARAM(wchar_t)
      #ifdef BOOST_RE_LOCALE_CPP
         #pragma message "locale support enabled"
      #endif
   #endif

#else

   #define jm_assert(x)
   #define jm_trace(x)
   #define BOOST_RE_GUARD_STACK
   #define BOOST_RE_GUARD_GLOBAL(x)
   #ifndef jm_instrument 
      #define jm_instrument
   #endif


#endif

//
// compiler fixes:

// fix for namespace problems:
//
// the following are defined as macros which are
// incompatable with std::something syntax, no
// choice but to undef them?
#ifdef memcpy
#undef memcpy
#endif
#ifdef memmove
#undef memmove
#endif
#ifdef memset
#undef memset
#endif
#ifdef sprintf
#undef sprintf
#endif
#ifdef strcat
#undef strcat
#endif
#ifdef strcmp
#undef strcmp
#endif
#ifdef strcpy
#undef strcpy
#endif
#ifdef strlen
#undef strlen
#endif
#ifdef swprintf
#undef swprintf
#endif
#ifdef wcslen
#undef wcslen
#endif
#ifdef wcscpy
#undef wcscpy
#endif
#ifdef wcscmp
#undef wcscmp
#endif
#ifdef isalpha
#undef isalpha
#endif
#ifdef iscntrl
#undef iscntrl
#endif
#ifdef isdigit
#undef isdigit
#endif
#ifdef islower
#undef islower
#endif
#ifdef isupper
#undef isupper
#endif
#ifdef ispunct
#undef ispunct
#endif
#ifdef isspace
#undef isspace
#endif
#ifdef isxdigit
#undef isxdigit
#endif

#ifdef tolower
#undef tolower
#endif
#ifdef iswalpha
#undef iswalpha
#endif
#ifdef iswcntrl
#undef iswcntrl
#endif
#ifdef iswdigit
#undef iswdigit
#endif
#ifdef iswlower
#undef iswlower
#endif
#ifdef iswpunct
#undef iswpunct
#endif
#ifdef iswspace
#undef iswspace
#endif
#ifdef iswupper
#undef iswupper
#endif
#ifdef iswxdigit
#undef iswxdigit
#endif
#ifdef towlower
#undef towlower
#endif
#ifdef wcsxfrm
#undef wcsxfrm
#endif

#if defined(BOOST_NO_STDC_NAMESPACE) || (defined(std) && defined(__SGI_STL_PORT)) || defined(_STLP_IMPORT_VENDOR_CSTD) || defined(__STL_IMPORT_VENDOR_CSTD)
//
// fix namespaces,
// note that we almost always do this for STLPort, as it doesn't always
// catch all the wide character functions:
namespace std{
   using ::ptrdiff_t;
   using ::size_t;
   using ::memcpy;
   using ::memmove;
   using ::memset;
   using ::memcmp;
   using ::sprintf;
   using ::strcat;
   using ::strcmp;
   using ::strcpy;
   using ::strlen;
   using ::strxfrm;
   using ::isalpha;
   using ::iscntrl;
   using ::isdigit;
   using ::islower;
   using ::isupper;
   using ::ispunct;
   using ::isspace;
   using ::isxdigit;
   using ::tolower;
   using ::abs;
   using ::setlocale;
#ifndef BOOST_RE_NO_WCSTRING
#ifndef BOOST_RE_NO_SWPRINTF
   using ::swprintf;
#endif
   using ::wcslen;
   using ::wcscpy;
   using ::wcscmp;
   using ::iswalpha;
   using ::iswcntrl;
   using ::iswdigit;
   using ::iswlower;
   using ::iswpunct;
   using ::iswspace;
   using ::iswupper;
   using ::iswxdigit;
   using ::towlower;
   using ::wcsxfrm;
   using ::wcstombs;
   using ::mbstowcs;
#if !defined(BOOST_RE_NO_LOCALE_H) && !defined (__STL_NO_NATIVE_MBSTATE_T)
   using ::mbstate_t;
#endif
#endif // BOOST_RE_NO_WCSTRING
   using ::fseek;
   using ::fread;
   using ::ftell;
   using ::fopen;
   using ::fclose;
   using ::FILE;
}

#endif

#if defined(__SGI_STL_PORT) && defined(BOOST_MSVC) && !defined(_MT) && (__SGI_STL_PORT >= 0x400)
#error STLPort libraries require multithread support to be turned on.
#endif


#endif  /* __cplusplus */

#ifndef BOOST_RE_CALL
#define BOOST_RE_CALL
#endif

#ifndef BOOST_RE_CCALL
#define BOOST_RE_CCALL
#endif

#ifndef BOOST_RE_DECL
#define BOOST_RE_DECL
#endif


#endif  // BOOST_REGEX_CONFIG_HPP
















































