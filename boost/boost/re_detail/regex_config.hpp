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
  *   VERSION      3.01
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
<boost/re_detail/_opt.h> instead. See <jm_opt.h> for a full list of macros and their usage.

************************************************************************/

#include <boost/re_detail/regex_options.hpp>

#ifdef __cplusplus
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <string>
#include <boost/smart_ptr.hpp>
#else
#include <stdlib.h>
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
#ifdef __BORLANDC__

   #if __BORLANDC__ < 0x500
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_BOOL
      #define BOOST_RE_NO_MUTABLE
   #endif

   #if __BORLANDC__ < 0x520
      #define BOOST_RE_NO_WCSTRING
      #define BOOST_RE_NO_INT64
      // Early versions of Borlands namespace code can't cope with iterators
      // that are in different namespaces from STL code.
      #define boost std
      #define BOOST_RE_NO_NOT_EQUAL
   #endif

   #if __BORLANDC__ < 0x530
      #define BOOST_RE_NO_WCTYPE_H
      #define BOOST_RE_NO_WCHAR_H
      #define BOOST_RE_OLD_IOSTREAM
      #define BOOST_RE_NO_TRICKY_DEFAULT_PARAM
      #define BOOST_RE_NO_EXCEPTION_H
      #ifndef __WIN32__
         #define BOOST_RE_NO_WCSTRING
      #endif
      #define BOOST_RE_NO_LOCALE_H
      #define BOOST_RE_NO_TEMPLATE_RETURNS
      //
      // this is a hack to get around buggy namespace support in the
      // 0x520 compiler version
      #define BOOST_RE_NO_USING
      #define BOOST_RE_USING_HACK
      #define BOOST_RE_OLD_IOSTREAM
   #endif

   #if __BORLANDC__ < 0x540
      #define BOOST_RE_NO_MEMBER_TEMPLATES
      // inline contructors exhibit strange behaviour
      // under Builder 3 and C++ 5.x when throwing exceptions
      #define INLINE_EXCEPTION_BUG
      #define BOOST_RE_NESTED_TEMPLATE_DECL
      #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
      #define BOOST_RE_NO_STRING_DEF_ARGS
      #define BOOST_RE_NO_TYPEINFO    // bad_cast etc not in namespace std.
   #endif
   //
   // Builder 4 seems to have broken template friend support:
   #define BOOST_RE_NO_TEMPLATE_FRIEND

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

   #ifdef _Windows
      #define BOOST_RE_PLATFORM_WINDOWS
   #else
      #define BOOST_RE_PLATFORM_DOS
   #endif

   #ifndef __WIN32__
      #define BOOST_RE_CALL
      #define BOOST_RE_CCALL
   #else
      #define BOOST_RE_CALL __fastcall
      #define BOOST_RE_CCALL __stdcall
   #endif

   #define BOOST_RE_INT64t __int64
   #define BOOST_RE_IMM64(val) val##i64
   #define BOOST_RE_NO_CAT

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
   #ifdef _RTLDLL
      #ifdef BOOST_RE_BUILD_DLL
         #define BOOST_RE_IX_DECL __declspec( dllexport )
      #elif !defined(BOOST_REGEX_LIBRARY_INCLUDE_HPP) && !defined(BOOST_RE_NO_LIB)
         #define BOOST_RE_IX_DECL __declspec( dllimport )
      #endif
   #endif
   #include <boost/re_detail/regex_library_include.hpp>

#include <cwchar>
#include <cwctype>

#endif

//
// only want "real" Visual C++ here:
#if defined(BOOST_MSVC) && !defined(__WATCOMC__) && !defined(__BORLANDC__) && !defined(__GNUC__) && !defined(__MWERKS__) && !defined (__ICL)
   #define BOOST_RE_CALL __fastcall
   #define BOOST_RE_CCALL __stdcall

   #if BOOST_MSVC < 1100
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_DEFAULT_PARAM
      #define BOOST_RE_NO_BOOL
      #define BOOST_RE_NO_MUTABLE
      #define BOOST_RE_NO_WCSTRING
      #define BOOST_RE_NO_LOCALE_H
      #define BOOST_RE_NO_TEMPLATE_RETURNS
      #define BOOST_RE_NO_INT64
   #endif

   #if BOOST_MSVC < 1200
      #define BOOST_RE_NESTED_TEMPLATE_DECL
      #define BOOST_RE_NO_STRING_DEF_ARGS
   #endif

   #ifndef _CPPUNWIND
      #error exception handling support required
   #endif

   #define BOOST_RE_PLATFORM_WINDOWS
   //
   // no support for nested template classes yet....
   // although this part of VC6 is badly documented
   #define BOOST_RE_NO_MEMBER_TEMPLATES
   #define BOOST_RE_INT64t __int64
   #define BOOST_RE_IMM64(val) val##i64
   #define BOOST_RE_NO_CAT
   #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
   #define BOOST_RE_NO_TEMPLATE_FRIEND

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
   #ifdef _DLL
      #ifdef BOOST_RE_BUILD_DLL
         #define BOOST_RE_IX_DECL __declspec( dllexport )
      #elif !defined(BOOST_REGEX_LIBRARY_INCLUDE_HPP) && !defined(BOOST_RE_NO_LIB)
         #define BOOST_RE_IX_DECL __declspec( dllimport ) 
      #endif
   #endif
   #include <boost/re_detail/regex_library_include.hpp>

