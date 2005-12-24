/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2006 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

// Test, if  function like macros are correctly expanded if used as object like 
// macros

#define CAT(a, b) a ## b
#define ARGS (1, 2)

//R #line 18 "t_1_012.cpp"
//R CAT (1, 2)
CAT ARGS

#define INVOKE(macro) macro ARGS

//R #line 24 "t_1_012.cpp"
//R CAT (1, 2)
INVOKE(CAT)

#define EXPAND(x) x

//R #line 30 "t_1_012.cpp"
//R 12
EXPAND(CAT ARGS)
