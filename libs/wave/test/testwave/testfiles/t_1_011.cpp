/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Test if macros at not used parameter positions are expanded correctly

#define MACRO() /**/
#define ID(x)           // parameter not used at all
#define CAT(x) X ## x   // expanded parameter not used

ID( MACRO(*) )
//R #line 19 "t_1_011.cpp"
//R XMACRO( * )
CAT( MACRO(*) )