#endif

#ifdef __GNUC__
   #if (__GNUC__ < 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ < 91))
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_MUTABLE
      #define BOOST_RE_NO_MEMBER_TEMPLATES
      #define BOOST_RE_NO_PARTIAL_FUNC_SPEC
      #define BOOST_RE_NO_TEMPLATE_FRIEND
   #endif
   #ifndef __STL_USE_NAMESPACES
      //#define BOOST_RE_NO_EXCEPTION_H
   #endif
   #define BOOST_RE_INT64t long long
   #define BOOST_RE_IMM64(val) val##LL

   #ifdef _WIN32
      /* there seems to be a problem with <windows.h> in gcc */
      #define BOOST_RE_LOCALE_C
      #define BOOST_RE_NO_W32
      #define BOOST_RE_NO_WCTYPE_H
      #define BOOST_RE_NO_TEMPLATE_SWITCH_MERGE
   #endif
   #define BOOST_RE_NO_CAT
   #define BOOST_RE_OLD_IOSTREAM
   #define BOOST_RE_NESTED_TEMPLATE_DECL
   #define BOOST_RE_NO_WCSTRING

#endif

#ifdef __SUNPRO_CC
   #if (__SUNPRO_CC < 0x500)
      #define BOOST_RE_NO_NAMESPACES
      #define BOOST_RE_NO_MUTABLE
      #define BOOST_RE_NO_MEMBER_TEMPLATES
      #define BOOST_RE_OLD_IOSTREAM
   #endif
   #ifndef __STL_USE_NAMESPACES
      #define BOOST_RE_NO_EXCEPTION_H
   #endif
   #define BOOST_RE_INT64t long long
   #define BOOST_RE_IMM64(val) val##LL
   #define BOOST_RE_NESTED_TEMPLATE_DECL
   #define BOOST_RE_NO_SWPRINTF
   #define BOOST_RE_NO_TEMPLATE_FRIEND
#endif

#ifdef __HP_aCC
   // putative HP aCC support, run configure for
   // support tailored to your system....
   #define BOOST_RE_NO_NAMESPACES
   #define BOOST_RE_NO_MUTABLE
   #define BOOST_RE_NO_MEMBER_TEMPLATES
   #define BOOST_RE_OLD_IOSTREAM
   #ifndef __STL_USE_NAMESPACES
      #define BOOST_RE_NO_EXCEPTION_H
   #endif
   #define BOOST_RE_INT64t long long
   #define BOOST_RE_IMM64(val) val##LL
   #define BOOST_RE_NESTED_TEMPLATE_DECL
   #define BOOST_RE_NO_TEMPLATE_FRIEND
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

#if !defined(BOOST_RE_INT64t) || !defined(BOOST_RE_IMM64)
#define BOOST_RE_NO_INT64
#endif

#ifndef BOOST_RE_INT32_LONG
typedef unsigned int jm_uintfast32_t;
#else
typedef unsigned long jm_uintfast32_t;
#endif

#ifndef BOOST_RE_NESTED_TEMPLATE_DECL
#define BOOST_RE_NESTED_TEMPLATE_DECL template
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
#ifdef BOOST_RE_NO_STL
   #define BOOST_RE_NO_EXCEPTION_H
   #define BOOST_RE_NO_ITERATOR_H
   #define BOOST_RE_NO_MEMORY_H
   #define BOOST_RE_NO_LOCALE_H
   #define BOOST_RE_NO_STRING_H
#endif

#ifndef BOOST_RE_NO_EXCEPTION_H
   #include <exception>
#endif

