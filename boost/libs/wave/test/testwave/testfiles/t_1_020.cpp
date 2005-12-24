/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Tests the handling of placeholder tokens, which have to be inserted, when
// some macro expands into nothing (certainly these have to be ignored 
// afterwards :-)

#define NIL

#define A B NIL
#define B() anything

//R #line 21 "t_1_020.cpp"
//R B() 
A()   // not 'anything'!

