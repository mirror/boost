// Copyright 2005 Alexander Nasonov.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <climits>

#if !defined(BOOST_NO_CWCHAR)
#include <cwchar>
#endif

#include "promote_util.hpp"

struct Struct {};

int main()
{
    // char types

#if CHAR_MAX <= INT_MAX
    test_cv< char, int >();
#else
    // TODO: dead branch?
    test_cv< char, unsigned int >();
#endif

    test_cv< signed char, int >();

#if UCHAR_MAX <= INT_MAX
    test_cv< unsigned char, int >();
#else
    test_cv< unsigned char, unsigned int >();
#endif


    // short types

    test_cv< short int, int >();

#if USHRT_MAX <= INT_MAX
    test_cv< unsigned short, int >();
#else
    test_cv< unsigned short, unsigned int >();
#endif


    // int and long

    test_cv< int,           int           >();
    test_cv< unsigned int,  unsigned int  >();
    test_cv< long,          long          >();
    test_cv< unsigned long, unsigned long >();

    // wchar_t

#if !defined(BOOST_NO_CWCHAR) && defined(WCHAR_MAX) && defined(WCHAR_MIN)

// Version prior to VC8 didn't allow WCHAR_MAX in #if expressions
#if defined(BOOST_MSVC) && BOOST_MSVC < 1400
#define BOOST_TT_AUX_WCHAR_MAX 0 // force test_cv< wchar_t, int >
#else
#define BOOST_TT_AUX_WCHAR_MAX WCHAR_MAX
#endif

#if BOOST_TT_AUX_WCHAR_MAX <= INT_MAX
    test_cv< wchar_t, int >();
#elif WCHAR_MIN == 0 && BOOST_TT_AUX_WCHAR_MAX <= UINT_MAX
    test_cv< wchar_t, unsigned int >();
#elif BOOST_TT_AUX_WCHAR_MAX <= LONG_MAX
    test_cv< wchar_t, long >();
#else
    test_cv< wchar_t, unsigned long >();
#endif

#undef BOOST_TT_AUX_WCHAR_MAX

#endif


    // floating point promotion

    test_cv< float , double >();
    test_cv< double, double >();


    // Other types

    test_cv< Struct, Struct >();
    test_cv< void  , void   >();
    test_cv< void* , void*  >();

    // Array types

    typedef int arr[3];
    typedef int (&arr_ref)[3];
    typedef int (*arr_ptr)[3];

    test_cv< arr    , arr     >();
    test_cv< arr_ptr, arr_ptr >();

    test_no_cv<arr_ref,arr_ref>();


    // Function types

    typedef int (fun)();
    typedef int (&fun_ref)();
    typedef int (*fun_ptr)();

    test_no_cv< fun    , fun     >();
    test_no_cv< fun_ref, fun_ref >();
    test_no_cv< fun_ptr, fun_ptr >();

    // Member pointer types

    typedef int (Struct::*mem_fun_ptr)();
    typedef int Struct::*mem_ptr;

    test_no_cv< mem_ptr,     mem_ptr     >();
    test_no_cv< mem_fun_ptr, mem_fun_ptr >();

    return 0;
}