#ifndef BOOST_RE_NO_ITERATOR_H
   #include <iterator>

   #if defined(__SGI_STL_INTERNAL_ITERATOR_H) || defined(__SGI_STL_ITERATOR_H)

      /* we are using SGI's STL
       some of these (std)
       may be guesswork: */

      # if !defined (__SGI_STL_OWN_IOSTREAMS) || defined (__STL_HAS_NO_NEW_IOSTREAMS) || defined (__STL_USE_NO_IOSTREAMS)
         // Old IO streams:
         #define BOOST_RE_NO_LOCALE_H
         #define BOOST_RE_OLD_IOSTREAM
      #else
         #ifdef __STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS
            #define BOOST_RE_USE_FACET(l, m) (*std::_Use_facet<m >(l))
         #endif
      #endif
      #if !defined(__STL_MEMBER_TEMPLATE_CLASSES) ||  !defined(__STL_MEMBER_TEMPLATES)
         #define BOOST_RE_NO_MEMBER_TEMPLATES
      #endif
      #define BOOST_RE_NO_TYPEINFO

      #ifdef __STL_NO_BOOL
         #define BOOST_RE_NO_BOOL
      #endif
      #ifdef __STL_LIMITED_DEFAULT_TEMPLATES
         #define BOOST_RE_NO_TRICKY_DEFAULT_PARAM
         #define BOOST_RE_NO_STRING_DEF_ARGS  
      #endif
      #ifndef __STL_USE_EXCEPTIONS
         #error exception handling support required
      #endif

      #include <algorithm>
      #include <memory>

      #define BOOST_RE_ALGO_INCLUDED

      #define BOOST_RE_DISTANCE(i, j, n) do { n = 0; std::distance(i, j, n); } while(false)
      #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::output_iterator
      #define BOOST_RE_INPUT_ITERATOR(T, D) std::input_iterator<T, D>
      #define BOOST_RE_FWD_ITERATOR(T, D) std::forward_iterator<T, D>
      #define BOOST_RE_BIDI_ITERATOR(T, D) std::bidirectional_iterator<T, D>
      #define BOOST_RE_RA_ITERATOR(T, D) std::random_access_iterator<T, D>

      #if defined(__STL_USE_STD_ALLOCATORS) || (defined(__SGI_STL_PORT ) && !defined(__STL_MEMBER_TEMPLATE_CLASSES) && !defined(__STL_MEMBER_TEMPLATES))

         /* new style allocator's with nested template classes */
         #undef BOOST_RE_NO_MEMBER_TEMPLATES
         #define REBIND_INSTANCE(x, y, inst) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other(inst)
         #define REBIND_TYPE(x, y) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other
         #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( std::allocator<x> )
         #define BOOST_RE_DEF_ALLOC(x) std::allocator<x>

      #else  /* __STL_USE_STD_ALLOCATORS */
            #define BOOST_RE_OLD_ALLOCATORS
            #define REBIND_INSTANCE(x, y, inst) BOOST_RE_MAYBE_ACCESS_SPEC boost::re_detail::re_alloc_binder<x, y>(inst)
            #define REBIND_TYPE(x, y) BOOST_RE_MAYBE_ACCESS_SPEC re_alloc_binder<x, y>
            #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( jm_def_alloc )
            #define BOOST_RE_DEF_ALLOC(x) jm_def_alloc
            #define BOOST_RE_NEED_BINDER
            #define BOOST_RE_NEED_ALLOC
      #endif /* __STL_USE_STD_ALLOCATORS */

      #define BOOST_RE_STL_DONE
      #ifndef __SGI_STL_PORT
         //#define BOOST_RE_NO_NOT_EQUAL
      #endif

   #elif defined(__STD_ITERATOR__)

      /* Rogue Wave STL */

      #if defined(RWSTD_NO_MEMBER_TEMPLATES) || defined(RWSTD_NO_MEM_CLASS_TEMPLATES)
         #define BOOST_RE_NO_MEMBER_TEMPLATES
      #endif
      #ifdef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
         #define BOOST_RE_NO_TEMPLATE_RETURNS
      #endif

      #ifdef RWSTD_NO_EXCEPTIONS
         #error exception handling support required
      #endif

      #ifdef RWSTD_NO_MUTABLE
         #define BOOST_RE_NO_MUTABLE
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

      #if _RWSTD_VER > 0x020000
         #ifdef _RWSTD_NO_CLASS_PARTIAL_SPEC
          #define BOOST_RE_DISTANCE(i, j, n) do { n = 0; std::distance(i, j, n); } while(false)
         #else 
          #define BOOST_RE_DISTANCE(i, j, n) (n = std::distance(i, j))
         #endif
         #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::iterator<std::output_iterator_tag, T, D, T*, T&>
         #define BOOST_RE_INPUT_ITERATOR(T, D) std::iterator<std::input_iterator_tag, T, D, T*, T&>
         #define BOOST_RE_FWD_ITERATOR(T, D) std::iterator<std::forward_iterator_tag, T, D, T*, T&>
         #define BOOST_RE_BIDI_ITERATOR(T, D) std::iterator<std::bidirectional_iterator_tag, T, D, T*, T&>
         #define BOOST_RE_RA_ITERATOR(T, D) std::iterator<std::random_access_iterator_tag, T, D, T*, T&>
      #else 
         #define BOOST_RE_DISTANCE(i, j, n) std::distance(i, j, n)do { n = 0; std::distance(i, j, n); } while(false)
         #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::output_iterator
         #if _RWSTD_VER >= 0x0200
            #define BOOST_RE_INPUT_ITERATOR(T, D) std::input_iterator<T>
         #else
            #define BOOST_RE_INPUT_ITERATOR(T, D) std::input_iterator<T, D>
         #endif
         #define BOOST_RE_FWD_ITERATOR(T, D) std::forward_iterator<T, D>
         #define BOOST_RE_BIDI_ITERATOR(T, D) std::bidirectional_iterator<T, D>
         #define BOOST_RE_RA_ITERATOR(T, D) std::random_access_iterator<T, D>
      #endif

      #include <memory>

      #ifdef _RWSTD_ALLOCATOR

         /* new style allocator */

         #define REBIND_INSTANCE(x, y, inst) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other(inst)
         #define REBIND_TYPE(x, y) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other
         #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( std::allocator<x> )
         #define BOOST_RE_DEF_ALLOC(x)  std::allocator<x>

      #else
         /*
         // old style allocator
         // this varies a great deal between versions, and there is no way
         // that I can tell of differentiating between them, so use our
         // own default allocator...
         */
         #define BOOST_RE_OLD_ALLOCATORS
         #define REBIND_INSTANCE(x, y, inst) BOOST_RE_MAYBE_ACCESS_SPEC boost::re_detail::re_alloc_binder<x, y>(inst)
         #define REBIND_TYPE(x, y) BOOST_RE_MAYBE_ACCESS_SPEC re_alloc_binder<x, y>
         #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( jm_def_alloc )
         #define BOOST_RE_DEF_ALLOC(x) jm_def_alloc

         #define BOOST_RE_NEED_BINDER
         #define BOOST_RE_NEED_ALLOC

      #endif

      #define BOOST_RE_STL_DONE
      #if _RWSTD_VER < 0x020100
         #define BOOST_RE_NO_OI_ASSIGN
      #endif

   #elif defined (ITERATOR_H)

      /* HP STL */

      #define BOOST_RE_NO_LOCALE_H

      #include <algo.h>
      #define BOOST_RE_ALGO_INCLUDED

      #define BOOST_RE_DISTANCE(i, j, n) std::distance(i, j, n)do { n = 0; std::distance(i, j, n); } while(false)
      #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::output_iterator
      #define BOOST_RE_INPUT_ITERATOR(T, D) std::input_iterator<T, D>
      #define BOOST_RE_FWD_ITERATOR(T, D) std::forward_iterator<T, D>
      #define BOOST_RE_BIDI_ITERATOR(T, D) std::bidirectional_iterator<T, D>
      #define BOOST_RE_RA_ITERATOR(T, D) std::random_access_iterator<T, D>

      /* old style allocator */
      #define BOOST_RE_OLD_ALLOCATORS
      #define REBIND_INSTANCE(x, y, inst) BOOST_RE_MAYBE_ACCESS_SPEC boost::re_detail::re_alloc_binder<x, y>(inst)
      #define REBIND_TYPE(x, y) BOOST_RE_MAYBE_ACCESS_SPEC re_alloc_binder<x, y>
      #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( jm_def_alloc )
      #define BOOST_RE_DEF_ALLOC(x) jm_def_alloc

      #define BOOST_RE_NEED_BINDER
      #define BOOST_RE_NEED_ALLOC
      #define BOOST_RE_NO_NOT_EQUAL

      #define BOOST_RE_STL_DONE

   #elif defined (BOOST_MSVC)

      /* assume we're using MS's own STL (VC++ 5/6) */
      #define BOOST_RE_NO_OI_ASSIGN

      #define BOOST_RE_DISTANCE(i, j, n) n = std::distance(i, j)
      #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::iterator<std::output_iterator_tag, T, D>
      #define BOOST_RE_INPUT_ITERATOR(T, D) std::iterator<std::input_iterator_tag, T, D>
      #define BOOST_RE_FWD_ITERATOR(T, D) std::iterator<std::forward_iterator_tag, T, D>
      #define BOOST_RE_BIDI_ITERATOR(T, D) std::iterator<std::bidirectional_iterator_tag, T, D>
      #define BOOST_RE_RA_ITERATOR(T, D) std::iterator<std::random_access_iterator_tag, T, D>

      /* MS's allocators are rather ambiguous about their properties
      at least as far as MSDN is concerned, so play safe: */
      #define BOOST_RE_OLD_ALLOCATORS
      #define REBIND_INSTANCE(x, y, inst) BOOST_RE_MAYBE_ACCESS_SPEC boost::re_detail::re_alloc_binder<x, y>(inst)
      #define REBIND_TYPE(x, y) BOOST_RE_MAYBE_ACCESS_SPEC re_alloc_binder<x, y>
      #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( jm_def_alloc )
      #define BOOST_RE_DEF_ALLOC(x) jm_def_alloc

      #define BOOST_RE_NEED_BINDER
      #define BOOST_RE_NEED_ALLOC

      #define BOOST_RE_STL_DONE

      #define BOOST_RE_USE_FACET(l, type) std::use_facet(l, (type*)0, true)
      #define BOOST_RE_HAS_FACET(l, type) std::has_facet(l, (type*)0)



   #else

      /* unknown STL version
       try the defaults: */

      #define BOOST_RE_DISTANCE(i, j, n) std::distance(i, j, n)do { n = 0; std::distance(i, j, n); } while(false)
      /* these may be suspect for older libraries */
      #define BOOST_RE_OUTPUT_ITERATOR(T, D) std::iterator<std::output_iterator_tag, T, D, T*, T&>
      #define BOOST_RE_INPUT_ITERATOR(T, D) std::iterator<std::input_iterator_tag, T, D, T*, T&>
      #define BOOST_RE_FWD_ITERATOR(T, D) std::iterator<std::forward_iterator_tag, T, D, T*, T&>
      #define BOOST_RE_BIDI_ITERATOR(T, D) std::iterator<std::bidirectional_iterator_tag, T, D, T*, T&>
      #define BOOST_RE_RA_ITERATOR(T, D) std::iterator<std::random_access_iterator_tag, T, D, T*, T&>

   #endif  /* <iterator> config */

#else   /* no <iterator> at all */

   #define BOOST_RE_DISTANCE(i, j, n) (n = j - i)
   #define BOOST_RE_OUTPUT_ITERATOR(T, D) boost::re_detail::dummy_iterator_base<T>
   #define BOOST_RE_INPUT_ITERATOR(T, D) boost::re_detail::dummy_iterator_base<T>
   #define BOOST_RE_FWD_ITERATOR(T, D) boost::re_detail::dummy_iterator_base<T>
   #define BOOST_RE_BIDI_ITERATOR(T, D) boost::re_detail::dummy_iterator_base<T>
   #define BOOST_RE_RA_ITERATOR(T, D) boost::re_detail::dummy_iterator_base<T>


#endif

/* now do allocator if not already done */

#ifndef BOOST_RE_STL_DONE

   #ifdef BOOST_RE_NO_MEMORY_H

      /* old style allocator */
      
      #define BOOST_RE_OLD_ALLOCATORS

      #define REBIND_INSTANCE(x, y, inst) BOOST_RE_MAYBE_ACCESS_SPEC boost::re_detail::re_alloc_binder<x, y>(inst)
      #define REBIND_TYPE(x, y) BOOST_RE_MAYBE_ACCESS_SPEC re_alloc_binder<x, y>
      #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( jm_def_alloc )
      #define BOOST_RE_DEF_ALLOC(x) jm_def_alloc

      #define BOOST_RE_NEED_BINDER
      #define BOOST_RE_NEED_ALLOC

   #else

      /* new style allocator's with nested template classes */

      #define REBIND_INSTANCE(x, y, inst) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other(inst)
      #define REBIND_TYPE(x, y) y::BOOST_RE_NESTED_TEMPLATE_DECL rebind<x>::other
      #define BOOST_RE_DEF_ALLOC_PARAM(x) BOOST_RE_TRICKY_DEFAULT_PARAM( std::allocator<x> )
      #define BOOST_RE_DEF_ALLOC(x) std::allocator<x>

   #endif

#endif
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

#ifdef BOOST_RE_NO_MUTABLE
   #define BOOST_RE_MUTABLE
#else
   #define BOOST_RE_MUTABLE mutable
#endif

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



/* add our class def's if they are needed: */

namespace boost{
   namespace re_detail{

#ifdef __BORLANDC__
   #if __BORLANDC__ == 0x530
    #pragma option push -a4 -b
   #elif __BORLANDC__ > 0x530
    #pragma option push -a8 -b
   #endif
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
   typedef size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   re_alloc_binder(const Allocator& i);
   re_alloc_binder(const re_alloc_binder& o) : Allocator(o) {}

   T* BOOST_RE_CALL allocate(size_t n, size_t /* hint */ = 0)
      { return 0 == n ? 0 : (T*) this->Allocator::allocate(n * sizeof(T)); }
   void BOOST_RE_CALL deallocate(T *p, size_t n)
             { if (0 != n) this->Allocator::deallocate((char*)p, n * sizeof (T)); }

   pointer BOOST_RE_CALL address(reference x) const { return &x; }
   const_pointer BOOST_RE_CALL address(const_reference x) const { return &x; }
   static size_type BOOST_RE_CALL max_size() { return -1; }
   static void BOOST_RE_CALL construct(pointer p, const T& val) { jm_construct(p, val); }
   void BOOST_RE_CALL destroy(pointer p) { jm_destroy(p); }

   const Allocator& BOOST_RE_CALL instance()const { return *this; }

#ifndef BOOST_RE_NO_MEMBER_TEMPLATES

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
   typedef size_t    size_type;
   typedef std::ptrdiff_t difference_type;

   pointer BOOST_RE_CALL address(reference x) const { return &x; }
   const_pointer BOOST_RE_CALL address(const_reference x) const { return &x; }
   static size_type BOOST_RE_CALL max_size() { return (size_type)-1; }
   static void BOOST_RE_CALL construct(pointer , const char& ) {  }
   void BOOST_RE_CALL destroy(pointer ) {  }
   static void * BOOST_RE_CALL allocate(size_t n, size_t /* hint */ = 0)
   {
      return ::operator new(n);
   }
   static void BOOST_RE_CALL deallocate(void *p, size_t /*n*/ )
   {
      ::operator delete(p);
   }

#ifndef BOOST_RE_NO_MEMBER_TEMPLATES
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

#ifdef __BORLANDC__
 #if __BORLANDC__ > 0x520
  #pragma option pop
 #endif
#endif

} // namespace re_detail
#ifdef BOOST_RE_NEED_BINDER
using re_detail::re_alloc_binder;
#endif
#ifdef BOOST_RE_NEED_ALLOC
using re_detail::jm_def_alloc;
#endif
} // namespace boost

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
      #pragma message "macro jm_input_iterator: " BOOST_RE_INPUT_ITERATOR(char, std::ptrdiff_t)
      #pragma message "macro jm_output_iterator: " BOOST_RE_OUTPUT_ITERATOR(char, std::ptrdiff_t)
      #pragma message "macro jm_fwd_iterator: " BOOST_RE_FWD_ITERATOR(char, std::ptrdiff_t)
      #pragma message "macro jm_bidi_iterator: " BOOST_RE_BIDI_ITERATOR(char, std::ptrdiff_t)
      #pragma message "macro jm_ra_iterator: " BOOST_RE_RA_ITERATOR(char, std::ptrdiff_t)
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

#if defined(BOOST_NO_STDC_NAMESPACE) || (defined(__STL_NO_USING_FOR_GLOBAL_FUNCTIONS) && defined(__SGI_STL_PORT))
//
// fix namespaces:
namespace std{
   using ::ptrdiff_t;
   using ::size_t;
   using ::memcpy;
   using ::memmove;
   using ::memset;
   using ::sprintf;
   using ::strcat;
   using ::strcmp;
   using ::strcpy;
   using ::strlen;
   using ::swprintf;
   using ::wcslen;
   using ::wcscpy;
   using ::wcscmp;
   using ::isalpha;
   using ::iscntrl;
   using ::isdigit;
   using ::islower;
   using ::isupper;
   using ::ispunct;
   using ::isspace;
   using ::isxdigit;
   using ::tolower;
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
   using ::mbstate_t;
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





































